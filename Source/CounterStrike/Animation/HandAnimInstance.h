// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Component/PlayerShootingComponent.h"
#include "HandAnimInstance.generated.h"


enum class GunName : uint8;
/**
 * 
 */
UCLASS()
class COUNTERSTRIKE_API UHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	// �������� �� ���� �Լ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimSettings")
		class APlayerCharacter* Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimSettings")
		bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimSettings")
		bool IsInMoving;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimSettings")
		int WeaponSwitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimSettings")
		EGunName WeaponName;


	//-----------------------------AK47---------------------------------------
	// �ѽ�⿡�� ����� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* AKFireMontage;
	// ������ ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* AKReloadMontage;
	// �ѽ�� ����Լ�
	void PlayAKFireAnimation();
	void PlayAKReloadAnimation();

	//-----------------------------MP5-----------------------------------------
	// �ѽ�⿡�� ����� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* MP5FireMontage;
	// ������ ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* MP5ReloadMontage;
	// �ѽ�� ����Լ�
	void PlayMP5FireAnimation();
	void PlayMP5ReloadAnimation();

	//-----------------------------Glock-----------------------------------------
	// �ѽ�⿡�� ����� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* GlockFireMontage;
	// ������ ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* GlockReloadMontage;
	// �ѽ�� ����Լ�
	void PlayGlockFireAnimation();
	void PlayGlockReloadAnimation();

	//-----------------------------Knife-----------------------------------------
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
		UAnimMontage* KnifeAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
		UAnimMontage* KnifeAttackMontage2;

	bool KnifeMotion = true;

	void KnifeAttackAnimation();

	//----------------------------Grenade----------------------------------------
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* GrenadeThrowMontage;

	void PlayGrenadeThrowAnimation();

	// ������ ������ �� ȣ��� Notify �Լ�
	UFUNCTION()
	void AnimNotify_OnReloadFinish();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	





};
