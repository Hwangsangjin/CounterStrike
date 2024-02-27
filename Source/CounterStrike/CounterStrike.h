// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// ī�װ��� �츮�� ���� ��밡�� UE_LOG(LogTemp �κ��� NetLog�� �ٲ��ְڴٴ� �ǹ�.)
DECLARE_LOG_CATEGORY_EXTERN(NetLog, Log, All);

#define LOCALROLE (UEnum::GetValueAsString<ENetRole>(GetLocalRole()))
#define REMOTEROLE (UEnum::GetValueAsString<ENetRole>(GetRemoteRole()))

//Ŭ���̾�Ʈâ���� �������� ��������
#define NETMODE (GetWorld()->GetNetMode()==ENetMode::NM_Client ? TEXT("Client") : GetWorld()->GetNetMode() == ENetMode::NM_Standalone ? TEXT("Standalone") : TEXT("Server"))


// ������ ����Ŭ Ȯ�ο�
// �Լ� ȣ��Ǵ� ����
//���� ����� ���Ŀ� ��ĭ ��������.(����)
#define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
// ���� ����ϴ� �Լ� ��ũ��
// ��� �Լ��� ������ �ٿ��� ��. \ �������ô� �ڿ� �ִ� ������ �ѹ������� ���� ����.
#define PRINTLOG(fmt, ...) \
UE_LOG(NetLog, Warning, TEXT("[%s]%s %s"),NETMODE,*CALLINFO, *FString::Printf(fmt, ##__VA_ARGS__))

//FSTRING�� *�� �ٿ���������, TEXT�� �Ⱥٿ�����!