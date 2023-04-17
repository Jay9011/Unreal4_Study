#include "ButtonCommand.h"

#include "CStaticMesh.h"
#include "DesktopPlatformModule.h"
#include "StaticMesh_Detail.h"
#include "Interfaces/IMainFrameModule.h"
#include "Misc/MessageDialog.h"
#include "Serialization/BufferArchive.h"

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
	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();


	FString path;
	FPaths::GetPath(path);

	TArray<FString> fileNames;

	IDesktopPlatform* platform = FDesktopPlatformModule::Get();
	platform->OpenFileDialog(handle, "Open Mesh File", path, "", "Mesh Binary File(*.bin)|*.bin",
							 EFileDialogFlags::None, fileNames);

	if (fileNames.Num() < 1) return;

	FBufferArchive buffer;
	FFileHelper::LoadFileToArray(buffer, *fileNames[0]);

	FMemoryReader reader = FMemoryReader(buffer, true);
	reader.Seek(0);

	FStaticMesh_DetailData data;
	reader << data;
	reader.FlushCache();
	reader.Close();


	GLog->Logf(L"Vertex Count : %d", data.Positions.Num());
	GLog->Logf(L"Triangle Count : %d", data.Indices.Num() / 3);
	GLog->Logf(L"Extent : %s", *data.Extent.ToString());
	GLog->Logf(L"Radius : %f", data.Radius);
}
