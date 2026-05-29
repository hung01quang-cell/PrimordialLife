// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PL_PickUpBase.h"
#include "PL_StoneBase.generated.h"

UCLASS()
class PRIMORDIALLIFE_API APL_StoneBase : public APL_PickUpBase
{
	GENERATED_BODY()

	
protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};