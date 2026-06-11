// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "CharacterBasics/PL_EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Combat/Components/Enemy/PL_EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "AbilitySystem/DataAssets/DataAsset_EnemyStartUpData.h"
#include "UI/EnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/PlayerWidgetBase.h"
#include "Components/BoxComponent.h"
#include "PL_FunctionLibrary.h"
#include "GameModes/PL_GameModeBase.h"

#include "PL_DebugHelper.h"

APL_EnemyCharacter::APL_EnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	EnemyCombatComponent = CreateDefaultSubobject<UPL_EnemyCombatComponent>(TEXT("EnemyCombatComponent"));
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));
	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());

	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftHandCollisionBox");
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightHandCollisionBox");
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
}

void APL_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (UPlayerWidgetBase* HealthWidget = Cast<UPlayerWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreateWidget(this);
	}
}

void APL_EnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartUpData();

}

UPL_CombatComponentBase* APL_EnemyCharacter::GetPLCombatComponentBase() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* APL_EnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* APL_EnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void APL_EnemyCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Debug::Print(OtherActor->GetActorNameOrLabel());
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UPL_FunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			EnemyCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

#if WITH_EDITOR
void APL_EnemyCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxAttachBoneName);
	}
}
#endif

void APL_EnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull()) return;

	int32 AbilityApplyLevel = 1;

	if (APL_GameModeBase* BaseGameMode = GetWorld()->GetAuthGameMode<APL_GameModeBase>())
	{
		switch (BaseGameMode->GetCurrentGameDifficulty())
		{
		case E_PrimordialLifeGameDifficulty::Easy:
			AbilityApplyLevel = 1;
			break;

		case E_PrimordialLifeGameDifficulty::Normal:
			AbilityApplyLevel = 2;
			break;

		case E_PrimordialLifeGameDifficulty::Hard:
			AbilityApplyLevel = 3;
			break;

		case E_PrimordialLifeGameDifficulty::VeryHard:
			AbilityApplyLevel = 4;
			break;

		default:
			break;
		}
	}
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this, AbilityApplyLevel]()
			{
				if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(PL_AbilitySystemComponent, AbilityApplyLevel);
				}
			}
		)
	);
}
