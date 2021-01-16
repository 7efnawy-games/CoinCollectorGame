// Fill out your copyright notice in the Description page of Project Settings.


#include "GridHandler.h"

// Sets default values for this component's properties
UGridHandler::UGridHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGridHandler::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGridHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
int UGridHandler::GetValidGrid(TArray<int> Available)
{
	int Size=Available.Num();
	if (Size > 0)
	{

		uint32 Rand = rand() % Size;
		return Available[Rand];
	}
	return -1;


}

void UGridHandler::GenerateInitalAvailableGrids(UPARAM(ref) TArray<int> &Available, UPARAM() int Size)
{	for (int i = 0; i < Size; i++)
	{
		Available.Add(i);
	}
	
}
bool UGridHandler::IsValidGrid(UPARAM() int GridIndex, UPARAM() TArray<int>  Available)

{	
	
	if( Available.Find(GridIndex)<0)return false;
	return true;
}

