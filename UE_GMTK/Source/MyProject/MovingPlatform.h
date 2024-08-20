// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class MYPROJECT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Launch")
	bool Launch;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Launch")
	FRotator RotationLaunch;
	UPROPERTY(BlueprintreadWrite, EditAnywhere, Category="Launch")
	FRotator StartRotation;
	UPROPERTY(BlueprintreadWrite, EditAnywhere, Category ="Rotation");
	FRotator RotationVelocity;
	UPROPERTY(EditAnywhere, Category ="Rotation");
	FRotator HasRotated;
	UPROPERTY(EditAnywhere, Category ="Rotation");
	bool ResetLaunch;
	

	void LaunchPad(float DeltaTime);


private:
    

	UPROPERTY(EditAnywhere, Category="Moving")
	FVector PlatformVelocity = FVector(100, 0, 0);
	UPROPERTY(EditAnywhere, Category="Moving")
	float MovedDistance = 100;
	
	
	
	

    
	FVector StartLocation;

	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);

	bool ShouldPlatformReturn() const;

	float GetDistanceMoved() const;








};
