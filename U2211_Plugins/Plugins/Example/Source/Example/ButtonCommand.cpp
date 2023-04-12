#include "ButtonCommand.h"

FButtonCommand::FButtonCommand()
	: TCommands("ToolBar_Buttons", FText::FromString(""), NAME_None, FEditorStyle::GetStyleSetName())
{
	Command = MakeShareable(new FUICommandList());
}

FButtonCommand::~FButtonCommand()
{
	if(Command.IsValid())
		Command.Reset();
}

void FButtonCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(LoadMesh, "LoadMesh", "", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE


	Command->MapAction(LoadMesh, FExecuteAction::CreateRaw(this, &FButtonCommand::OnClicked_LoadMesh));
}

void FButtonCommand::OnClicked_LoadMesh()
{
	GLog->Log("Test");
}
