// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PrimordialLifeType/PL_EnumType.h"
#include "PL_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPL_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	E_PrimordialLifeGameDifficulty SavedCurrentGameDifficulty;
};
