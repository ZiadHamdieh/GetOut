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
		// Bind input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UObjectGrabber::GrabObject);
		InputComponent->BindAction("Grab", IE_Released, this, &UObjectGrabber::ReleaseObject);
	}
}


void UObjectGrabber::GrabObject()
{
	// Reach out to object
	GetFirstPhysicsBody();
	// Note only LINE TRACEing when we reach out for object. This is to optimize performance
	// so the engine isn't getting overloaded with useless LINE TRACEing every frame unless we are trying to grab something

	// If Object is close enough, attach PhysicsHandle
}

void UObjectGrabber::ReleaseObject()
{
	// TODO release PhysicsHandle
}

FHitResult UObjectGrabber::GetFirstPhysicsBody() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	/// Get Player's View Point every frame
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerReach * PlayerViewPointRotation.Vector());

	/// Query Parameters
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	/// Ray-cast to player reach below
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	/// Log the Actor Hit
	AActor* ObjectHit = Hit.GetActor();
	if (ObjectHit) UE_LOG(LogTemp, Warning, TEXT("Hitting Object: %s"), *(ObjectHit->GetName()))
	
	return Hit;
}

// Called every frame
void UObjectGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If PhysicsHandle is attached, it means we are holding an object
	// Move object that is being grabbed
	


}

