// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPadel.h"
#include "Kismet/GameplayStatics.h"
#include "Ball.h"

AAIPadel::AAIPadel()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIPadel::BeginPlay()
{
	Super::BeginPlay();
}

void AAIPadel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveAccordingToBall(DeltaTime);
}

void AAIPadel::MoveAccordingToBall(float DeltaTime)
{
	BallObject = Cast<ABall>(UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass()));
	if (BallObject)
	{
		FVector BallMovement = GetActorLocation();
		FVector NewLocation = FVector(GetActorLocation().X, BallObject->GetActorLocation().Y, GetActorLocation().Z);
		FVector Direction = FMath::VInterpConstantTo(GetActorLocation(),NewLocation , DeltaTime,350.0f);
		SetActorLocation(Direction);
	}
}
