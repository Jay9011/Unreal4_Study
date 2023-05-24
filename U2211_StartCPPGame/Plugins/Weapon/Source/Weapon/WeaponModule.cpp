#include "WeaponModule.h"
#include "WeaponStyle.h"
#include "WeaponContextMenu.h"
#include "FWeaponCommand.h"

#include "IAssetTools.h"
#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "FWeaponModule"

IMPLEMENT_MODULE(FWeaponModule, Weapon)

void FWeaponModule::StartupModule()
{
	FWeaponStyle::Get();

	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type type = assetTools.RegisterAdvancedAssetCategory("WeaponAsset", FText::FromString("Weapons"));

	ContextMenu = MakeShareable<FWeaponContextMenu>(new FWeaponContextMenu(type));
	assetTools.RegisterAssetTypeActions(ContextMenu.ToSharedRef());

	Command = MakeShareable<FWeaponCommand>(new FWeaponCommand());
	Command->Startup();
}

void FWeaponModule::ShutdownModule()
{
	if (ContextMenu.IsValid())
	{
		ContextMenu.Reset();
	}

	if (Command.IsValid())
	{
		Command.Reset();
	}

	FWeaponStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE
	
