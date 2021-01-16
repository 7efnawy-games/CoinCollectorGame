// Fill out your copyright notice in the Description page of Project Settings.


#include "AimingComponent.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Turret =Cast<ATurret>(GetOwner());

	// ...
}


// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	UnitTime = Turret->ProjectileSpeed/ 1500;
	// ...
	
}

void UAimingComponent::Fire()
{
	// Spawn a projectile at the socket location on the barrel


	if (Turret->Barrel)
		if (!ensure(ProjectileBlueprint)){return;}
			
		//	UE_LOG(LogTemp, Warning, TEXT("FIRED!!"))
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Turret->SpawnPoint->GetComponentLocation(),
				Turret->SpawnPoint->GetComponentRotation()
				);
			//Projectile->LaunchProjectile(Turret->ProjectileSpeed, Turret->TurretProjectileDamage);
			Projectile->LaunchProjectileConstantSpeed(Turret->ProjectileSpeed, Turret->TurretProjectileDamage);
	

}
// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (State == ETurretState::ReadyToFire)
	{
		Fire();
		State = ETurretState::Reloading;
		LastFireTime = Time;
	}
	else if (State == ETurretState::Reloading)
	{
		if (Time - LastFireTime >= ReloadTime)
		{
			Turret->Barrel->SetRelativeRotation(Turret->BarrelRot);//Returns the value of the Barrel Rotation so it won't mess aiming
			State = ETurretState::Idling;
		}
	}
	else if (State == ETurretState::Aiming)
	{
		if (AimtAtLocation_inTimeRange(CabinetTargetRot))
		{
			State = ETurretState::ReadyToFire;
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("STILL AIMING"))

		}
	}
	else if (State == ETurretState::Locked)
	{
		AActor* HitActor = LineTrace();
		ACharacterSphere* Char = Cast<ACharacterSphere>(HitActor);
		if (Char)
		{
			TargetLocation = CalculateCharacterFutureLocation(Char, UnitTime);
			CalculateFutureTurretRotation(TargetLocation);
			CalculateAngularSpeed();
			State = ETurretState::Aiming;
		}
		else
		{
			State = ETurretState::Idling;
		}
	}
	else
	{

		AActor* HitActor=LineTrace();
		ACharacterSphere* Char = Cast<ACharacterSphere>(HitActor);
		if (Char)
		{
			State=ETurretState::Locked;
		}
		else
		Patrol();
	}
	Time += DeltaTime;
	// ...
}
void UAimingComponent::CalculateFutureTurretRotation(FVector Location)
{
	FRotator NewRot;
	 CabinetInitialRot =Turret->Cabinet->GetComponentRotation();
	NewRot=UKismetMathLibrary::FindLookAtRotation(Turret->Cabinet->GetComponentLocation(), Location);
	 CabinetTargetRot = FRotator(CabinetInitialRot.Pitch, NewRot
		.Yaw, CabinetInitialRot.Roll);
	 
	 Turret->Cabinet->SetWorldRotation(CabinetTargetRot); /// I made this to get the Future SpawnLoc

	NewRot = UKismetMathLibrary::FindLookAtRotation(Turret->Barrel->GetComponentLocation(), Location);
	BarrelInitialRot = Turret->Barrel->GetComponentRotation();
	BarrelTargetRot = FRotator(NewRot.Pitch, BarrelInitialRot.Yaw, BarrelInitialRot.Roll);


	//Check this part if the Firing functionality is not correct 
	Turret->Barrel->SetWorldRotation(BarrelTargetRot);

	FutureSpawnLoc=Turret->SpawnPoint->GetComponentLocation();
	TimeForProjectileToHit = (Location - FutureSpawnLoc).Size() / Turret->ProjectileSpeed;

	Turret->Barrel->SetWorldRotation(BarrelInitialRot);
	Turret->Cabinet->SetWorldRotation(CabinetInitialRot);





}
void UAimingComponent::CalculateAngularSpeed()
{

	TimeForTurretToRotate = UnitTime - TimeForProjectileToHit;
	if (TimeForTurretToRotate <= 0) ///Meaning the projectile speed is so slow meaning the character will reach the point before the projectile
	{
		TimeForTurretToRotate = 0.1; ///Arbitary value
	}
		//Turret_AngularSpeed = (CabinetTargetRot.Yaw-CabinetInitialRot.Yaw)/TimeForTurretToRotate; //To see the shortes roation distance
		Turret_AngularSpeed = CalculateTheTargetShortestPathToRotator(CabinetInitialRot, CabinetTargetRot) / TimeForTurretToRotate;
		Barrel_AngularSpeed = (BarrelTargetRot.Pitch-BarrelInitialRot.Pitch)/TimeForTurretToRotate;
		//UE_LOG(LogTemp,Warning,TEXT("Float %f,,,, %f , %f"), TimeForProjectileToHit,Turret_AngularSpeed,Barrel_AngularSpeed)
}
float UAimingComponent::CalculateTheTargetShortestPathToRotator(FRotator InitialRot, FRotator TarRot)
{
	float First=TarRot.Yaw-InitialRot.Yaw;
	float Second = (TarRot.Yaw - InitialRot.Yaw); //Same Agle As first
	Second = Second < 0 ? Second + 360 : Second-360;
	float Best = FMath::Abs(First)< FMath::Abs(Second)?First:Second ;
	return Best ;
	

}

bool UAimingComponent::AimtAtLocation_inTimeRange(FRotator CabinetFinalRotation)
{

	if (AngularVelocityTimer>=TimeForTurretToRotate)    //unit of travel
	{
		AngularVelocityTimer = 0;
		return true;	
	}
	else
	{
		//FMath::Clamp(Barrel_AngularSpeed, 0.f, 40.f)
		Turret->TurretRotate(Turret_AngularSpeed);
		Turret->BarrelElevate(Barrel_AngularSpeed);
		AngularVelocityTimer += GetWorld()->GetDeltaSeconds();
		return false;
	}
	//Turret->Barrel->SetWorldRotation(BarrelTargetRot);
	//return true;
}
FVector UAimingComponent::CalculateCharacterFutureLocation(ACharacterSphere* Char, float time_range)
{
	
	///If the Projectile Speed increase the turret angular veocity decrease and vice versa
	/// We Can control the Angular Velocity
		FVector FutureLocation;
		FVector FutureVelocity;

		FutureVelocity = Char->GetVelocity() + (Char->AccelerationVector * time_range); 
		// When I use FutureVelocity it should be more accurate but that's not the case but it's not consistent
			//Ans that's because  Future Velocity i
		FutureLocation = Char->GetActorLocation() + (Char->GetVelocity() * time_range);
		//FVector FutureSpawnLocation=
		
		return FutureLocation;
}
AActor* UAimingComponent::LineTrace()
{
	FHitResult Hit;
	//Turret->FindComponentByClass<>
	USceneComponent* SpawnPoint;
	FVector Start;
	SpawnPoint = Turret->SpawnPoint;
	if (SpawnPoint)
	{

		Start = SpawnPoint->GetComponentLocation();
		FVector End = Start + (SpawnPoint->GetComponentRotation().Vector()) * TraceRange;
		ECollisionChannel TraceChannel = ECollisionChannel::ECC_Pawn;

		bool Traceresult = GetWorld()->LineTraceSingleByChannel
		(
			Hit,
			Start,
			End,
			TraceChannel
		);
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, GetWorld()->GetDeltaSeconds(), '\000', 5.f);
		if (Traceresult)
		{
		//	UE_LOG(LogTemp, Warning, TEXT("I have hit %s"), *Hit.GetActor()->GetName())
		}

		return Hit.GetActor();
	}
	else return nullptr;
	
	
}
void UAimingComponent::Patrol()
{
	if(IsValid(Turret))
	{
		//FPlatformTime::Seconds Returns Integer Seconds not fractions ??
		float DeltaRotaion = (FMath::Sin((Time + GetWorld()->GetDeltaSeconds()) * Turret->PatrolFrequency) - FMath::Sin(Time * Turret->PatrolFrequency));///Frequency
		//UE_LOG(LogTemp, Warning, TEXT("Rotation %f"), DeltaRotaion)

		FRotator CurrentRot = Turret->Cabinet->GetComponentRotation();
		CurrentRot.Yaw += DeltaRotaion * (Turret->UpperRotationRange - Turret->LowerRotationRange);
		Turret->Cabinet->SetWorldRotation(CurrentRot);
	}
}
float UAimingComponent::TruncSin(float T)
{
	float Y = FMath::Sin(T);
	if (Y < 0)
	{
		return -1;
	}
	else { return 1; }
}



////Target Loc
///Angular Velocity