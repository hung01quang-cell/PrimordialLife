// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PL_GameModeBase.h"
#include "PL_SurvialGameMode.generated.h"


UENUM(BlueprintType)
enum class EPlayerSurvialGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesDone,
	PlayerDied
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvialGameModeStateChangedDelegate,EPlayerSurvialGameModeState,CurrentState);

/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API APL_SurvialGameMode : public APL_GameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	
private:
	void SetCurrentSurvialGameModeState(EPlayerSurvialGameModeState InState);
	
	UPROPERTY()
	EPlayerSurvialGameModeState CurrentSurvialGameModeState;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnSurvialGameModeStateChangedDelegate OnSurvialGameModeStateChanged;
};
