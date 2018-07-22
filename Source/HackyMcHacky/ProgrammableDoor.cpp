// Fill out your copyright notice in the Description page of Project Settings.

#include "ProgrammableDoor.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values
AProgrammableDoor::AProgrammableDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> frameAssett(TEXT("/Game/StarterContent/Props/SM_DoorFrame"));
	if (frameAssett.Succeeded())
	{
		doorFrameComponent->SetStaticMesh(frameAssett.Object);
		doorFrameComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	doorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> doorAssett(TEXT("/Game/StarterContent/Props/SM_Door"));
	if (doorAssett.Succeeded())
	{
		doorComponent->SetStaticMesh(doorAssett.Object);
		doorComponent->SetRelativeLocation(FVector(0.0f, 45.0f, 0.0f));
	}

	doorComponent->SetupAttachment(doorFrameComponent);

	RootComponent = doorFrameComponent;
}

// Called when the game starts or when spawned
void AProgrammableDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProgrammableDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

