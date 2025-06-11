// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class MYPROJECT_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int numOfFood ;
	UPROPERTY(EditAnywhere)
	int numOfStone;
	UPROPERTY(EditAnywhere)
	int numOfWater;
	UPROPERTY(EditAnywhere)
	int numOfWood;

	
	UPROPERTY(EditAnywhere)
	int costOfFVillager = 50;
	

	UFUNCTION(BlueprintCallable)
	void SpawnPawn(TSubclassOf<ABasePawn> VillagerClass);
	
	UPROPERTY(BlueprintReadWrite)
	class AMainBuild* EdificioSeleccionado;

	UFUNCTION(BlueprintCallable)
	void AddFood(int Amount);

	UFUNCTION(BlueprintCallable)
	void AddStone(int Amount);

	UFUNCTION(BlueprintCallable)
	void AddWater(int Amount);

	UFUNCTION(BlueprintCallable)
	void AddWood(int Amount);


};
