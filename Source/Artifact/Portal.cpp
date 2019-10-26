// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APortal::IsActive()
{
	return false;
}

void APortal::SetActive(bool NewActive)
{
	return;
}

void APortal::ClearRTT_Implementation()
{

}

void APortal::SetRTT_Implementation(UTexture* RenderTexture)
{

}



