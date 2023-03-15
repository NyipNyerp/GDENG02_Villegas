// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabBehavior.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
//#include "GrabberBehavior.h"
#include "DrawDebugHelpers.h"

#define out

// Sets default values for this component's properties
UGrabBehavior::UGrabBehavior()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabBehavior::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UInputComponent* inputComponent = this->GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent != nullptr)
	{
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabBehavior::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabBehavior::Release);
		inputComponent->BindAction("Throw", IE_Pressed, this, &UGrabBehavior::Throw);
	}
	else UE_LOG(LogTemp, Warning, TEXT("Input component is missing. Try possessing a pawn"));
}


// Called every frame
void UGrabBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (this->hasGrabbed)
	{
		FVector location;
		FRotator rotation;

		this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out location, out rotation);
		FVector lineTraceEnd = location + rotation.Vector() * this->REACH;

		if (this->grabbedActor != nullptr)
		{
			if (this->physicsHandle != nullptr)
			{
				this->physicsHandle->SetTargetLocation(lineTraceEnd);
			}
			else
			{
				//FVector grabbedLoc = this->grabbedActor->GetActorLocation();
				FVector grabbedLoc = lineTraceEnd;
				grabbedActor->SetActorLocation(grabbedLoc);
			}
		}
	}	
	
}

void UGrabBehavior::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab function called by %s"), *this->GetOwner()->FindComponentByClass<UGrabBehavior>()->GetName());

	FVector location;
	FRotator rotation;

	this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out location, out rotation);
	FVector lineTraceEnd = location + rotation.Vector() * this->REACH;
	DrawDebugLine(this->GetWorld(), location, lineTraceEnd, FColor::Blue, false, 1.0, 0, 5.0f);

	FHitResult hitResult;
	FCollisionQueryParams traceParams(FName(TEXT("traceQuery")), false, this->GetOwner());
	FCollisionObjectQueryParams objectTypeParams(ECollisionChannel::ECC_PhysicsBody);
	this->GetWorld()->LineTraceSingleByObjectType(out hitResult, location, lineTraceEnd, objectTypeParams, traceParams);

	this->grabbedActor = hitResult.GetActor();
	if (this->grabbedActor != nullptr)
	{
		this->hasGrabbed = true;
		this->primitiveComp = hitResult.GetComponent();
		UE_LOG(LogTemp, Warning, TEXT("Grabbed object: %s %s"), *this->grabbedActor->GetName(), *this->primitiveComp->GetName());

		this->physicsHandle = this->grabbedActor->FindComponentByClass<UPhysicsHandleComponent>();
		if (this->physicsHandle != nullptr)
		{
			this->physicsHandle->GrabComponentAtLocation(this->primitiveComp, EName::None, lineTraceEnd);
		}
	}
}

void UGrabBehavior::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release function called by %s"), *this->GetOwner()->FindComponentByClass<UGrabBehavior>()->GetName());
	this->hasGrabbed = false;
	this->grabbedActor = nullptr;

	if (this->physicsHandle != nullptr)
	{
		this->physicsHandle->ReleaseComponent();
	}
}

void UGrabBehavior::Throw()
{
	UE_LOG(LogTemp, Warning, TEXT("Throw function called by %s"), *this->GetOwner()->FindComponentByClass<UGrabBehavior>()->GetName());

}

