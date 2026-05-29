// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AbilitySystem/Components/PL_AbilitySystemComponent.h"
#include "AbilitySystem/Abilites/Player/PL_PlayerGameplayAbility.h"
#include "PL_GameplayTags.h"

void UPL_AbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;
	for (const FGameplayAbilitySpec AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;
		if (AbilitySpec.IsActive() && InInputTag.MatchesTag(PrimordialLifeGameplayTags::InputTag_Toggleable))
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
		else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UPL_AbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(PrimordialLifeGameplayTags::InputTag_MustBeHeld)) return;
	for (const FGameplayAbilitySpec AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
}

void UPL_AbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<F_PLPlayerAbilitySet>& InDefaultWeaponAbilities, const TArray<F_PLSpecialAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if(InDefaultWeaponAbilities.IsEmpty()) return;

	for (const F_PLPlayerAbilitySet PlayerAbilitySet : InDefaultWeaponAbilities)
	{
		if (!PlayerAbilitySet.IsValid())continue;
		FGameplayAbilitySpec AbilitySpce(PlayerAbilitySet.AbilityToGrant);
		AbilitySpce.SourceObject = GetAvatarActor();
		AbilitySpce.Level = ApplyLevel;
		AbilitySpce.DynamicAbilityTags.AddTag(PlayerAbilitySet.InputTag);
		OutGrantedAbilitySpecHandles.Add(GiveAbility(AbilitySpce));
	}
	for (const F_PLSpecialAbilitySet PlayerAbilitySet : InSpecialWeaponAbilities)
	{
		if (!PlayerAbilitySet.IsValid())continue;
		FGameplayAbilitySpec AbilitySpce(PlayerAbilitySet.AbilityToGrant);
		AbilitySpce.SourceObject = GetAvatarActor();
		AbilitySpce.Level = ApplyLevel;
		AbilitySpce.DynamicAbilityTags.AddTag(PlayerAbilitySet.InputTag);
		OutGrantedAbilitySpecHandles.Add(GiveAbility(AbilitySpce));
	}

}

void UPL_AbilitySystemComponent::RemovedGrantedHeroWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty()) return;
	for (const FGameplayAbilitySpecHandle SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}
	InSpecHandlesToRemove.Empty();
}

bool UPL_AbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());

	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;

	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check(SpecToActivate);
		if (!SpecToActivate->IsActive())
		{
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}
	return false;
}

