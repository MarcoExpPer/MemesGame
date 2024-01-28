// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayersData.generated.h"

UENUM(BlueprintType)
enum class EPlayerSkin : uint8 {
	PS_NONE,
	PS_BOY_1,
	PS_GIRL_1,
	PS_BOY_2,
	PS_GIRL_2
};

UCLASS()
class MEMESGAMES_API UPlayersData : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	EPlayerSkin Player1Skin = EPlayerSkin::PS_NONE;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	EPlayerSkin Player2Skin = EPlayerSkin::PS_NONE;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float Player1Score = 0;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float Player2Score = 0;
};
