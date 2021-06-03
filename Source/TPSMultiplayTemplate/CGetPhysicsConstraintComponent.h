// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "CGetPhysicsConstraintComponent.generated.h"

/**
 * 
 */
UCLASS()
class TPSMULTIPLAYTEMPLATE_API UCGetPhysicsConstraintComponent : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintPure, Category = "BP_Function")
        static void GetConstrainedActors(UPhysicsConstraintComponent* InputComponent, AActor*& ConstraintActor1, AActor*& ConstraintActor2, FName& Name1);


    UFUNCTION(BlueprintPure, Category = "BP_Function")
        static void GetConstrainedComponents(UPhysicsConstraintComponent* InputComponent, UPrimitiveComponent*& ConstraintComponent1, UPrimitiveComponent*& ConstraintComponent2, FName& Name1, FName& Name2);
};