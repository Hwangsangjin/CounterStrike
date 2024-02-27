// Fill out your copyright notice in the Description page of Project Settings.



#include "Widget/ChatMain.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/GameStateBase.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/PlayerState.h>
#include "Controller/CounterStrikePlayerController.h"

void UChatMain::NativeConstruct()
{
	Super::NativeConstruct();
}

void UChatMain::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{	
													
	Super::NativeTick(MyGeometry, InDeltaTime);
													
	//���� ��� �÷��̾��� �̸��� ���� �ʹ�.
	// �ٸ� ����ڵ��� GameInstance�� �ִ� ���ǳ����� �������� �ʹ�.
	// GameMode�� ���������� �����ϹǷ� GameState�� PlayerState�� �̿��ؼ� �����´�.
																	
	auto PlayerArr = GetWorld()->GetGameState()->PlayerArray;
	FString Name;								
																	
	for (auto pState : PlayerArr) //��� ������� �÷��̾� ������ �����´�.
	{												
		Name.Append(FString::Printf(TEXT("%s : %d\n"), *pState->GetPlayerName(), (int32)pState->GetScore()));
	}
																	
	Txt_Users->SetText(FText::FromString(Name));	
					


}

void UChatMain::OnRespawn()
{
	auto CounterStrikePlayerController = Cast<ACounterStrikePlayerController>(GetWorld()->GetFirstPlayerController());

	if (CounterStrikePlayerController)
	{
		CounterStrikePlayerController->SetShowMouseCursor(false);
		CounterStrikePlayerController->ServerRPC_ChangeToSpectator();
	}
}
