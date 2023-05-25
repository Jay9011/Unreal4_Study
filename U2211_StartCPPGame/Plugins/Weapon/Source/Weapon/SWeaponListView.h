#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class WEAPON_API SWeaponListView
	: public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeaponListView) {}
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	FText OnGetAssetCount() const;
	int32 TestCount;
};
