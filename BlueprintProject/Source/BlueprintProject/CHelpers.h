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
		static void DebugPrintString(const FString& InString, int InKey = -1, float InDuration = 3, FLinearColor InColor = FLinearColor(0, 1, 1, 1), bool InNewerOnTop = true);

};
