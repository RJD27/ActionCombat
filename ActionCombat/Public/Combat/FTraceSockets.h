// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTraceSockets.generated.h" // must be included or wont work

/**
 * 
 */
USTRUCT(BlueprintType)
struct ACTIONCOMBAT_API FTraceSockets
{
	GENERATED_BODY(); // Allows Unreal to generate additional code thats needed
	UPROPERTY(EditAnywhere)
	FName Start; // F for storing strings

	UPROPERTY(EditAnywhere)
	FName End;

	UPROPERTY(EditAnywhere)
	FName Rotation;
};
