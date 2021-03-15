// Fill out your copyright notice in the Description page of Project Settings.


#include "MinaMove.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMinaMove::AMinaMove()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 500.f;
	SpringArmComp->SetRelativeRotation(FRotator(SetRotation));

	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 10.f;
	//SpringArmComp->bInheritYaw = true;
	SpringArmComp->bDoCollisionTest = false;


	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Jumping = false;
}

// Called when the game starts or when spawned
void AMinaMove::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinaMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	cameraCompRotation = camManager->GetCameraRotation();

	FRotator NewRot = cameraCompRotation + PanLR;
	SpringArmComp->SetRelativeRotation(NewRot);
	*/

	if (Jumping)
	{
		Jump();
	}

}

// Called to bind functionality to input
void AMinaMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AMinaMove::Forward);
	PlayerInputComponent->BindAxis("Right", this, &AMinaMove::Right);
	PlayerInputComponent->BindAxis("MouseMove", this, &AMinaMove::SpringArmYawL);
	PlayerInputComponent->BindAxis("MouseMove", this, &AMinaMove::SpringArmYawR);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMinaMove::CheckJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMinaMove::CheckJump);
	

}

void AMinaMove::CheckJump() 
{
	if (Jumping)
	{
		Jumping = false;
	}
	else
	{
		Jumping = true;
	}
}

void AMinaMove::SpringArmYawR(float Value)
{
	PanLR.Yaw = FMath::Clamp(Value, -1.f, 1.f);

}

void AMinaMove::SpringArmYawL(float Value)
{
	PanLR.Yaw = FMath::Clamp(Value, -1.f, 1.f);
	
}

void AMinaMove::Forward(float Value)
{
	if (Value)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMinaMove::Right(float Value) 
{
	if (Value)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

