// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "RTSHUD.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
class ABasePawn;
class ARTSHUD;
struct FInputActionValue;

UCLASS()

class MYPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> InputMappingContext;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	//Funcion para seleccionar un personaje o edificio
	void Select(const FInputActionValue& value);
	//Funcion para poder manejar a los personajes
	void CommandSelectedActors(const FInputActionValue& value);
	//Funciones para hacer una seleccion grande
	void StartSelect(const FInputActionValue& value);
	void OnGoingSelect(const FInputActionValue& value);
	void EndSelect(const FInputActionValue& value);
	void SelectMultipleActors();
	//Funciones para construir
	void EnterBuildMode();
	void PlaceBuilding(); 

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> SelectAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> CommandAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> BuildModeAction;

	UPROPERTY(EditAnywhere, Category = "Build System")
	TSubclassOf<class AWarriorBuild> BuildingToPlaceClass;

	


	UPROPERTY()
	TObjectPtr<AActor> HitActor;
	UPROPERTY()
	TObjectPtr<ARTSHUD> HUD;

	FVector2D SelectStartPosition;
	FVector2D RectangleSize;
	float mousePosX, mousePosY;
	TArray<AActor*> SelectedActores;
	FTimerHandle TimerHandle;
};
