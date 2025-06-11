// Fill out your copyright notice in the Description page of Project Settings.


#include "MovePawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AMovePawn::AMovePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Crar la capusla (el player por asi decirlo)
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;

	//Crear el Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));


	//Crear camara
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//Unir camara/SpringArm/Capsula
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	//Modificar el como se ve la camara y la distancia entre camara - jugador
	SpringArm->TargetArmLength = 1000;
	//Se pone Orthographic para darle ese efecto tipico de RTS
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

}

// Called when the game starts or when spawned
void AMovePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovePawn::Move(const FInputActionValue& Value)
{
	const FVector2D InputMovement = Value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator Rotator = Controller->GetControlRotation();
		const FRotator YRotation(0, Rotator.Yaw, 0);

		const FVector Forward = FRotationMatrix(YRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, InputMovement.Y);
		AddMovementInput(Right, InputMovement.X);
	}
}

void AMovePawn::Zoom(const FInputActionValue& Value)
{
	const float ZoomDirection = Value.Get<float>();
	if (Controller)
	{
		float DirectionZoom = Camera->OrthoWidth + ZoomDirection * -ZoomSpeed;
		DirectionZoom = FMath::Clamp(DirectionZoom, 200.0f, 5000.0f); //Esto para que no puedas hacer zoom infinito

		Camera->OrthoWidth = DirectionZoom;
	}
}

void AMovePawn::EdgeSroll()
	{
		APlayerController* PlayerController = Cast<APlayerController>(Controller);
		if (PlayerController == nullptr)
			return;
		float mousePosX = 0, mousePosY = 0;
		float EdgeThreshold = 10.f;
		FVector MovementInputs	= FVector::ZeroVector;
		if (PlayerController->GetMousePosition(mousePosX, mousePosY))
		{
			FVector2D ViewPort;
			if (GEngine && GEngine->GameViewport)
			{
				GEngine->GameViewport->GetViewportSize(ViewPort);
				if (mousePosX < EdgeThreshold) //Borde Izquierda
				{
					MovementInputs.X = -1.f;
				}
				if (mousePosX > (ViewPort.X - EdgeThreshold)) //Borde Derecha
				{
					MovementInputs.X = +1.f;
				}
				if (mousePosY < EdgeThreshold)//Borde Arriba
				{
					MovementInputs.Y = 1.f;
				}
				if (mousePosY > (ViewPort.Y - EdgeThreshold))//Borde Abajo
				{
					MovementInputs.Y = -1.f;
				}

				if (!MovementInputs.IsZero())
					Move(FInputActionValue(MovementInputs));
			}
		}
	}


// Called every frame
void AMovePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		EdgeSroll();

}

// Called to bind functionality to input
void AMovePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
		Super::SetupPlayerInputComponent(PlayerInputComponent);
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			//Agregar la funcion de mover
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMovePawn::Move);

			//Agregar la funcion de hacer zoom
			EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AMovePawn::Zoom);
		}

}

