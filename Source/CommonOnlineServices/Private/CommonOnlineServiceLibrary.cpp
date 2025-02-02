// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonOnlineServiceLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Online/Auth.h"
#include "Online/OnlineResult.h"
#include "Subsystems/CommonOnlineAuthSubsystem.h"

UE::Online::FAccountId UCommonOnlineServiceLibrary::GetLocalAccountIdFromPlayerControllerIndex(UObject* Context,
                                                                                               int32 PlayerControllerIndex)
{
	if (!Context)
	{
		return UE::Online::FAccountId();
	}
	UWorld* World=Context->GetWorld();
	
	if (!World)
	{
		return UE::Online::FAccountId();
	}
	
	const auto AuthSubsystem=World->GetGameInstance()->GetSubsystem<UCommonOnlineAuthSubsystem>();
	
	return AuthSubsystem->GetLoggedAccount(PlayerControllerIndex).AccountId;
}

FString UCommonOnlineServiceLibrary::GetMapAsServerURL(const FString& Map)
{
	return Map+TEXT("?listen");
}
