// Copyright (c) 2025 Hung Pham. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilites/PL_GameplayAbility.h"
#include "PL_EnemyGameplayAbility.generated.h"

class UPL_EnemyCombatComponent;
class APL_EnemyCharacter;

/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPL_EnemyGameplayAbility : public UPL_GameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	APL_EnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	UPL_EnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,const FScalableFloat& InDamageScalableFloat);

private:
	TWeakObjectPtr<APL_EnemyCharacter> CachedPLEnemyCharacter;

};
