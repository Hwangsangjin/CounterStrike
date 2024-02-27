// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatComponent.generated.h"

class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COUNTERSTRIKE_API UPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// �÷��̾�
	UPROPERTY()
	TObjectPtr<APlayerCharacter> Player;

	// ������
	void DamageProcess(int32 Damage);

	// ����
	void DeadProcess();

	// ü��
	UFUNCTION()
	void OnRep_Hp();

	UPROPERTY(EditDefaultsOnly, Category = "Hp")
	float MaxHp = 100.0f;

	UPROPERTY(ReplicatedUsing = OnRep_Hp)
	float Hp = MaxHp;

	// ����
	UPROPERTY(Replicated)
	bool bHasGun;

	// ����
	UPROPERTY()
	bool bIsReload;

	// ����
	UPROPERTY()
	bool bIsDead;
};
