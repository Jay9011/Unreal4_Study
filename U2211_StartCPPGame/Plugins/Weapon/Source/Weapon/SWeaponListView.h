#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STableRow.h"

struct FWeaponRowData
{
	int Number = 1;
	FString Name;
	class UCWeaponAsset* Asset = nullptr;
	
	FWeaponRowData() {}
	FWeaponRowData(int32 InNumber, FString InName, class UCWeaponAsset* InAsset)
	  : Number(InNumber), Name(InName), Asset(InAsset)
	{
	}

	static TSharedPtr<FWeaponRowData> Make(int32 InNumber, FString InName, class UCWeaponAsset* InAsset)
	{
		return MakeShareable(new FWeaponRowData(InNumber, InName, InAsset));
	}
};
typedef TSharedPtr<FWeaponRowData> FWeaponRowDataPtr;

/******************************************************
 * SWeaponTableRow
 ******************************************************/
class WEAPON_API SWeaponTableRow
	: public SMultiColumnTableRow<FWeaponRowDataPtr>
{
	SLATE_BEGIN_ARGS(SWeaponTableRow) {}
	SLATE_ARGUMENT(FWeaponRowDataPtr, Row)
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable);

protected:
	TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;

private:
	FWeaponRowDataPtr Row;
};
typedef SListView<FWeaponRowDataPtr> SWeaponListViewer;

/******************************************************
 *  SWeaponListView
 ******************************************************/
class WEAPON_API SWeaponListView
	: public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeaponListView) {}
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	TSharedRef<ITableRow> OnGenerateRow(FWeaponRowDataPtr InRow, const TSharedRef<STableViewBase>& InTable);

private:
	FText OnGetAssetCount() const;

private:
	TArray<FWeaponRowDataPtr> RowDatas;

private:
	TSharedPtr<SWeaponListViewer> ListViewer;
};
