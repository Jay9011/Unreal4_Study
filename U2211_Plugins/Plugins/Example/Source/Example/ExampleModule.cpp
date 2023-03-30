#include "ExampleModule.h"
#include "ExampleConsoleCommand.h"
#include "ExampleDebuggerCategory.h"
#include "GameplayDebugger.h"

#define LOCTEXT_NAMESPACE "ExampleModule"

IMPLEMENT_MODULE(FExampleModule, Example)

void FExampleModule::StartupModule()
{
	IGameplayDebugger::FOnGetCategory category;
	category.BindStatic(&FExampleDebuggerCategory::MakeInstance);

	IGameplayDebugger::Get().RegisterCategory("Example", category, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
	IGameplayDebugger::Get().NotifyCategoriesChanged();

	ConsoleCommand = MakeShareable(new FExampleConsoleCommand());
}

void FExampleModule::ShutdownModule()
{
	if(IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("Example");

	if(ConsoleCommand.IsValid())
		ConsoleCommand.Reset();
}

#undef LOCTEXT_NAMESPACE