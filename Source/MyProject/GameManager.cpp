// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "MainBuild.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameManager::AGameManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	numOfFood = 50;
	numOfStone = 100;
	numOfWater = 200;
	numOfWood = 3000;
	if (numOfWater == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("The number of water is 0"));
	}
	
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay - Agua: %d"), numOfWater);
	if (ResourceWidgetClass)
	{
		ResourceWidget = CreateWidget<UResourceWidget>(GetWorld(), ResourceWidgetClass);
		if (ResourceWidget)
		{
			ResourceWidget->AddToViewport();
			ResourceWidget->UpdateResources(numOfFood, numOfStone, numOfWater, numOfWood);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ResourceWidget is null"));
	}
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
	if (ResourceWidget)
		ResourceWidget->UpdateResources(numOfFood, numOfStone, numOfWater, numOfWood);
}

void AGameManager::AddStone(int Amount)
{
	numOfStone += Amount;
	UE_LOG(LogTemp, Log, TEXT("Piedra total: %d"), numOfStone);
	if (ResourceWidget)
		ResourceWidget->UpdateResources(numOfFood, numOfStone, numOfWater, numOfWood);;
}

void AGameManager::AddWater(int Amount)
{
	numOfWater += Amount;
	UE_LOG(LogTemp, Log, TEXT("Agua total: %d"), numOfWater);
	if (ResourceWidget)
		ResourceWidget->UpdateResources(numOfFood, numOfStone, numOfWater, numOfWood);
}

void AGameManager::AddWood(int Amount)
{
	numOfWood += Amount;
	UE_LOG(LogTemp, Log, TEXT("Madera total: %d"), numOfWood);
	if (ResourceWidget)
		ResourceWidget->UpdateResources(numOfFood, numOfStone, numOfWater, numOfWood);
}
