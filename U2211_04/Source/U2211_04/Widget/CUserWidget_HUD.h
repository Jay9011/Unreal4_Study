#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_HUD.generated.h"

UCLASS()
class U2211_04_API UCUserWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnAutoFire();

	UFUNCTION(BlueprintImplementableEvent)
	void OffAutoFire();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMagazine(uint8 InCurr, uint8 InMax);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWeaponType(EWeaponType InType);

};
