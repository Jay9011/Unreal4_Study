#include "ButtonCommand.h"

#include "CStaticMesh.h"
#include "CStaticMesh_Copied.h"
#include "DesktopPlatformModule.h"
#include "Editor.h"
#include "LevelEditorViewport.h"
#include "StaticMesh_Detail.h"
#include "Interfaces/IMainFrameModule.h"
#include "Misc/FileHelper.h"
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


	FString text;
	for (int32 i = 0; i < data.Positions.Num(); i++)
	{
		text.Append(data.Positions[i].ToString() + ", ");
		text.Append(data.Normals[i].ToString() + ", ");
		text.Append(data.Uvs[i].ToString() + ", ");
		text.Append(data.Colors[i].ToString() + "\r\n");
	}

	FString textFileName = FPaths::GetBaseFilename(fileNames[0], false);
	FString textSaveName = textFileName + "_Copied.csv";

	FFileHelper::SaveStringToFile(text, *textSaveName);

	FLevelEditorViewportClient* client = static_cast<FLevelEditorViewportClient*>(GEditor->GetActiveViewport()->GetClient());
	if(client == nullptr) return;

	FVector start = client->GetViewLocation();
	FVector end = start + client->GetViewRotation().RotateVector(FVector(10000, 0, 0));

	FHitResult hitResult;
	UWorld* world = GEditor->GetEditorWorldContext().World();

	world->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility);
	if (hitResult.bBlockingHit == false)
	{
		FMessageDialog dialog;
		dialog.Debugf(FText::FromString("Can't be placed in this location."));

		return;
	}

	FTransform transform;
	FVector direction = (hitResult.TraceEnd - hitResult.TraceStart);
	direction.Normalize();

	FVector location = hitResult.TraceStart + direction * (hitResult.Distance - data.Radius);
	transform.SetLocation(location);

	FRotator rotation = FRotator(0, direction.Rotation().Yaw, 0);
	transform.SetRotation(FQuat(rotation));


	ACStaticMesh_Copied* actor = world->SpawnActorDeferred<ACStaticMesh_Copied>
	(
		ACStaticMesh_Copied::StaticClass(),
		transform,
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
	);

	actor->SetPositions(data.Positions);
	actor->SetIndices(data.Indices);
	actor->SetNormals(data.Normals);
	actor->SetUvs(data.Uvs);
	actor->SetColors(data.Colors);

	actor->FinishSpawning(transform);
}
