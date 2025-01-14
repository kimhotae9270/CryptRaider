// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("trigger"));

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    AActor* ActorInfo = GetAcceptableActor();
    if (ActorInfo != nullptr){
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(ActorInfo->GetRootComponent());
        if (Component != nullptr){
            Component->SetSimulatePhysics(false);
        }
        ActorInfo->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetShouldMove(true);

    }else{
        Mover->SetShouldMove(false);
    }
}
void UTriggerComponent::SetMover(UMover* NewMover){
    Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
        
    
    for(AActor* Actor : Actors){
        if (Actor->ActorHasTag(Name) && !Actor->ActorHasTag("Grabbed"))
        {
            return Actor;
        }
    }
    return nullptr;
       
}

