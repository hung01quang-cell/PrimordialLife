// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM()
enum class E_PrimordialLifeConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class E_PrimordialLifeValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class E_PrimordialLifeSuccessType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class E_PrimordialLifeCountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class E_PrimordialLifeCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};

UENUM(BlueprintType)
enum class E_PrimordialLifeGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
	VeryHard
};

UENUM(BlueprintType)
enum class E_PrimordialLifeInputMode : uint8
{
	GameOnly,
	UIOnly
};