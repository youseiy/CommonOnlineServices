// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonOnlineServiceLibrary.generated.h"

/**
 * 
 */

UCLASS()
class COMMONONLINESERVICES_API UCommonOnlineServiceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	//todo: make wrappers so that we can expose to BP the most used things
public:
	static UE::Online::FAccountId GetLocalAccountIdFromPlayerControllerIndex(UObject* Context,int32 PlayerControllerIndex);

	static FString GetMapAsServerURL(const FString& Map);


};
