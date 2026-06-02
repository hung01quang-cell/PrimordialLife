// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PL_SurvialGameMode.h"

void APL_SurvialGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void APL_SurvialGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APL_SurvialGameMode::SetCurrentSurvialGameModeState(EPlayerSurvialGameModeState InState)
{
	CurrentSurvialGameModeState = InState;
	OnSurvialGameModeStateChanged.Broadcast(CurrentSurvialGameModeState);
}
