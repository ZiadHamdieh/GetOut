// Ziad Hamdieh 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GET_OUT_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)				
	float DoorAngle = 45.f;					// Set initial door angle to 45 deg

	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorClosePressurePlate;	// Pressure plate that closes the door when player walks over it

	UPROPERTY(EditAnywhere)
	AActor* ActorThatClosesDoor;

	
};
