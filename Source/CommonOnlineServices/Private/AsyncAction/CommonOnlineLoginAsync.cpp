// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/CommonOnlineLoginAsync.h"
#include "OnlineServicesTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineResult.h"
#include "Subsystems/CommonOnlineAuthSubsystem.h"


UCommonOnlineLoginAsync* UCommonOnlineLoginAsync::Login(UObject* Context,int32 PlayerControllerIndex,FString CredentialsId,FString CredentialToken,ELoginCredentialsType LoginType)
{
	auto* AsyncTask=NewObject<UCommonOnlineLoginAsync>();
	AsyncTask->RegisterWithGameInstance(Context);
	if (AsyncTask->IsRegistered())
	{
		AsyncTask->WorldContext=Context;
		AsyncTask->CredentialId=CredentialsId;
		AsyncTask->CredentialToken=CredentialToken;
		AsyncTask->Type=LoginType;
		AsyncTask->ControllerIndex=PlayerControllerIndex;
	}
	else
	{
		AsyncTask->SetReadyToDestroy();
	}
	return AsyncTask;
}

void UCommonOnlineLoginAsync::Activate()
{
	Super::Activate();
	if (!WorldContext.IsValid())
	{
		SetReadyToDestroy();
		return;
	}
	
	OSAuthSubsystem=WorldContext->GetWorld()->GetGameInstance()->GetSubsystem<UCommonOnlineAuthSubsystem>();
	if (!OSAuthSubsystem.IsValid())
	{
		SetReadyToDestroy();
		return;
	}
	
	APlayerController* ControllerToLogin=UGameplayStatics::GetPlayerControllerFromID(WorldContext.Get(),ControllerIndex);

	UE::Online::FAuthLogin::Params AuthParams;
	AuthParams.PlatformUserId=ControllerToLogin->GetPlatformUserId();
	AuthParams.CredentialsType= CommonOnlineServices::EvaluateLoginType(Type);
	//AuthParams.CredentialsId
	//AuthParams.CredentialsToken=WorldContext->GetWorld()->GetFirstPlayerController()

	
	OSAuthSubsystem->GetAuthPtr()->Login(MoveTempIfPossible(AuthParams)).OnComplete([this](const UE::Online::TOnlineResult<UE::Online::FAuthLogin>& Result)
	{
		if(Result.IsOk())
		{
			const TSharedRef<UE::Online::FAccountInfo> AccountInfo = Result.GetOkValue().AccountInfo;
			// AccountInfo object is now accessible

			OSAuthSubsystem->AddLoggedAccount(0,Result.GetOkValue().AccountInfo);
			
			if (ShouldBroadcastDelegates())
			{
				OnLoginSuccessful.Broadcast();
			}
		}
		else
		{
			auto Error = Result.GetErrorValue();

			if (ShouldBroadcastDelegates())
			{
				OnLoginError.Broadcast(Error.GetFriendlyErrorCode());	
			}
		}
		SetReadyToDestroy();
	});
	
}

void UCommonOnlineLoginAsync::Cancel()
{
	OSAuthSubsystem.Reset();
	Super::Cancel();
}

void UCommonOnlineLoginAsync::SetReadyToDestroy()
{
	OSAuthSubsystem.Reset();
	Super::SetReadyToDestroy();
}
