// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Board.h"
#include "MyGameModeBase.h"
// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("BallCollisionSphere"));

	SetRootComponent(BallCollisionSphere);

	BallStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallStaticMeshComponent"));
	
	BallStaticMeshComponent->SetupAttachment(RootComponent);

	BallCollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BallCollisionSphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));



	BallCollisionSphere->GetBodyInstance()->bLockXRotation = true;
	BallCollisionSphere->GetBodyInstance()->bLockYRotation = true;
	BallCollisionSphere->GetBodyInstance()->bLockZRotation = true;
	BallCollisionSphere->GetBodyInstance()->bLockXTranslation = true;
	BallCollisionSphere->GetBodyInstance()->bLockZTranslation = true;


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 900.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bShouldBounce = true;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	BallCollisionSphere->OnComponentHit.AddDynamic(this,&ABall::OnCollisionSphereHit);
	BallCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnCollisionSphereBeginOverlap);

	OwningBoard = Cast<ABoard>(GetOwner());
	
}

void ABall::OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	if (OtherComp == Cast<UPrimitiveComponent>(OwningBoard->PlayerGoalBox)) {
		this->Destroy();
		GameMode->IncreaseScore(2,OwningBoard);
	} else if (OtherComp == Cast<UPrimitiveComponent>(OwningBoard->AIGoalBox)) {
		this->Destroy();
		GameMode->IncreaseScore(1, OwningBoard);
	}
}

void ABall::OnCollisionSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	if (OtherComp->GetCollisionProfileName() == FName("BlockAll")|| OtherComp->GetCollisionProfileName() == FName("BlockAllDynamic")) {
		FVector NewVelocity = FMath::GetReflectionVector(ProjectileMovement->Velocity, Hit.ImpactNormal);
		
		ProjectileMovement->Velocity = NewVelocity;
	}
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



