// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include <Runtime\Core\Public\Misc\Paths.h>
#include<Runtime\Core\Public\HAL\PlatformFilemanager.h>

FString UMyBlueprintFunctionLibrary::LoadFileToString(FString Filename)
{
	FString directory = FPaths::ProjectContentDir();
	FString result;
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*directory))
	{
		FString myfile=directory+"/"+ Filename;
		FFileHelper::LoadFileToString(result, *myfile);
	}
	return result;
}
TArray<FString> UMyBlueprintFunctionLibrary::LoadFileToStringArray(FString Filename)
{
	FString directory = FPaths::ProjectContentDir();
	TArray<FString> result;
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*directory))
	{
		FString myfile = directory + "/" + Filename;
		FFileHelper::LoadFileToStringArray(result, *myfile);
	}
	return result;
}