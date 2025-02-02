// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineLobbiesTypes.h"
#include "Engine/CancellableAsyncAction.h"
#include "CommonOnlineFindLobbiesAsync.generated.h"


UCLASS()
class COMMONONLINESERVICES_API UCommonOnlineFindLobbiesAsync : public UCancellableAsyncAction
{
	GENERATED_BODY()

	int32 ControllerIndex;

	int32 MaxResults{20};
	
	virtual void Activate() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLobbiesResult,TArray<FOnlineLobby>, Result);
	UPROPERTY(BlueprintAssignable)
	FOnLobbiesResult OnLobbiesResult;
	
	UFUNCTION(BlueprintCallable,Category=CommonOnlineServices,meta=(BlueprintInternalUseOnly = "true",DefaultToSelf=Context,HidePin=Context))
	static UCommonOnlineFindLobbiesAsync* FindLobbies(UObject* Context,int32 ControllerIndex=0,int32 MaxResults=20);
	
	TWeakObjectPtr<UObject> WorldContext;

protected:
	virtual UWorld* GetWorld() const override;
};
