// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Online/Lobbies.h"
#include "OnlineLobbiesTypes.generated.h"

/*
struct FLobby
{
	FLobbyId LobbyId;
	FAccountId OwnerAccountId;
	FName LocalName;
	FSchemaId SchemaId;
	int32 MaxMembers;
	ELobbyJoinPolicy JoinPolicy;
	TMap<FSchemaAttributeId, FSchemaVariant> Attributes;
	TMap<FAccountId, TSharedRef<const FLobbyMember>> Members;
};
 */

namespace UE::Online
{
	struct FLobby;
}


USTRUCT(BlueprintType)
struct FOnlineLobby
{
	GENERATED_BODY()
	FOnlineLobby(): MaxMembers(0), Lobby()
	{
	};
	FOnlineLobby(const TSharedRef<const UE::Online::FLobby>& Lobby): LocalName(Lobby->LocalName),MaxMembers(Lobby->MaxMembers),Lobby(Lobby.Get())
	{
		for (auto& Attribute : Lobby->Attributes)
		{
			AttributeNamesDebug.Add(Attribute.Key);
		}
		
	}
	
	UPROPERTY(BlueprintReadOnly)
	FName LocalName;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxMembers;
	
	//Equivalent to TMap<FSchemaAttributeId, FSchemaVariant> Attributes; but only keys
	UPROPERTY(BlueprintReadOnly)
	TArray<FName> AttributeNamesDebug;

	FOnlineLobby& operator=(const FOnlineLobby& Other) const
	{
		FOnlineLobby Temp(Other);
		return Temp;
	}
	
	UE::Online::FLobby GetLobby() const
	{
		return Lobby;
	};
private:
	const UE::Online::FLobby Lobby;
};
