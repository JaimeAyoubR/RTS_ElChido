// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "Kismet/GameplayStatics.h"

void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ABasePawn* Villager = nullptr;
	Villager = Cast<ABasePawn>(Villager);
	if (Villager && !Villager->IsBeingChased())
	{
		UE_LOG(LogTemp, Warning, TEXT("Persiguiendo de nuevo"));
		Villager->StartEscape(this);
	}
	if (!CurrentTarget || FVector::Dist(GetActorLocation(), CurrentTarget->GetActorLocation()) > DetectionRadius)
	{
		CurrentTarget = GetCloserVillager();
	}

	if (CurrentTarget)
	{
		float Distance = FVector::Dist(GetActorLocation(), CurrentTarget->GetActorLocation());

		if (Distance > StopFollowDistance)
		{
			FVector Direction = (CurrentTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			AddActorWorldOffset(Direction * MoveSpeed * DeltaTime, true);
		}
		else
		{
			//Aqui podria agregar que atacara el enemigo al aldeano... o no jaja
		}
	}
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
}

AActor* AEnemyPawn::GetCloserVillager()
{
	TArray<AActor*> FoundVillagers;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Villager"), FoundVillagers);

	AActor* ClosestVillager = nullptr;
	float ClosestDistance = DetectionRadius;

	for (AActor* Villager : FoundVillagers)
	{
		float Dist = FVector::Dist(GetActorLocation(), Villager->GetActorLocation());
		//UE_LOG(LogTemp, Warning, TEXT("Dist to villager: %f"), Dist);
		//UE_LOG(LogTemp, Warning, TEXT("Distance menor: %f"), ClosestDistance);
		if (Dist < ClosestDistance)
		{
			ClosestDistance = Dist;
			ClosestVillager = Villager;
		}
	}
	return ClosestVillager;
}
