// Fill out your copyright notice in the Description page of Project Settings.


#include "PongHUD.h"
#include "Components/TextBlock.h"
#include "Components/Widget.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameStateBase.h"
void UPongHUD::NativeConstruct()
{
}

bool UPongHUD::Initialize()
{
	bool Success = Super::Initialize();

	if (PlayerScore) {
		PlayerScore->TextDelegate.BindUFunction(this, "SetPlayerScore");
	}

	if (AIScore) {
		AIScore->TextDelegate.BindUFunction(this, "SetAIScore");
	}
	return Success;
}

FText UPongHUD::SetPlayerScore()
{
	AMyGameStateBase* MyGameState = GetWorld()->GetGameState<AMyGameStateBase>();
	if (MyGameState)
	{
		return FText::FromString(FString::FromInt(MyGameState->PlayerScore));
	}
	return FText();
}

FText UPongHUD::SetAIScore()
{
	AMyGameStateBase* MyGameState = GetWorld()->GetGameState<AMyGameStateBase>();
	if (MyGameState)
	{
		return FText::FromString(FString::FromInt(MyGameState->AIScore));
	}
	return FText();
}