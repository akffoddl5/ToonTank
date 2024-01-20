// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BasePawn.generated.h"


UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UPROPERTY(VisibleInstanceOnly)
	int32 red;

	UPROPERTY(VisibleDefaultsOnly)
	int32 red2;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(meta=(AllowPrivateAccess = "true"), BlueprintReadWrite, Category= " _component_ ", EditDefaultsOnly)
	class UCapsuleComponent* CapsuleCompo;
	UPROPERTY(meta=(AllowPrivateAccess = "true"), BlueprintReadWrite, Category= " _component_ ", EditDefaultsOnly)
	UStaticMeshComponent* Base_Mesh;
	UPROPERTY(meta=(AllowPrivateAccess = "true"), BlueprintReadWrite, Category= " _component_ ", EditDefaultsOnly)
	UStaticMeshComponent* Turret_Mesh;
	UPROPERTY(meta=(AllowPrivateAccess = "true"), BlueprintReadWrite, Category= " _component_ ", EditDefaultsOnly)
	USceneComponent* ProjectileSpawnPoint;

	void TurretRotate(FVector Target){
		FVector MyLocation = Turret_Mesh->GetComponentLocation();
		FVector Direction = Target - MyLocation;
		FRotator DirRotator = FRotator(0.f,Direction.Rotation().Yaw,0.f);
		Turret_Mesh->SetWorldRotation(FMath::RInterpTo(Turret_Mesh->GetComponentRotation(),
		 DirRotator, UGameplayStatics::GetWorldDeltaSeconds(this),20.f));
		
	}


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AProjectile> Projectile_BP;
};
