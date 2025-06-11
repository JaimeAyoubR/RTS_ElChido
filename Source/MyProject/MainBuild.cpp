// Fill out your copyright notice in the Description page of Project Settings.


#include "MainBuild.h"

#include "GameManager.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBox.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainBuild::AMainBuild()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	SelectIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectIndicator"));
	SelectIndicator->SetupAttachment(RootComponent);
	SelectIndicator->SetHiddenInGame(true);
	SelectIndicator->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	


	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainBuild::BeginPlay()
{
	Super::BeginPlay();

	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (!CurrentWidget)
		{
			UE_LOG(LogTemp, Error, TEXT("No se pudo crear CurrentWidget en %s"), *GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HUDWidgetClass no está asignado en %s"), *GetName());
	}
}

// Called every frame
void AMainBuild::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("isSelected? : %S" ), isSelected? "true" : "false");
}

void AMainBuild::SelectActor_Implementation(const bool select)
{
	isSelected = select;
	SelectIndicator->SetHiddenInGame(!isSelected);
	if (CurrentWidget)
	{
		if (isSelected)
		{
			if (!CurrentWidget->IsInViewport())
			{
				CurrentWidget->AddToViewport();
			}
		}
		else
		{
			CurrentWidget->RemoveFromParent();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No existe el HUD" ));
	}
	if (select)
	{
		AGameManager* GM = Cast<AGameManager>(
			UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
		if (GM)
		{
			GM->EdificioSeleccionado = this;
		}
	}
}

void AMainBuild::SpawnVillager()
{
	// if (SpawnableActor)
	// {
	// 	FVector SpawnLocation = GetActorLocation() + FVector(200, 0, 0);
	// 	FRotator SpawnRotation = GetActorRotation();
	//
	// 	ABasePawn* SpawnVill = GetWorld()->SpawnActor<ABasePawn>(SpawnLocation, SpawnRotation);
	//
	// 	if (SpawnVill)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("SpawnVillager"));
	// 	}
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("PawnToSpawnClass no está asignado"));
	// }
}
