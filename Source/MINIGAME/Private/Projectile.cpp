// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	//SetRootComponent(CollisionMesh);
	RootComponent = CollisionMesh;
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	//ProjectileMovement->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Projectile Beginplay"))

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);//Bind Event to this function
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlap);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Moving_ConstantSpeed)
	{
			
			FVector DeltaDistance = GetActorForwardVector() * DeltaTime * ProjectileSpeed;
			SetActorLocation(GetActorLocation() + DeltaDistance,true);
			TimeSinceLaunced += DeltaTime;
			//UE_LOG(LogTemp,Warning,TEXT("Projectile Moving %s"),*GetActorForwardVector().ToString())
			if (TimeSinceLaunced >= 10.f)
			{
				Destroy();
			}
	}
	if (IsHit)
	{
		if (HitTime >= AfterHitTime )
		{
			Destroy();
		}
		HitTime += DeltaTime;
	}
	
	
}
void AProjectile::LaunchProjectile(float Speed,float Damage)
{
	/*ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);///Local Space of the point
	ProjectileDamage =Damage;
	ProjectileMovement->Activate();*/
}
void AProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped Target"))
		LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	Moving_ConstantSpeed = false;
	IsHit = true;
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();
	
	
}
void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit Target"))
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	Moving_ConstantSpeed = false;
	IsHit = true;
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();
	
	
}
void AProjectile::LaunchProjectileConstantSpeed(float Speed, float Damage)
{

	Moving_ConstantSpeed = true;
	ProjectileDamage = Damage;
	ProjectileSpeed = Speed;
	return;
}

