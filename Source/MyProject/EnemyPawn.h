// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemyPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:

	UPROPERTY(EditAnywhere, Category="Movimiento")
	float MoveSpeede = 400.0f; 

	AActor* GetCloserVillager();
	AActor* CurrentTarget;

	UPROPERTY(EditAnywhere)
	float DetectionRadius = 1000.0f;

	UPROPERTY(EditAnywhere)
	float StopFollowDistance = 300.0f;
	
};
