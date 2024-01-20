// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCompo = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule_compo"));
	this->RootComponent = CapsuleCompo;

	Base_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base_MESH"));
	Base_Mesh->SetupAttachment(CapsuleCompo);

	Turret_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret_Mesh"));
	Turret_Mesh->SetupAttachment(Base_Mesh);

	UE_LOG(LogTemp, Log, TEXT("flag3"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Turret_Mesh);
	
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}



// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//UE_LOG(LogTemp, Log, TEXT("compo"));
	
	
}

