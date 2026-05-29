// Copyright (c) 2025 Hung Pham. All Rights Reserved.


#include "PL_FunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Components/PL_AbilitySystemComponent.h"
#include "Combat/Interface/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "PL_GameplayTags.h"
#include "PrimordialLifeType/PlayerCountDownAction.h"

#include "PL_DebugHelper.h"

UPL_AbilitySystemComponent* UPL_FunctionLibrary::NativeGetPrimordialLifeASCFromActor(AActor* InActor)
{
	check(InActor)
	return Cast<UPL_AbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UPL_FunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UPL_AbilitySystemComponent* ASC = NativeGetPrimordialLifeASCFromActor(InActor);
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UPL_FunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UPL_AbilitySystemComponent* ASC = NativeGetPrimordialLifeASCFromActor(InActor);
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UPL_FunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UPL_AbilitySystemComponent* ASC = NativeGetPrimordialLifeASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UPL_FunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, E_PrimordialLifeConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? E_PrimordialLifeConfirmType::Yes : E_PrimordialLifeConfirmType::No;
}

UPL_CombatComponentBase* UPL_FunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);
	if (IPawnCombatInterface* CombatInter = Cast<IPawnCombatInterface>(InActor))
	{
		return CombatInter->GetPLCombatComponentBase();
	}
	return nullptr;
}

UPL_CombatComponentBase* UPL_FunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, E_PrimordialLifeValidType& OutValidType)
{
	UPL_CombatComponentBase* CombatComp = NativeGetPawnCombatComponentFromActor(InActor);
	OutValidType = CombatComp ? E_PrimordialLifeValidType::Valid : E_PrimordialLifeValidType::Invalid;
	return CombatComp;
}

bool UPL_FunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

FGameplayTag UPL_FunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker && InVictim);
	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormal = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormal);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormal);
	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if (OutAngleDifference >= -45 && OutAngleDifference <= 45)
	{
		return PrimordialLifeGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference <= -135 || OutAngleDifference >= 135)
	{
		return PrimordialLifeGameplayTags::Shared_Status_HitReact_Bock;
	}
	else if (OutAngleDifference <= -45 && OutAngleDifference >= -135)
	{
		return PrimordialLifeGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference >= 45 && OutAngleDifference <= 135)
	{
		return PrimordialLifeGameplayTags::Shared_Status_HitReact_Right;
	}
	return PrimordialLifeGameplayTags::Shared_Status_HitReact_Front;
}

bool UPL_FunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());
	/*const FString DebugString = FString::Printf(TEXT("Dot Result: %f %s"), DotResult, DotResult < -0.1f ? TEXT("Valid Block") : TEXT("InvalidBlock"));

	Debug::Print(DebugString, DotResult < -0.1f ? FColor::Green : FColor::Red);*/

	return DotResult < -0.1f;
}

bool UPL_FunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UPL_AbilitySystemComponent* SourceASC = NativeGetPrimordialLifeASCFromActor(InInstigator);
	UPL_AbilitySystemComponent* TargetASC = NativeGetPrimordialLifeASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UPL_FunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, E_PrimordialLifeCountDownActionInput CountDownInput, UPARAM(DisplayName = "Output") E_PrimordialLifeCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;

	if (GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}

	if (!World)
	{
		return;
	}

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

	FlayerCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FlayerCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);

	if (CountDownInput == E_PrimordialLifeCountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FlayerCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo)
			);
		}
	}

	if (CountDownInput == E_PrimordialLifeCountDownActionInput::Cancel)
	{
		if (FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}