// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavegateInterface.h"
#include "Resources.h"
//#include "GameManager.h"
#include "SelectableInterface.h"
#include "GameFramework/Pawn.h"

#include "BasePawn.generated.h" //Todos los includes van antes que este


class UCapsuleComponent;

class UFloatingPawnMovement;

class USkeletalMeshComponent;

class UStaticMeshComponent;

UCLASS()
class MYPROJECT_API ABasePawn : public APawn, public ISelectableInterface, public INavegateInterface
{
	GENERATED_BODY()

private:
	//Capsule Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> Capsule;


	//Floating PawnMovement Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

	//Indicador si esta seleccionado
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> IndicatorSelect;

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	//Skeleton Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	int Level;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	int Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	FString ClassName;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move();

	FVector MoveTargetLocation = FVector::ZeroVector;
	bool bIsMoving = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float DistanceOffset = 50.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float RotationSpeed = 5.0f;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DistanceOffsetResource = 350.f; 

	UPROPERTY()
	AResources* ResourceToCollect = nullptr;

	UPROPERTY()
	class AGameManager* GameManager;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MoveSpeed = 500.0f;
	
	UFUNCTION()
	void SelectActorLocal(const bool isSelected);

	UFUNCTION()
	void DeselectActor(const bool isSelected);

	void SelectActor_Implementation(const bool select) override;

	void MoveToLocation_Implementation(const FVector location) override;

	UFUNCTION()
	void GoCollectResource(AResources* Resource);

	UPROPERTY(EditAnywhere, Category = "Escape")
	AActor* MainBuild; 

	UPROPERTY(EditAnywhere, Category = "Escape")
	float EscapeSpeed = 500.0f;

	bool bIsBeingChased = false;

	void StartEscape(AActor* InChaser);

	AActor* EnemyActor = nullptr;

	UPROPERTY(EditAnywhere)
	float EscapeStopDistance = 500.f;

	UFUNCTION(BlueprintCallable)
	bool IsBeingChased() const { return bIsBeingChased; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Costos")
	int32 CostFood = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Costos")
	int32 CostStone = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Costos")
	int32 CostWater = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Costos")
	int32 CostWood = 0;

	
};
