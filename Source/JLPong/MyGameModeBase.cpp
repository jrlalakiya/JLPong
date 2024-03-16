// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Board.h"
#include "MyGameStateBase.h"



void AMyGameModeBase::IncreaseScore(int32 Player, ABoard* GameBoard)
{
	MyGameState = GetWorld()->GetGameState<AMyGameStateBase>();
	if (Player == 1) {
		MyGameState->PlayerScore += 1;
	} else{
		MyGameState->AIScore += 1;
	}
	UE_LOG(LogTemp, Warning, TEXT("Score: %d"), MyGameState->PlayerScore);
	GameBoard->SpawnBall();
}
