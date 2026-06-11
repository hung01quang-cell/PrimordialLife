// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AbilitySystem/Abilites/Enemy/PL_EnemyGameplayAbility.h"
#include "CharacterBasics/PL_EnemyCharacter.h"
#include "AbilitySystem/Components/PL_AbilitySystemComponent.h"
#include "PL_GameplayTags.h"

APL_EnemyCharacter* UPL_EnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedPLEnemyCharacter.IsValid())
	{
		CachedPLEnemyCharacter = Cast< APL_EnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedPLEnemyCharacter.IsValid() ? CachedPLEnemyCharacter.Get() : nullptr;
}

UPL_EnemyCombatComponent* UPL_EnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetPLEnemyCombatComponent();
}

FGameplayEffectSpecHandle UPL_EnemyGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetPLAbilitySystemComponentFromActorInfor()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle SpecHandle = GetPLAbilitySystemComponentFromActorInfor()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	SpecHandle.Data->SetSetByCallerMagnitude(
		PrimordialLifeGameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);
	return SpecHandle;
}
