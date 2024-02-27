// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/CounterStrikePlayerState.h"
#include "GameInstance/CounterStrikeGameInstance.h"

void ACounterStrikePlayerState::BeginPlay()
{
	Super::BeginPlay();

	/*APlayerController* PlayerController = GetPlayerController();
	if (PlayerController && PlayerController->IsLocalController())
	{
		UCounterStrikeGameInstance* CounterStrikeGameInstance = GetWorld()->GetGameInstance<UCounterStrikeGameInstance>();
		ServerSetUserName(CounterStrikeGameInstance->OnlineSessionName);
	}*/
}

void ACounterStrikePlayerState::ServerSetUserName_Implementation(const FString& InName)
{
	SetPlayerName(InName);
}
