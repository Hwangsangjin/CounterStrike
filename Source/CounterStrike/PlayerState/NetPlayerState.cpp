// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/NetPlayerState.h"
#include "../GameInstance/GI.h"

void ANetPlayerState::BeginPlay()
{
	Super::BeginPlay();

	auto con = GetPlayerController();	 //PlayerState�� ���ʴ� PlayerController
	if (con && con->IsLocalController()) // PC�� �ְ�, ���������� pc�� �������̹Ƿ� �� �ڽ�����
	{
		auto GI = GetWorld()->GetGameInstance<UGI>();
		ServerRPC_SetUserName(GI->MySessionName);
	
	
	}



}

void ANetPlayerState::ServerRPC_SetUserName_Implementation(const FString& name)
{

	SetPlayerName(name);

}
