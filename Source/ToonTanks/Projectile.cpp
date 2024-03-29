// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("projectile_staticmeshcomponent"));
	RootComponent = StaticMeshComponent;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent_RED"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectile component"));
	ProjectileMovementComponent->InitialSpeed = 1300.f;
	ProjectileMovementComponent->MaxSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit_Red );
	UGameplayStatics::PlaySoundAtLocation(this, Launch_Sound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile:: OnHit_Red(UPrimitiveComponent* MyPrimitive, AActor* OtherActor, UPrimitiveComponent* OtherPrimitive, FVector NormalImpulse,const FHitResult& HitResult)
{
	

	if(GetOwner() && GetOwner()->GetInstigatorController() && OtherActor != this && OtherActor != GetOwner())
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
		UGameplayStatics::SpawnEmitterAtLocation(this, ParticleSystem_Hit, HitResult.ImpactPoint);
		UE_LOG(LogTemp, Log, TEXT("flag4"));
		UE_LOG(LogTemp, Log, TEXT("Hit RED %s "), *OtherActor->GetName() );
		UGameplayStatics::PlaySoundAtLocation(this, Boom_Sound, GetActorLocation());
		//UE_LOG(LogTemp, Log, TEXT("%s %s"),*NormalImpulse.ToCompactString(), *HitResult.ImpactPoint.ToCompactString());
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeBase_Hit);
	}
	else
	{
		if(!GetOwner())
		{
			UE_LOG(LogTemp, Log, TEXT("flag1"));
		}else if(!GetOwner()->GetInstigatorController())
		{
			UE_LOG(LogTemp, Log, TEXT("flag2"));
		}else
		{
			UE_LOG(LogTemp, Log, TEXT("flag3"));
		}
	}
	
	Destroy();
}

