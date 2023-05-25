#include "SWeaponListView.h"

void SWeaponListView::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1)
		[
			SNew(STextBlock)
			.Text(FText::FromString("ListView"))
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

}

FText SWeaponListView::OnGetAssetCount() const
{
	FString str = FString::Printf(TEXT("%d 에셋"), TestCount);

	return FText::FromString(str);
}
