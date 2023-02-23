#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C04_Trigger.generated.h"

DECLARE_DELEGATE(FBoxLightOverlap); // void func_name()


UCLASS()
class U2211_03_API AC04_Trigger : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
		class UTextRenderComponent* Text;

public:	
	AC04_Trigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOvelap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FBoxLightOverlap OnBoxLightBeginOverlap;
	FBoxLightOverlap OnBoxLightEndOverlap;

};
