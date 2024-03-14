// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemUI/BTS_ItemUI.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ABTS_ItemUI::ABTS_ItemUI()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemMesh"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

	SetRootComponent(Root);
	ItemMesh->SetupAttachment(Root);
	Sphere->SetupAttachment(ItemMesh);
}

void ABTS_ItemUI::BeginPlay()
{
	Super::BeginPlay();
	
}

