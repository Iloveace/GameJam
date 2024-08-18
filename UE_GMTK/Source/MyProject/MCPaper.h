// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PaperCharacter.h"
#include "MCPaper.generated.h"

/**
 *
 */
UCLASS()
class MYPROJECT_API AMCPaper : public APaperCharacter
{
    GENERATED_BODY()
public:
    AMCPaper();
protected:
    virtual void BeginPlay() override;

/*
    *   Forward declared UInputMappingContext and UinputAction as well as initialized them as pointers.
    *   Then forward declared my "Forward" function. It takes a const FInputActionValue address that
    *   needed to be included in this header file.
    * 
    */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
    class UInputMappingContext* IMC_Default{};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
    class UInputAction* MoveAction{};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
    UInputAction* JumpAction{};

    void Forward(const FInputActionValue& Value);
    void JumpAct(const FInputActionValue& Value);

    void AddDefaultMapping();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="CapsuleComponent", meta=(AllowPrivateAccess="true"))
    class UCapsuleComponent* CapsuleComp{};
    
    // We create USpringArmComponent pointer and UCameraComponent.
    // Created a spring arm component pointer that is used to connect our camera to our player pawn.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
    class USpringArmComponent* SpringArm{};
    // Created a camera component pointer that is used to view our player pawn.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
    class UCameraComponent* CameraComponent{};
public:
    // called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
