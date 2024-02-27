// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CounterStrikePlayerController.generated.h"

class ACounterStrikeGameMode;

UCLASS()
class COUNTERSTRIKE_API ACounterStrikePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// ������ ���� ����
	UFUNCTION(Server, Reliable)
	void ServerRPC_ChangeToSpectator();

	// �÷��̾� ������ ���� ����
	UFUNCTION(Server, Reliable)
	void ServerRPC_RespawnPlayer();

	// ������ ������ �ϴ� ���Ӹ��
	UPROPERTY()
	TObjectPtr<ACounterStrikeGameMode> CounterStrikeGameMode;


	// UI ������ ����.
	//GDH Code
	UPROPERTY(EditDefaultsOnly, Category ="UI")
	TSubclassOf<class UChatMain> ChatMainWidget;

	UPROPERTY(BlueprintReadWrite)
	class UChatMain* ChatMain;
	//GDH Code
};
