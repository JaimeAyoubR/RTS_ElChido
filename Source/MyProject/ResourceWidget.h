// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResourceWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UResourceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FoodText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StoneText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WaterText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WoodText;

	UFUNCTION(BlueprintCallable)
	void UpdateResources(int32 Food, int32 Stone, int32 Water, int32 Wood);
};
