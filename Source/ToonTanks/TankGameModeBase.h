// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DieActor);
	class ATank* MyTank;
	class AMyPlayerController* MyPlayerController;
	FTimerHandle TimerHandle;
	void GameStartHandle();

	UFUNCTION(BlueprintImplementableEvent)
	void GameInit();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bVal);

	int32 GetTargetNum();
	int32 TargetNum;

protected:
	void BeginPlay() override;
};
