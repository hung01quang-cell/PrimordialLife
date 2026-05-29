// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "PrimordialLifeType/PL_StructTypes.h"
#include "AbilitySystem/Abilites/Player/PL_PlayerGameplayAbility.h"

bool F_PLPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}