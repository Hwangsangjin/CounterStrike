// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/LoginWidget.h"
#include "../GameInstance/GI.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Button.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/EditableText.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Slider.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetSwitcher.h>
#include "SessionSlotWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ScrollBox.h>

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GI = Cast<UGI>(GetWorld()->GetGameInstance());
	// ���� �߰� �̺�Ʈ �ݹ� ����ϱ�
	GI->OnSearchCompleted.AddDynamic(this, &ULoginWidget::AddSlotWidget);
	Btn_Find->OnClicked.AddDynamic(this, &ULoginWidget::OnClickedFindSession);
	GI->OnSearchState.AddDynamic(this, &ULoginWidget::OnChangeButtonEnabled);

	Btn_CreateRoom->OnClicked.AddDynamic(this,&ULoginWidget::CreateRoom);
	Slider_PlayerCount->OnValueChanged.AddDynamic(this,&ULoginWidget::OnValueChanged);

	Btn_CreateSession->OnClicked.AddDynamic(this,&ULoginWidget::SwitchCreatePanel);
	Btn_FindSession->OnClicked.AddDynamic(this, &ULoginWidget::SwitchFindPanel);
	Btn_Back->OnClicked.AddDynamic(this, &ULoginWidget::SwitchMainPanel);
	Btn_Back2->OnClicked.AddDynamic(this, &ULoginWidget::SwitchMainPanel);

}

void ULoginWidget::AddSlotWidget(const struct FSessionInfo& SessionInfo)
{
	//���� ����
	if (SessionSlotWidget)
	{
		auto slot = CreateWidget<USessionSlotWidget>(this, SessionSlotWidget);
		slot->Set(SessionInfo);
		//��ũ�� �ڽ��� �߰�
		ScrollRoomList->AddChild(slot);

	}


}

void ULoginWidget::CreateRoom()
{
	//GameInstance �� �ִ� CreateMySession�Լ� ȣ��
	if (GI && Edit_RoomName->GetText().IsEmpty() == false)
	{
		const FString RoomName = Edit_RoomName->GetText().ToString();
		GI->CreateMySession(RoomName, (int32) Slider_PlayerCount->GetValue());

	}


}

void ULoginWidget::OnValueChanged(const float Value)
{
	Txt_PlayerCount->SetText(FText::AsNumber(Value));
}

void ULoginWidget::SwitchCreatePanel()
{
	//���� �̸� ����
	FString UserName = Edit_UserName->GetText().ToString();
	if (UserName.IsEmpty() == false)
	{

		GI->MySessionName = UserName;
	}

	WidgetSwitcher->SetActiveWidgetIndex(1);

}

void ULoginWidget::SwitchFindPanel()
{
	//���� �̸� ����
	// �� ��� �˻�
	FString UserName = Edit_UserName->GetText().ToString();
	if (UserName.IsEmpty() == false)
	{

		GI->MySessionName = UserName;
	}

	WidgetSwitcher->SetActiveWidgetIndex(2);
	GI->FindOtherSessions();

}

void ULoginWidget::SwitchMainPanel()
{

	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void ULoginWidget::OnClickedFindSession()
{
	// �� ��� ����
	ScrollRoomList->ClearChildren();

	// �� ��� �˻�

	if (GI)
	{
		GI->FindOtherSessions();
	}
}

void ULoginWidget::OnChangeButtonEnabled(bool bIsSearching)
{
	Btn_Find->SetIsEnabled(!bIsSearching);
	if (bIsSearching)
	{
		Txt_FindingMsg->SetVisibility(ESlateVisibility::Visible);
	}
	else 
	{
		Txt_FindingMsg->SetVisibility(ESlateVisibility::Hidden);

	}
}
