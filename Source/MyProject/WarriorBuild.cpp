// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorBuild.h"

// Sets default values
AWarriorBuild::AWarriorBuild()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CostFood = 100;
	CostStone = 100;
	CostWater = 100;
	CostWood = 100;



}

// Called when the game starts or when spawned
void AWarriorBuild::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarriorBuild::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

