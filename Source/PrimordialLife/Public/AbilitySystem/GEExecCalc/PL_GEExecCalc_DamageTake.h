// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "PL_GEExecCalc_DamageTake.generated.h"

/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPL_GEExecCalc_DamageTake : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UPL_GEExecCalc_DamageTake();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
										FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
