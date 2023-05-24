#include "FWeaponAssetEditor.h"
#include "Weapons/CWeaponAsset.h"

const FName FWeaponAssetEditor::EditorName	  = "WeaponAssetEditor";
const FName FWeaponAssetEditor::ListViewTabId = "ListView";
const FName FWeaponAssetEditor::DetailTabId	  = "Details";

TSharedPtr<FWeaponAssetEditor> FWeaponAssetEditor::Instance = nullptr;

void FWeaponAssetEditor::OpenWindow(FString InAssetName)
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}

	Instance = MakeShareable(new FWeaponAssetEditor());
	Instance->Open(InAssetName);
}

void FWeaponAssetEditor::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}
}

void FWeaponAssetEditor::Open(FString InAssetName)
{
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("WeaponAssetEditor_Layout")
	->AddArea
	(
		//주 영역 설정
		FTabManager::NewPrimaryArea()
		//주 영역을 가로로 분할함
		->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)
			->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
		)
		->Split
		(
			//영역 크기 조절 가능한 Splitter
			FTabManager::NewSplitter()
			->SetOrientation(Orient_Horizontal)
			//첫 번째 영역
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.175f)
				->AddTab(ListViewTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
			//두 번째 영역
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.725f)
				->AddTab(DetailTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		)
	);

	UCWeaponAsset* asset = NewObject<UCWeaponAsset>();
	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), EditorName, Layout, true,
										 true, asset);
}

void FWeaponAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab tab;
	tab.BindSP(this, &FWeaponAssetEditor::Spawn_ListViewTab);

	TabManager->RegisterTabSpawner(ListViewTabId, tab);
}

TSharedRef<SDockTab> FWeaponAssetEditor::Spawn_ListViewTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab);
}

FName FWeaponAssetEditor::GetToolkitFName() const
{
	return EditorName;
}

FText FWeaponAssetEditor::GetBaseToolkitName() const
{
	return FText::FromName(EditorName);
}

FString FWeaponAssetEditor::GetWorldCentricTabPrefix() const
{
	return EditorName.ToString();
}

FLinearColor FWeaponAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1);
}