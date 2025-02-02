// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/CommonOnlineJoinLobbyAsync.h"

#include "Kismet/GameplayStatics.h"
#include "Online/Lobbies.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "Subsystems/CommonOnlineAuthSubsystem.h"
#include "Subsystems/CommonOnlineLobbiesSubystem.h"
#include "Subsystems/CommonOnlineServicesSubsystem.h"


UCommonOnlineJoinLobbyAsync* UCommonOnlineJoinLobbyAsync::JoinLobby(UObject* Context,int32 PlayerControllerIndex, const FOnlineLobby& Lobby, bool PresenceEnabled)
{
	auto* AsyncTask=NewObject<UCommonOnlineJoinLobbyAsync>();
	AsyncTask->RegisterWithGameInstance(Context);
	
	if (AsyncTask->IsRegistered())
	{
		AsyncTask->WorldContext=Context;
		AsyncTask->bPresenceEnabled=PresenceEnabled;
		AsyncTask->LobbyToJoin=Lobby;
		AsyncTask->PlayerControllerIndex=PlayerControllerIndex;
	}
	else
	{
		AsyncTask->SetReadyToDestroy();
	}
	return AsyncTask;
	
}
void UCommonOnlineJoinLobbyAsync::Activate()
{
	Super::Activate();

	auto LobbiesPtr=GetWorld()->GetGameInstance()->GetSubsystem<UCommonOnlineLobbiesSubsystem>()->GetLobbiesPtr();
	auto AuthPtr=GetWorld()->GetGameInstance()->GetSubsystem<UCommonOnlineAuthSubsystem>();
	auto OnlineServicesPtr=GetWorld()->GetGameInstance()->GetSubsystem<UCommonOnlineServicesSubsystem>()->GetOnlineServicesPtr();

	auto ControllerToJoin=UGameplayStatics::GetPlayerControllerFromID(WorldContext.Get(),PlayerControllerIndex);
	
	const auto Account=AuthPtr->GetLoggedAccount(PlayerControllerIndex); 
	
	UE::Online::FJoinLobby::Params JoinLobbyParams;
	JoinLobbyParams.LocalAccountId=Account.AccountId;
	JoinLobbyParams.bPresenceEnabled=bPresenceEnabled;
	JoinLobbyParams.LobbyId=LobbyToJoin.GetLobby().LobbyId;
	JoinLobbyParams.LocalName=LobbyToJoin.GetLobby().LocalName;
	JoinLobbyParams.UserAttributes=LobbyToJoin.GetLobby().Attributes;
	

	
	LobbiesPtr->JoinLobby(MoveTemp(JoinLobbyParams)).OnComplete([this,Account,OnlineServicesPtr,ControllerToJoin](const UE::Online::TOnlineResult<UE::Online::FJoinLobby>& Result)
	{
		if (!Result.IsOk())
		{
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Orange, FString::Printf(TEXT("OnJoinLobbyComplete failed: %s."), *ToLogString(Result.GetErrorValue())));
			SetReadyToDestroy();
			return;
		}

		UE::Online::FLobby Lobby = *Result.GetOkValue().Lobby;
		
		if (Account.AccountId.IsValid())
		{
			UE::Online::TOnlineResult<UE::Online::FGetResolvedConnectString> GetResolvedConnectStringResult = OnlineServicesPtr->GetResolvedConnectString({Account.AccountId, Lobby.LobbyId});
			
			if (!GetResolvedConnectStringResult.IsOk())
			{
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Orange, FString::Printf(TEXT("GetResolvedConnectString failed %s"), *ToLogString(Result.GetErrorValue())));
				SetReadyToDestroy();
				return;
			}
			
			const FString TravelURL = GetResolvedConnectStringResult.GetOkValue().ResolvedConnectString;
			
			ensure(ControllerToJoin);
			GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Cyan, FString::Printf(TEXT("ClientTravel initiated to %s"), *TravelURL));
			ControllerToJoin->ClientTravel(TravelURL, TRAVEL_Absolute);
		}
	});
};
