// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

int32 ATankGameModeBase::Current_Stage = 1;

void ATankGameModeBase:: ActorDied(AActor* DieActor)
{
	if(DieActor == MyTank && !vIsOver)
	{
		Current_Stage = 1;
		 vIsOver = true; 
		//RestartLevel();
		TimerDelegate = FTimerDelegate::CreateUObject(this,
			&ATankGameModeBase::RestartLevel
			);
		GetWorldTimerManager().ClearTimer(TimerHandle);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 2, false);
		MyTank->PawnDie();
		if(!MyPlayerController) return;
		MyPlayerController->SetEnableControl(false);
		// MyTank->DisableInput(MyTank->GetController());
		
		// MyTank->GetController()->bShowMouseCursor = false;
		GameOver(false);

		
		
		
	}else if(ATower* thisTower = Cast<ATower>(DieActor))
	{
		thisTower->PawnDie();
		TargetNum--;
		if(TargetNum <=0)
		{
			GameOver(true);
			Current_Stage++;
			GetWorldTimerManager().ClearTimer(TimerHandle);
			TimerDelegate = FTimerDelegate::CreateUObject(this,
			&ATankGameModeBase::RestartLevel
			);
			GetWorldTimerManager().ClearTimer(TimerHandle);
			GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 2, false);
		}
	}

}

void ATankGameModeBase::RestartLevel()
{
	UE_LOG(LogTemp, Log, TEXT("Restart level M<<<<<<<<<<<<<<< %d "), Current_Stage);
	// 현재 레벨의 이름을 가져옵니다.
	//FName CurrentLevelName = *UGameplayStatics::GetCurrentLevelName(GetWorld());
	FString LevelName = FString::Printf(TEXT("Main%d"), Current_Stage);

	// FString을 FName으로 변환합니다.
	FName CurrentLevelName = FName(*LevelName);
	
	// 현재 레벨을 다시 로드합니다.
	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName);
}

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameStartHandle();
	TargetNum = GetTargetNum();
	TargetNum_Init = TargetNum;
}

int32 ATankGameModeBase::GetTargetNum()
{
	TArray<AActor*> Tower_Array;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Tower_Array);
	
	return Tower_Array.Num();
}



void ATankGameModeBase::GameStartHandle()
{
	MyTank  = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	GameInit();
	
	if(MyPlayerController)
	{
		MyPlayerController->SetEnableControl(false);
		TimerDelegate = FTimerDelegate::CreateUObject(MyPlayerController,
			&AMyPlayerController::SetEnableControl,
			true
			);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 3, false);
	}
	
}