// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainBuild.h"
#include "GameFramework/Actor.h"
#include "WarriorBuild.generated.h"

UCLASS()
class MYPROJECT_API AWarriorBuild : public AMainBuild
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarriorBuild();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cost")
	int32 CostFood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cost")
	int32 CostStone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cost")
	int32 CostWater;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cost")
	int32 CostWood;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
