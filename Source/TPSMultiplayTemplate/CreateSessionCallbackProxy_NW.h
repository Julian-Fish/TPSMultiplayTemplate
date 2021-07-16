//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "CreateSessionCallbackProxy.h"
//#include "CreateSessionCallbackProxy_NW.generated.h"
//
///**
// * 
// */
//UCLASS()
//class TPSMULTIPLAYTEMPLATE_API UCreateSessionCallbackProxy_NW : public UCreateSessionCallbackProxy
//{
//	GENERATED_BODY()
//	
//	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Online|Session|NW")
//	static UCreateSessionCallbackProxy* CreateSession(UObject* WorldContextObject, class APlayerController* PlayerController, int32 PublicConnections, bool bUseLAN);
//
//	virtual void Activate() override;
//
//private:
//	// Internal callback when session creation completes, calls StartSession
//	void OnCreateCompleted(FName SessionName, bool bWasSuccessful);
//
//	// Internal callback when session creation completes, calls StartSession
//	void OnStartCompleted(FName SessionName, bool bWasSuccessful);
//
//	// The player controller triggering things
//	TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;
//
//	// The delegate executed by the online subsystem
//	FOnCreateSessionCompleteDelegate CreateCompleteDelegate;
//
//	// The delegate executed by the online subsystem
//	FOnStartSessionCompleteDelegate StartCompleteDelegate;
//
//	// Handles to the registered delegates above
//	FDelegateHandle CreateCompleteDelegateHandle;
//	FDelegateHandle StartCompleteDelegateHandle;
//
//	// Number of public connections
//	int NumPublicConnections;
//
//	// Whether or not to search LAN
//	bool bUseLAN;
//
//	// The world context object in which this call is taking place
//	UObject* WorldContextObject;
//};
