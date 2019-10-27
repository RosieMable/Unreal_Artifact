// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "StaticTools.generated.h"
/**
 * 
 */
UCLASS()
class ARTIFACT_API UStaticTools : public UObject
{
	GENERATED_UCLASS_BODY()

		//FORCEINLNE function
		static FORCEINLINE bool IsValid(AActor* TheActor)
	{
		if (!TheActor) return false;
		if (!TheActor->IsValidLowLevel()) return false;
		return true;
	}
	
	UFUNCTION(BlueprintCallable, Category = "Static Tools")
	static FVector ConvertLocationToActorSpace(FVector Location, AActor* Reference, AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Static Tools")
	static FRotator ConvertRotationToActorSpace(FRotator Rotation, AActor* Reference, AActor* Target);
};
