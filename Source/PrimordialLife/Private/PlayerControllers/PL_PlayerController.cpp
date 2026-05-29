// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/PL_PlayerController.h"

APL_PlayerController::APL_PlayerController()
{
	PlayerTeamID = FGenericTeamId(0);
}

FGenericTeamId APL_PlayerController::GetGenericTeamId() const
{
	return PlayerTeamID;
}
