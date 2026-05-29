// Copyright (c) 2025 Hung Pham. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilites/PL_GameplayAbility.h"
#include "PL_PlayerGameplayAbility.generated.h"

class APL_PlayerCharacter;
class APL_PlayerController;
class UPL_PlayerCombatComponent;
/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPL_PlayerGameplayAbility : public UPL_GameplayAbility
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	APL_PlayerCharacter* GetPlayerCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	APL_PlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	UPL_PlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, 
																FGameplayTag InCurrentAttackTypeTag, int32 InUserComboCount);
	UFUNCTION(BlueprintCallable, Category = "Player|Ability")
	bool GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime);
	
	UFUNCTION(BlueprintCallable, Category = "Player|Ability")
	void ApplyGameplayEffectSpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle,const TArray<FHitResult>& InHitResults);
private:
	TWeakObjectPtr<APL_PlayerCharacter> CachedPL_PlayerCharacter;
	TWeakObjectPtr<APL_PlayerController> CachedPL_PlayerController;

};
