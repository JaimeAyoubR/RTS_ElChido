// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMainBuild.h"
#include "GameManager.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

AEnemyMainBuild::AEnemyMainBuild()
{
	Tags.Add(FName("Edificio"));
	Tags.Add(FName("Enemigo"));
	MaxtHealth = 200;
	CurrentHealth = MaxtHealth;
	EnemyHealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthBar"));
	EnemyHealthBar->SetupAttachment(RootComponent);
	EnemyHealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	EnemyHealthBar->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
	EnemyHealthBar->SetWidgetClass(HealthBarWidgetClass);
}

void AEnemyMainBuild::Damage(int32 Damage)
{
	CurrentHealth -= Damage;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxtHealth);

	if (EnemyHealthBar && EnemyHealthBar->GetUserWidgetObject())
	{
		UUserWidget* Widget = EnemyHealthBar->GetUserWidgetObject();
		if (Widget)
		{
			UProgressBar* HealthBar = Cast<UProgressBar>(Widget->GetWidgetFromName(TEXT("HealthBar")));
			if (HealthBar)
			{
				if (EnemyHealthBar)
				{
					EnemyHealthBar->SetVisibility(true);
					EnemyHealthBar->SetHiddenInGame(false); // por si está oculto en juego
				}
				HealthBar->SetPercent(CurrentHealth / (float)MaxtHealth);
				UE_LOG(LogTemp, Warning, TEXT("Barra de vida actualizada"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No hay barra"));
	}

	if (CurrentHealth <= 0)
	{
		Destroy();
	}
}

void AEnemyMainBuild::BeginPlay()
{
	Super::BeginPlay();
	if (HealthBarWidgetClass)
	{
		EnemyHealthBar->SetWidgetClass(HealthBarWidgetClass);
		EnemyHealthBar->InitWidget();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HealthBarWidgetClass no está asignado"));
	}
}

void AEnemyMainBuild::Destroyed()
{
	Super::Destroyed();


	UE_LOG(LogTemp, Warning, TEXT("Edificio enemigo destruido"));

	if (AGameManager* GM = Cast<AGameManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass())))
	{
		GM->HandleVictory();
	}
}
