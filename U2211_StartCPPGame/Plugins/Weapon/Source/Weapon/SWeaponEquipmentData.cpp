#include "SWeaponEquipmentData.h"

#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IDetailPropertyRow.h"
#include "IPropertyUtilities.h"

TSharedRef<IPropertyTypeCustomization> SWeaponEquipmentData::MakeInstance()
{
	return MakeShareable(new SWeaponEquipmentData());
}

void SWeaponEquipmentData::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	FText name = InPropertyHandle->GetPropertyDisplayName();
	
	InHeaderRow
	.NameContent()
	[
		SNew(STextBlock)
		.Text(name)
	]
	.ValueContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Value"))
	];
}

void SWeaponEquipmentData::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	GLog->Log("CustomizeChildren");
}
