// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/CommonOnlineHostLobbyAsync.h"

#include "CommonOnlineServiceLibrary.h"
#include "OnlineServicesTypes.h"
#include "Online/Lobbies.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "Online/OnlineSessionNames.h"
#include "Online/Sessions.h"
#include "Subsystems/CommonOnlineLobbiesSubystem.h"
#include "Subsystems/CommonOnlineServicesSubsystem.h"


UCommonOnlineHostLobbyAsync* UCommonOnlineHostLobbyAsync::HostLobby(UObject* Context,int32 PlayerControllerIndex,EJoinPolicy JoinPolicy,int32 MaxMembers, bool bPresenceEnabled,FName MapName)
{
	auto obj=NewObject<UCommonOnlineHostLobbyAsync>();
	obj->RegisterWithGameInstance(Context);
	
	if (obj->IsRegistered())
	{
		obj->WorldContext=Context;
		obj->bPresenceEnabled=bPresenceEnabled;
		obj->JoinPolicy=JoinPolicy;
		obj->MaxMembers=MaxMembers;
		obj->ControllerIndex=PlayerControllerIndex;
		obj->MapName=MapName;
	}
	else
	{
		obj->SetReadyToDestroy();
	}
	return obj;
}



void UCommonOnlineHostLobbyAsync::Activate()
{
	Super::Activate();
	//TODO::SUPORT SESSIONS
	auto LobbiesPtr=GetWorld()->GetGameInstance()->GetSubsystem<UCommonOnlineLobbiesSubsystem>()->GetLobbiesPtr();

	UE::Online::FCreateLobby::Params CreateLobbyParams{};
	CreateLobbyParams.LocalAccountId=UCommonOnlineServiceLibrary::GetLocalAccountIdFromPlayerControllerIndex(WorldContext.Get(),ControllerIndex);
	CreateLobbyParams.JoinPolicy=CommonOnlineServices::EvaluateJoinPolicy(JoinPolicy);
	CreateLobbyParams.MaxMembers=MaxMembers;
	CreateLobbyParams.bPresenceEnabled = bPresenceEnabled;
	CreateLobbyParams.SchemaId= UE::Online::FSchemaId(TEXT("GameLobby"));
	CreateLobbyParams.LocalName=NAME_GameSession;

	CreateLobbyParams.UserAttributes.Emplace(SETTING_GAMEMODE, FString(TEXT("GameSession")));

	


	
	//test attributes
	CreateLobbyParams.Attributes.Emplace(SETTING_GAMEMODE, UE::Online::FSchemaVariant{FString{"GameLobby"}});
	CreateLobbyParams.Attributes.Emplace(SETTING_MAPNAME, UE::Online::FSchemaVariant{FString{"SomeMap"}});
	
	CreateLobbyParams.Attributes.Emplace(SETTING_MATCHING_TIMEOUT, UE::Online::FSchemaVariant{float{120.0f}});
	CreateLobbyParams.Attributes.Emplace(SETTING_SESSION_TEMPLATE_NAME, UE::Online::FSchemaVariant{FString{"GameSession"}});


	LobbiesPtr->CreateLobby(MoveTemp(CreateLobbyParams)).OnComplete([this](const UE::Online::TOnlineResult<UE::Online::FCreateLobby>& Result)
	{
		if (!Result.IsOk())
		{
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Orange, FString::Printf(TEXT("OnCreateLobbyComplete failed: %s."), *ToLogString(Result.GetErrorValue())));
			SetReadyToDestroy();
			return;
		}
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green, FString::Printf(TEXT("OnCreateLobbyComplete succeeded. Created lobby %s."), *ToLogString(Result.GetOkValue().Lobby->LobbyId)));
		if (GetWorld()->ServerTravel(UCommonOnlineServiceLibrary::GetMapAsServerURL(MapName.ToString())))
		{
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green, FString::Printf(TEXT("ServerTravel succeeded.")));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green, FString::Printf(TEXT("ServerTravel failed.")));
		}
		SetReadyToDestroy();
	});
}
UWorld* UCommonOnlineHostLobbyAsync::GetWorld() const
{
	return WorldContext.IsValid()?WorldContext->GetWorld():nullptr;
}
