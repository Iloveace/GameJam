// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	

	StartLocation = GetActorLocation();
	HasRotated;
    // Using the function GetName() to get the name of the actor.
	FString Name = GetName();

    
    // Perameter 1(LogTemp) tells us what category we are doing.
	// The second parameter(Display) tells us the level of the log.
	// Lastly the TEXT function tells us the text we need to print out.
	// Make sure to add a * to "MyString" so that it gets the contents, I believe thats a pointer.
	// UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
	

	
    
} 

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


    MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
	LaunchPad(DeltaTime);
	// ShouldPlatformReturn();


}
void AMovingPlatform::LaunchPad(float DeltaTime)
{
	if(Launch && !ResetLaunch)
	{   
		
		AddActorLocalRotation(RotationVelocity*DeltaTime);
		HasRotated.Pitch += FMath::Abs(RotationVelocity.Pitch * DeltaTime);
        HasRotated.Yaw += FMath::Abs(RotationVelocity.Yaw * DeltaTime);
        HasRotated.Roll += FMath::Abs(RotationVelocity.Roll * DeltaTime);

		if(HasRotated.Pitch >= 90.0f){
            RotationVelocity = -1*RotationVelocity;
			ResetLaunch = true;

		}
		else if(HasRotated.Yaw >= 90.0f){
            RotationVelocity = -1*RotationVelocity;
			ResetLaunch = true;

		}
		else if(HasRotated.Roll >= 90.0f){
            RotationVelocity = -1*RotationVelocity;
			ResetLaunch = true;

		}
	}
	if (ResetLaunch)
	{
		AddActorLocalRotation(RotationVelocity*DeltaTime);
		HasRotated.Pitch += FMath::Abs(RotationVelocity.Pitch * DeltaTime);
        HasRotated.Yaw += FMath::Abs(RotationVelocity.Yaw * DeltaTime);
        HasRotated.Roll += FMath::Abs(RotationVelocity.Roll * DeltaTime);

		if(HasRotated.Pitch <= 0.0){
            RotationVelocity = -1*RotationVelocity;
			ResetLaunch = false;
			Launch = false;

		}
		else if(HasRotated.Yaw < 0.0){
            RotationVelocity = -1*RotationVelocity;
			ResetLaunch = false;
			Launch = false;


		}
		else if(HasRotated.Roll < 0.0){
            RotationVelocity = -1*RotationVelocity;
			ResetLaunch = false;
			Launch = false;


		}
	} 
	


}
// :: Known as the scope resolution operator.
void AMovingPlatform::MovePlatform(float DeltaTime)
{

	if (ShouldPlatformReturn()) {
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MovedDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		// Move platform forwards
		// Get current location
	FVector CurrentLocation = GetActorLocation();
		// Add vector to that location by getting the product of velocity and time between frames.
	CurrentLocation += (PlatformVelocity * DeltaTime);
		// Set the location
	SetActorLocation(CurrentLocation);
	
	}

}

bool AMovingPlatform::ShouldPlatformReturn() const
    {
    return GetDistanceMoved() > MovedDistance;
	}

float AMovingPlatform::GetDistanceMoved() const
	{
	float DistDifference = FVector::Dist(StartLocation, GetActorLocation());
    return DistDifference;
	}

void AMovingPlatform::RotatePlatform(float DeltaTime)
	{
    // Simply add's the RotationVelocity times DeltaTime to the current rotation so that it rotates.    
	AddActorLocalRotation(RotationVelocity*DeltaTime);
	}
 