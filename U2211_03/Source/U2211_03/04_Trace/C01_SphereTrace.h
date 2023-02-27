#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "C01_SphereTrace.generated.h"

UCLASS()
class U2211_03_API AC01_SphereTrace : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Settings")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebug;

	UPROPERTY(EditAnywhere, Category = "Settings")
		float DrawDuration = 5;

	UPROPERTY(EditAnywhere, Category = "Settings")
		float MaxMass = 300;

	UPROPERTY(EditAnywhere, Category = "Settings")
		float ImpulseAmount = 5000;

private:
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* Particle;

public:	
	AC01_SphereTrace();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);


};
