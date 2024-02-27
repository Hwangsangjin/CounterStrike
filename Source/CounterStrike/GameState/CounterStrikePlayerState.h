// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CounterStrikePlayerState.generated.h"

UCLASS()
class COUNTERSTRIKE_API ACounterStrikePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void ServerSetUserName(const FString& InName);
};
