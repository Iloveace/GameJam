// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MYPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character", meta=(AllowPrivateAccess="true"))
    class UPaperFlipbookComponent* FBComponent{};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Collision", meta=(AllowPrivateAccess="true"))
    class USphereComponent* SphereComp{};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess="true"))
    class UProjectileMovementComponent* ProjectileComp{};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Boom", meta=(AllowPrivateAccess="true"))
    class UPaperFlipbook* Project{};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Boom", meta=(AllowPrivateAccess="true"))
    class UPaperFlipbook* Boom{};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
    virtual void Tick(float DeltaTime) override;
private:
    UFUNCTION()
    void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

    static constexpr int FrameOffset{71};

};
