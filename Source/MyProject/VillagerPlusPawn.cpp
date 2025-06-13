// Fill out your copyright notice in the Description page of Project Settings.


#include "VillagerPlusPawn.h"

AVillagerPlusPawn::AVillagerPlusPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 600;
}

void AVillagerPlusPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AVillagerPlusPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVillagerPlusPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
