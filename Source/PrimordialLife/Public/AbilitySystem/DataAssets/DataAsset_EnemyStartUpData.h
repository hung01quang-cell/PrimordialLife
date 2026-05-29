// Copyright (c) 2025 Hung Pham. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/DataAssets/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"
class UPL_EnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	
public: 
	virtual void GiveToAbilitySystemComponent(UPL_AbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<TSubclassOf<UPL_EnemyGameplayAbility>> EnemyStartUpabilitySets;
};
