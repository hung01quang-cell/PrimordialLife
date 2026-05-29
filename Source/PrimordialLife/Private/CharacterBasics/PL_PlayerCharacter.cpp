// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterBasics/PL_PlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Input/DataAsset/DataAsset_InputConfig.h"
#include "Input/Components/PL_InputComponent.h"
#include "PL_GameplayTags.h"
#include "AbilitySystem/Components/PL_AbilitySystemComponent.h"
#include "AbilitySystem/DataAssets/DataAsset_PlayerStartUpData.h"
#include "Combat/Components/Player/PL_PlayerCombatComponent.h"
#include "UI/PlayerUIComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "PL_DebugHelper.h"

APL_PlayerCharacter::APL_PlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	PlayerCombatComponent = CreateDefaultSubobject<UPL_PlayerCombatComponent>(TEXT("PlayerCombatComponent"));
	PlayerUIComponent = CreateDefaultSubobject<UPlayerUIComponent>(TEXT("PlayerUIComponent"));
}

void APL_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(PL_AbilitySystemComponent);
		}
	}
}

UPL_CombatComponentBase* APL_PlayerCharacter::GetPLCombatComponentBase() const
{
	return PlayerCombatComponent;
}

UPawnUIComponent* APL_PlayerCharacter::GetPawnUIComponent() const
{
	return PlayerUIComponent;
}

UPlayerUIComponent* APL_PlayerCharacter::GetPlayerUIComponent() const
{
	return PlayerUIComponent;
}

void APL_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UPL_InputComponent* PL_InputComponent = CastChecked<UPL_InputComponent>(PlayerInputComponent);
	//Action Move
	PL_InputComponent
		->BindNativeInputAction(InputConfigDataAsset, PrimordialLifeGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	//Action Look
	PL_InputComponent
		->BindNativeInputAction(InputConfigDataAsset, PrimordialLifeGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	PL_InputComponent
		->BindNativeInputAction(InputConfigDataAsset, PrimordialLifeGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);


	PL_InputComponent
		->BindNativeInputAction(InputConfigDataAsset, PrimordialLifeGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	// Action Abilites Equip Weapont
	PL_InputComponent
		->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
	PL_InputComponent
	->BindNativeInputAction(InputConfigDataAsset,PrimordialLifeGameplayTags::InputTag_PickUp_Stones,ETriggerEvent::Started,this,&ThisClass::Input_PickUpStonesStarted);

}

void APL_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void APL_PlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APL_PlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APL_PlayerCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void APL_PlayerCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0 ? PrimordialLifeGameplayTags::Player_Event_SwitchTarget_Right : PrimordialLifeGameplayTags::Player_Event_SwitchTarget_Left,
		Data
	);
}

void APL_PlayerCharacter::Input_PickUpStonesStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		PrimordialLifeGameplayTags::Player_Event_ConsumeStones,
		Data
	);
}

//loại tag nào thì kích hoạt loại vũ khí đó 
void APL_PlayerCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	//PL_AbilitySystemComponent->OnAbilityInputPressed(PlayerCombatComponent->CurrentEquippedWeaponTag);
	PL_AbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void APL_PlayerCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	//PL_AbilitySystemComponent->OnAbilityInputReleased(PlayerCombatComponent->CurrentEquippedWeaponTag);
	PL_AbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
