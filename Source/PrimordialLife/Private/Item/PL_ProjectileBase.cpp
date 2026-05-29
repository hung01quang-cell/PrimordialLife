// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PL_ProjectileBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PL_FunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PL_GameplayTags.h"


#include "PL_DebugHelper.h"

APL_ProjectileBase::APL_ProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	ProjectileCollissionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollissionBox"));
	SetRootComponent(ProjectileCollissionBox);
	ProjectileCollissionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollissionBox->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Block);
	ProjectileCollissionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	ProjectileCollissionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Block);
	ProjectileCollissionBox->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectileHit);
	ProjectileCollissionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnProjectileBeginOverlap);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->InitialSpeed = 700.f;
	ProjectileMovementComp->MaxSpeed = 900.f;
	ProjectileMovementComp->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovementComp->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 4.f;
}

void APL_ProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	{
		ProjectileCollissionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

void APL_ProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);
	APawn* HitPawn = Cast<APawn>(OtherActor);
	if (!HitPawn || !UPL_FunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Destroy();
		return;
	}
	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UPL_FunctionLibrary::NativeDoesActorHaveTag(HitPawn, PrimordialLifeGameplayTags::Player_Status_Blocking);

	if (bIsPlayerBlocking)
	{
		bIsValidBlock = UPL_FunctionLibrary::IsValidBlock(this, OtherActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.Target = HitPawn;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitPawn,
			PrimordialLifeGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		HandleApplyProjectileDamage(HitPawn, EventData);
	}
	Destroy();
}

void APL_ProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedActors.Contains(OtherActor))
	{
		return;
	}
	OverlappedActors.AddUnique(OtherActor);
	if (APawn* HitPaw = Cast<APawn>(OtherActor))
	{
		FGameplayEventData Data;
		Data.Instigator = GetInstigator();
		Data.Target = HitPaw;
		if (UPL_FunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPaw))
		{
			HandleApplyProjectileDamage(HitPaw, Data);
		}
	}
}

void APL_ProjectileBase::HandleApplyProjectileDamage(APawn* InHitPawn,const FGameplayEventData& InPayload)
{
	checkf(ProjectileDamageEffectSpecHandle.IsValid(), TEXT("Forgot to assign a valid spec handle to the projectile: %s"), *GetActorNameOrLabel());

	const bool bWasApplied = UPL_FunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, ProjectileDamageEffectSpecHandle);

	if (bWasApplied)
	{
		Debug::Print(InHitPawn->GetActorNameOrLabel());
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			InHitPawn,
			PrimordialLifeGameplayTags::Shared_Event_HitReact,
			InPayload
		);
	}
}

