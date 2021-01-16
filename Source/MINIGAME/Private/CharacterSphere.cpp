// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSphere.h"

// Sets default values
ACharacterSphere::ACharacterSphere()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharacterSphereComponent = CreateDefaultSubobject<USphereComponent>("My Sphere");
	//EmptyRoot = CreateDefaultSubobject<USceneComponent>("My Root");
	//RootComponent = EmptyRoot;
	RootComponent = CharacterSphereComponent;
	CharacterSphereComponent->SetNotifyRigidBodyCollision(true);
	//CharacterSphereComponent->SetupAttachment(EmptyRoot);
	CharacterSphereComponent->InitSphereRadius(50.f);
	CharacterSphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	

	CharacterSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CharacterSphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	//CharacterSphereComponent->SetCollisionProfileName(FName)
	
	CharacterSphereComponent->SetSimulatePhysics(true);
	MovingForce = 100000.f;
	JumpingImpulse = 50000.f;
	Health = StartingHealth;
	LastFrameVelocity = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void ACharacterSphere::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterSphereComponent->OnComponentHit.AddDynamic(this,&ACharacterSphere::OnHit);
	OnActorBeginOverlap.AddDynamic(this, &ACharacterSphere::OnOverlap);
}
void ACharacterSphere::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	AProjectile* PotentialBullet = Cast<AProjectile>(OtherActor);
	if (!ensure(PotentialBullet)) { return; }
	
	GettingHit(PotentialBullet->ProjectileDamage);

}
// Called every frame
void ACharacterSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//int time = FGenericPlatformMath::TruncToInt(GetWorld()->GetTimeSeconds());
	AccelerationVector = (GetVelocity()- LastFrameVelocity) / GetWorld()->GetDeltaSeconds();
	LastFrameVelocity = GetVelocity();
}
void ACharacterSphere::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AProjectile* PotentialBullet = Cast<AProjectile>(OtherActor);
	if (!ensure(PotentialBullet)) { return; }
	
	GettingHit(PotentialBullet->ProjectileDamage);
	
}
// Called to bind functionality to input
void ACharacterSphere::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterSphere::MoveForward(float Value)
{
	//FVector Direction = GetActorForwardVector();
	FVector Direction = FVector(1, 0, 0);
	ForwardAxisVal = Value;

	ApplyForce(Direction, Value);
}

void ACharacterSphere::MoveRight(float Value)
{
	FVector Direction = FVector(0, 1, 0);
	RightAxisVal = Value;
	
	ApplyForce(Direction, Value);
	
}
void ACharacterSphere::Jump(float value)
{
	FVector Direction = FVector(0, 0, 1);
	
	CharacterSphereComponent->AddImpulse(Direction * JumpingImpulse, NAME_None, false);
}
///To Handle Different fps later
void ACharacterSphere::ApplyForce(FVector Direction,float Axis)
{	
	if (GetVelocity().Size() < MaxVelocity )
	{
		
		CharacterSphereComponent->AddForce(MovingForce * Axis * Direction, NAME_None, false);

	}
}

void ACharacterSphere::GettingHit(float Damage)
{	
	
	Health -=Damage;
	Health = FMath::Max(0.f, Health);
	if (Health == 0)
	{	
		OnDeath();
	}
}
void ACharacterSphere::OnDeath()
{

	GetWorld()->GetFirstPlayerController()->StartSpectatingOnly();
	//GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(GetWorld,2.f,)
}