// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AbilitySystem/Abilites/PL_GameplayAbility.h"
#include "AbilitySystem/Components/PL_AbilitySystemComponent.h"
#include "Combat/Components/PL_CombatComponentBase.h"
#include "AbilitySystemBlueprintLibrary.h"


void UPL_GameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (AbilityActivationPolicy == E_PLAbilityActivetionPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UPL_GameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (AbilityActivationPolicy == E_PLAbilityActivetionPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPL_CombatComponentBase* UPL_GameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPL_CombatComponentBase>();	
}

UPL_AbilitySystemComponent* UPL_GameplayAbility::GetPLAbilitySystemComponentFromActorInfor()
{
	return Cast<UPL_AbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);

}

FActiveGameplayEffectHandle UPL_GameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetASC && InSpecHandle.IsValid());

	return GetPLAbilitySystemComponentFromActorInfor()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		TargetASC
	);
}

FActiveGameplayEffectHandle UPL_GameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, E_PrimordialLifeSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? E_PrimordialLifeSuccessType::Successful : E_PrimordialLifeSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}