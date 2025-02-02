// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineServicesTypes.h"
#include "Engine/CancellableAsyncAction.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "CommonOnlineHostLobbyAsync.generated.h"



UCLASS()
class COMMONONLINESERVICES_API UCommonOnlineHostLobbyAsync : public UCancellableAsyncAction
{
	GENERATED_BODY()

protected:
	TWeakObjectPtr<UObject> WorldContext;
	
	int32 ControllerIndex;
	
	FName LobbyName;
	
	EJoinPolicy JoinPolicy;
	
	int32 MaxMembers;
	
	bool bPresenceEnabled;

	FName MapName;
	
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable,Category=CommonOnlineServices, meta = (DefaultToSelf=Context,HidePin=Context,BlueprintInternalUseOnly = "true"))
	static UCommonOnlineHostLobbyAsync* HostLobby(UObject* Context,int32 PlayerControllerIndex,EJoinPolicy JoinPolicy,int32 MaxMembers, bool bPresenceEnabled,FName MapName);
	
	virtual UWorld* GetWorld() const override;


private:
	
};
