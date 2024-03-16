// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPadel.h"
#include "AIPadel.generated.h"

/**
 * 
 */
UCLASS()
class JLPONG_API AAIPadel : public APlayerPadel
{
	GENERATED_BODY()
	
public:
	AAIPadel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "AI Settings")
	float AISpeed = 300.0f;

	void MoveAccordingToBall(float DeltaTime);
	class ABall* BallObject;
};
