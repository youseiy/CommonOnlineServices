// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CommonOnlineAuthSubsystem.h"
#include "Subsystems/CommonOnlineServicesSubsystem.h"

UE::Online::IAuthPtr UCommonOnlineAuthSubsystem::GetAuthPtr()
{
	return AuthPtr;
}

void UCommonOnlineAuthSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


	AuthPtr=GetGameInstance()->GetSubsystem<UCommonOnlineServicesSubsystem>()->GetAuthPtr();
	
	ensureMsgf(AuthPtr,TEXT("AuthPtr not valid on Auth Subsystem"));
	
}

void UCommonOnlineAuthSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
bool UCommonOnlineAuthSubsystem::IsLoggedIn(int32 ControllerIndex) const
{
	if (AccountInfos.Contains(ControllerIndex))
	{
		const auto Account=*AccountInfos.Find(ControllerIndex);
		
		return AuthPtr->IsLoggedIn(Account->AccountId);
	}
	return false;
}

void UCommonOnlineAuthSubsystem::AddLoggedAccount(int32 Controller, const TSharedRef<UE::Online::FAccountInfo>& AccountLogged)
{
	AccountInfos.Add(Controller, AccountLogged);
}

UE::Online::FAccountInfo UCommonOnlineAuthSubsystem::GetLoggedAccount(int32 Controller) const
{
	if (AccountInfos.Contains(Controller))
	{
		return AccountInfos.Find(Controller)->Get();
	}
	return UE::Online::FAccountInfo{};
}
