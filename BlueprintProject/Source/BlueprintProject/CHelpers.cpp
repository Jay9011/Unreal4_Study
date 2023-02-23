#include "CHelpers.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(GP, Display, All)

void UCHelpers::DebugPrintString(const FString& InString, int InKey, float InDuration, FLinearColor InColor, bool InNewerOnTop)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor.ToFColor(false), InString, InNewerOnTop);
}