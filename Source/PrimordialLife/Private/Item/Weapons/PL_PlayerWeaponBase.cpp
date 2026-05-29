// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "Item/Weapons/PL_PlayerWeaponBase.h"

void APL_PlayerWeaponBase::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> APL_PlayerWeaponBase::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
