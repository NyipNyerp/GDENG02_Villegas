// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowmanPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ASnowmanPawn::ASnowmanPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->AutoPossessPlayer = EAutoReceiveInput::Player0; // automatically get player controls.

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object.
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	this->snowmanMeshComponent = (USceneComponent*)CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-750.0f, 0.0f, 500.0f));
	OurCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	this->snowmanMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASnowmanPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnowmanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->alongX)
	{
		FVector location = this->GetTransform().GetLocation();
		; location.X += this->movementX * DeltaTime * this->SPEED_MULTIPLIER;
		this->SetActorLocation(location);
	}

	if (this->alongY)
	{
		FVector location = this->GetTransform().GetLocation();
		; location.Y += this->movementY * DeltaTime * this->SPEED_MULTIPLIER;
		this->SetActorLocation(location);
	}
}

// Called to bind functionality to input
void ASnowmanPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	this->InputComponent->BindAxis(this->MOVE_X_KEY, this, &ASnowmanPawn::MoveX);
	this->InputComponent->BindAxis(this->MOVE_Y_KEY, this, &ASnowmanPawn::MoveY);
}

void ASnowmanPawn::MoveX(float axisValue)
{
	this->movementX = FMath::Clamp(axisValue, -1.0f, 1.0f);
	if (this->movementX != 0.0f)
	{
		this->alongX = true;
		this->alongY = false;
	}
}

void ASnowmanPawn::MoveY(float axisValue)
{
	this->movementY = FMath::Clamp(axisValue, -1.0f, 1.0f);
	if (this->movementY != 0.0f)
	{
		this->alongX = false;
		this->alongY = true;
	}
}

