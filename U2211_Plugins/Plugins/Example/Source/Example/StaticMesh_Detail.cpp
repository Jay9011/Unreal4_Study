#include "StaticMesh_Detail.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "CStaticMesh.h"
#include "Misc/MessageDialog.h"

TSharedRef<IDetailCustomization> FStaticMesh_Detail::MakeInstance()
{
	return MakeShareable(new FStaticMesh_Detail());
}

void FStaticMesh_Detail::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& mesh = DetailBuilder.EditCategory("Mesh");

	mesh.AddCustomRow(FText::FromString("Color"))
		.NameContent()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Color"))
		]
		.ValueContent()
		.VAlign(VAlign_Center)
		.MaxDesiredWidth(250)
		[
			SNew(SButton)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Fill)
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString("Paint"))
			]
			.OnClicked(this, &FStaticMesh_Detail::OnClicked_Paint)
		];

	mesh.AddCustomRow(FText::FromString("SaveMesh"))
		.NameContent()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Mesh"))
		]
		.ValueContent()
		.VAlign(VAlign_Center)
		.MaxDesiredWidth(250)
		[
			SNew(SButton)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Fill)
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString("Save Meshes"))
			]
			.OnClicked(this, &FStaticMesh_Detail::OnClicked_SaveMesh)
		];

	DetailBuilder.GetObjectsBeingCustomized(Objects);
}

FReply FStaticMesh_Detail::OnClicked_Paint()
{
	for(TWeakObjectPtr<UObject> obj : Objects)
	{
		ACStaticMesh* mesh = Cast<ACStaticMesh>(obj);

		if(!!mesh)
			mesh->Paint();

	}

	return FReply::Handled();
}

FReply FStaticMesh_Detail::OnClicked_SaveMesh()
{
	if(FApp::IsGame())
	{
		FMessageDialog dialog;
		dialog.Debugf(FText::FromString("In game mode is not working"));

		return FReply::Handled();
	}

	GLog->Log("Save Mesh");

	return FReply::Handled();
}
