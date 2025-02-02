// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/CommonOnlineLeaveLobbyAsync.h"

#include "Kismet/GameplayStatics.h"
#include "Online/Lobbies.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "Subsystems/CommonOnlineAuthSubsystem.h"
#include "Subsystems/CommonOnlineLobbiesSubystem.h"


UCommonOnlineLeaveLobbyAsync* UCommonOnlineLeaveLobbyAsync::LeaveLobby(UObject* Context)
{
	auto AsyncTask=NewObject<UCommonOnlineLeaveLobbyAsync>();

	AsyncTask->RegisterWithGameInstance(Context);
	
	if (AsyncTask->IsRegistered())
	{
		AsyncTask->WorldContext=Context;
	}
	else
	{
		AsyncTask->SetReadyToDestroy();
	}
	return AsyncTask;
}
void UCommonOnlineLeaveLobbyAsync::Activate()
{
	Super::Activate();

	auto LobbiesPtr=GetWorld()->GetGameInstance()->GetSubsystem<UCommonOnlineLobbiesSubsystem>()->GetLobbiesPtr();
	auto AuthPtr=GetWorld()->GetGameInstance()->GetSubsystem<UCommonOnlineAuthSubsystem>();

	const auto Account=AuthPtr->GetLoggedAccount(0); 
	

	
	UE::Online::FLeaveLobby::Params LeaveLobbyParams;
	LeaveLobbyParams.LocalAccountId=Account.AccountId;
	// do i need this? LeaveLobbyParams.LobbyId
	LobbiesPtr->LeaveLobby(MoveTemp(LeaveLobbyParams)).OnComplete([this](const UE::Online::TOnlineResult<UE::Online::FLeaveLobby>& Result)
	{
		if (!Result.IsOk())
		{
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Orange, FString::Printf(TEXT("OnLeaveLobbyComplete failed: %s."), *ToLogString(Result.GetErrorValue())));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Orange, FString::Printf(TEXT("OnLeaveLobbyComplete succeed: %s."), *ToLogString(Result.GetErrorValue())));
		}
		SetReadyToDestroy();
	});
	
}
