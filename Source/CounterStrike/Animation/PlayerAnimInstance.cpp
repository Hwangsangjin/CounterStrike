// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerAnimInstance.h"
#include "Character/PlayerCharacter.h"
#include "Component/PlayerStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (PlayerCharacter)
	{
		MovementComponent = PlayerCharacter->GetCharacterMovement();
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (MovementComponent)
	{
		const FVector Velocity = PlayerCharacter->GetVelocity();
		const FVector RightVector = PlayerCharacter->GetActorRightVector();
		Direction = FVector::DotProduct(RightVector, Velocity);

		const FVector ForwardVector = PlayerCharacter->GetActorForwardVector();
		Speed = FVector::DotProduct(ForwardVector, Velocity);

		// ���� �ӵ��� ���� �Ӱ谪 �̻��� ���(�ӵ��� ��û���� ���� ��� �ִϸ��̼��� Ʈ���ŵ��� �ʵ��� ����)�� ���� ����(�Է�)�� ����� ��쿡�� �̵�
		const float Threshold = 3.0f;
		bShouldMove = (Speed > Threshold && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);

		bIsFalling = MovementComponent->IsFalling();
		bIsCrouch = MovementComponent->IsCrouching();

	}
}

void UPlayerAnimInstance::PlayFireMontage()
{
	if (FireMontage)
	{
		Montage_Play(FireMontage);
	}
}

void UPlayerAnimInstance::PlayReloadMontage()
{
	if (ReloadMontage)
	{
		Montage_Play(ReloadMontage);
	}
}

void UPlayerAnimInstance::PlayDeadMontage()
{
	if (DeadMontage)
	{
		Montage_Play(DeadMontage);
	}
}

void UPlayerAnimInstance::AnimNotify_OnReloadEnd()
{
}

void UPlayerAnimInstance::AnimNotify_OnDeadEnd()
{
}
