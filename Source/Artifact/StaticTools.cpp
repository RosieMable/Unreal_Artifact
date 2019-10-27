// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticTools.h"

UStaticTools::UStaticTools(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

FVector UStaticTools::ConvertLocationToActorSpace(FVector Location, AActor* Reference, AActor* Target)
{
	//If reference and target are null
	if (Reference == nullptr || Target == nullptr)
	{
		return FVector::ZeroVector;
	}

	//The direction vector is not normalised, so we can re-multiply the dot result against the vectors of the target to retrive the location at exactly the same distance in the local space of the target actor
	FVector Direction = Location - Reference->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	//Compute the dot product between vectors to determine multiple angles
	FVector Dots;
	Dots.X = FVector::DotProduct(Direction, Reference->GetActorForwardVector);
	Dots.Y = FVector::DotProduct(Direction, Reference->GetActorRightVector);
	Dots.Z = FVector::DotProduct(Direction, Reference->GetActorUpVector);

	FVector NewDirection = Dots.X * Target->GetActorForwardVector()
		+ Dots.Y * Target->GetActorRightVector()
		+ Dots.Z * Target->GetActorUpVector();

	return TargetLocation + NewDirection;
}

FRotator UStaticTools::ConvertRotationToActorSpace(FRotator Rotation, AActor* Reference, AActor* Target)
{
	if (Reference == nullptr || Target == nullptr)
	{
		return FRotator::ZeroRotator;
	}

	FTransform SourceTransform = Reference->GetActorTransform();
	FTransform TargetTransform = Target->GetActorTransform();
	FQuat QuatRotation = FQuat(Rotation);

	// Inverse() against the Rotation we want to convert will translate it into a local space
	FQuat LocalQuat = SourceTransform.GetRotation().Inverse() * QuatRotation;
	FQuat NewWorldQuat = TargetTransform.GetRotation() * LocalQuat;


	return NewWorldQuat.Rotator();
}
