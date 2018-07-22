// Fill out your copyright notice in the Description page of Project Settings.

#include "ProgrammableObject.h"

Property::Property(FText name, void* propertyReference, int propertyType)
	: name(name), reference(propertyReference), propertyType(propertyType)
{
}

ProgrammableObject::ProgrammableObject()
{
}

ProgrammableObject::~ProgrammableObject()
{
}

void ProgrammableObject::registerProperty(FText name, void* propertyReference, int propertyType)
{
	properties.push_back(Property(name, propertyReference, propertyType));
}

void ProgrammableObject::propertyChanged(FText name)
{
}
