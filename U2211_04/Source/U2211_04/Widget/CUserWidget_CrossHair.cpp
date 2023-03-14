#include "Widget/CUserWidget_CrossHair.h"

#include "Global.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#define LOG_UCUserWidget_CrossHair 1

void UCUserWidget_CrossHair::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UCanvasPanel* panel =  Cast<UCanvasPanel>(WidgetTree->RootWidget);
	CheckNull(panel)

	TArray<UWidget*> widgets = panel->GetAllChildren();
	for(UWidget* widget : widgets)
	{
		UBorder* border = Cast<UBorder>(widget);

		if (!!border)
		{
			UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(border);

			Borders.Add(border);
			Alignments.Add(slot->GetAlignment());
		}
	}

#if LOG_UCUserWidget_CrossHair
	for (int32 i = 0; i < Borders.Num(); i++)
	{
		UBorder* border = Borders[i];
		CLog::Log(border->GetName());
		CLog::Log(Alignments[i].ToString());
	}
#endif
}

void UCUserWidget_CrossHair::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
