// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/CommonOnlineFindLobbiesAsync.h"

#include "Online/Lobbies.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "Subsystems/CommonOnlineAuthSubsystem.h"
#include "Subsystems/CommonOnlineLobbiesSubystem.h"


UCommonOnlineFindLobbiesAsync* UCommonOnlineFindLobbiesAsync::FindLobbies(UObject* Context,int32 ControllerIndex,int32 MaxResults)
{
	auto AsyncTask=NewObject<UCommonOnlineFindLobbiesAsync>();
	
	AsyncTask->RegisterWithGameInstance(Context);
	if (AsyncTask->IsRegistered())
	{
		AsyncTask->WorldContext=Context;
		AsyncTask->ControllerIndex=ControllerIndex;
		AsyncTask->MaxResults=MaxResults;
	}
	else
	{
		AsyncTask->SetReadyToDestroy();
	}
	return AsyncTask;
}

UWorld* UCommonOnlineFindLobbiesAsync::GetWorld() const
{
	return WorldContext.IsValid()?WorldContext->GetWorld():nullptr;
}

void UCommonOnlineFindLobbiesAsync::Activate()
{
	Super::Activate();

	auto LobbiesPtr=GetWorld()->GetGameInstance()->GetSubsystem<UCommonOnlineLobbiesSubsystem>()->GetLobbiesPtr();
	auto AuthPtr=GetWorld()->GetGameInstance()->GetSubsystem<UCommonOnlineAuthSubsystem>();
	
	UE::Online::FFindLobbies::Params FindLobbiesParams;
	FindLobbiesParams.LocalAccountId=AuthPtr->GetLoggedAccount(ControllerIndex).AccountId;

	FindLobbiesParams.Filters.Add(UE::Online::FFindLobbySearchFilter{NAME_GameSession,UE::Online::ESchemaAttributeComparisonOp::Equals,true});

	FindLobbiesParams.MaxResults=MaxResults;
	
	//optional 
	//FindLobbiesParams.TargetUser;
	//FindLobbiesParams.LobbyId;
	

	
	LobbiesPtr->FindLobbies(MoveTemp(FindLobbiesParams)).OnComplete([this](const UE::Online::TOnlineResult<UE::Online::FFindLobbies>& Response)
	{
		if (!Response.IsOk())
		{
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Orange, FString::Printf(TEXT("FindLobbies failed.")));
			SetReadyToDestroy();
			return;
		}
		TArray<FOnlineLobby> Result;
		
		for (auto& FoundLobby : Response.GetOkValue().Lobbies)
		{
			Result.Add({FoundLobby});
		}
		OnLobbiesResult.Broadcast(Result);
		SetReadyToDestroy();
	});
	
}
