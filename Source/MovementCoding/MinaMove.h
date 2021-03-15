// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "MinaMove.generated.h"

UCLASS()
class MOVEMENTCODING_API AMinaMove : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMinaMove();

	UPROPERTY(EditAnywhere);
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere);
	class UCameraComponent* CameraComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//movement for Mina
	void Forward(float Value);
	void Right(float Value);

	void CheckJump();

	UPROPERTY()
		bool Jumping;

	void SpringArmYawL(float Value);
	void SpringArmYawR(float Value);
protected:
	FRotator SetRotation{ 30.f,0.f,-10.f };
	FRotator PanLR{0.f,0.f,0.f};
	FRotator cameraCompRotation;
};
