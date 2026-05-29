// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComponentBase/PawnExtensionActorComponent.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangDelegate, float, newHealth);
/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPawnUIComponent : public UPawnExtensionActorComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangDelegate OnCurrentHealthChanged;
};
