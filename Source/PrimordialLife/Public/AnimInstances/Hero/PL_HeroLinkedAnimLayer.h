// Copyright (c) 2025 Hung Pham. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/PL_BaseAnimInstance.h"
#include "PL_HeroLinkedAnimLayer.generated.h"


class UPL_PlayerCharacterAnimInstance;
/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPL_HeroLinkedAnimLayer : public UPL_BaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (NotBlueprintThreadSafe))
	UPL_PlayerCharacterAnimInstance* GetPLPlayerAnimInstance()const;
};
