// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CommonOnlineServicesSubsystem.h"

#include "Online/OnlineServicesEngineUtils.h"




void UCommonOnlineServicesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	OnlineServices = UE::Online::GetServices(UE::Online::EOnlineServices::Epic);
	
	ensureMsgf(OnlineServices,TEXT("OnlineServices not initialized."));
	
	if (OnlineServices)
	{
		AuthInterface = OnlineServices->GetAuthInterface();
		SessionsInterface= OnlineServices->GetSessionsInterface();
		LobbiesInterface= OnlineServices->GetLobbiesInterface();
		SocialInterface= OnlineServices->GetSocialInterface();
		ConnectivityInterface= OnlineServices->GetConnectivityInterface();
	}
	
	
}

void UCommonOnlineServicesSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
}
UE::Online::IOnlineServicesPtr UCommonOnlineServicesSubsystem::GetOnlineServicesPtr()
{
	return OnlineServices;
}
UE::Online::IAuthPtr UCommonOnlineServicesSubsystem::GetAuthPtr()
{
	return AuthInterface;
}

UE::Online::ISessionsPtr UCommonOnlineServicesSubsystem::GetSessionsPtr()
{
	return SessionsInterface;
}

UE::Online::ILobbiesPtr UCommonOnlineServicesSubsystem::GetLobbiesPtr()
{
	return LobbiesInterface;
}

