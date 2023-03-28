#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class EXAMPLE_API FExampleDebuggerCategory
	: public FGameplayDebuggerCategory
{
public:
	FExampleDebuggerCategory();
	~FExampleDebuggerCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

public:
	void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

private:
	struct FCategoryData
	{
		bool bDraw = false;
		FString Name;
		FVector Location;
		FVector Forward;
	};

private:
	FCategoryData PlayerPawnData;
	FCategoryData ForwardActorData;
	FCategoryData DebugActorData;

private:
	float TraceDistance = 500;
};
