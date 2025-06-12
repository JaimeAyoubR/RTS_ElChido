// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "GameFramework/Pawn.h"
#include "GuerreroPawn.generated.h"

UCLASS()
class MYPROJECT_API AGuerreroPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGuerreroPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere)
	float AttackRange = 1000.0f;

	UPROPERTY(EditAnywhere)
	float AttackInterval = 1.0f;

	UPROPERTY(EditAnywhere)
	float AttackDamage = 10.0f;

	UPROPERTY()
	AActor* TargetToAttack = nullptr;

	FTimerHandle AttackCheckTimerHandle;

	void PrepareToAttack(AActor* Target);

	void PerformAttack();

	void StartAttackIfInRange();

	void StopAttacking();
};
