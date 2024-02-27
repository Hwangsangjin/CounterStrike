#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "GI.generated.h"


// �� ����(����) ����� ����ü
USTRUCT(BlueprintType)
struct FSessionInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString RoomName;
	
	UPROPERTY(BlueprintReadOnly)
	FString HostName;
	
	UPROPERTY(BlueprintReadOnly)
	FString PlayerCount;
	
	UPROPERTY(BlueprintReadOnly)
	int32 PingSpeed;
	
	UPROPERTY(BlueprintReadOnly)
	int32 Index;

	inline FString ToString()
	{
		return FString::Printf(TEXT("[%d] %s : %s - %s , %d ms"), Index, *RoomName, *HostName, *PlayerCount, PingSpeed);
	}


};
// ���� �˻��� ������ �� ȣ��� Delegate
// �������Ʈ(Dynamic)�� ��ε�ĳ����(Multicast) ����� ����Ѵٸ� DECLARE_Dynamic_Multicast_DELEGATE_OneParam
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSearchSignature, const FSessionInfo&, SessionInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSearchStateSignature, bool, bIsSearching);


UCLASS()
class COUNTERSTRIKE_API UGI : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGI();

	virtual void Init()override;

	// ����(��) ����
	IOnlineSessionPtr SessionInterface;

	// ������ ����(HOST) �̸� <- �����̸�
	FString MySessionName = "Mumyung";

	//���� ���� �Լ�
	void CreateMySession(FString RoomName, int32 PlayerCount);
	//���� ���� �Ϸ� �̺�Ʈ �ݹ�
	void OnCreateSessionComplete(FName SessionName,bool bWasSuccessful);
	
	// �� �˻�
	TSharedPtr<class FOnlineSessionSearch> SessionSearch; // UPROPERTY�� �� �� ���� ���� C++ Ŭ������ ������ TSharedPtr ���
	void FindOtherSessions();

	// ���� �˻� �Ϸ� �� �̺�Ʈ �ݹ�
	UFUNCTION()
	void OnFindSessionsComplete(bool bWasSuccessful);

	// �� ã�� �Ϸ�Ǹ� �ݹ��� ��� �� ��������Ʈ
	FSearchSignature OnSearchCompleted;

	// �� ã�� ���� �ݹ� ��������Ʈ
	FSearchStateSignature OnSearchState;

	//���� ���� �Լ�
	void JoinSelectedSession(int32 RoomIndex);

	//���� ���� ��������Ʈ �ݹ�
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

};

