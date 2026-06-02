// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBasics/PL_CharacterBasic.h"
#include "GameplayTagContainer.h"
#include "PL_PlayerCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UDataAsset_InputConfig;
class UPL_PlayerCombatComponent;
/**
 *  
 */
UCLASS()
class PRIMORDIALLIFE_API APL_PlayerCharacter : public APL_CharacterBasic
{


	GENERATED_BODY()

private:
#pragma region Camera

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UPL_PlayerCombatComponent* PlayerCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UPlayerUIComponent* PlayerUIComponent;

#pragma endregion

#pragma region Inputs

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);
	UPROPERTY()
	FVector2D SwitchDirection = FVector2D::ZeroVector;
	void Input_PickUpStonesStarted(const FInputActionValue& InputActionValue);
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

#pragma endregion
protected:
	//~ Begin APawn Interface.k
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
public:

	

	//~ Begin IPawnCombatInterface Interface.
	virtual UPL_CombatComponentBase* GetPLCombatComponentBase() const override;
	//~ End IPawnCombatInterface Interface

	//~ Begin IPawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UPlayerUIComponent* GetPlayerUIComponent() const override;
	//~ End IPawnUIInterface Interface

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;


	APL_PlayerCharacter();

	FORCEINLINE UPL_PlayerCombatComponent* GetPlayerCombatComponent() const { return PlayerCombatComponent; }
};
