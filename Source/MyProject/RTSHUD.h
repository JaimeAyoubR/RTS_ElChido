// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ARTSHUD : public AHUD
{
	GENERATED_BODY()
	
private:
	bool isSelecting = false;
	bool SelectedActors = false;
	FVector2D RectStartPos;
	FVector2D RectSize;
	FLinearColor ColorRelleno = FLinearColor(255.f,255.f,255.f,.2f);

	TArray<AActor*> ActorsSelected;

	void ActorsSelectedInRect();

public:
	void TurnOnSelectionRect(const FVector2D InRectStartPos,const FVector2D InRectSize);
	void TurnOffSelectionRect();
	TArray<AActor*> GetSelectedActors();

protected:
	virtual void DrawHUD() override;
};
