#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTestActor.generated.h"

UCLASS()
class BLUEPRINTPROJECT_API ACTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTestActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
