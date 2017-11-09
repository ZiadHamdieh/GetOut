// Ziad Hamdieh 2017

#include "ObjectGrabber.h"
#include "Gameframework/Actor.h"


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

	FString ObjectName = GetOwner()->GetName();
	FString ObjectPos = GetOwner()->GetActorTransform().GetLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s is at Position %s"), *ObjectName, *ObjectPos);
	
}


// Called every frame
void UObjectGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

