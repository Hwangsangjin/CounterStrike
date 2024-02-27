// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SessionSlotWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Button.h>
#include "../GameInstance/GI.h"

void USessionSlotWidget::Set(const struct FSessionInfo& SessionInfo)
{
	// ����(��) ��ȣ
	Txt_SessionNumber->SetText(FText::FromString(FString::Printf(TEXT("[%d]"),SessionInfo.Index)));
	// �� �̸�
	Txt_RoomName->SetText(FText::FromString(SessionInfo.RoomName));
	// ȣ��Ʈ �̸�
	Txt_HostName->SetText(FText::FromString(SessionInfo.HostName));
	Txt_PlayerCount->SetText(FText::FromString(SessionInfo.PlayerCount));
	// ��
	Txt_PingSpeed->SetText(FText::FromString(FString::Printf(TEXT("%d ms"),SessionInfo.PingSpeed)));
	SessionNumber = SessionInfo.Index;

}

void USessionSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Join->OnClicked.AddDynamic(this,&USessionSlotWidget::JoinSession);

}

void USessionSlotWidget::JoinSession()
{
	auto GI = Cast<UGI>(GetWorld()->GetGameInstance());
	if (GI)
	{

		GI->JoinSelectedSession(SessionNumber);
	}
}


