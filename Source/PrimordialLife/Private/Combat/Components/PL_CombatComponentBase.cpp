// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "Combat/Components/PL_CombatComponentBase.h"
#include "Item/Weapons/PL_PlayerWeaponBase.h"
#include "Components/BoxComponent.h"



#include "PL_DebugHelper.h"

void UPL_CombatComponentBase::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, APL_WeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named named %s has already been added as carried weapon"),
		*InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPullFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
	/*const FString WeaponString = FString::Printf(TEXT("A weapon named: %s has been registered using the tag %s"), *InWeaponToRegister->GetName(), 
		*InWeaponTagToRegister.ToString());
	Debug::Print(WeaponString);*/
}

APL_WeaponBase* UPL_CombatComponentBase::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (!CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))return nullptr;
	APL_WeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet);
	if (!*FoundWeapon) return nullptr;
	return *FoundWeapon;

}

APL_WeaponBase* UPL_CombatComponentBase::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) return nullptr;
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPL_CombatComponentBase::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		ToggleCurrentEquippedWeapontCollision(bShouldEnable);
	}
	else
	{
		ToggleBodyCollisionBoxCollision(bShouldEnable, ToggleDamageType);
	}
}

void UPL_CombatComponentBase::OnHitTargetActor(AActor* HitActor)
{
}

void UPL_CombatComponentBase::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}

void UPL_CombatComponentBase::ToggleCurrentEquippedWeapontCollision(bool bShouldEnable)
{
	APL_WeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();
	if (!WeaponToToggle)return;

	if (bShouldEnable)
	{
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		OverlappedActors.Empty();
	}
}

void UPL_CombatComponentBase::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
}
