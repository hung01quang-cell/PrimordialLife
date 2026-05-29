// Copyright (c) 2025 Hung Pham. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/PL_CharacterAnimInstance.h"
#include "PL_PlayerCharacterAnimInstance.generated.h"

class APL_PlayerCharacter;

UCLASS()
class PRIMORDIALLIFE_API UPL_PlayerCharacterAnimInstance : public UPL_CharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	APL_PlayerCharacter* OwningPlayerCharacter = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldRelax = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 6.f;

	float IdleElpaseTime = 0;

};
