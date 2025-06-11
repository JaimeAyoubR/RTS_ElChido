// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Resources.generated.h"


UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Food,
	Stone,
	Water,
	Wood
};

UCLASS()
class MYPROJECT_API AResources : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AResources();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame


	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EResourceType ResourceType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ResourceAmount = 100;
	

	UFUNCTION(BlueprintNativeEvent)
	void Collect();
	virtual void Collect_Implementation();
};
