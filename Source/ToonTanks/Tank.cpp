// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Engine/EngineTypes.h"

ATank::ATank(){
    Spring_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm77"));
    Spring_Arm->SetupAttachment(RootComponent);

    Camera_component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera88"));
    Camera_component->SetupAttachment(Spring_Arm);
}

void ATank::PawnDie()
{
    Super::PawnDie();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    
    
    UE_LOG(LogTemp, Log, TEXT("죽었어"));
}

APlayerController* ATank::GetController()
{
    return PlayerController;
    
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this ,&ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this,&ATank::Turn );
    PlayerInputComponent->BindAction( TEXT("Fire"), IE_Pressed, this, &ATank::Fire );
}

void ATank::Fire()
{
    UE_LOG(LogTemp, Log, TEXT("Fire .."));
    FHitResult Hit;
    if(!PlayerController) return;
    bool Is_Hit = PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
    if(Is_Hit)
    {
        AProjectile* SpawnProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile_BP,
            ProjectileSpawnPoint->GetComponentLocation(),
            ProjectileSpawnPoint->GetComponentRotation());

        SpawnProjectile->SetOwner(this);
        
        
        UE_LOG(LogTemp, Log, TEXT(" Fire hit !!"));
        //DebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 30, 10, FColor::Red , false, 0.5f);
    }else
    {
        UE_LOG(LogTemp, Log, TEXT(" XXXXXXXXXXXXXX hit !!"));
    }
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this,0));
}



void ATank::Move(float a){
    FVector dir(0,0,0);
    dir.X = a * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    //UE_LOG(LogTemp, Log, TEXT("MoveForward : %s"), *dir.ToCompactString());
    AddActorLocalOffset(dir, true);
}

void ATank::Turn(float a){
    //UE_LOG(LogTemp, Log, TEXT("Turn : %f"), a);
    
    FRotator Rotate = FRotator::ZeroRotator;
    Rotate.Yaw = TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this) * a;
    AddActorLocalRotation(Rotate, true);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    FHitResult FHit;
    if(!PlayerController) return;
    bool Hit = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, FHit);
    if(Hit){
        //DrawDebugSphere(GetWorld(), FHit.ImpactPoint, 5, 8, FColor::Red, false, -1);
        TurretRotate(FHit.ImpactPoint);
    }
}