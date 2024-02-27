// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/CounterStrikePlayerController.h"
#include "GameMode/CounterStrikeGameMode.h"
#include "GameFramework/SpectatorPawn.h"
#include "../Widget/ChatMain.h"

void ACounterStrikePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 서버일때만 게임모드 인스턴스 할당
	if (HasAuthority())
	{
		CounterStrikeGameMode = Cast<ACounterStrikeGameMode>(GetWorld()->GetAuthGameMode());

	}
	//GDH CODE
	//자기자신일때, UI 생성
	/*if (IsLocalController()) 
	{
		ChatMain = Cast<UChatMain>(CreateWidget(GetWorld(),ChatMainWidget));
		ChatMain->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
	}*/
	//GDH CODE

}

void ACounterStrikePlayerController::ServerRPC_ChangeToSpectator_Implementation()
{
	auto ExistingPlayer = GetPawn();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto Spectator = GetWorld()->SpawnActor<ASpectatorPawn>(CounterStrikeGameMode->SpectatorClass, ExistingPlayer->GetActorTransform(), Params);

	Possess(Spectator);

	ExistingPlayer->Destroy();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACounterStrikePlayerController::ServerRPC_RespawnPlayer_Implementation, 5.0f, false);
}

void ACounterStrikePlayerController::ServerRPC_RespawnPlayer_Implementation()
{
	auto ExistingPlayer = GetPawn();

	UnPossess();

	ExistingPlayer->Destroy();

	CounterStrikeGameMode->RestartPlayer(this);
}
