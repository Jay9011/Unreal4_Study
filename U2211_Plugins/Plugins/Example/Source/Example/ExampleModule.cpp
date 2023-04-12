#include "ExampleModule.h"

#include "ButtonCommand.h"
#include "CStaticMesh.h"
#include "ExampleConsoleCommand.h"
#include "ExampleDebuggerCategory.h"
#include "GameplayDebugger.h"
#include "LevelEditor.h"
#include "StaticMesh_Detail.h"

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

	// ToolBar
	{
		FButtonCommand::Register();

		Extender = MakeShareable(new FExtender());

		FToolBarExtensionDelegate toolbar;
		toolbar.BindRaw(this, &FExampleModule::AddToolBar);

		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().Command, toolbar);

		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	}
}

void FExampleModule::ShutdownModule()
{
	if(IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("Example");

	if(ConsoleCommand.IsValid())
		ConsoleCommand.Reset();
}

void FExampleModule::AddToolBar(FToolBarBuilder& InBuilder)
{
	InBuilder.AddSeparator();
	InBuilder.AddToolBarButton
	(
		FButtonCommand::Get().LoadMesh,
		"LoadMesh",
		FText::FromString("Load Mesh"),
		FText::FromString("Load Mesh Data")
	);

}

#undef LOCTEXT_NAMESPACE
