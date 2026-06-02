// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilites/Player/PL_PlayerGameplayAbility_PickUpStone.h"

#include "Item/PickUps/PL_StoneBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CharacterBasics/PL_PlayerCharacter.h"
#include "UI/PlayerUIComponent.h"

void UPL_PlayerGameplayAbility_PickUpStone::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                            const FGameplayEventData* TriggerEventData)
{
	GetPlayerUIComponentFromActorInfo()->OnStoneInteracted.Broadcast(true);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPL_PlayerGameplayAbility_PickUpStone::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	GetPlayerUIComponentFromActorInfo()->OnStoneInteracted.Broadcast(false);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPL_PlayerGameplayAbility_PickUpStone::CollectStones()
{
	CollectedStones.Empty();

	TArray<FHitResult> TraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() + -GetPlayerCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		(-GetPlayerCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		StoneTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for (const FHitResult& TraceHit : TraceHits)
	{
		if (APL_StoneBase* FoundStone = Cast<APL_StoneBase>(TraceHit.GetActor()))
		{
			CollectedStones.AddUnique(FoundStone);
		}
	}

	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void UPL_PlayerGameplayAbility_PickUpStone::ConsumeStones()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}
	for (APL_StoneBase* Stone : CollectedStones)
	{
		Stone->Consume(GetPLAbilitySystemComponentFromActorInfor(), GetAbilityLevel());
	}
	
}
