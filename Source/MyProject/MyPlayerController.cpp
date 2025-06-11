// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "BasePawn.h"
#include "Resources.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUD = Cast<ARTSHUD>(GetHUD());
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputMappingContext == nullptr)
	{
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* Subsystem;
	Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem != nullptr)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
		UE_LOG(LogTemp, Display, TEXT("InputMapping Agregado"));
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//Agregar la funcion de mover
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this,
		                                   &AMyPlayerController::Select);

		//Secuencia para hacer la seleccion grande y que aparezca un rectangulo
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this,
		                                   &AMyPlayerController::StartSelect);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this,
		                                   &AMyPlayerController::OnGoingSelect);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this,
		                                   &AMyPlayerController::EndSelect);


		//Agregar la funcion de command
		EnhancedInputComponent->BindAction(CommandAction, ETriggerEvent::Completed, this,
		                                   &AMyPlayerController::CommandSelectedActors);
	}
}

void AMyPlayerController::Select(const FInputActionValue& value)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, false, HitResult);

	//sDeseleccionar el personaje anterior
	if (HitActor)
	{
		if (HitActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
		{
			ISelectableInterface::Execute_SelectActor(HitActor, false);
		}
	}
	HitActor = HitResult.GetActor();

	if (HitActor)
	{
		UE_LOG(LogTemp, Display, TEXT("Click Personaje: %s"), *HitActor->GetName());

		//Vemos si lo que clickeamos contiene SelectableInterface, o sea,
		//Si es algo que podemos seleccionar en primer lugar
		if (HitActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
		{
			ISelectableInterface::Execute_SelectActor(HitActor, true);
		}
	}
}

void AMyPlayerController::CommandSelectedActors(const FInputActionValue& value)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, false, HitResult);
	if (!HitResult.bBlockingHit)
	{
		return;
	}

	AResources* ClickedResource = Cast<AResources>(HitResult.GetActor());

	if (ClickedResource)
	{
		for (AActor* Actor : SelectedActores)
		{
			ABasePawn* BasePawn = Cast<ABasePawn>(Actor);
			if (BasePawn)
			{
				BasePawn->GoCollectResource(ClickedResource);
				return;
			}
		}
	}
	else if (SelectedActores.Num() > 0)
	{
		int i = SelectedActores.Num() / -2;
		for (AActor* Actor : SelectedActores)
		{
			UE_LOG(LogTemp, Display, TEXT("SelectActors: %s"), *Actor->GetName());
			if (Actor != nullptr && Actor->GetClass()->ImplementsInterface(UNavegateInterface::StaticClass()))
			{
				INavegateInterface::Execute_MoveToLocation(Actor, HitResult.Location + FVector(0, 100 * i, 0));
				i++;
			}
		}
	}
	else
	{
		if (HitActor->IsA(AResources::StaticClass()))
		{
			for (AActor* Actor : SelectedActores)
			{
				ABasePawn* BasePawnRef = Cast<ABasePawn>(Actor);
				if (BasePawnRef)
				{
					BasePawnRef->GoCollectResource(Cast<AResources>(HitActor));
				}
			}
		}
		else if (HitActor->GetClass()->ImplementsInterface(UNavegateInterface::StaticClass()))
		{
			INavegateInterface::Execute_MoveToLocation(HitActor, HitResult.Location);
		}
	}
}

void AMyPlayerController::StartSelect(const FInputActionValue& value)
{
	GetMousePosition(mousePosX, mousePosY);
	SelectStartPosition = FVector2D(mousePosX, mousePosY);
}

void AMyPlayerController::OnGoingSelect(const FInputActionValue& value)
{
	GetMousePosition(mousePosX, mousePosY);
	RectangleSize = FVector2D(mousePosX - SelectStartPosition.X, mousePosY - SelectStartPosition.Y);
	if (HUD != nullptr)
	{
		HUD->TurnOnSelectionRect(SelectStartPosition, RectangleSize);
	}
}

void AMyPlayerController::EndSelect(const FInputActionValue& value)
{
	if (HUD != nullptr)
	{
		HUD->TurnOffSelectionRect();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
		                                       &AMyPlayerController::SelectMultipleActors, 0.02f, false);
	}
}

void AMyPlayerController::SelectMultipleActors()
{
	if (HUD != nullptr)
	{
		for (AActor* Actor : SelectedActores)
		{
			UE_LOG(LogTemp, Display, TEXT("SelectActors: %s"), *Actor->GetName());
			if (Actor != nullptr)
			{
				if (Actor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
				{
					ISelectableInterface::Execute_SelectActor(Actor, false); //Para desactivar los anteriores
				}
			}
		}
		SelectedActores.Empty();
		TArray<AActor*> AllActorsSelected = HUD->GetSelectedActors();
		for (AActor* Actor : AllActorsSelected)
		{
			if (Actor != nullptr)
			{
				if (Actor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
				{
					ISelectableInterface::Execute_SelectActor(Actor, true);
					SelectedActores.AddUnique(Actor);
				}
			}
		}
	}
}
