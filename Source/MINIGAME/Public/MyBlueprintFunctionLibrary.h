// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <Runtime\Core\Public\Misc\Filehelper.h>
#include "MyBlueprintFunctionLibrary.generated.h"


/**
 * 
 */
UCLASS()
class MINIGAME_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		///I exposed these engine functions to the blueprints because parsing will be easier in blueprints
public:
		UFUNCTION(BlueprintCallable, Category = "File IO")
		static FString LoadFileToString(FString Filename);

		UFUNCTION(BlueprintCallable, Category = "File IO")
		static TArray<FString> LoadFileToStringArray(FString Filename);
};
