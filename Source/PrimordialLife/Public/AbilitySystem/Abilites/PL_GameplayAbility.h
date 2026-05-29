// Copyright (c) 2025 Hung Pham. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PrimordialLifeType/PL_EnumType.h"
#include "PL_GameplayAbility.generated.h"

UENUM(BlueprintType)
enum class E_PLAbilityActivetionPolicy : uint8
{
	OnTriggerted,
	OnGiven
};

class UPL_CombatComponentBase;
class UPL_AbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPL_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	UPROPERTY(EditDefaultsOnly, Category = "PrimordialLife|Ability")
	E_PLAbilityActivetionPolicy AbilityActivationPolicy = E_PLAbilityActivetionPolicy::OnTriggerted;

	UFUNCTION(BlueprintPure, Category = "PrimordialLife|Ability")
	UPL_CombatComponentBase* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "PrimordialLife|Ability")
	UPL_AbilitySystemComponent* GetPLAbilitySystemComponentFromActorInfor();

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "PrimordialLife|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, E_PrimordialLifeSuccessType& OutSuccessType);
};

