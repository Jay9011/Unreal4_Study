#include "ExampleStyle.h"

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

const FName FExampleStyle::StyleSetName = "ExampleStyle";

TSharedPtr<FExampleStyle> FExampleStyle::Instance = nullptr;

TSharedPtr<FExampleStyle> FExampleStyle::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new FExampleStyle());

	return Instance;
}

void FExampleStyle::Shutdown()
{
	if (Instance.IsValid())
		Instance.Reset();
}

FExampleStyle::FExampleStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	FString path = FPaths::ProjectPluginsDir() / "Example" / "Resources";
	StyleSet->SetContentRoot(path);

	GLog->Log(ELogVerbosity::Warning, path);
}

FExampleStyle::~FExampleStyle()
{
}
