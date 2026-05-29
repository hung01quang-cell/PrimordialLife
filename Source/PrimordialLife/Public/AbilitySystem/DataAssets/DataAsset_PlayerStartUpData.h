// Copyright (c) 2025 Hung Pham. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/DataAssets/DataAsset_StartUpDataBase.h"
#include "PrimordialLifeType/PL_StructTypes.h"
#include "DataAsset_PlayerStartUpData.generated.h"



/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UDataAsset_PlayerStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()


public:

	virtual void GiveToAbilitySystemComponent(UPL_AbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<F_PLPlayerAbilitySet> PlayerStartUpAbilitySets;
	
};
