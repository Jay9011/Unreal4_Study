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
	IDetailCategoryBuilder& actor = DetailBuilder.EditCategory("Actor");
	// actor.SetCategoryVisibility(false);

	// IDetailCategoryBuilder& rendering = DetailBuilder.EditCategory("Rendering");

	TArray<TSharedRef<IPropertyHandle>> handles;
	actor.GetDefaultProperties(handles);

	for(TSharedRef<IPropertyHandle> handle : handles)
	{
		// GLog->Log(handle->GetProperty()->GetName());
		// GLog->Log(handle->GetProperty()->GetFullName());
		if(handle->GetProperty()->GetName().Contains("bCanBeDamaged"))
			DetailBuilder.HideProperty(handle);
	}

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
	if(Objects[0]->GetWorld()->IsPlayInEditor())
	{
		FMessageDialog dialog;
		dialog.Debugf(FText::FromString("It doesn't work in game mode"));

		return FReply::Handled();
	}


	TArray<ACStaticMesh*> meshActors;
	for(TWeakObjectPtr<UObject> obj : Objects)
	{
		ACStaticMesh* meshActor = Cast<ACStaticMesh>(obj);
		if(meshActor == nullptr) continue;

		meshActors.Add(meshActor);
	}

	for(int32 i = 0; i < meshActors.Num(); i++)
	{
		UActorComponent* actorComponent = meshActors[i]->GetComponentByClass(UStaticMeshComponent::StaticClass());
		UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(actorComponent);
		if(meshComponent == nullptr) return FReply::Unhandled();

		UStaticMesh* mesh = meshComponent->GetStaticMesh();
		if(mesh == nullptr) return FReply::Unhandled();

		FStaticMeshRenderData* renderData = mesh->RenderData.Get();
	}

	return FReply::Handled();
}
