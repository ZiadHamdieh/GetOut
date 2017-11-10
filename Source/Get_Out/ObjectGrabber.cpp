// Ziad Hamdieh 2017

#include "ObjectGrabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UObjectGrabber::UObjectGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UObjectGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

// Search for the Physics Handle
void UObjectGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle!"), *(GetOwner()->GetName()))
}

void UObjectGrabber::SetupInputComponent()
{
	/// Search for the Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent) UE_LOG(LogTemp, Error, TEXT("%s missing Input Component!"), *(GetOwner()->GetName()))
	else
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UObjectGrabber::GrabObject);
		InputComponent->BindAction("Grab", IE_Released, this, &UObjectGrabber::ReleaseObject);
	}
}

void UObjectGrabber::GrabObject()
{
	// Reach out to object
	auto HitResult = GetNearestPhysicsBody();
	auto ObjectToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	// If Object is close enough, attach PhysicsHandle
	if (ActorHit) {
		PhysicsHandle->GrabComponent(
			ObjectToGrab,
			NAME_None,											// 'bones' disabled
			ObjectToGrab->GetOwner()->GetActorLocation(),
			true												// True to allow grabbed object to rotate
		);
	}											
}

void UObjectGrabber::ReleaseObject()
{
	PhysicsHandle->ReleaseComponent();
}

FHitResult UObjectGrabber::GetNearestPhysicsBody() const
{
	/// Query Parameters
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());	

	/// Ray-cast to player reach below
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetReachVectorStart(),
		GetReachVectorEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	//AActor* ObjectHit = Hit.GetActor();
	//if (ObjectHit) UE_LOG(LogTemp, Warning, TEXT("Hitting Object: %s"), *(ObjectHit->GetName()))
	
	return Hit;
}

// Called every frame
void UObjectGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector LineTraceEnd = GetReachVectorEnd();

	// If PhysicsHandle is attached, GrabbedComponent is not null,
	// which it means we are holding an object.
	if (PhysicsHandle->GrabbedComponent) {
		// Move object that is being grabbed by setting
		// its location to the LineTraceEnd, every frame.
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

FVector UObjectGrabber::GetReachVectorStart() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	/// Get Player's View Point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}

FVector UObjectGrabber::GetReachVectorEnd() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	/// Get Player's View Point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + (PlayerReach * PlayerViewPointRotation.Vector());
}
