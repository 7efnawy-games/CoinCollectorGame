// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIGAME_API UGridHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	int GetValidGrid(TArray<int>  Available);
	UFUNCTION(BlueprintCallable)
		void GenerateInitalAvailableGrids(UPARAM(ref) TArray<int>& Available, UPARAM() int Size);
	UFUNCTION(BlueprintCallable)
	bool IsValidGrid(UPARAM() int GridIndex, UPARAM() TArray<int>  Available);
};
