// Copyright (c) 2025 Hung Pham. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Item/Weapons/PL_WeaponBase.h"
#include "PrimordialLifeType/PL_StructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "PL_PlayerWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API APL_PlayerWeaponBase : public APL_WeaponBase
{
	GENERATED_BODY()
	


private:
	
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
	

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	F_PLPlayerWeaponData PLayerWeaponData;


	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
};
