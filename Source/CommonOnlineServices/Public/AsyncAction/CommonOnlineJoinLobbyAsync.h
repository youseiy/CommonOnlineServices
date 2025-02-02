// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineLobbiesTypes.h"
#include "Engine/CancellableAsyncAction.h"
#include "CommonOnlineJoinLobbyAsync.generated.h"

/**
 * 
 */
UCLASS()
class COMMONONLINESERVICES_API UCommonOnlineJoinLobbyAsync : public UCancellableAsyncAction
{
	GENERATED_BODY()

protected:
	virtual void Activate() override;
	
	UPROPERTY(EditAnywhere)
	FOnlineLobby LobbyToJoin;
	UPROPERTY(EditAnywhere)
	bool bPresenceEnabled;
	
	int32 PlayerControllerIndex;
	
	UFUNCTION(BlueprintCallable,Category=CommonOnlineServices,meta=(BlueprintInternalUseOnly=true,DefaultToSelf="Context",HidePin="Context"))
	static UCommonOnlineJoinLobbyAsync* JoinLobby(UObject* Context,int32 PlayerControllerIndex, const FOnlineLobby& Lobby, bool PresenceEnabled=true);


	TWeakObjectPtr<UObject> WorldContext;
};
