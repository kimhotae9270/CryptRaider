// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhsicsHandle = GetPhysicsHandle();
	if (PhsicsHandle && PhsicsHandle->GetGrabbedComponent() != nullptr){
		FVector TargetLocation = GetComponentLocation()+ GetForwardVector() * HoldDistance;
		PhsicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	

}	
void UGrabber::Grab(){
	UPhysicsHandleComponent* PhsicsHandle = GetPhysicsHandle();
	if (PhsicsHandle == nullptr){
		return;
	}
	
	FHitResult HitResult;
	if (GetGrabbableInReach(HitResult)){
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		AActor* HitActor = HitResult.GetActor();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhsicsHandle->GrabComponentAtLocationWithRotation(
		HitComponent,
		NAME_None,
		HitResult.ImpactPoint,
		GetComponentRotation()
		);
	
}
}
void UGrabber::Relese(){
	UPhysicsHandleComponent* PhsicsHandle = GetPhysicsHandle();
	
	if(PhsicsHandle && PhsicsHandle->GetGrabbedComponent() != nullptr){
		AActor* GrabbedActor = PhsicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhsicsHandle->ReleaseComponent();
	}
}
UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(result == nullptr){
		UE_LOG(LogTemp, Error, TEXT("need UPhysicsHandleComponent"));
	}
	return result;
	
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const{
	FVector start = GetComponentLocation();
	FVector End = start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(),start,End,FColor::Red);
	DrawDebugSphere(GetWorld(),End,10,10,FColor::Blue, false, 5);
	FCollisionShape Shape = FCollisionShape::MakeSphere(GrabRadius);
	
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Shape
		);
	
}


