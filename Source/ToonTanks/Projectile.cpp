// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("projectile_staticmeshcomponent"));
	RootComponent = StaticMeshComponent;
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectile component"));
	ProjectileMovementComponent->InitialSpeed = 1300.f;
	ProjectileMovementComponent->MaxSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit_Red );
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile:: OnHit_Red(UPrimitiveComponent* MyPrimitive, AActor* OtherActor, UPrimitiveComponent* OtherPrimitive, FVector NormalImpulse,const FHitResult& HitResult)
{
	UE_LOG(LogTemp, Log, TEXT("Hit RED %s , %s , %s, %s"), *MyPrimitive->GetName(), *OtherActor->GetName() , *OtherPrimitive->GetName());
	UE_LOG(LogTemp, Log, TEXT("%s %s"),*NormalImpulse.ToCompactString(), *HitResult.ImpactPoint.ToCompactString());
}

