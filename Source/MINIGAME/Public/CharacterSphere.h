// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/StaticMesh.h"
#include"Projectile.h"
#include "CharacterSphere.generated.h"

UCLASS()
class MINIGAME_API ACharacterSphere : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACharacterSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void	OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Functions
	UFUNCTION(BluePrintCallable, Category = Input)
		void MoveForward(float Value);

	UFUNCTION(BluePrintCallable, Category = Input)
		void MoveRight(float Value);
	UFUNCTION(BluePrintCallable, Category = Input)
		void Jump(float Value);

	void ApplyForce(FVector Direction, float Value);
	
	void GettingHit(float DamageAmount);
	void OnDeath();


	//Vars
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Player")	
	USphereComponent* CharacterSphereComponent;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category ="Player Information")
	 float StartingHealth= 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Information")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Information")
	float MovingForce;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Information")
		float JumpingImpulse; /// I will not use Jump

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
	float MaxVelocity = 400.f; //PerSec
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
	float Score = 0;
	
	

	UPROPERTY(BlueprintReadWrite, Category = "Player Information")
	FVector AccelerationVector;
	FVector LastFrameVelocity;
	float ForwardAxisVal=0;
	float RightAxisVal=0;

};
