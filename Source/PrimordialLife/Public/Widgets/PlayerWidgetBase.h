// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidgetBase.generated.h"


class UPlayerUIComponent;
class UEnemyUIComponent;
/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPlayerWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Player UI Component Inittialized"))
	void BP_OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* OwningPlayerUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Enemy UI Component Inittialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);

public:

	UFUNCTION(BlueprintCallable)
	void InitEnemyCreateWidget(AActor* OwnerEnemyActor);
	
};
