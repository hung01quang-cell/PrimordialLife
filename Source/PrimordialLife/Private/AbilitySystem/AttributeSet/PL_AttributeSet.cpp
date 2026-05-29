// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "AbilitySystem/AttributeSet/PL_AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "PL_FunctionLibrary.h"
#include "PL_GameplayTags.h"
#include "UI/Interface/PawnUIInterface.h"
#include "UI/PawnUIComponent.h"
#include "UI/PlayerUIComponent.h"

#include "PL_DebugHelper.h"

UPL_AttributeSet::UPL_AttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UPL_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	checkf(PawnUIComponent, TEXT("Couldn't extract a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);

		if (GetCurrentRage() == GetMaxRage())
		{
			UPL_FunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PrimordialLifeGameplayTags::Player_Status_Rage_Full);
		}
		else if (GetCurrentRage() == 0.f)
		{
			UPL_FunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PrimordialLifeGameplayTags::Player_Status_Rage_None);
		}
		else
		{
			UPL_FunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), PrimordialLifeGameplayTags::Player_Status_Rage_None);
			UPL_FunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), PrimordialLifeGameplayTags::Player_Status_Rage_Full);
		}

		if (UPlayerUIComponent* PlayerUIComponent = CachedPawnUIInterface->GetPlayerUIComponent())
		{
			PlayerUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);
	/*	const FString DebugString = FString::Printf(
			TEXT("Old Health: %f, Damage Done: %f, NewCurrentHealth: %f"),
			OldHealth,
			DamageDone,
			NewCurrentHealth
		);

		Debug::Print(DebugString, FColor::Green);*/

		//TODO:: Notify the UI
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());


        if (NewCurrentHealth == 0)
		{
			UPL_FunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PrimordialLifeGameplayTags::Shared_Status_Dead);
		}
	}
}