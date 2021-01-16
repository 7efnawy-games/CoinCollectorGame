// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Barrel = CreateDefaultSubobject<UStaticMeshComponent>("Barrel");
	SpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	Cabinet = CreateDefaultSubobject<UStaticMeshComponent>("Cabinet");
	LaserBeam = CreateDefaultSubobject<UParticleSystemComponent>("Laser");
	Body->SetupAttachment(RootComponent);
	Cabinet->SetupAttachment(Body);
	Barrel->SetupAttachment(Cabinet);
	SpawnPoint->SetupAttachment(Barrel);
	ProjectileSpeed = 100.f;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	CabinetPitch = Cabinet->GetRelativeRotation().Pitch;
	CabinetRoll = Cabinet->GetRelativeRotation().Roll;
	BarrelRot = Barrel->GetRelativeRotation();

	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void  ATurret::TurretRotate(float Velocity)
{
	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	if (IsValid(Cabinet)&&IsValid(Barrel))
	{
		float RotationChange = Velocity * GetWorld()->DeltaTimeSeconds;
		float NewRotation = Cabinet->GetRelativeRotation().Yaw + RotationChange;
		Cabinet->SetRelativeRotation(FRotator(CabinetPitch, NewRotation, CabinetRoll));
	}

}
void ATurret::BarrelElevate(float Velocity)
{
	if (IsValid(Barrel))
	{
		float BarrelRotationChange = Velocity * GetWorld()->DeltaTimeSeconds;
		float BarrelNewRotation = Barrel->GetRelativeRotation().Pitch + BarrelRotationChange;
		Barrel->SetRelativeRotation(FRotator(BarrelNewRotation, BarrelRot.Yaw, BarrelRot.Roll));
	}
}
