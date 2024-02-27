// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class COUNTERSTRIKE_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// ------------------Variable------------------

	virtual void NativeConstruct()override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (BindWidget))
	class UButton* Btn_CreateRoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (BindWidget))
	class UEditableText* Edit_RoomName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (BindWidget))
	class USlider* Slider_PlayerCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (BindWidget))
	class UTextBlock* Txt_PlayerCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (BindWidget))
	class UButton* Btn_CreateSession;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (BindWidget))
	class UButton* Btn_FindSession;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (BindWidget))
	class UButton* Btn_Back;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (BindWidget))
	class UButton* Btn_Back2;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (BindWidget))
	class UTextBlock* Txt_FindingMsg;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (BindWidget))
	class UEditableText* Edit_UserName;

	//  ------------- FindRoom ĵ���� �� ------------

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UScrollBox* ScrollRoomList;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Btn_Find;

	// -------------- ���� ���� ���� -----------

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USessionSlotWidget> SessionSlotWidget;

	UFUNCTION()
	void AddSlotWidget(const struct FSessionInfo& SessionInfo);


	UPROPERTY()
	class UGI* GI;








	// ------------------Fuction------------------

	UFUNCTION()
	void CreateRoom();

	//�����̴� �� ����� ȣ��Ǵ� �ݹ��Լ�
	UFUNCTION()
	void OnValueChanged(const float Value);

	UFUNCTION()
	void SwitchCreatePanel();
	
	UFUNCTION()
	void SwitchFindPanel();

	UFUNCTION()
	void SwitchMainPanel();

	//Find ��ư Ŭ�� ��  ȣ��� �ݹ�
	UFUNCTION()
	void OnClickedFindSession();

	UFUNCTION()
	void OnChangeButtonEnabled(bool bIsSearching);
};
