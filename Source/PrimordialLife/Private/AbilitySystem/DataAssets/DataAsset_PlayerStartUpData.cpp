// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AbilitySystem/DataAssets/DataAsset_PlayerStartUpData.h"
#include "AbilitySystem/Components/PL_AbilitySystemComponent.h"
#include "AbilitySystem/Abilites/PL_GameplayAbility.h"



void UDataAsset_PlayerStartUpData::GiveToAbilitySystemComponent(UPL_AbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const F_PLPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
