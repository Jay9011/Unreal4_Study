#pragma once

#include "CoreMinimal.h"

class EXAMPLE_API FExampleStyle
{
public:
	static TSharedPtr<FExampleStyle> Get();
	static void Shutdown();

private:
	static TSharedPtr<FExampleStyle> Instance;

public:
	FExampleStyle();
	~FExampleStyle();

private:
	static const FName StyleSetName;
	TSharedPtr<class FSlateStyleSet> StyleSet;
};
