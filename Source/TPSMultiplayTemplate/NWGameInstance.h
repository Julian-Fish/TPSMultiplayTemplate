// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <Interfaces/OnlineSessionInterface.h>
#include <OnlineSessionSettings.h>
#include "FindSessionsCallbackProxy.h"
#include "NWGameInstance.generated.h"

//USTRUCT(BlueprintType)
//struct FBlueprintSessionResult;

//USTRUCT(BlueprintType)
//struct FBlueprintSessionResult
//{
//	GENERATED_USTRUCT_BODY()
//
//		FOnlineSessionSearchResult OnlineResult;
//};
//USTRUCT(BlueprintType)
//struct FSessionResultWithName_NW
//{
//	GENERATED_USTRUCT_BODY()
//
//	FOnlineSessionSearchResult SearchResult;
//	FName SessionName;
//};
/**
 * 
 */
UCLASS()
class TPSMULTIPLAYTEMPLATE_API UNWGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UNWGameInstance();
	~UNWGameInstance();

protected:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "Session_NW")
	virtual void CreateSessionWithName_NW(FString sessionName);

	UFUNCTION(BlueprintCallable, Category = "Session_NW")
	virtual bool JoinServer();

	UFUNCTION(BlueprintCallable, Category = "Session_NW")
	virtual TArray<FBlueprintSessionResult> FindSessions_NW();

	UFUNCTION(BlueprintCallable, Category = "Session_NW")
	virtual void DestroyServer();

	UFUNCTION(BlueprintCallable, Category = "Session_NW")
	virtual FString GetSessionName(const FBlueprintSessionResult& result);

	UFUNCTION(BlueprintCallable, Category = "Session_NW")
	virtual void PrintSessionPlayer(const FBlueprintSessionResult& result);

	FName _sessionName;
	IOnlineSessionPtr _session;
	TSharedPtr<FOnlineSessionSearch> _sessionSearch;
	TSharedPtr<FOnlineSessionSettings> SessionSettings;

	// complete event
	void _onCreateSessionComplete(FName serverName, bool succeeded);
	void _onFindSessionComplete(bool succeeded);
	void _onJoinSessionComplete(FName serverName, EOnJoinSessionCompleteResult::Type Result);
	void _onDestroySessionComplete(FName serverName, bool succeeded);
};
