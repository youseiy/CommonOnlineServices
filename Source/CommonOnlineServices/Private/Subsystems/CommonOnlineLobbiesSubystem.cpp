// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CommonOnlineLobbiesSubystem.h"

#include "Subsystems/CommonOnlineServicesSubsystem.h"



void UCommonOnlineLobbiesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	LobbiesInterface=GetGameInstance()->GetSubsystem<UCommonOnlineServicesSubsystem>()->GetLobbiesPtr();
	
	ensureMsgf(LobbiesInterface,TEXT("LobbiesInterface not valid on Auth Subsystem"));
	
	
}

void UCommonOnlineLobbiesSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
UE::Online::ILobbiesPtr UCommonOnlineLobbiesSubsystem::GetLobbiesPtr()
{
	return LobbiesInterface;
}