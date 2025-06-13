// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "MainBuild.h"
#include "Engine/OverlapResult.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameManager::AGameManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	numOfFood = 500;
	numOfStone = 500;
	numOfWater = 500;
	numOfWood = 5000;
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

void AGameManager::ShowDefeatWidget()
{
	if (DefeatWidgetClass)
	{
		UUserWidget* DefeatWidget = CreateWidget<UUserWidget>(GetWorld(), DefeatWidgetClass);
		if (DefeatWidget)
		{
			DefeatWidget->AddToViewport();

			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				PC->SetShowMouseCursor(true);
				PC->SetInputMode(FInputModeUIOnly());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DefeatWidgetClass no está asignado."));
	}
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsInBuildMode && BuildPreview)
	{
		FHitResult Hit;
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC && PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			FVector Location = Hit.Location;
			BuildPreview->SetActorLocation(Location);
		}
	}

	if (!bHasDefeatWidgetShown)
	{
		ElapsedTime += DeltaTime;
		if (ElapsedTime >= 300.0f)  // 5 minutos = 300 segundos
		{
			ShowDefeatWidget();
			bHasDefeatWidgetShown = true;
		}
	}

	if (bIsInBuildMode && BuildPreview)
	{
		FHitResult Hit;
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC && PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			FVector Location = Hit.Location;
			BuildPreview->SetActorLocation(Location);
		}
	}
}

void AGameManager::HandleVictory()
{
	UE_LOG(LogTemp, Warning, TEXT("Victoria"));
	if (VictoryWidgetClass)
	{
		UUserWidget* VictoryWidget = CreateWidget<UUserWidget>(GetWorld(), VictoryWidgetClass);
		if (VictoryWidget)
		{
			VictoryWidget->AddToViewport();

			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				PC->SetShowMouseCursor(true);
				PC->SetInputMode(FInputModeUIOnly());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No se encontro el widget"));
	}
}

void AGameManager::SpawnPawn(TSubclassOf<ABasePawn> VillagerClass)
{
	ABasePawn* DefaultUnit = Cast<ABasePawn>(VillagerClass->GetDefaultObject());
	if (!DefaultUnit) return;

	if (numOfFood >= DefaultUnit->CostFood &&
		numOfStone >= DefaultUnit->CostStone &&
		numOfWater >= DefaultUnit->CostWater &&
		numOfWood >= DefaultUnit->CostWood)
	{
		FVector SpawnLocation = EdificioSeleccionado->GetActorLocation() + FVector(-200.f, 200.f, 0.f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		ABasePawn* SpawnedPawn = GetWorld()->SpawnActor<ABasePawn>(VillagerClass, SpawnLocation, SpawnRotation);
		if (SpawnedPawn)
		{
			numOfFood -= DefaultUnit->CostFood;
			numOfStone -= DefaultUnit->CostStone;
			numOfWater -= DefaultUnit->CostWater;
			numOfWood -= DefaultUnit->CostWood;

			if (ResourceWidget)
				ResourceWidget->UpdateResources(numOfFood, numOfStone, numOfWater, numOfWood);

			UE_LOG(LogTemp, Warning, TEXT("Spawned: %s"), *SpawnedPawn->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Recursos insuficientes para spawnear unidad."));
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

void AGameManager::PlaceBuilding()
{
	if (!bIsInBuildMode || !PendingBuildClass || !BuildPreview) return;

	FVector Location = BuildPreview->GetActorLocation();

	const AWarriorBuild* DefaultBuilding = Cast<AWarriorBuild>(PendingBuildClass->GetDefaultObject());
	if (!DefaultBuilding) return;

	FVector BoxExtent = DefaultBuilding->GetStaticMeshComponent()->Bounds.BoxExtent;
	FVector BoxCenter = Location + FVector(0, 0, BoxExtent.Z);
	FCollisionShape CollisionBox = FCollisionShape::MakeBox(BoxExtent);

	TArray<FOverlapResult> Overlaps;

	bool bIsOverlapping = GetWorld()->OverlapMultiByChannel(
		Overlaps,
		BoxCenter,
		FQuat::Identity,
		ECC_WorldStatic,
		CollisionBox
	);

	if (bIsOverlapping)
	{
		for (const FOverlapResult& Result : Overlaps)
		{
			if (AActor* HitActor = Result.GetActor())
			{
				if (HitActor->ActorHasTag("Suelo"))
				{
					UE_LOG(LogTemp, Warning, TEXT("Suelo detectado - ignorado"));
					continue; // Ignorar suelo y seguir revisando
				}

				// Si choca con cualquier otro actor que no sea suelo, bloquear construcción
				UE_LOG(LogTemp, Warning, TEXT("Colisionando con: %s"), *HitActor->GetName());
				UE_LOG(LogTemp, Warning, TEXT("No se puede construir aquí. Ya hay algo."));
				return;
			}
		}
	}

	if (numOfFood >= DefaultBuilding->CostFood &&
		numOfStone >= DefaultBuilding->CostStone &&
		numOfWater >= DefaultBuilding->CostWater &&
		numOfWood >= DefaultBuilding->CostWood)
	{
		numOfFood -= DefaultBuilding->CostFood;
		numOfStone -= DefaultBuilding->CostStone;
		numOfWater -= DefaultBuilding->CostWater;
		numOfWood -= DefaultBuilding->CostWood;


		GetWorld()->SpawnActor<AWarriorBuild>(PendingBuildClass, Location, FRotator::ZeroRotator);


		if (ResourceWidget)
			ResourceWidget->UpdateResources(numOfFood, numOfStone, numOfWater, numOfWood);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No hay suficientes recursos"));
	}


	BuildPreview->Destroy();
	BuildPreview = nullptr;
	bIsInBuildMode = false;
	PendingBuildClass = nullptr;
}

void AGameManager::EnterBuildMode(TSubclassOf<AWarriorBuild> BuildingClass)
{
	if (bIsInBuildMode || !BuildingClass) return;

	bIsInBuildMode = true;
	PendingBuildClass = BuildingClass;


	FVector SpawnLocation = FVector::ZeroVector;
	BuildPreview = GetWorld()->SpawnActor<AWarriorBuild>(BuildingClass, SpawnLocation, FRotator::ZeroRotator);

	if (BuildPreview)
	{
		BuildPreview->SetActorEnableCollision(false);
		BuildPreview->SetActorHiddenInGame(false);
	}
}
