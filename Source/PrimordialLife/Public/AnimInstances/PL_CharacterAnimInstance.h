// Copyright (c) 2025 Hung Pham. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/PL_BaseAnimInstance.h"
#include "PL_CharacterAnimInstance.generated.h"

class APL_CharacterBasic;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPL_CharacterAnimInstance : public UPL_BaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	APL_CharacterBasic* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float LocomotionDirection;
};
