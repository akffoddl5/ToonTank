// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void ATankGameModeBase:: ActorDied(AActor* DieActor)
{
	if(DieActor == MyTank)
	{
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
		}
	}

}

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameStartHandle();
	TargetNum = GetTargetNum();
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
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(MyPlayerController,
			&AMyPlayerController::SetEnableControl,
			true
			);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 3, false);
	}
	
}