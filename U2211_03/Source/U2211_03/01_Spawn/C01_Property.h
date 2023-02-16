#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Property.generated.h"

UCLASS()
class U2211_03_API AC01_Property : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		int32 A = 10;

	UPROPERTY(EditInstanceOnly)
		int32 B;

	UPROPERTY(EditDefaultsOnly)
		int32 C;

	UPROPERTY(VisibleAnywhere, Category = "Property")
		int D = 30;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Property")
		int Variable = 60;

public:	
	AC01_Property();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
