// Ziad Hamdieh 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ExteriorDoor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GET_OUT_API UExteriorDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExteriorDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnCloseRequest OnCloseRequest;

private:

	AActor* Owner = nullptr;								// Object that exhibits the behaviour defined in this class

	// Macros below

	UPROPERTY(VisibleAnywhere)				
	float DoorOpenAngle = 110.f;				// initial door opening angle
	//UPROPERTY(VisibleAnywhere)
	//float DoorCloseAngle = 180.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = .5f;					// Set time for door to close shut to 0.5 sec
	float LastDoorOpenTime;						// Variable for keeping track of the time the door was last open

	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorClosePressurePlate = nullptr;		// Pressure plate that closes the door when player walks over it

	UPROPERTY(EditAnywhere)
	AActor* ActorThatClosesDoor = nullptr;				// Variable for keeping track of which actor is responsible for triggering door closure
};
