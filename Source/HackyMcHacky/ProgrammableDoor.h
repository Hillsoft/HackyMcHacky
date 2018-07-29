// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "InteractableObject.h"
#include "ProgrammableDoor.generated.h"

UCLASS()
class HACKYMCHACKY_API AProgrammableDoor : public AActor, public IInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProgrammableDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsOpen = false;
	bool IsAnimating = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		bool Locked;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* doorFrameComponent;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* doorComponent;

	UPROPERTY(EditAnywhere)
		UCurveFloat* AnimCurve;

	UPROPERTY(EditAnywhere)
		float AnimLength;
	
	FTimeline DoorAnim;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Interact();
	virtual void Interact_Implementation() override;

	UFUNCTION()
		void AnimProgress(float AnimValue);

	UFUNCTION()
		void AnimFinished();
};
