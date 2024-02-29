// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemUI/BTS_ItemObject.h"
#include "Materials/MaterialInterface.h"

FIntPoint UBTS_ItemObject::GetDimensions()
{
	if (Rotated)
	{
		int32 temp = Dimensions.X;
		Dimensions.X = Dimensions.Y;
		Dimensions.Y = temp;
	}

	return Dimensions;
}

UMaterialInterface* UBTS_ItemObject::GetIcon()
{
	if (Rotated)
	{
		return IconRotated;
	}

	return Icon;
}

void UBTS_ItemObject::Rotate()
{
	Rotated = !Rotated;
}

bool UBTS_ItemObject::IsRotate()
{
	return Rotated;
}

TSubclassOf<ABTS_ItemUI> UBTS_ItemObject::GetItemClass()
{
	return ItemClass;
}
