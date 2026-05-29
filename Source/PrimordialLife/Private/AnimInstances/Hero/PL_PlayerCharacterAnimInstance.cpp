// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AnimInstances/Hero/PL_PlayerCharacterAnimInstance.h"
#include "CharacterBasics/PL_PlayerCharacter.h"

void UPL_PlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (OwningCharacter)
	{
		OwningPlayerCharacter = Cast<APL_PlayerCharacter>(OwningCharacter);
	}
}

void UPL_PlayerCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (bHasAcceleration)
	{
		bShouldRelax = false;
		IdleElpaseTime = 0;
	}
	else
	{
		IdleElpaseTime += DeltaSeconds;
		bShouldRelax = (IdleElpaseTime >= EnterRelaxStateThreshold);
	}
}
