// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <vector>

#define PROPERTY_TYPE_BOOL 0
#define PROPERTY_TYPE_FLOAT 1
#define PROPERTY_TYPE_INT 2
#define PROPERTY_TYPE_STRING 3

struct Property
{
	FText name;
	void* reference;
	int propertyType;

	Property(FText name, void* propertyReference, int propertyType);
};

/**
 * 
 */
class HACKYMCHACKY_API ProgrammableObject
{
public:
	ProgrammableObject();
	~ProgrammableObject();

	void registerProperty(FText name, void* propertyReference, int propertyType);
	void propertyChanged(FText name);

	// TODO: complicated UI stuff here

protected:
	std::vector<Property> properties;
};
