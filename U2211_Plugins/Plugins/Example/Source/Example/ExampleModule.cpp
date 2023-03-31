#include "ExampleModule.h"

#include "ExampleConsoleCommand.h"
#include "ExampleDebuggerCategory.h"
#include "GameplayDebugger.h"

#include "StaticMesh_Detail.h"
#include "CStaticMesh.h"

#define LOCTEXT_NAMESPACE "ExampleModule"

IMPLEMENT_MODULE(FExampleModule, Example)

void FExampleModule::StartupModule()
{
	// Debug Category
	{
		IGameplayDebugger::FOnGetCategory category;
		category.BindStatic(&FExampleDebuggerCategory::MakeInstance);

		IGameplayDebugger::Get().RegisterCategory("Example", category,
												  EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		IGameplayDebugger::Get().NotifyCategoriesChanged();
	}

	// Console Command
	{
		ConsoleCommand = MakeShareable(new FExampleConsoleCommand());
	}

	// Property Editor
	{
		FOnGetDetailCustomizationInstance instance;
		instance.BindStatic(&FStaticMesh_Detail::MakeInstance);
	
		FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		prop.RegisterCustomClassLayout(ACStaticMesh::StaticClass()->GetFName(), instance);
	}
}

void FExampleModule::ShutdownModule()
{
	if(IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("Example");

	if(ConsoleCommand.IsValid())
		ConsoleCommand.Reset();
}

#undef LOCTEXT_NAMESPACE