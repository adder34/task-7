// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class TASK6_API ANPC_AIController : public AAIController
{
	GENERATED_BODY()

		namespace bb_keys
	{
		TCHAR const* const target_location = TEXT("TargetLocation");
	}

};
