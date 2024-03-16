// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class JLPONG_API ABall : public AActor
{
	GENERATED_BODY()
	

	
	UPROPERTY(EditAnywhere, Category = "Components")
	class USphereComponent* BallCollisionSphere;

	
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* BallStaticMeshComponent;
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ABoard* OwningBoard;

	UFUNCTION()
	void  OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

	UFUNCTION()
	void OnCollisionSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement;

	class AMyGameModeBase* GameMode;
	
};
