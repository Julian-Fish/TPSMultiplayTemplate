// Fill out your copyright notice in the Description page of Project Settings.


#include "CGetPhysicsConstraintComponent.h"

void UCGetPhysicsConstraintComponent::GetConstrainedActors(UPhysicsConstraintComponent* InputComponent, AActor*& ConstraintActor1, AActor*& ConstraintActor2, FName& Name1)
{
    ConstraintActor1 = InputComponent->ConstraintActor1;
    ConstraintActor2 = InputComponent->ConstraintActor2;

    Name1 = InputComponent->ComponentName1.ComponentName;

    // UPrimitiveComponent> OverrideComponent1

} // void GetConstrainedActors()

void UCGetPhysicsConstraintComponent::GetConstrainedComponents(UPhysicsConstraintComponent* InputComponent, UPrimitiveComponent*& ConstraintComponent1, UPrimitiveComponent*& ConstraintComponent2, FName& Name1, FName& Name2)
{

    if (InputComponent != NULL)
    {
        ConstraintComponent1 = InputComponent->OverrideComponent1.Get();
        ConstraintComponent2 = InputComponent->OverrideComponent2.Get();
        Name1 = InputComponent->ComponentName1.ComponentName;
        Name2 = InputComponent->ComponentName2.ComponentName;
    } // end if()

}
