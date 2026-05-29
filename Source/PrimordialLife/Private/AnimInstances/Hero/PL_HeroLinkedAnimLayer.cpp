// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AnimInstances/Hero/PL_HeroLinkedAnimLayer.h"
#include "AnimInstances/Hero/PL_PlayerCharacterAnimInstance.h"


UPL_PlayerCharacterAnimInstance* UPL_HeroLinkedAnimLayer::GetPLPlayerAnimInstance() const
{
    return Cast<UPL_PlayerCharacterAnimInstance>(GetOwningComponent()->GetAnimInstance());
}

