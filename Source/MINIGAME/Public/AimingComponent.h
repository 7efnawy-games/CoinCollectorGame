// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include"Turret.h"
#include "DrawDebugHelpers.h"
#include"Components/SceneComponent.h"
#include"CharacterSphere.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include"Math.h"
#include "AimingComponent.generated.h"
class ATurret;
UENUM()
enum class ETurretState: uint8
{
	ReadyToFire,
	Idling,
	Reloading,
	Aiming,
	Locked
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIGAME_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	float Time = 0;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	///Functions
	void Fire();//Aiming Component
	AActor* LineTrace();//Aiming Component
	void Patrol();
	float TruncSin(float Time);

	UFUNCTION(BluePrintCallable, Category = AimDebug)
	void CalculateFutureTurretRotation(FVector Location);
	
	float CalculateTheTargetShortestPathToRotator(FRotator InitialRot, FRotator TarRot);


	bool AimtAtLocation_inTimeRange(FRotator CabinetFinalRotation);
	void CalculateAngularSpeed();

	UFUNCTION(BluePrintCallable, Category = "Target Aiming")
	FVector CalculateCharacterFutureLocation(ACharacterSphere* Char, float time_range);
	
	

	//Aiming Component
	
	FVector TargetLocation;
	
	ATurret *  Turret= nullptr;
	ETurretState State = ETurretState::Idling;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aiming Information")
	float ReloadTime=2;

	float LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Aiming Information")
	float TraceRange = 400;
	
	///Vars for calculating the projectile hit location and the angular velocity
	float TimeForProjectileToHit = 0.f;
	float TimeForTurretToRotate = 0.f;
	float UnitTime=1.f ;
	float AngularVelocityTimer = 0.f;
	
	FRotator BarrelInitialRot;
	FRotator BarrelTargetRot;

	FRotator CabinetInitialRot;
	FRotator CabinetTargetRot;

	float Turret_AngularSpeed;
	float Barrel_AngularSpeed;
	
	FVector FutureSpawnLoc;
};


////Aiming Logic 
///Let L1 is the character's current location and L2 is the future Location and V ithe character's Veclocity
///R1 Current Turret Roatation and R2 future turret Rotation and AV is the turret's angular velocity
///Tl is the turrent Location
/// We want to Calculate AV ???

/// Time till Projectile Impact= Abs(L2-L1)/V = Abs(Tl-L2)/ProjectileVelocity + Abs(R2-R1)/AV

///Putting into consideration the reload time to know when exactly are we 