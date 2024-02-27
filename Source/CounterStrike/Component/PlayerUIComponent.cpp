// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerUIComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/PlayerCharacter.h"
#include "Controller/CounterStrikePlayerController.h"
#include "../Widget/Crosshair.h"
#include "../Widget/ReloadWidget.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/TimerHandle.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/ArrowComponent.h>
#include "../Widget/HP_BulletWIdget.h"
#include "../Widget/ChatMain.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ProgressBar.h>

UPlayerUIComponent::UPlayerUIComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);

}


void UPlayerUIComponent::BeginPlay()
{
	Super::BeginPlay();

	/*Player = GetOwner<APlayerCharacter>();
	Pc = Cast<ACounterStrikePlayerController>(Player->GetController());*/

	/*if (Pc&&Pc->IsLocalController())
	{
		ChatMain = Pc->ChatMain;
	}*/
	//InitWidget();
	SetState(ECrosshairState::None);


	// ----inhanced input ----
	if (APlayerController* PlayerController = Cast<APlayerController>(Player->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 3);
		}
	}
	// ----inhanced input ----


}
void UPlayerUIComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		EnhancedInput->BindAction(IA_Enter, ETriggerEvent::Completed, this, &UPlayerUIComponent::SetVisibleChat);
	}
}


void UPlayerUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	switch (State)
	{
	case ECrosshairState::None:
		break;

	case ECrosshairState::Move:
		Move();
		break;
	case ECrosshairState::Shot:
		Shoot();
		break;
	case ECrosshairState::Reload:
		break;

	}
}

void UPlayerUIComponent::InitWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("InitWidge() Player : %s"), Player->Controller ?TEXT("Valid") : TEXT("Invalid"));

	if (!Player->Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitWidget() Fail"));
		return;
	}
	auto pc = Cast<ACounterStrikePlayerController>(Player->Controller);
	if (pc->ChatMainWidget)
	{
		if (!pc->ChatMain)
		{
			pc->ChatMain = Cast<UChatMain>(CreateWidget(GetWorld(), pc->ChatMainWidget));
			pc->ChatMain->AddToViewport();

			UE_LOG(LogTemp, Warning, TEXT("InitWidget() AddToViewport"));
		}
		pc->ChatMain->WBP_HP_Bullet->HP->SetText(FText::AsNumber(100));
		pc->ChatMain->WBP_HP_Bullet->HPBar->SetPercent(1);
		ChatMain = pc->ChatMain;

		if (CrosshairWidgetFactory && ReloadWidgetFactory && HP_BulletWidgetFactory)
		{
			//ĳ���� ���ϰ� �θ�Ŭ������������ ���� ���������?
			//CrosshairWidget = Cast<UCrosshair>(CreateWidget(GetWorld(), CrosshairWidgetFactory));
			//CrosshairWidget->AddToViewport();
			ChatMain->WBP_Zoom->ShowCrosshair(false);
			//CrosshairWidget->ShowCrosshair(false);
			ReloadWidget = Cast<UReloadWidget>(CreateWidget(GetWorld(), ReloadWidgetFactory));
			ReloadWidget->AddToViewport();
			ReloadWidget->ShowReload(false);
			Player->UITargeting->SetVisibility(false);
			//HP_BulletWidget = Cast<UHP_BulletWIdget>(CreateWidget(GetWorld(), HP_BulletWidgetFactory));
			//HP_BulletWidget->AddToViewport();
		}
	}
}

void UPlayerUIComponent::Move()
{
	Delta = GetWorld()->GetDeltaSeconds();

	if (Player->GetVelocity().IsZero())
	{
		ChatMain->WBP_Zoom->SpreadLine(false, Delta * 3);
		//CrosshairWidget->SpreadLine(false, Delta * 3);
		//UE_LOG(LogTemp, Warning, TEXT("Stop"));
		return;
	}
	ChatMain->WBP_Zoom->SpreadLine(true, Delta * 3);
	//CrosshairWidget->SpreadLine(true, Delta*3);
	//UE_LOG(LogTemp, Warning, TEXT("Move"));

}
//������, õõ�� ���� ���� �̱��� ����
void UPlayerUIComponent::Zoom()
{

}
//Ʈ���� start���� �ѹ� ȣ�� ����
void UPlayerUIComponent::ShootStart()
{
	//Move ���� �϶���, ���� �����ϵ��� �ϱ�
	if (State != ECrosshairState::Move)
	{
		return;
	}
	SetState(ECrosshairState::Shot);


}
//Ʈ���� TRIGGER���� ���� ȣ�� ����
void UPlayerUIComponent::Shoot()
{
	ChatMain->WBP_Zoom->SpreadLine(true, Delta * 5);
	//CrosshairWidget->SpreadLine(true, Delta*5);

}
//Ʈ���� complete���� �ѹ� ȣ�� ����
void UPlayerUIComponent::ShootComplete()
{
	//Shot ���� �϶���, ���� �����ϵ��� �ϱ�
	if (State != ECrosshairState::Shot)
	{
		return;
	}
	SetState(ECrosshairState::Move);
}

void UPlayerUIComponent::SetState(ECrosshairState Next)
{
	State = Next;
}

void UPlayerUIComponent::Reload()
{
	//� ���¿����� �� �ü� �ְԲ�
	if (State == ECrosshairState::None || State == ECrosshairState::Reload)
	{
		return;
	}
	SetState(ECrosshairState::Reload);
	ChatMain->WBP_Zoom->ShowCrosshair(false);
	//CrosshairWidget->ShowCrosshair(false);
	ReloadWidget->ShowReload(true);
	ReloadWidget->PlayAnimationWidget();
	//Ÿ�̸� �Լ��� ���͸� ��� ���� �ֿ��� ��밡���ϹǷ�, ���ٹ���� �̷�����.
	//2�� �ڿ� �ٽ� ũ�ν��� �����ش�.
	// ���¸� ���ε忡�� ��� �ش�.
	//���ε� ������ �����.
	Player->GetWorldTimerManager().SetTimer(Handle, this,&UPlayerUIComponent::FinishReload, 2.0f,false);
	// ���� �ִϸ��̼��� �����Ų��.
	PlayReloadAnimation();
}

void UPlayerUIComponent::ClientDamageWidget_Implementation(APlayerCharacter* Enemy)
{
	if (Player->IsLocallyControlled())
	{
		Damage(Enemy);
	}
}

// �ܺ� ȣ��
void UPlayerUIComponent::Damage(APlayerCharacter* Enemy)
{
	Player->UITargeting->SetVisibility(true);

	FVector EnemyLoc = Enemy->GetActorLocation();
	FVector MyLoc = Player->GetActorLocation();
	EnemyLoc.Z = 0.0f;
	MyLoc.Z = 0.0f;
	//UE_LOG(LogTemp, Warning, TEXT("Enemy Loc : %f, %f, %f"), EnemyLoc.X , EnemyLoc.Y, EnemyLoc.Z);
	//UE_LOG(LogTemp, Warning, TEXT("My Loc :    %f, %f, %f"), MyLoc.X , MyLoc.Y, MyLoc.Z);
	//�� ������ ���Ѵ�
	FVector Dir = EnemyLoc - MyLoc;
	Dir.Normalize();
	//UE_LOG(LogTemp, Warning, TEXT("Dir :    %f, %f, %f"), Dir.X, Dir.Y, Dir.Z);
	float Dot = FVector::DotProduct(Dir, Player->GetActorForwardVector());
	float AcosAngle = FMath::Acos(Dot);
	float AngleDegree = FMath::RadiansToDegrees(AcosAngle);

	if (FVector::DotProduct(Player->GetActorRightVector(), Dir)<0) 
	{
		
		AngleDegree *= -1;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Dot : %.1f, AcosAngle : %.1f, AngleDegree : %.1f"), Dot, AcosAngle, AngleDegree);
	// 
	// �� �������� ������ ȸ�� ��Ų��
	Player->UITargeting->SetRelativeRotation(FRotator(0,0, AngleDegree));
	//UE_LOG(LogTemp, Warning, TEXT("AngleDegree : %.1f"),AngleDegree);
	// �� ������ ��ġ�� 90���� ������.
	// �̰� ƽ���� ������.

	FTimerHandle handle;
	Player->GetWorldTimerManager().SetTimer(handle, FTimerDelegate::CreateLambda([&]
		{
			Player->UITargeting->SetVisibility(false);
		}), 1, false);
}

//���� ������� �����.
void UPlayerUIComponent::SetVisible()
{
	ChatMain->WBP_Zoom->ShowCrosshair(true);
	//CrosshairWidget->ShowCrosshair(true);
	SetState(ECrosshairState::Move);

}
//���� �������� �����.
void UPlayerUIComponent::SetUnVisible()
{
	ChatMain->WBP_Zoom->ShowCrosshair(false);
	//CrosshairWidget->ShowCrosshair(false);
	SetState(ECrosshairState::None);

}

void UPlayerUIComponent::FinishReload()
{
	ChatMain->WBP_Zoom->ShowCrosshair(true);
	//CrosshairWidget->ShowCrosshair(true);
	ReloadWidget->ShowReload(false);
	SetState(ECrosshairState::Move);
}

void UPlayerUIComponent::PlayReloadAnimation()
{
	ReloadWidget->PlayAnimationWidget();
}

void UPlayerUIComponent::TestLog(const FInputActionValue& value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Test"));
}

void UPlayerUIComponent::SetVisibleChat(const FInputActionValue& value)
{

}
