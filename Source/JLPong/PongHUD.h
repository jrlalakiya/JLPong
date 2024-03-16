// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PongHUD.generated.h"

/**
 * 
 */
UCLASS()
class JLPONG_API UPongHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	virtual bool Initialize() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PlayerScore = nullptr;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* AIScore = nullptr;

	UFUNCTION()
	FText SetPlayerScore();

	UFUNCTION()
	FText SetAIScore();
};
