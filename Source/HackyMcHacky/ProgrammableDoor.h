// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		bool locked;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* doorFrameComponent;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* doorComponent;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Interact();
	virtual void Interact_Implementation() override;
};
