// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AbilitySystem/DataAssets/DataAsset_EnemyStartUpData.h"
#include "AbilitySystem/Components/PL_AbilitySystemComponent.h"
#include "AbilitySystem/Abilites/Enemy/PL_EnemyGameplayAbility.h"


void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UPL_AbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	for (const TSubclassOf<UPL_EnemyGameplayAbility>& AbilityClass : EnemyStartUpabilitySets)
	{
		if (!AbilityClass) continue;
		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
