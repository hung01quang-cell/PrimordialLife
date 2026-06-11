
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PrimordialLifeType/PL_EnumType.h"
#include "PL_FunctionLibrary.generated.h"

class UPL_GameInstance;
class UPL_AbilitySystemComponent;
class UPL_CombatComponentBase;
/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API UPL_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	 
public:
	static UPL_AbilitySystemComponent* NativeGetPrimordialLifeASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Player|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Player|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Player|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, E_PrimordialLifeConfirmType& OutConfirmType);

	static UPL_CombatComponentBase* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Player|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPL_CombatComponentBase* BP_GetPawnCombatComponentFromActor(AActor* InActor, E_PrimordialLifeValidType& OutValidType);

	UFUNCTION(BlueprintCallable, Category = "Player|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintCallable, Category = "Player|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintCallable, Category = "Player|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "Player|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Player|FunctionLibrary", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
		float& OutRemainingTime, E_PrimordialLifeCountDownActionInput CountDownInput,
		UPARAM(DisplayName = "Output") E_PrimordialLifeCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintPure, Category = "Player|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static UPL_GameInstance* GetPLayerGameInstance(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable,Category = "Player|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(const UObject* WorldContextObject,E_PrimordialLifeInputMode InInputMode);
	
	UFUNCTION(BlueprintCallable,Category = "Player|FunctionLibrary")
	static void SaveCurrentGameDifficulty(E_PrimordialLifeGameDifficulty InDifficultyToSave);

	UFUNCTION(BlueprintCallable,Category = "Player|FunctionLibrary")
	static bool TryLoadSavedGameDifficulty(E_PrimordialLifeGameDifficulty& OutSavedDifficulty);
	
};
