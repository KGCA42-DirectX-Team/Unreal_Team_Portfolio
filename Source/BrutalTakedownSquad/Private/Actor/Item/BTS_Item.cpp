// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/BTS_Item.h"

// Sets default values
ABTS_Item::ABTS_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABTS_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABTS_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

