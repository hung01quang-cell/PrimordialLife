// Copyright (c) 2025 Hung Pham. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Combat/Components/PL_CombatComponentBase.h"
#include "PL_PlayerCombatComponent.generated.h"


class APL_PlayerWeaponBase;
/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPL_PlayerCombatComponent : public UPL_CombatComponentBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	APL_PlayerWeaponBase* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	APL_PlayerWeaponBase* GetPlayerCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	float GetPlayerCurrentEquippWeaponDamageAtLevel(float InLevel) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
