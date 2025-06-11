// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectableInterface.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "SelectableInterface.h"
#include "BasePawn.h"
#include "MainBuild.generated.h"

UCLASS()
class MYPROJECT_API AMainBuild : public AActor, public ISelectableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainBuild();

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Building,meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	//Select Indicator
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Building,meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SelectIndicator;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Build)
	int health;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Build)
	bool isSelected = false;

	void SelectActor_Implementation(const bool select) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UUserWidget> BuildingHUDClass;

	UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere,Category="Spawn")
	TSubclassOf<ABasePawn> SpawnableActor;


	UFUNCTION(BlueprintCallable, Category="Spawning")
	void SpawnVillager();

};
