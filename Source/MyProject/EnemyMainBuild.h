// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainBuild.h"
#include "EnemyMainBuild.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemyMainBuild : public AMainBuild
{
	GENERATED_BODY()

public:
	AEnemyMainBuild();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxtHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentHealth;

	UFUNCTION()
	void Damage(int32 Damage);
protected:
	virtual void BeginPlay() override;

public:
	virtual void Destroyed() override;
};
