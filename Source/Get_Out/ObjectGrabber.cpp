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
	
}


// Called every frame
void UObjectGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	/// Get Player's View Point every frame
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,							
		OUT PlayerViewPointRotation
	);
	
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerReach * PlayerViewPointRotation.Vector());		// Vector that points to the player's reach
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0.f,
		7.5f
	);

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

}

