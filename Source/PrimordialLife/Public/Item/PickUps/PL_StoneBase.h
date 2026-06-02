// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PL_PickUpBase.h"
#include "PL_StoneBase.generated.h"

class UGameplayEffect;
class UPL_AbilitySystemComponent;

UCLASS()
class PRIMORDIALLIFE_API APL_StoneBase : public APL_PickUpBase
{
	GENERATED_BODY()

public:
	void Consume(UPL_AbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Stone Consumed"))
	void BP_OnStoneCosumed();
protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditDefaultsOnly, Category = "Stone")
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};