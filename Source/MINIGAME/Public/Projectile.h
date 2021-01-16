// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include"Components/StaticMeshComponent.h"
#include "Projectile.generated.h"


UCLASS()
class MINIGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	///Functions 
	/// Two implementations of the launching
	void LaunchProjectile(float Speed,float Damage);
	void LaunchProjectileConstantSpeed(float Speed, float Damage);
	//USphere
	////I Will Implement both technically Physics Based Projectile (Projectile movement component) and also Guided Projectile
	bool Moving_ConstantSpeed = false;
	bool IsHit = false; ///Overlapped or hit
	float ProjectileSpeed = 100;
	float AfterHitTime=2.f;
	float HitTime = 0.f;
	float TimeSinceLaunced = 0.f;

	//UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* ImpactBlast = nullptr;
	float ProjectileDamage = 0;

};
