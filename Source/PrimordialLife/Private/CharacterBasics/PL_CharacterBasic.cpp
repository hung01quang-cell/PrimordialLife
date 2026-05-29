// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBasics/PL_CharacterBasic.h"
#include "AbilitySystem/Components/PL_AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/PL_AttributeSet.h"
#include "MotionWarpingComponent.h"


// Sets default values
APL_CharacterBasic::APL_CharacterBasic()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	PL_AbilitySystemComponent = CreateDefaultSubobject<UPL_AbilitySystemComponent>(TEXT("PL_AbilitySystemComponent"));
	PL_AttributeSet = CreateDefaultSubobject<UPL_AttributeSet>(TEXT("PL_AttributeSet"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* APL_CharacterBasic::GetAbilitySystemComponent() const
{
	return GetPLAbilitySystemComponent();
}

UPL_CombatComponentBase* APL_CharacterBasic::GetPLCombatComponentBase() const
{
	return nullptr;
}

UPawnUIComponent* APL_CharacterBasic::GetPawnUIComponent() const
{
	return nullptr;
}

void APL_CharacterBasic::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (PL_AbilitySystemComponent)
	{
		PL_AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	//ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
}
