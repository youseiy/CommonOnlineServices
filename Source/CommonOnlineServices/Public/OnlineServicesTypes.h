// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online/Auth.h"
#include "Online/Lobbies.h"
#include "OnlineServicesTypes.generated.h"

UENUM(BlueprintType)
enum ELoginCredentialsType
{
	/*
	ONLINESERVICESINTERFACE_API extern const FName Auto;
	ONLINESERVICESINTERFACE_API extern const FName Password;
	ONLINESERVICESINTERFACE_API extern const FName ExchangeCode;
	ONLINESERVICESINTERFACE_API extern const FName PersistentAuth;
	ONLINESERVICESINTERFACE_API extern const FName Developer;
	ONLINESERVICESINTERFACE_API extern const FName RefreshToken;
	ONLINESERVICESINTERFACE_API extern const FName AccountPortal;
	ONLINESERVICESINTERFACE_API extern const FName ExternalAuth;
	 */
	Auto,
	Password,
	ExchangeCode,
	PersistentAuth,
	Developer,
	RefreshToken,
	AccountPortal,
	ExternalAuth
};
UENUM(BlueprintType)
enum EJoinPolicy
{
	/** 
	* Lobby can be found through searches based on attribute matching,
	* by knowing the lobby id, or by invitation.
	*/
	PublicAdvertised,

	/** Lobby may be joined by knowing the lobby id or by invitation. */
	PublicNotAdvertised,

	/** Lobby may only be joined by invitation. */
	InvitationOnly,
};


namespace CommonOnlineServices
{
	
	static FName EvaluateLoginType(ELoginCredentialsType LoginType)
	{
		switch (LoginType)
		{
		case Auto:return UE::Online::LoginCredentialsType::Auto;
		case Password:   return UE::Online::LoginCredentialsType::Password;
		case ExchangeCode: return UE::Online::LoginCredentialsType::ExchangeCode;
		case PersistentAuth: return UE::Online::LoginCredentialsType::PersistentAuth;
		case Developer: return UE::Online::LoginCredentialsType::Developer;
		case RefreshToken: return UE::Online::LoginCredentialsType::RefreshToken;
		case AccountPortal: return UE::Online::LoginCredentialsType::AccountPortal;
		case ExternalAuth: return UE::Online::LoginCredentialsType::ExternalAuth;
		}
		return {};
	}
	static UE::Online::ELobbyJoinPolicy EvaluateJoinPolicy(EJoinPolicy LobbyJoinPolicy)
	{
		switch (LobbyJoinPolicy)
		{
		case  InvitationOnly: return UE::Online::ELobbyJoinPolicy::InvitationOnly;

		case PublicAdvertised: return  UE::Online::ELobbyJoinPolicy::PublicAdvertised;
			
		case PublicNotAdvertised: return  UE::Online::ELobbyJoinPolicy::PublicNotAdvertised;
		}
		return UE::Online::ELobbyJoinPolicy::PublicAdvertised;
	}

	
}

