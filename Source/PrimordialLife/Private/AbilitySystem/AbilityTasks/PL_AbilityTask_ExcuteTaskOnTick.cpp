// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/PL_AbilityTask_ExcuteTaskOnTick.h"


UPL_AbilityTask_ExcuteTaskOnTick::UPL_AbilityTask_ExcuteTaskOnTick()
{
	bTickingTask = true;
}

UPL_AbilityTask_ExcuteTaskOnTick* UPL_AbilityTask_ExcuteTaskOnTick::ExecuteTaskOnTick(UGameplayAbility* OwningAbility)
{
	UPL_AbilityTask_ExcuteTaskOnTick* Node = NewAbilityTask<UPL_AbilityTask_ExcuteTaskOnTick>(OwningAbility);
	return Node;
}

void UPL_AbilityTask_ExcuteTaskOnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTaskTick.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}
