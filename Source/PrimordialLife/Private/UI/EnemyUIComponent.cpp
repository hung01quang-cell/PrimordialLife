// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyUIComponent.h"
#include "Widgets/PlayerWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawWidget(UPlayerWidgetBase* InWidgetRegister)
{
	EnemyDrawWidgets.Add(InWidgetRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawWidgetsIfAny()
{
	if (EnemyDrawWidgets.IsEmpty())
	{
		return;
	}
	for (UPlayerWidgetBase* WidgetDraw : EnemyDrawWidgets)
	{
		if(WidgetDraw)
		{
			WidgetDraw->RemoveFromParent();
		}
	}
	EnemyDrawWidgets.Empty();
}
