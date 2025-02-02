// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/CancellableAsyncAction.h"
#include "CommonOnlineLeaveLobbyAsync.generated.h"

/**
 * 
 */
UCLASS()
class COMMONONLINESERVICES_API UCommonOnlineLeaveLobbyAsync : public UCancellableAsyncAction
{
	GENERATED_BODY()
	
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable,Category=CommonOnlineServices,meta=(BlueprintInternalUseOnly=true,DefaultToSelf=Context,HidePin=Context))
	static UCommonOnlineLeaveLobbyAsync* LeaveLobby(UObject* Context);
	
	TWeakObjectPtr<UObject> WorldContext;
};
