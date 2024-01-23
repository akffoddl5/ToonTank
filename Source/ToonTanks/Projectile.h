// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	UPROPERTY(EditAnywhere, meta= (AllowPrivateAccess = "true"), BlueprintReadWrite, Category= "AA_ MY PROPERTY")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnHit_Red(UPrimitiveComponent* MyPrimitive, AActor* OtherActor, UPrimitiveComponent* OtherPrimitive, FVector NormalImpulse,const FHitResult& HitResult);

	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category=" Particle_RED ")
	UParticleSystem* ParticleSystem_Hit;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* Launch_Sound;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* Boom_Sound;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> CameraShakeBase_Hit;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
