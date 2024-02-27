// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/BTS_MapActor.h"

// Sets default values
ABTS_MapActor::ABTS_MapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABTS_MapActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABTS_MapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

