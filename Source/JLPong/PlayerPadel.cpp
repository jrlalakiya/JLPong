// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPadel.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "PongHUD.h"
// Sets default values
APlayerPadel::APlayerPadel()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaddleCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PaddleCollisionBox"));

	SetRootComponent(PaddleCollisionBox);

	PaddleStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleStaticMeshComponent"));

	PaddleStaticMeshComponent->SetupAttachment(RootComponent);

	
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;

	PaddleStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PaddleStaticMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	PaddleCollisionBox->GetBodyInstance()->bLockXRotation = true;
	PaddleCollisionBox->GetBodyInstance()->bLockYRotation = true;
	PaddleCollisionBox->GetBodyInstance()->bLockZRotation = true;
	PaddleCollisionBox->GetBodyInstance()->bLockXTranslation = true;
	PaddleCollisionBox->GetBodyInstance()->bLockYTranslation = true;
	PaddleCollisionBox->GetBodyInstance()->bLockZTranslation = true;

}

// Called when the game starts or when spawned
void APlayerPadel::BeginPlay()
{
	Super::BeginPlay();
	PaddleCollisionBox->OnComponentHit.AddDynamic(this,
		&APlayerPadel::OnCollisionBoxHit);
	if (WBP_PongHUD) {
		PongHUDInstance = CreateWidget<UPongHUD>(GetWorld(), WBP_PongHUD);
		PongHUDInstance->AddToViewport();
	}
}

void APlayerPadel::OnCollisionBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->GetCollisionProfileName() == FName("TopBoundary") || OtherComp->GetCollisionProfileName() == FName("BottomBoundary")) {
		FVector Direction = GetActorLocation();
		UBoxComponent* BoundryComponent = Cast<UBoxComponent>(OtherComp);
		Direction.Y = FMath::Clamp(Direction.Y, BoundryComponent->GetComponentLocation().Y - BoundryComponent->GetScaledBoxExtent().Y, BoundryComponent->GetComponentLocation().Y + BoundryComponent->GetScaledBoxExtent().Y);
		SetActorLocation(Direction);
	}
}



// Called every frame
void APlayerPadel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller)
	{
		//DECLARE a FRotator Rotation and Initialize it to pitch=0, roll=0 and the Yaw to the Controllers Yaw Rotation
		FRotator Rotation(0.0f, 0.0f, GetControlRotation().Yaw);
		//DECLARE a FVector Direction and set it to zero vector
		FVector Direction = FVector::ZeroVector;
		//IF the MoveForwardAmount is not zero
		if (MoveUpAmount != 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("MoveUp called with Value: %f"), MoveUpAmount);
			Direction = GetActorLocation() + FRotationMatrix(GetActorRotation()).GetUnitAxis(EAxis::Y) * MoveUpAmount * MoveSpeed * DeltaTime;

			//SET this actors location to the Direction
			SetActorLocation(Direction);
		}
		//ENDIF

	}
}

// Called to bind functionality to input
void APlayerPadel::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &APlayerPadel::MoveUp);
}

void APlayerPadel::MoveUp(float Value)
{
	MoveUpAmount = -Value;
}

