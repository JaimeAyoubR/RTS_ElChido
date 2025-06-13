// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "GameManager.h"


// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Creamos la capsula
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	//FVector ScalaNueva = FVector(1.0f, 1.0f, 90.0f);

	//Capsule->SetWorldScale3D(ScalaNueva);
	RootComponent = Capsule;
	Capsule->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	//Creamos el Esqueleto
	SkeletMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletMesh"));
	SkeletMesh->SetupAttachment(Capsule);
	//SkeletMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -Capsule->GetUnscaledCapsuleHalfHeight()));

	//Creamos el movimiento
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	//Creamos el Indicador
	IndicatorSelect = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IndicatorSelect"));
	IndicatorSelect->SetupAttachment(RootComponent);
	IndicatorSelect->SetHiddenInGame(true);
	IndicatorSelect->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AGameManager> It(GetWorld()); It; ++It)
	{
		GameManager = *It;
		break; // Asumimos solo un GameManager
	}
}

void ABasePawn::Move()
{
	//UE_LOG(LogTemp, Warning, TEXT("IsMoving"));
	if (ResourceToCollect)
	{
		float DistToResource = FVector::Dist(GetActorLocation(), ResourceToCollect->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("Dist to resource: %f"), DistToResource);
		UE_LOG(LogTemp, Warning, TEXT("Dist OFFSET: %f"), DistanceOffsetResource);
		if (DistToResource < DistanceOffsetResource && ResourceToCollect)
		{
			if (GameManager)
			{
				switch (ResourceToCollect->ResourceType)
				{
				case EResourceType::Food:
					GameManager->AddFood(ResourceToCollect->ResourceAmount);
					break;
				case EResourceType::Stone:
					GameManager->AddStone(ResourceToCollect->ResourceAmount);
					break;
				case EResourceType::Water:
					GameManager->AddWater(ResourceToCollect->ResourceAmount);
					break;
				case EResourceType::Wood:
					GameManager->AddWood(ResourceToCollect->ResourceAmount);
					break;
				}
			}

			ResourceToCollect->Collect();
			ResourceToCollect = nullptr;
			bIsMoving = false;
			return;
		}
	}

	if (!bIsMoving)
	{
		return;
	}

	FVector MoveDirection = (MoveTargetLocation - GetActorLocation());
	float Distance = MoveDirection.Size();

	if (Distance < DistanceOffsetResource)
	{
		bIsMoving = false;


		return;
	}

	MoveDirection.Normalize();
	FRotator RotateDirection = UKismetMathLibrary::MakeRotFromX(MoveDirection);
	RotateDirection.Pitch = 0;
	RotateDirection.Roll = 0;
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), RotateDirection, GetWorld()->GetDeltaSeconds(),
	                                        RotationSpeed);
	SetActorRotation(NewRotation);

	AddMovementInput(MoveDirection, 1.0f);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsBeingChased && EnemyActor)
	{
		//UE_LOG(LogTemp,Warning,TEXT("ME PERSIGUEEEN AAAAAAH"));
		FVector EscapeDirection = (GetActorLocation() - EnemyActor->GetActorLocation()).GetSafeNormal();
		AddActorWorldOffset(EscapeDirection * EscapeSpeed * GetWorld()->GetDeltaSeconds(), true);

		float Distance = FVector::Dist(GetActorLocation(), EnemyActor->GetActorLocation());
		if (Distance > EscapeStopDistance) 
		{
			bIsBeingChased = false;
			EnemyActor = nullptr;
		}
	}
	if (!bIsBeingChased)
	{
		//UE_LOG(LogTemp,Warning,TEXT("NO hay enemy actor"));
	}


	Move();
	//UE_LOG(LogTemp, Warning, TEXT("Actor Location: %s"), *GetActorLocation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Mesh Relative Location: %s"), *SkeletMesh->GetRelativeLocation().ToString());
	//UE_LOG(LogTemp, Display, TEXT("4"));
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasePawn::SelectActorLocal(const bool isSelected)
{
	IndicatorSelect->SetHiddenInGame(!isSelected);
}

void ABasePawn::DeselectActor(const bool isSelected)
{
}

void ABasePawn::SelectActor_Implementation(const bool select)
{
	IndicatorSelect->SetHiddenInGame(!select);
}

void ABasePawn::MoveToLocation_Implementation(const FVector location)
{
	UE_LOG(LogTemp, Display, TEXT("Naveg"));
	MoveTargetLocation = location + FVector(0, 0, GetDefaultHalfHeight());
	bIsMoving = true;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->MoveToLocation(location, DistanceOffset);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveToLocation failed: AIController is nullptr"));
	}
}

void ABasePawn::GoCollectResource(AResources* Resource)
{
	if (!Resource)
	{
		UE_LOG(LogTemp, Warning, TEXT("GoCollectResource called with nullptr"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("GoCollectResource called with resource: %s"), *Resource->GetName());

	MoveTargetLocation = Resource->GetActorLocation();
	bIsMoving = true;
	ResourceToCollect = Resource;
}

void ABasePawn::StartEscape(AActor* InChaser)
{
	EnemyActor = InChaser;
	bIsBeingChased = true;
}
