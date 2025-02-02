// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineServicesTypes.h"
#include "Engine/CancellableAsyncAction.h"
#include "Online/Auth.h"

#include "Online/Auth.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "Subsystems/CommonOnlineServicesSubsystem.h"
#include "CommonOnlineLoginAsync.generated.h"

class UOSAuthSubsystem;



UCLASS()
class COMMONONLINESERVICES_API UCommonOnlineLoginAsync : public UCancellableAsyncAction
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoginSuccessful);
	UPROPERTY(BlueprintAssignable)
	FOnLoginSuccessful OnLoginSuccessful;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoginError,FString, Error);
	UPROPERTY(BlueprintAssignable)
	FOnLoginError OnLoginError;

	int32 ControllerIndex;
	TWeakObjectPtr<UObject> WorldContext;
	ELoginCredentialsType Type;
	FString CredentialId;
	FString CredentialToken;

	TWeakObjectPtr<UCommonOnlineAuthSubsystem> OSAuthSubsystem;
	
	
	UFUNCTION(BlueprintCallable,Category=CommonOnlineServices, meta = (DefaultToSelf=Context,HidePin=Context,BlueprintInternalUseOnly = "true"))
	static UCommonOnlineLoginAsync* Login(UObject* Context,int32 PlayerControllerIndex,FString CredentialsId,FString CredentialToken,ELoginCredentialsType LoginType);
	
	virtual void Activate() override;

	virtual void Cancel() override;
	
	virtual void SetReadyToDestroy() override;
};
