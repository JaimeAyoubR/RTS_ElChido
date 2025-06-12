// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMainBuild.h"
#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

AEnemyMainBuild::AEnemyMainBuild()
{
	Tags.Add(FName("Edificio"));
	Tags.Add(FName("Enemigo"));
	MaxtHealth = 200;
	CurrentHealth = MaxtHealth;
}

void AEnemyMainBuild::Damage(int32 Damage)
{
	CurrentHealth -= Damage;
	//UE_LOG(LogTemp, Warning, TEXT("Edificio %s recibió daño. Vida restante: %I64d"), *GetName(), CurrentHealth);
	UE_LOG(LogTemp,Warning,TEXT("Tomando Daño"));
	if (CurrentHealth <= 0)
	{
		Destroy();
	}
}

void AEnemyMainBuild::BeginPlay()
{
	Super::BeginPlay();
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
