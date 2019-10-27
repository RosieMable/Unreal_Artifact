// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture.h"
#include "Portal.generated.h"

UCLASS()
class ARTIFACT_API APortal : public AActor
{
	GENERATED_UCLASS_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Status of the Portal (being visualized by the player or not)
	UFUNCTION(BlueprintPure, Category = "Portal")
		bool IsActive();

	UFUNCTION(BlueprintCallable, Category = "Portal")
		void SetActive(bool NewActive);


	//Render target to use to display the portal
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Portal")
		void ClearRTT();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Portal")
		void SetRTT(UTexture* RenderTexture);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Portal")
		void ForceTick();

	//Target of where the portal is looking
	UFUNCTION(BlueprintPure, Category = "Portal")
		AActor* GetTarget();

	UFUNCTION(BlueprintCallable, Category = "Portal")
		void SetTarget(AActor* newTarget);

	//Helpers
	UFUNCTION(BlueprintCallable, Category = "Portal|Helpers")
		bool isPointInFrontOfPortal(FVector point, FVector portalLocation, FVector portalNormal);

	UFUNCTION(BlueprintCallable, Category = "Portal|Helpers")
		bool isPointCrossingPortal(FVector point, FVector portalLocation, FVector portalNormal);

	UFUNCTION(BlueprintCallable, Category = "Portal|Helpers")
		void TeleportActor(AActor* actorToTeleport);

protected:
	UPROPERTY(BlueprintReadOnly)
		USceneComponent* PortalRootComponent;

private:
	bool isActive;

	AActor* Target;

	//Used to track movement of a point
	FVector LastPos;
	bool LastInFront;



};
