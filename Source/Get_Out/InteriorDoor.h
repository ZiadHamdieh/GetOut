// Ziad Hamdieh 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "InteriorDoor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);


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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnCloseRequest;

private:

	AActor* Owner = nullptr;						// Object that exhibits the behaviour defined in this class

	UPROPERTY(EditAnywhere)
	float MinimumMassToOpenDoor = .1f;			// Minimum mass needed to trigger pressure plate (i.e. to open the door) (kg)	
		
	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorOpenPressurePlate = nullptr;// Pressure plate that closes the door when player walks over it
	float GetMassOnPlate();							// returns the total amount of mass currently on the pressure plate (kg)
};
