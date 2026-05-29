// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "Combat/Components/Enemy/PL_EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PL_GameplayTags.h"
#include "PL_FunctionLibrary.h"
#include "CharacterBasics/PL_EnemyCharacter.h"
#include "Components/BoxComponent.h"

#include "PL_DebugHelper.h"


void UPL_EnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

	//TODO:: Implement block check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UPL_FunctionLibrary::NativeDoesActorHaveTag(HitActor, PrimordialLifeGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = UPL_FunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), PrimordialLifeGameplayTags::Enemy_Status_Unblockable);

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UPL_FunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			PrimordialLifeGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			PrimordialLifeGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}

void UPL_EnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	APL_EnemyCharacter* OwningEnemyChar = GetOwningPawn<APL_EnemyCharacter>();
	
	check(OwningEnemyChar);

	UBoxComponent* LeftHandColisionBox = OwningEnemyChar->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyChar->GetRightHandCollisionBox();

	check(LeftHandColisionBox && RightHandCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandColisionBox->SetCollisionEnabled(bShouldEnable? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}
	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}