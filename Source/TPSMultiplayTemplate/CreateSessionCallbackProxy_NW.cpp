//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "CreateSessionCallbackProxy_NW.h"
//#include <OnlineSubsystem.h>
//#include "Helper/LogHelper.h"
//#include "Engine/EngineBaseTypes.h"
//#include "OnlineSubsystemTypes.h"
//
//UCreateSessionCallbackProxy_NW::UCreateSessionCallbackProxy_NW(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//	, CreateCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateCompleted))
//	, StartCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartCompleted))
//	, NumPublicConnections(1)
//{
//}
//
//void UCreateSessionCallbackProxy_NW::Activate()
//{
//	FUniqueNetIdRepl userid = UGameInstance::GetFirstGamePlayer()->GetPreferredUniqueNetId();
//
//	if (IOnlineSubsystem* _subsystem = IOnlineSubsystem::Get())
//	{
//		auto Sessions = _subsystem->GetSessionInterface();
//
//		if (Sessions.IsValid())
//		{
//			CreateCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(CreateCompleteDelegate);
//
//			FOnlineSessionSettings* Settings;
//			Settings = MakeShareable(new FOnlineSessionSettings());
//			Settings.NumPublicConnections = NumPublicConnections;
//			Settings.bShouldAdvertise = true;
//			Settings.bAllowJoinInProgress = true;
//			Settings.bIsLANMatch = bUseLAN;
//			Settings.bUsesPresence = true;
//			Settings.bAllowJoinViaPresence = true;
//
//			Sessions->CreateSession(*userid, NAME_GameSession, Settings);
//
//			// OnCreateCompleted will get called, nothing more to do now
//			return;
//		}
//		else
//		{
//			FFrame::KismetExecutionMessage(TEXT("Sessions not supported by Online Subsystem"), ELogVerbosity::Warning);
//		}
//	}
//
//	// Fail immediately
//	OnFailure.Broadcast();
//}
//
//void UCreateSessionCallbackProxy_NW::OnCreateCompleted(FName SessionName, bool bWasSuccessful)
//{
//	if (IOnlineSubsystem* _subsystem = IOnlineSubsystem::Get())
//	{
//		auto Sessions = _subsystem->GetSessionInterface();
//
//		if (Sessions.IsValid())
//		{
//			Sessions->ClearOnCreateSessionCompleteDelegate_Handle(CreateCompleteDelegateHandle);
//
//			if (bWasSuccessful)
//			{
//				StartCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(StartCompleteDelegate);
//				Sessions->StartSession(NAME_GameSession);
//
//				// OnStartCompleted will get called, nothing more to do now
//				return;
//			}
//		}
//	}
//
//	if (!bWasSuccessful)
//	{
//		OnFailure.Broadcast();
//	}
//}
//
//void UCreateSessionCallbackProxy_NW::OnStartCompleted(FName SessionName, bool bWasSuccessful)
//{
//	if (IOnlineSubsystem* _subsystem = IOnlineSubsystem::Get())
//	{
//		auto Sessions = _subsystem->GetSessionInterface();
//
//		if (Sessions.IsValid())
//		{
//			Sessions->ClearOnStartSessionCompleteDelegate_Handle(StartCompleteDelegateHandle);
//		}
//	}
//
//	if (bWasSuccessful)
//	{
//		OnSuccess.Broadcast();
//	}
//	else
//	{
//		OnFailure.Broadcast();
//	}
//}
