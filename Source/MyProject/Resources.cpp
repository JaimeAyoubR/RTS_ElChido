// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources.h"

// Sets default values
AResources::AResources()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly );
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AResources::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AResources::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AResources::Collect_Implementation()
{

	Destroy();
}

