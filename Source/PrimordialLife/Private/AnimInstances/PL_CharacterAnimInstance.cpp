// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AnimInstances/PL_CharacterAnimInstance.h"
#include "CharacterBasics/PL_CharacterBasic.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

#include "PL_DebugHelper.h"

void UPL_CharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<APL_CharacterBasic>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UPL_CharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent) return;

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared() > 0.f;
	
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}
