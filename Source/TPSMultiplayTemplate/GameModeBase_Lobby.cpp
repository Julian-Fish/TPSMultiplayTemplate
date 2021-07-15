// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase_Lobby.h"
#include "Helper/LogHelper.h"

// https://answers.unrealengine.com/questions/564834/num-players-in-session-isnt-refreshed.html
void AGameModeBase_Lobby::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG_FISH("custom login");
	if (this->GameSession)
	{
		FJoinabilitySettings OutSettings;
		this->GameSession->GetSessionJoinability()
	}
}