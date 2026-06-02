// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUps/PL_StoneBase.h"

#include "PL_GameplayTags.h"
#include "CharacterBasics/PL_PlayerCharacter.h"
#include "AbilitySystem/Components/PL_AbilitySystemComponent.h"

void APL_StoneBase::Consume(UPL_AbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);
	UGameplayEffect* EffectCDD = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();
	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDD,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext()
	);
	BP_OnStoneCosumed();
}

void APL_StoneBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APL_PlayerCharacter* OverlappedHeroCharacter = Cast<APL_PlayerCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetPLAbilitySystemComponent()->TryActivateAbilityByTag(PrimordialLifeGameplayTags::Player_Ability_PickUp_Stones);
	}
}


