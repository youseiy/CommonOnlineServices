// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CommonOnlineServicesSubsystem.h"

#include "OnlineLobbiesTypes.h"
#include "Logging/StructuredLog.h"
#include "Online/OnlineServicesEngineUtils.h"




void UCommonOnlineServicesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
#if WITH_EDITOR
	OnlineServices = UE::Online::GetServices(UE::Online::EOnlineServices::Null);
#else
	OnlineServices = UE::Online::GetServices(UE::Online::EOnlineServices::Default);
#endif

	UE_LOGFMT(LogCommonOnlineServicesSubsystem,Display,"OnlineServicesSubsystem {ServiceName} initialized",OnlineServices->GetInstanceName());
	
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

