// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "EngineGlobals.h"
#include "Engine.h"

// define log category
DEFINE_LOG_CATEGORY_STATIC(LogFish, Log, All);

// new log marco
#define UE_LOG_FISH(str, ...) UE_LOG(LogFish, Log, TEXT(str), __VA_ARGS__);

// log on screen
#define UE_LOG_SCREEN(format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Blue, FString::Printf(TEXT(format), __VA_ARGS__));
