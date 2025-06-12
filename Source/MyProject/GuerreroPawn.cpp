// Fill out your copyright notice in the Description page of Project Settings.


#include "GuerreroPawn.h"

#include "EnemyMainBuild.h"
#include "NavigationSystem.h"
#include "WarriorBuild.h"

// Sets default values
AGuerreroPawn::AGuerreroPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGuerreroPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGuerreroPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGuerreroPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AGuerreroPawn::PrepareToAttack(AActor* Target)
{
	TargetToAttack = Target;

	if (!TargetToAttack)
	{
		UE_LOG(LogTemp, Warning, TEXT("No hay objetivo para atacar"));
		return;
	}


	UE_LOG(LogTemp, Warning, TEXT("Moviéndose hacia el objetivo para atacar: %s"), *TargetToAttack->GetName());
	INavegateInterface::Execute_MoveToLocation(this, TargetToAttack->GetActorLocation());

	GetWorld()->GetTimerManager().SetTimer(
		AttackCheckTimerHandle, this, &AGuerreroPawn::StartAttackIfInRange, 0.5f, true
	);
}


void AGuerreroPawn::PerformAttack()
{
	if (AttackMontage && SkeletMesh)
	{
		UE_LOG(LogTemp,Warning,TEXT(" Anim agregada"));
		UAnimInstance* AnimInstance = SkeletMesh->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(AttackMontage);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT(" no hay montageAnim "));
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("No hay Anim"));
	}
	if (!IsValid(TargetToAttack))
	{
		return;
	}

	if (AEnemyMainBuild* Build = Cast<AEnemyMainBuild>(TargetToAttack))
	{
		Build->Damage(AttackDamage);
	}
}

void AGuerreroPawn::StartAttackIfInRange()
{
	if (!IsValid(TargetToAttack))
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackCheckTimerHandle);
		return;
	}

	float Distance = FVector::Dist(GetActorLocation(), TargetToAttack->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Dist to build: %f"), Distance);
	UE_LOG(LogTemp, Warning, TEXT("Attack RANGE: %f"), AttackRange);

	if (Distance <= AttackRange)
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackCheckTimerHandle);

		
		GetWorld()->GetTimerManager().SetTimer(AttackCheckTimerHandle, this, &AGuerreroPawn::PerformAttack,
		                                       AttackInterval, true);
	}
}

void AGuerreroPawn::StopAttacking()
{
	if (!TargetToAttack) return;

	float Distance = FVector::Dist(GetActorLocation(), TargetToAttack->GetActorLocation());

	if (Distance <= AttackRange)
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackCheckTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(AttackCheckTimerHandle, this, &AGuerreroPawn::PerformAttack,
		                                       AttackInterval, true);
	}
}
