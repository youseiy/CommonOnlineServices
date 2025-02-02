// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online/OnlineServices.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonOnlineLobbiesSubystem.generated.h"

/**
 * 
 */
UCLASS()
class COMMONONLINESERVICES_API UCommonOnlineLobbiesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UE::Online::ILobbiesPtr GetLobbiesPtr();

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
private:
	UE::Online::ILobbiesPtr LobbiesInterface;
};
