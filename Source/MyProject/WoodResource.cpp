// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodResource.h"

// Sets default values
AWoodResource::AWoodResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWoodResource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWoodResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWoodResource::Collect_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Colecting AResources"));
	Super::Collect_Implementation();
}

