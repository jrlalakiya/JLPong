// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPadel.generated.h"

UCLASS()
class JLPONG_API APlayerPadel : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* PaddleCollisionBox;


	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* PaddleStaticMeshComponent;


	

	/*The Pawns Move Forward Amount per frame*/
	float MoveUpAmount= 0;
public:
	// Sets default values for this pawn's properties
	APlayerPadel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnCollisionBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUp(float Value);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 500.0f;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UPongHUD> WBP_PongHUD;

	class UPongHUD* PongHUDInstance;

};
