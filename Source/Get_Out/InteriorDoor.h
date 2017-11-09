// Ziad Hamdieh 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "InteriorDoor.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GET_OUT_API UInteriorDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteriorDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	AActor* Owner;									// Object that exhibits the behaviour defined in this class

	// Macros below

	UPROPERTY(VisibleAnywhere)
		float DoorOpenAngle = -135.f;				// Set door opening angle to 45 deg
	UPROPERTY(VisibleAnywhere)
		float DoorCloseAngle = -90.f;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = .75f;					// Set time for door to close shut to 0.5 sec
		float LastDoorOpenTime;						// Variable for keeping track of the time the door was last open

	UPROPERTY(EditAnywhere)
		ATriggerVolume* DoorOpenPressurePlate;		// Pressure plate that closes the door when player walks over it

	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpensDoor;					// Variable for keeping track of which actor is responsible for triggering door closure
};
