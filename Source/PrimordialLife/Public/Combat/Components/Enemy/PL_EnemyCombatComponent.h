// Copyright (c) 2025 Hung Pham. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Combat/Components/PL_CombatComponentBase.h"
#include "PL_EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPL_EnemyCombatComponent : public UPL_CombatComponentBase
{
	GENERATED_BODY()
	
public:

	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType) override;

	virtual void OnHitTargetActor(AActor* HitActor) override;
};
