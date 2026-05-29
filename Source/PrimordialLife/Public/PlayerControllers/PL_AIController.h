// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PL_AIController.generated.h"


class UAIPerceptionComponent;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class PRIMORDIALLIFE_API APL_AIController : public AAIController
{
	GENERATED_BODY()
	
public:

	APL_AIController(const FObjectInitializer& ObjectInitializer);

	//~ Begin IGenericTeamAgentInterface Interface.
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//~ End IGenericTeamAgentInterface Interface

	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float SightRadius = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float LoseSightRadius = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float Perspective = 360.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FGenericTeamId EnemyTeamID = FGenericTeamId(1);

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config")
	bool bEnableDetourCrowAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowAvoidance", UIMin = "1", UIMax = "4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowAvoidance"))
	float CollosionQueryRange = 600.f;

};
