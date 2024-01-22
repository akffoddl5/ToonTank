// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::SetEnableControl(bool bVal)
{
	if(bVal)
	{
		GetPawn()->EnableInput(this);
	}else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bVal;
	
	
}