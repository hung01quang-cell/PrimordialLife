// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AbilitySystem/DataAssets/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/Components/PL_AbilitySystemComponent.h"
#include "AbilitySystem/Abilites/PL_GameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UPL_AbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

	if (StartUpGameplayEffect.IsEmpty()) return;
	for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffect)
	{
		if (!EffectClass) continue;
		UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject< UGameplayEffect>();
		InASCToGive->ApplyGameplayEffectToSelf(
			EffectCDO,
			ApplyLevel,
			InASCToGive->MakeEffectContext()
		);
	}
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UPL_GameplayAbility>>& InAbilitiesToGive, 
												UPL_AbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;

	for (const TSubclassOf<UPL_GameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive;
		AbilitySpec.Level = ApplyLevel;
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
