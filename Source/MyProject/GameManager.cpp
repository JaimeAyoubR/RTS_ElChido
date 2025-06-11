// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "MainBuild.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameManager::AGameManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	numOfFood = 500;
	numOfStone = 500;
	numOfWater = 500;
	numOfWood = 100;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGameManager::SpawnPawn(TSubclassOf<ABasePawn> VillagerClass)
{
	if (!VillagerClass || !EdificioSeleccionado) return;

	if (numOfFood >= costOfFVillager)
	{
		
		FVector SpawnLocation = EdificioSeleccionado->GetActorLocation() + FVector(-200.f, 200.f, 0.f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		ABasePawn* SpawnedPawn = GetWorld()->SpawnActor<ABasePawn>(VillagerClass, SpawnLocation, SpawnRotation);
		if (SpawnedPawn)
		{
			numOfFood -= costOfFVillager;
			UE_LOG(LogTemp, Warning, TEXT("Pawn creado junto al edificio: %s"), *SpawnedPawn->GetName());
			UE_LOG(LogTemp, Warning, TEXT("Recursos restantes: %i"), numOfFood);
		
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No se tienen suficientes recursos" ));
	}
}

void AGameManager::AddFood(int Amount)
{
	numOfFood += Amount;
	UE_LOG(LogTemp, Log, TEXT("Comida total: %d"), numOfFood);
}

void AGameManager::AddStone(int Amount)
{
	numOfStone += Amount;
	UE_LOG(LogTemp, Log, TEXT("Piedra total: %d"), numOfStone);
}

void AGameManager::AddWater(int Amount)
{
	numOfWater += Amount;
	UE_LOG(LogTemp, Log, TEXT("Agua total: %d"), numOfWater);
}

void AGameManager::AddWood(int Amount)
{
	numOfWood += Amount;
	UE_LOG(LogTemp, Log, TEXT("Madera total: %d"), numOfWood);
}
