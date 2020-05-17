// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include <Artifact\ArtifactCharacter.h>
#include "StaticTools.h"

// Sets default values
APortal::APortal(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isActive = false; //Teleport is not active at start

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->Mobility = EComponentMobility::Static; //Make the component static

	PortalRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PortalRootComponent"));
	PortalRootComponent->SetupAttachment(GetRootComponent()); //Make this a child of the root component
	PortalRootComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); //Set up the position to the center of the rooot
	PortalRootComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f)); //Set up the rotation to the center of the root
	PortalRootComponent->Mobility = EComponentMobility::Movable;
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

//Blueprints events
void APortal::ClearRTT_Implementation()
{

}

void APortal::SetRTT_Implementation(UTexture* RenderTexture)
{

}

void APortal::ForceTick_Implementation()
{
}

//----------------


//Get and Set functions for the target actor
AActor* APortal::GetTarget()
{
	return Target;
}

void APortal::SetTarget(AActor* newTarget)
{
	Target = newTarget;
}

//-------------

//To determine if we are in front of a place (plane = portal), it uses FPlane struct
bool APortal::isPointInFrontOfPortal(FVector point, FVector portalLocation, FVector portalNormal)
{
	FPlane PortalPlane = FPlane(portalLocation, portalNormal);
	float portalDot = PortalPlane.PlaneDot(point);
	//If < 0 it means we are behind the portal
	return (portalDot >= 0);
}

//To determine if a point has crossed the portal plane
//It keeps track of a the point position and sees if it is infront of the portal and if it has crossed it
bool APortal::isPointCrossingPortal(FVector point, FVector portalLocation, FVector portalNormal)
{
	FVector IntersectionPoint;
	FPlane PortalPlane = FPlane(portalLocation, portalNormal);
	float PortalDot = PortalPlane.PlaneDot(point);
	bool isCrossing = false;
	bool isInFront = PortalDot >= 0;

	bool isIntersect = FMath::SegmentPlaneIntersection(LastPos, point, PortalPlane, IntersectionPoint);

	//Inteserct with the portal since last location?
	//If yes, check the direction -> If crossing forward means we were in front of the portal and now at its back
	//If crossed backwards, ignore it
	if (isIntersect && !isInFront && LastInFront)
	{
		isCrossing = true;
	}

	//Stores values for next check
	LastInFront = isInFront;
	LastPos = point;

	return isCrossing;
}

void APortal::TeleportActor(AActor* actorToTeleport)
{
	if (actorToTeleport == nullptr || Target == nullptr)
	{
		return;
	}

	//Retrieve and save player velocity from the movement component
	FVector SavedVelocity = FVector::ZeroVector;
	AArtifactCharacter* EC = nullptr;

	if (actorToTeleport->IsA(AArtifactCharacter::StaticClass())) {
		EC = Cast<AArtifactCharacter>(actorToTeleport);

		SavedVelocity = EC->GetVelocity();
	}

	//Compute and apply new location
	FHitResult HitResul;
	FVector NewLocation = UStaticTools::ConvertLocationToActorSpace(actorToTeleport->GetActorLocation(), this, Target);

	actorToTeleport->SetActorLocation(NewLocation,
		false,
		&HitResul,
		ETeleportType::TeleportPhysics);

	//Compute and apply new rotation
	FRotator NewRotation = UStaticTools::ConvertRotationToActorSpace(actorToTeleport->GetActorRotation(), this, Target);

	//Apply new rotation
	actorToTeleport->SetActorRotation(NewRotation);

	if (actorToTeleport->IsA(AArtifactCharacter::StaticClass()))
	{
		//Reapply Velocity (Need to reorient direction into local space of Portal)
		{
			FVector Dots;
			Dots.X = FVector::DotProduct(SavedVelocity, GetActorForwardVector());
			Dots.Y = FVector::DotProduct(SavedVelocity, GetActorRightVector());
			Dots.Z = FVector::DotProduct(SavedVelocity, GetActorUpVector());

			FVector NewVelocity = Dots.X * Target->GetActorForwardVector()
				+ Dots.Y * Target->GetActorRightVector()
				+ Dots.Z * Target->GetActorUpVector();

			EC->GetVelocity() = NewVelocity;

		}
		//Cleanup Teleport
		LastPos = NewLocation;
	}
}

