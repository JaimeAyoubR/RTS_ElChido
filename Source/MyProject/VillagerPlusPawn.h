// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "VillagerPlusPawn.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AVillagerPlusPawn : public ABasePawn
{
	GENERATED_BODY()
	AVillagerPlusPawn();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

protected:
};
