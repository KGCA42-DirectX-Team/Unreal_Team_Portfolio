// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/BTS_HideStructureBase.h"

// Sets default values
ABTS_HideStructureBase::ABTS_HideStructureBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Hidable"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(Root);

	StructureMesh = CreateDefaultSubobject<UStaticMeshComponent>("StructureMesh");
	StructureMesh->SetupAttachment(Root);


}

// Called when the game starts or when spawned
void ABTS_HideStructureBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABTS_HideStructureBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

