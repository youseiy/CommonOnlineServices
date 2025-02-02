// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online/OnlineServices.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonOnlineServicesSubsystem.generated.h"

namespace UE::Online
{
	struct FAccountInfo;
}

/**
 * 
 */
UCLASS()
class COMMONONLINESERVICES_API UCommonOnlineServicesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	friend class UCommonOnlineLobbiesSubsystem;
	friend class UCommonOnlineAuthSubsystem;
	

public:

	UE::Online::IOnlineServicesPtr GetOnlineServicesPtr();
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
private:
	UE::Online::IAuthPtr GetAuthPtr();
	UE::Online::ISessionsPtr GetSessionsPtr();
	UE::Online::ILobbiesPtr GetLobbiesPtr();

	
	UE::Online::IOnlineServicesPtr OnlineServices;
	UE::Online::IAuthPtr AuthInterface;
	UE::Online::ILobbiesPtr LobbiesInterface;
	UE::Online::ISessionsPtr SessionsInterface;
	UE::Online::ISocialPtr SocialInterface;
	UE::Online::IConnectivityPtr ConnectivityInterface;
};
