// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Projectile.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    
    //UE_LOG(LogTemp, Log, TEXT("Tower tick777"));
    if(Tank){
        //UE_LOG(LogTemp, Log, TEXT("Tower tick77"));
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Distance < Range){
            //get rotation
            //FRotator Dir = (Tank->GetActorLocation() - GetActorLocation()).Rotation();
            
            //init rotation
            TurretRotate(Tank->GetActorLocation());
        }
    }
}

void ATower::BeginPlay(){
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Tower begin"));
    //UGamePlayStatics::GetPlayerPawn();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(TimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
    
}

void ATower::CheckFireCondition()
{
    if(Tank){
        //UE_LOG(LogTemp, Log, TEXT("Tower tick77"));
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Distance < Range){
            //get rotation
            //FRotator Dir = (Tank->GetActorLocation() - GetActorLocation()).Rotation();
            
            //init rotation
            Fire();
        }
    }
}

void ATower::Fire()
{
    UE_LOG(LogTemp, Log, TEXT("Tower Fire"));
    DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 30, 20, FColor::Red, false, 0.5f);

    auto SpawnProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile_BP,
        ProjectileSpawnPoint->GetComponentLocation(),
        ProjectileSpawnPoint->GetComponentRotation());

    SpawnProjectile->SetOwner(this);
}