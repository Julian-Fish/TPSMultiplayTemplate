// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NWGameInstance.h"
#include "GameModeBase_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class TPSMULTIPLAYTEMPLATE_API AGameModeBase_Lobby : public AGameMode
{
	GENERATED_BODY()
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void UpdateSessionName(FName sessionName);

};
