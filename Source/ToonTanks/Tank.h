// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:

	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(float a);
	void Turn(float a);
	void Fire();
	
	
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category=" _component_ ", BlueprintReadWrite)
	class USpringArmComponent* Spring_Arm;
	UPROPERTY(meta = (AllowPrivateAccess = "true"), Category=" _component_ ", BlueprintReadWrite, VisibleAnywhere)
	class UCameraComponent* Camera_component;

	UPROPERTY(EditAnywhere, Category=" move ", BlueprintReadWrite, meta=(AllowPrivateAccess= "true"))
	float Speed;

	UPROPERTY(EditInstanceOnly, Category = "_move_", BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float TurnRate;
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	APlayerController* PlayerController;

};
