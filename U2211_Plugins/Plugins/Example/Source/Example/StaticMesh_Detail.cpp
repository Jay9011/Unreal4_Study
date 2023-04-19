#include "StaticMesh_Detail.h"

#include "CStaticMesh.h"
#include "DesktopPlatformModule.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Interfaces/IMainFrameModule.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"
#include "Serialization/BufferArchive.h"

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
		if(renderData->LODResources.Num() < 1) return FReply::Unhandled();

		FStaticMeshLODResources& lod = renderData->LODResources[0];
		FPositionVertexBuffer& vb = lod.VertexBuffers.PositionVertexBuffer;
		FStaticMeshVertexBuffer& meshVB = lod.VertexBuffers.StaticMeshVertexBuffer;	// UV, Normal 정보를 가진다.
		FColorVertexBuffer& colorVB = lod.VertexBuffers.ColorVertexBuffer;
		FRawStaticIndexBuffer& ib = lod.IndexBuffer;

		uint32 vertexCount = vb.GetNumVertices();
		int32 triangleCount = ib.GetNumIndices() / 3;

		GLog->Logf(L"%d Mesh, Vertex Count : %d", i + 1, vertexCount);
		GLog->Logf(L"%d Mesh, Triangle Count: %d", i + 1, triangleCount);

		FStaticMesh_DetailData data;

		TArray<FColor> colors;
		colorVB.GetVertexColors(colors);

		if (colors.Num() < 1)
		{
			for (uint32 index = 0; index < vertexCount; index++)
				colors.Add(FColor(255, 255, 255, 255));
		}

		FVector minBounds = FVector(+MAX_FLT, +MAX_FLT, +MAX_FLT);
		FVector maxBounds = FVector(-MAX_FLT, -MAX_FLT, -MAX_FLT);

		for (uint32 index = 0; index < vertexCount; index++)
		{
			FVector position = vb.VertexPosition(index);

			if (position.X < minBounds.X) minBounds.X = position.X;
			if (position.Y < minBounds.Y) minBounds.Y = position.Y;
			if (position.Z < minBounds.Z) minBounds.Z = position.Z;

			if (position.X > maxBounds.X) maxBounds.X = position.X;
			if (position.Y > maxBounds.Y) maxBounds.Y = position.Y;
			if (position.Z > maxBounds.Z) maxBounds.Z = position.Z;


			data.Positions.Add(position);
			data.Normals.Add(meshVB.VertexTangentZ(index));
			data.Uvs.Add(meshVB.GetVertexUV(index, 0));
			data.Colors.Add(colors[index]);
		}

		const float x = FMath::Abs(minBounds.X - maxBounds.X);
		const float y = FMath::Abs(minBounds.Y - maxBounds.Y);
		const float z = FMath::Abs(minBounds.Z - maxBounds.Z);

		data.Extent = FVector(x, y, z);
		data.Radius = FMath::Max(x, y);
		data.Radius = FMath::Max(data.Radius, z);

		GLog->Logf(L"x : %0.1f, y : %0.1f, z : %0.1f", x, y, z);
		GLog->Logf(L"Radius : %f", data.Radius);


		TArray<uint32> indices;
		ib.GetCopy(indices);
		data.Indices.Insert((int32*)indices.GetData(), triangleCount * 3, 0);

		IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
		void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();


		FString path;
		FPaths::GetPath(path);

		FString meshFileName = meshActors[i]->GetName();

		TArray<FString> fileNames;

		IDesktopPlatform* platform = FDesktopPlatformModule::Get();
		// OpenFileDialog(nullptr) : 어떤 창에 종속적인 모달인지 독립적인 창인지 결정해준다.
		platform->SaveFileDialog(handle, meshFileName, path, meshFileName + ".bin", "Mesh Binary File(*.bin)|*.bin", EFileDialogFlags::None, fileNames);
		if(fileNames.Num() < 1) continue;

		FBufferArchive buffer;
		buffer << data;


		FFileHelper::SaveArrayToFile(buffer, *fileNames[0]);
		buffer.FlushCache();
		buffer.Empty();


		FString text;
		for (int32 index = 0; index < data.Positions.Num(); index++)
		{
			text.Append(data.Positions[index].ToString() + ", ");
			text.Append(data.Normals[index].ToString() + ", ");
			text.Append(data.Uvs[index].ToString() + ", ");
			text.Append(data.Colors[index].ToString() + "\r\n");
		}

		FString textFileName = FPaths::GetBaseFilename(fileNames[0], false);
		FString textSaveName = textFileName + ".csv";


		FFileHelper::SaveStringToFile(text, *textSaveName);


		FString str;
		str.Append(FPaths::GetBaseFilename(fileNames[0]));
		str.Append(" Saved.");
		GLog->Log(str);

	}
	

	return FReply::Handled();
}
