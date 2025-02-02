// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online/Auth.h"
#include "Online/OnlineServices.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonOnlineAuthSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class COMMONONLINESERVICES_API UCommonOnlineAuthSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UE::Online::IAuthPtr GetAuthPtr();

	UFUNCTION(BlueprintCallable,Category=OSAuthSubsystem)
	bool IsLoggedIn(int32 ControllerIndex)const;

	void AddLoggedAccount(int32 Controller , const TSharedRef<UE::Online::FAccountInfo>& AccountLogged);

	UE::Online::FAccountInfo GetLoggedAccount(int32 Controller)const;


protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

private:
	UE::Online::IAuthPtr AuthPtr;

	TMap<int32,TSharedRef<UE::Online::FAccountInfo>> AccountInfos;
	
};
