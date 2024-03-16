// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ball.h"
// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoardGraphics = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardGraphics"));
	TopBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TopBox"));
	BottomBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomBox"));
	PlayerGoalBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerGoalBox"));
	AIGoalBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AIGoalBox"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnArrow"));

	SetRootComponent(BoardGraphics);
	TopBox->SetupAttachment(RootComponent);
	BottomBox->SetupAttachment(RootComponent);
	PlayerGoalBox->SetupAttachment(RootComponent);
	AIGoalBox->SetupAttachment(RootComponent);
	Camera->SetupAttachment(RootComponent);
	SpawnArrow->SetupAttachment(RootComponent);

	TopBox->SetCollisionProfileName("BlockAll");
	BottomBox->SetCollisionProfileName("BlockAll");
	PlayerGoalBox->SetCollisionProfileName("OverlapAllDynamic");
	AIGoalBox->SetCollisionProfileName("OverlapAllDynamic");

	
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	if (Camera)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);  // Assuming you are dealing with the first player controller
		if (PC)
		{
			PC->SetViewTargetWithBlend(this, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
	SpawnBall();
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoard::SpawnBall()
{
	BallObject = nullptr;
	if (!BallObject) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		UWorld* World = GetWorld();
		if (BoardGraphics) {
			// Calculate the center of the bounding box of BoardGraphics
			FVector BoardCenter = BoardGraphics->Bounds.Origin;



			// Spawn the ball at the center of the board
			BallObject = World->SpawnActor<ABall>(BallBlueprint, BoardCenter+ FVector(0, 0, 50.0f), GetActorRotation(), SpawnParams);
			FVector ArrowDirection = SpawnArrow->GetForwardVector();
			

			if (BallObject) {
				UE_LOG(LogTemp, Warning, TEXT("Ball spawned successfully."));
				BallObject->ProjectileMovement->Velocity = ArrowDirection * BallObject->ProjectileMovement->InitialSpeed;
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("Failed to spawn the ball."));
			}
		}
	}
}

