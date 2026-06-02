// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AbilitySystem/Abilites/Player/PL_PlayerGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "PL_FunctionLibrary.h"
#include "CharacterBasics/PL_PlayerCharacter.h"
#include "PlayerControllers/PL_PlayerController.h"
#include "AbilitySystem/Components/PL_AbilitySystemComponent.h"
#include "PL_GameplayTags.h"

APL_PlayerCharacter* UPL_PlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPL_PlayerCharacter.IsValid())
	{
		CachedPL_PlayerCharacter = Cast<APL_PlayerCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPL_PlayerCharacter.IsValid() ? CachedPL_PlayerCharacter.Get() : nullptr;
}

APL_PlayerController* UPL_PlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPL_PlayerController.IsValid())
	{
		CachedPL_PlayerController = Cast<APL_PlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedPL_PlayerController.IsValid() ? CachedPL_PlayerController.Get() : nullptr;
}

UPL_PlayerCombatComponent* UPL_PlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}

UPlayerUIComponent* UPL_PlayerGameplayAbility::GetPlayerUIComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerUIComponent();
}


FGameplayEffectSpecHandle UPL_PlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, 
                                                                                      FGameplayTag InCurrentAttackTypeTag, int32 InUserComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetPLAbilitySystemComponentFromActorInfor()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetPLAbilitySystemComponentFromActorInfor()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		PrimordialLifeGameplayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage
	);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUserComboCount);
	}

	return EffectSpecHandle;
}

bool UPL_PlayerGameplayAbility::GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime)
{
	check(InCooldownTag.IsValid());

	FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());

	TArray< TPair <float, float> > TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);

	if (TimeRemainingAndDuration.IsEmpty())
	{
		return false;
	}
	RemainingCooldownTime = TimeRemainingAndDuration[0].Key;
	TotalCooldownTime = TimeRemainingAndDuration[0].Value;
	return RemainingCooldownTime > 0.f;
}

void UPL_PlayerGameplayAbility::ApplyGameplayEffectSpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle,
	const TArray<FHitResult>& InHitResults)
{
	if (InHitResults.IsEmpty())
	{
		return;
	}

	APawn* OwningPawn = CastChecked<APawn>(GetAvatarActorFromActorInfo());

	for (const FHitResult& Hit : InHitResults)
	{
		if (APawn* HitPawn = Cast<APawn>(Hit.GetActor()))
		{
			if (UPL_FunctionLibrary::IsTargetPawnHostile(OwningPawn, HitPawn))
			{
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(HitPawn,InSpecHandle);

				if (ActiveGameplayEffectHandle.WasSuccessfullyApplied())
				{	
					FGameplayEventData Data;
					Data.Instigator = OwningPawn;
					Data.Target = HitPawn;
					    
					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
						HitPawn,
						PrimordialLifeGameplayTags::Shared_Event_HitReact,
						Data
					);
				}
			}
		}
	}
}
