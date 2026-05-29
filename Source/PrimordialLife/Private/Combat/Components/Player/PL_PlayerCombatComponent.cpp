// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "Combat/Components/Player/PL_PlayerCombatComponent.h"
#include "Item/Weapons/PL_PlayerWeaponBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PL_GameplayTags.h"

#include "PL_DebugHelper.h"

APL_PlayerWeaponBase* UPL_PlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<APL_PlayerWeaponBase>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

APL_PlayerWeaponBase* UPL_PlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
    return Cast< APL_PlayerWeaponBase>(GetCharacterCurrentEquippedWeapon());
}

float UPL_PlayerCombatComponent::GetPlayerCurrentEquippWeaponDamageAtLevel(float InLevel) const
{
    return GetPlayerCurrentEquippedWeapon()->PLayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UPL_PlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if (OverlappedActors.Contains(HitActor)) return;

    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;


    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        PrimordialLifeGameplayTags::Shared_Event_MeleeHit,
        Data
    );

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        PrimordialLifeGameplayTags::Player_Event_HitPause,
        FGameplayEventData()
    );
}

void UPL_PlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        PrimordialLifeGameplayTags::Player_Event_HitPause,
        FGameplayEventData()
    );
}
