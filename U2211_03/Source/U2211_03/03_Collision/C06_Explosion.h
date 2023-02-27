#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C06_Explosion.generated.h"

UCLASS()
class U2211_03_API AC06_Explosion : public AActor
{
	GENERATED_BODY()
	
public:	
	AC06_Explosion();

private:
	UPROPERTY(EditAnywhere, Category = "Particles")
	class UParticleSystem* Particles[3];

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnExplosion(int32 InIndex);

};
