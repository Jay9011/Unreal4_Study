#include "SWeaponListView.h"

void SWeaponTableRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable)
{
	Row = InArgs._Row;

	SMultiColumnTableRow<FWeaponRowDataPtr>::Construct
	(
		FSuperRowType::FArguments().Style(FEditorStyle::Get(), "TableView.DarkRow"), InOwnerTable
	);
}

TSharedRef<SWidget> SWeaponTableRow::GenerateWidgetForColumn(const FName& InColumnName)
{
	FString str;
	if(InColumnName == "Number")
		str = FString::FromInt(Row->Number);
	else if(InColumnName == "Name")
		str = Row->Name;

	return SNew(STextBlock)
		.Text(FText::FromString(str));
}

//////////////////////////////////////////////////////////////////////////////////////////

void SWeaponListView::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1)
		[
			SAssignNew(ListViewer, SWeaponListViewer)
			.HeaderRow
             (
                 SNew(SHeaderRow)
                 + SHeaderRow::Column("Number")
                 .DefaultLabel(FText::FromString("Number"))
                 + SHeaderRow::Column("Name")
                 .DefaultLabel(FText::FromString("Name"))
             )
			.ListItemsSource(&RowDatas)
			.OnGenerateRow(this, &SWeaponListView::OnGenerateRow)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBox)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Right)
			.Padding(FMargin(8, 2))
			[
				SNew(STextBlock)
				.Text(this, &SWeaponListView::OnGetAssetCount)
			]
		]
	];
	
	RowDatas.Add(FWeaponRowData::Make(1, "Test", nullptr));
	RowDatas.Add(FWeaponRowData::Make(2, "Test1", nullptr));
	RowDatas.Add(FWeaponRowData::Make(3, "Test2", nullptr));
}

TSharedRef<ITableRow> SWeaponListView::OnGenerateRow(FWeaponRowDataPtr InRow, const TSharedRef<STableViewBase>& InTable)
{
	return SNew(SWeaponTableRow, InTable)
	.Row(InRow);
}

FText SWeaponListView::OnGetAssetCount() const
{
	FString str = FString::Printf(TEXT("%d 에셋"), 0);

	return FText::FromString(str);
}
