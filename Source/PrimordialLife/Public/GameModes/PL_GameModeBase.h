// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PrimordialLifeType/PL_EnumType.h"
#include "PL_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API APL_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APL_GameModeBase();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settings")
	E_PrimordialLifeGameDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE E_PrimordialLifeGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty;}
};
