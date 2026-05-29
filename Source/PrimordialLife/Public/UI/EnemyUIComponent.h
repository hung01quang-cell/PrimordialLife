// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"


class UPlayerWidgetBase;

/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawWidget(UPlayerWidgetBase* InWidgetRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawWidgetsIfAny();

private:

	TArray<UPlayerWidgetBase*> EnemyDrawWidgets;
};
