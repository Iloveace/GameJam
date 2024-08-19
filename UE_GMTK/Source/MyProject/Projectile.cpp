// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "PaperFlipbook.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"




// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    RootComponent = SphereComp;
    FBComponent = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(APaperCharacter::SpriteComponentName);
    if (FBComponent)
    {
        FBComponent->AlwaysLoadOnClient = true;
        FBComponent->AlwaysLoadOnServer = true;
        FBComponent->bOwnerNoSee = false;
        FBComponent->bAffectDynamicIndirectLighting = true;
        FBComponent->PrimaryComponentTick.TickGroup = TG_PrePhysics;
        FBComponent->SetupAttachment(RootComponent);
        static FName CollisionProfileName(TEXT("CharacterMesh"));
        FBComponent->SetCollisionProfileName(CollisionProfileName);
        FBComponent->SetGenerateOverlapEvents(false);
    }
    ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
    

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
    Super::BeginPlay();
    OnActorHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{

    UE_LOG(LogTemp, Display, TEXT("%s"), *OtherActor->GetName());
    FBComponent->SetFlipbook(Boom);
    // We have to include a minus 1 
    if (FBComponent->GetPlaybackPositionInFrames()==FBComponent->GetFlipbookLengthInFrames()-FrameOffset)
    {
        Destroy();
    }
}
