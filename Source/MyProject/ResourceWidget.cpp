// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceWidget.h"
#include "Components/TextBlock.h"

void UResourceWidget::UpdateResources(int32 Food, int32 Stone, int32 Water, int32 Wood)
{
	if (FoodText) FoodText->SetText(FText::FromString(FString::FromInt(Food)));
	if (StoneText) StoneText->SetText(FText::FromString(FString::FromInt(Stone)));
	if (WaterText) WaterText->SetText(FText::FromString(FString::FromInt(Water)));
	if (WoodText) WoodText->SetText(FText::FromString(FString::FromInt(Wood)));
}
