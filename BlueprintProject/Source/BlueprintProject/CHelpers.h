#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CHelpers.generated.h"

UCLASS()
class BLUEPRINTPROJECT_API UCHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Debug")
		static void DebugPrintString(const FString& InString, int InKey = -1, float InDuration = 3, FColor InColor = FColor::Cyan, bool InNewerOnTop = true);

};
