// Fill out your copyright notice in the Description page of Project Settings.


#include "NWGameInstance.h"
#include <OnlineSubsystem.h>
#include "Helper/LogHelper.h"
#include "Engine/EngineBaseTypes.h"
#include "OnlineSubsystemTypes.h"

UNWGameInstance::UNWGameInstance()
{

}

UNWGameInstance::~UNWGameInstance()
{
	//UE_LOG_FISH("Quit Game");
	//_session->DestroySession(_sessionName);
}

void UNWGameInstance::Init()
{
	UE_LOG_FISH("Init GameInstance");
	if (IOnlineSubsystem* _subsystem = IOnlineSubsystem::Get())
	{
		_session = _subsystem->GetSessionInterface();

		if (_session.IsValid())
		{
			//_session->OnCreateSessionCompleteDelegates.AddUObject(this, &UNWGameInstance::_onCreateSessionComplete);
			//_session->OnFindSessionsCompleteDelegates.AddUObject(this, &UNWGameInstance::_onFindSessionComplete);
			//_session->OnJoinSessionCompleteDelegates.AddUObject(this, &UNWGameInstance::_onJoinSessionComplete);
			//_session->OnDestroySessionCompleteDelegates.AddUObject(this, &UNWGameInstance::_onDestroySessionComplete);
		}
	}
	else
	{
		UE_LOG_SCREEN("init online subsystem failed");
	}
}

void UNWGameInstance::CreateSessionWithName_NW(FString sessionName)
{
	FUniqueNetIdRepl userid = GetFirstGamePlayer()->GetPreferredUniqueNetId();
	//FOnlineSessionSetting nameSetting = new FOnlineSessionSetting<int>(FName("julianfish"));

	SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bAllowJoinInProgress = true;
	SessionSettings->bAllowJoinViaPresence = true;
	SessionSettings->bIsDedicated = false;
	SessionSettings->bIsLANMatch = true;
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUsesPresence = true;
	SessionSettings->NumPublicConnections = 4;
	SessionSettings->Set(FName("SESSION_NAME"), sessionName, EOnlineDataAdvertisementType::Type::ViaOnlineServiceAndPing);

	if (_session->CreateSession(*userid, FName(*sessionName), *SessionSettings))
	{
		// create successed
		UE_LOG_SCREEN("create session succeeded. Name: %s", *sessionName);
		_sessionName = FName(*sessionName);
	}
	else
	{
		// create failed
		UE_LOG_SCREEN("create session failed");
	}
}

TArray<FBlueprintSessionResult> UNWGameInstance::FindSessions_NW()
{
	FUniqueNetIdRepl userid = GetFirstGamePlayer()->GetPreferredUniqueNetId();
	TArray<FBlueprintSessionResult> results;
	//TArray<FSessionResultWithName_NW> namedSessionResults;
	//FOnlineSessionSearch SessionSearchSetting;
	_sessionSearch = MakeShareable(new FOnlineSessionSearch());

	_sessionSearch->bIsLanQuery = true;
	_sessionSearch->MaxSearchResults = 20;
	_sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	if (_session->FindSessions(*userid, _sessionSearch.ToSharedRef()))
	{
		// found sessions
		//for (FOnlineSessionSearchResult m : _sessionSearch->SearchResults)
		//{
		//	FSessionResultWithName_NW n;
		//	
		//	n.SearchResult = m;
		//	n.SessionName = ((FNamedOnlineSession)(m.Session)).SessionName;
		//	namedSessionResults.Add(n);
		//}
		//return namedSessionResults;

		for (FOnlineSessionSearchResult m : _sessionSearch->SearchResults)
		{
			FBlueprintSessionResult n;
			n.OnlineResult = m;
			results.Add(n);
		}

		return results;
	}
	else
	{
		// cannot found sessions
		_onFindSessionComplete(false);
		return results;
	}
}


bool UNWGameInstance::JoinServer()
{
	bool succeeded = false;

	FUniqueNetIdRepl userid = GetFirstGamePlayer()->GetPreferredUniqueNetId();
	if (_session.IsValid() && userid.IsValid())
	{
		succeeded = _session->JoinSession(*userid, FName("Fish Test Session"), _sessionSearch->SearchResults[0]);
	}

	return succeeded;
}

void UNWGameInstance::DestroyServer()
{
	_session->DestroySession(_sessionName);
}

FString UNWGameInstance::GetSessionName(const FBlueprintSessionResult& result)
{

	for (auto m : result.OnlineResult.Session.SessionSettings.Settings)
	{
		
		if (m.Key == FName("SESSION_NAME"))
		{
			return m.Value.Data.ToString();
		}
		//UE_LOG_FISH("key: %s", *m.Key.ToString());
		//UE_LOG_FISH("value: %s", *m.Value.Data.ToString());
	}

	return "";
}

void UNWGameInstance::PrintSessionPlayer(const FBlueprintSessionResult& result)
{
	UE_LOG_FISH("num of connections: %d", result.OnlineResult.Session.NumOpenPublicConnections);
}

void UNWGameInstance::_onCreateSessionComplete(FName serverName, bool succeeded)
{
	if (succeeded)
	{
		UE_LOG_FISH("create session(%s) succeeded", *(serverName.ToString()));
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Lobby"), true, "listen");
		//GetWorld()->ServerTravel("/Game/FirstPersonCPP/Maps/FirstPersonExampleMap?listen");
	}
}

void UNWGameInstance::_onFindSessionComplete(bool succeeded)
{

	if (succeeded & _sessionSearch != NULL)
	{
		UE_LOG_FISH("find session succeeded");
		UE_LOG_SCREEN("Search Results Numbers: %d", _sessionSearch->SearchResults.Num())
			if (_sessionSearch->SearchResults.Num() > 0)
			{
				for (int i = 0; i < _sessionSearch->SearchResults.Num(); ++i)
				{
					UE_LOG_SCREEN("Session %d : %s", i + 1, *(_sessionSearch->SearchResults[i].Session.OwningUserName));
				}
			}
	}
	else
	{
		UE_LOG_FISH("cannot find session");
	}


}

void UNWGameInstance::_onJoinSessionComplete(FName serverName, EOnJoinSessionCompleteResult::Type Result)
{

	switch (Result)
	{
		// success
	case 0:
		UE_LOG_SCREEN("join session(%s) successed", *(serverName.ToString()));
		if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			FString JoinAddress = "";
			_session->GetResolvedConnectString(serverName, JoinAddress);
			if (JoinAddress != "")
			{
				UE_LOG_SCREEN("client trvel to %s", *JoinAddress);
				PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute, true);
			}
		}
		break;
		// full
	case 1:
		UE_LOG_SCREEN("session(%s) is full", *(serverName.ToString()));
		break;
		// not exist
	case 2:
		UE_LOG_SCREEN("session(%s) is not exist", *(serverName.ToString()));
		break;
		//unknown error
	case 5:
		UE_LOG_SCREEN("join session(%s) failed: unknown error", *(serverName.ToString()));
		break;
	}
}

void UNWGameInstance::_onDestroySessionComplete(FName serverName, bool succeeded)
{
	if (succeeded)	UE_LOG_FISH("destroy session(%s) succeeded", *(serverName.ToString()));
}