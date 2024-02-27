// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/GI.h"
#include <../../../../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h>
#include <../../../../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSessionSettings.h>
#include "../CounterStrike.h"
#include <../../../../../../../Plugins/Online/OnlineBase/Source/Public/Online/OnlineSessionNames.h>

UGI::UGI()
{

}

void UGI::Init()
{
	Super::Init();
	//���ǿ� ����� ��������
	// �� ����� ���ÿ��� �Ұ���, �������� �Ұ���
	// �¶��� ���� �������̽� �����
	auto Subsys = IOnlineSubsystem::Get();
	if (Subsys)
	{
		SessionInterface = Subsys->GetSessionInterface();
		//�ݹ�
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this,&UGI::OnCreateSessionComplete);

		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this,&UGI::OnFindSessionsComplete);
		
		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UGI::OnJoinSessionCompleted);
	}

	//���� ���� �Լ� ȣ�� (�񵿱� ó��)
	// �׽�Ʈ ���̾���. ���� �Ⱦ�����.
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
	{
		//CreateMySession(MySessionName, 10);
		//FindOtherSessions();

	}), 2, false);

}

void UGI::CreateMySession(FString RoomName, int32 PlayerCount)
{
	//PRINTLOG(TEXT("RoomName : %s, pc : %d"), *RoomName, PlayerCount);
	
	
	//���� ����
	FOnlineSessionSettings SessionSettings;

	// 1. Dedicated Server ��� ����
	SessionSettings.bIsDedicated = false;
	// 2. ���� ��Ī (����) , ���� ��Ī ������� ����
	FName SubsysName = IOnlineSubsystem::Get()->GetSubsystemName();
	SessionSettings.bIsLANMatch = SubsysName == "NULL"; // Default Engine.ini�� ���� OnlineSubsystem���� Ȯ�� ����
	// 3. ��Ī�� �¶����� ���� ����� �� ���� (false�� ��� �ʴ븦 ���ؼ��� ���� ����)
	SessionSettings.bShouldAdvertise = true;
	// 4. �¶��� ���� ������ Ȱ���ϰ� ���� ���� (������. �ڸ���� ��..)
	SessionSettings.bUsesPresence = true;
	// 5. ���� ���� �߿� Join �� �� �ִ��� ����
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bAllowJoinViaPresence= true;
	// 6. �ִ� ��� �ο� ��
	SessionSettings.NumPublicConnections = PlayerCount;
	// 7. Ŀ���� �ɼ� -> �� ���� , �� üũ , ȣ��Ʈ �̸�
	SessionSettings.Set(FName("Room_Name"), RoomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	SessionSettings.Set(FName("Host_Name"), MySessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);


	//�̺κ��� ��¥ �� ����� ���ΰ���.
	// ���� ���� -> Ư�� ģ���� �ʴ��ϰų�, ���̽� ê�� �ؾ� �� ��, NetID�� �־�� �ϹǷ� NetID�� �����´�.
	FUniqueNetIdPtr NetID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();
	SessionInterface->CreateSession(*NetID, FName(MySessionName), SessionSettings);


}

void UGI::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	PRINTLOG(TEXT("Create Session Start : %s , %d"), *SessionName.ToString(), bWasSuccessful);

	// �� �ȿ� ������ ������ �����.
	if (bWasSuccessful)
	{
		//���� ����ǥ �ٱ��� �ִ� ���� �����, �� ��γ��� ?listen ġ�� SereverTravel�� �����ϴ�.
		GetWorld()->ServerTravel(TEXT("/Game/Maps/GameMap?listen"));
	}

}

void UGI::FindOtherSessions()
{

	// �˻� ���� ���� (��� �� , PRIVATE ��)
	SessionSearch = MakeShareable(new FOnlineSessionSearch);// TSharedPtr �𸮾� ����Ʈ �����ʹ� �̷��� �����Ѵ�.

	// 1. Presence ������ True �� �Ǿ��ִ� ����
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	// 2. LanMatching ����
	SessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";

	//3. �ִ� ���� �˻� ��
	SessionSearch->MaxSearchResults = 10;

	// 4. �˻�
	SessionInterface->FindSessions(0,SessionSearch.ToSharedRef());

	// 5. �� �˻� ������ �˸���.
	OnSearchState.Broadcast(true);

}

void UGI::OnFindSessionsComplete(bool bWasSuccessful)
{

	// ã�� ���� ��
	if (bWasSuccessful == false)
	{

		PRINTLOG(TEXT("Session Search Failed..."));
		return;
	}


	//���� �˻� ���
	const auto Results = SessionSearch->SearchResults;
	PRINTLOG(TEXT("Search Result Count : %d"), Results.Num());


	// �迭�� ������ ������ ��. �ϳ��� �˻�
	for (int i = 0;i < Results.Num();i++)
	{
		auto sr = Results[i];

		if (sr.IsValid() == false)
		{
			continue;
		}

		FSessionInfo SessionInfo;
		SessionInfo.Index = i;
	

		// 1. �� �̸�
		sr.Session.SessionSettings.Get(FName("ROOM_NAME"), SessionInfo.RoomName);
		
		// PC ������ �̸�
		FString OwnerName = sr.Session.OwningUserName;
		
		// 2. ȣ��Ʈ �̸�
		sr.Session.SessionSettings.Get(FName("HOST_NAME"), SessionInfo.HostName);
		
		// 3. �÷��̾� �� (�ִ� ���� �� - ���� ���� ���� ��)
		int32 MaxPlayerCount = sr.Session.SessionSettings.NumPublicConnections;
		int32 CurrentPlayerCount = MaxPlayerCount - sr.Session.NumOpenPublicConnections;
		
		SessionInfo.PlayerCount = FString::Printf(TEXT("(%d/%d)"),MaxPlayerCount, CurrentPlayerCount);
		
		//4. �� (���� ��Ī�� ���� 9999 �̷� ������ ���´�.)
		SessionInfo.PingSpeed = sr.PingInMs;

		PRINTLOG(TEXT("%s"), *SessionInfo.ToString());

		// ���� �߰� ��ε�ĳ�����ε���. (��������Ʈ ��, �̺�Ʈ�� ���⼭ �߻� ��Ű�ڴ�.�ε�?)
		OnSearchCompleted.Broadcast(SessionInfo);

	}

	OnSearchState.Broadcast(false);

}

void UGI::JoinSelectedSession(int32 RoomIndex)
{
	//�������� �� ��� �� �ϳ��� ����
	auto sr = SessionSearch->SearchResults[RoomIndex];

	// ���ǿ� ���� �Լ�
	SessionInterface->JoinSession(0,FName(MySessionName), sr);
}



void UGI::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	// Client �� ������ ����.
	// -> Client Travel
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		//������ ���� ������ URL�� �ʿ���.
		FString URL;
		SessionInterface->GetResolvedConnectString(SessionName, URL);
		
		if (URL.IsEmpty() == false)
		{
			//���� ������, Ŭ�� ������ �� ���� �÷��̾� ��Ʈ�ѷ��� �־�� �Ѵ�.
			auto pc = GetWorld()->GetFirstPlayerController();
			pc->ClientTravel(URL,TRAVEL_Absolute);
		}

	}
	else
	{

		PRINTLOG(TEXT("Join Session Failed... %d"), Result );
	}

}
