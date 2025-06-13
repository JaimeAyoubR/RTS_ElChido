// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainBuild.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
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
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent* EnemyHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UFUNCTION()
	void Damage(int32 Damage);
protected:
	virtual void BeginPlay() override;

public:
	virtual void Destroyed() override;
};
