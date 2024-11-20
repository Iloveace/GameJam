// Fill out your copyright notice in the Description page of Project Settings.



#include "MCPaper.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Projectile.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Templates/SubclassOf.h"
#include "Engine/World.h"


AMCPaper::AMCPaper()
{
    PrimaryActorTick.bCanEverTick=true;

    RootComponent = GetCapsuleComponent();
    // Made SpringArm a default subobject and attached it to our RootComponent.
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    if (SpringArm)
    {
        SpringArm->SetUsingAbsoluteRotation(true);
    }
    // Made CameraComponent a default subobject and attached it to our SpringArm.
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArm);

    ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectilePoint"));
    ArrowComp->SetupAttachment(RootComponent);

}
void AMCPaper::BeginPlay()
{
    Super::BeginPlay();
    AMCPaper::AddDefaultMapping();
}


void AMCPaper::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AnimSwitch();
}

void AMCPaper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    /*
    *   Initilize the UEnhancedInputComponent pointer to the UInputComponent pointer using a
    *   "CastChecked<>()" template funciton that acts like the "Cast<>()" template function,
    *   however, it will crash if are Input variable comes back as a nullptr.
    *   From there, the Input pointer points to its function "BindAction()".
    */
    if (UEnhancedInputComponent* Input{CastChecked<UEnhancedInputComponent>(PlayerInputComponent)})
    {
        Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMCPaper::Forward);
        Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AMCPaper::JumpAct);
        Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMCPaper::StopJumpAct);
        Input->BindAction(ProjectAction, ETriggerEvent::Started, this, &AMCPaper::Project);
    }
}

void AMCPaper::Forward(const FInputActionValue& Value)
{
    // This float represents the direction which will either be 1.0, -1.0, and 0.0 depending on the input W, S, or lack there of.
    const float DirectionValue{Value.Get<float>()};


    if (Controller && DirectionValue)
    {
        FVector Direction(1.0f, 0.0f, 0.0f);
        AddMovementInput(Direction, DirectionValue);
        FRotator NewRotation{0.0f, DirectionValue > 0.0f ? 0.0f : 180.0f, 0.0f};
        GetController()->SetControlRotation(NewRotation);
    }
}



void AMCPaper::JumpAct(const FInputActionValue& Value)
{
    const bool JumpingAct{Value.Get<bool>()};

    if (JumpingAct)
    {
        Jump();
    }
}

void AMCPaper::StopJumpAct(const FInputActionValue& Value)
{
    const bool JumpingAct{Value.Get<bool>()};

    if (!JumpingAct)
    {
        StopJumping();
    }
}


void AMCPaper::Project(const FInputActionValue& Value)
{
    const bool ProjectAct{Value.Get<bool>()};

    if (Controller && ProjectAct)
    {
        FVector CompLoc{ArrowComp->GetComponentLocation()};
        FRotator CompRot{ArrowComp->GetComponentRotation()};
        GetWorld()->SpawnActor<AProjectile>(Projectile, CompLoc, CompRot);
        
        // if (Pro)
        // {
        //     GetWorld()->SpawnActor(Pro, &CompLoc, &CompRot);
        // }
    }
}

void AMCPaper::AddDefaultMapping()
{
    // Initialize the APlayerController pointer to a Cast of the same type to GetController() function.
    APlayerController* PlayerController{Cast<APlayerController>(GetController())};
    if (PlayerController)
    {
        // Initialize the UEnhancedInputLocalPlayerSubsystem pointer to the subsystem of the PlayerController.
        UEnhancedInputLocalPlayerSubsystem* Subsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())};
        if (Subsystem)
        {
            // Then we access the Subsystem pointer and use its function "AddMappingContext" to add an InputMappingContext.
            Subsystem->AddMappingContext(IMC_Default, 0);
        }
    }
}

void AMCPaper::AnimSwitch()
{
    if (GetCharacterMovement()->IsMovingOnGround() && !DingDong)
    {
        if (GetVelocity().Length())
        {
            GetSprite()->SetFlipbook(Running);
        }
        else
        {
            GetSprite()->SetFlipbook(Idle);
        }
    }
    else
    {
        // Checks if our sprite is in the air and if so, we set our animation to the jumping animation.
        if (GetVelocity().Z)
        {
            GetSprite()->SetFlipbook(Jumping);
        }
    }

}
