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

		
	}else if(ATower* thisTower = Cast<ATower>(DieActor))
	{
		thisTower->PawnDie();
	}

}

void ATankGameModeBase::BeginPlay()
{
	MyTank  = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
}
