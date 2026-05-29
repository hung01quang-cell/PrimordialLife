// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnCombatInterface.generated.h"

class UPL_CombatComponentBase;

UINTERFACE(MinimalAPI)
class UPawnCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PRIMORDIALLIFE_API IPawnCombatInterface
{
	GENERATED_BODY()

public:
	
	virtual UPL_CombatComponentBase* GetPLCombatComponentBase() const = 0;
};
