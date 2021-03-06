// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase_Lobby.h"
#include <OnlineSubsystem.h>
#include "Helper/LogHelper.h"
#include "Engine/EngineBaseTypes.h"
#include "OnlineSubsystemTypes.h"
#include <Interfaces/OnlineSessionInterface.h>
#include <OnlineSessionSettings.h>


void AGameModeBase_Lobby::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

}

void AGameModeBase_Lobby::UpdateHostName(FName hostName)
{
	FUniqueNetIdRepl userid = GetGameInstance()->GetFirstGamePlayer()->GetPreferredUniqueNetId();

	if (IOnlineSubsystem* _subsystem = IOnlineSubsystem::Get())
	{
		IOnlineSessionPtr _session = _subsystem->GetSessionInterface();
		if (_session.IsValid())
		{
			// make settings
			TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bIsDedicated = false;
			SessionSettings->bIsLANMatch = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bUsesPresence = true;
			SessionSettings->NumPublicConnections = 4;
			SessionSettings->Set(FName("HOST_NAME"), hostName.ToString(), EOnlineDataAdvertisementType::Type::ViaOnlineServiceAndPing);

			FNamedOnlineSession* namedSession = _session->GetNamedSession(Cast<UNWGameInstance>(GetGameInstance())->GetCurrentSessionName());
			if (namedSession != NULL)
			{
				namedSession->SessionSettings = *SessionSettings;
			}
			UE_LOG_FISH("update host name");
		}
	}
}
