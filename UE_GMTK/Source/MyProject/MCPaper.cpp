// Fill out your copyright notice in the Description page of Project Settings.


#include "MCPaper.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"


AMCPaper::AMCPaper()
{
    PrimaryActorTick.bCanEverTick=true;

    RootComponent = GetCapsuleComponent();
    // Made SpringArm a default subobject and attached it to our RootComponent.
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    // Made CameraComponent a default subobject and attached it to our SpringArm.
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArm);


}
void AMCPaper::BeginPlay()
{
    Super::BeginPlay();
    AMCPaper::AddDefaultMapping();
}


void AMCPaper::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
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
        Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMCPaper::JumpAct);
    }
}

void AMCPaper::Forward(const FInputActionValue& Value)
{
    // This float represents the direction which will either be 1.0, -1.0, and 0.0 depending on the input W, S, or lack there of.
    const float DirectionValue{Value.Get<float>()};

    if (Controller && DirectionValue)
    {
        FVector Direction(GetActorForwardVector());
        AddMovementInput(Direction, DirectionValue);
    }

    // Controller is a default variable that is inherited from the APawn class and represents controller possessing the object.
    // If we have a controller and we have an input W or S...
    // if (Controller && DirectionValue)
    /*{
        FVector Direction{GetActorForwardVector()};
        // AddMovementInput is a default function that is inherited from APawn class and it
        AddMovementInput(Direction, DirectionValue);
    }
    */
}



void AMCPaper::JumpAct(const FInputActionValue& Value)
{
    const bool Jumping{Value.Get<bool>()};

    if (Jumping)
    {
        Jump();
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
