// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include"Components/StaticMeshComponent.h"
#include"Components/SceneComponent.h"
#include"Projectile.h"
#include "Turret.generated.h"


UCLASS()
class MINIGAME_API ATurret : public APawn
{
	GENERATED_BODY()
private:
	
public:
	// Sets default values for this pawn's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//vars

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	///Functions
	
	void  TurretRotate(float CabinetAngularVelocity);
	void  BarrelElevate(float AngularVelocity);
	///Vars
	/// ///BarrelInfo
	float CabinetRoll;
	float CabinetPitch;
	FRotator BarrelRot;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Components")
	float PatrolFrequency;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Components")
		UStaticMeshComponent* Body=nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Components")
		UStaticMeshComponent* Barrel= nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Components")
		UStaticMeshComponent* Cabinet = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Components")
		USceneComponent* SpawnPoint = nullptr;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Projectile Information")
	  float ProjectileSpeed;
	//For all turrets Should be static

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projetile Information")
		AProjectile* Projectile;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Components")
	float AngularVelocity=20; /// Velocity in Degrees persecond
							  ///-ve means opposite direction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Components")
		float UpperRotationRange=75;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Components")
		float LowerRotationRange=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Information")
		float TurretLaserDamage = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Information")
		float TurretProjectileDamage = 10.f;


};