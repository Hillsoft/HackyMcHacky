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
		doorFrameComponent->SetMobility(EComponentMobility::Static);
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

	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAssett(TEXT("/Game/Animations/DoorRotationAnim"));
	if (CurveAssett.Succeeded())
	{
		AnimCurve = CurveAssett.Object;
	}

	AnimLength = 0.7;
	Locked = true;
}

// Called when the game starts or when spawned
void AProgrammableDoor::BeginPlay()
{
	Super::BeginPlay();
	
	DoorAnim.SetTimelineLength(AnimLength);

	FOnTimelineEvent TimelineFinished = FOnTimelineEvent();
	TimelineFinished.BindDynamic(this, &AProgrammableDoor::AnimFinished);
	
	DoorAnim.SetTimelineFinishedFunc(TimelineFinished);

	FOnTimelineFloat TimelineTick = FOnTimelineFloat();
	TimelineTick.BindUFunction(this, "AnimProgress");

	DoorAnim.AddInterpFloat(AnimCurve, TimelineTick, FName("Percentage_Complete"));
}

// Called every frame
void AProgrammableDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorAnim.TickTimeline(DeltaTime);
}

void AProgrammableDoor::Interact_Implementation()
{
	if (!Locked)
	{
		if (IsAnimating)
		{
			if (IsOpen)
			{
				DoorAnim.Reverse();
			}
			else
			{
				DoorAnim.Play();
			}
		}
		else
		{
			if (!IsOpen)
			{
				DoorAnim.PlayFromStart();
			}
			else
			{
				DoorAnim.ReverseFromEnd();
			}
		}

		IsOpen = !IsOpen;
		IsAnimating = true;
	}
}

void AProgrammableDoor::AnimProgress(float AnimValue)
{
	UE_LOG(LogTemp, Display, TEXT("Door progress: %f"), AnimValue);
	doorComponent->SetRelativeRotation(FRotator(0.0f, AnimValue, 0.0f));
}

void AProgrammableDoor::AnimFinished()
{
	IsAnimating = false;
}
