// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AnimInstances/PL_BaseAnimInstance.h"
#include "PL_FunctionLibrary.h"

bool UPL_BaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UPL_FunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
