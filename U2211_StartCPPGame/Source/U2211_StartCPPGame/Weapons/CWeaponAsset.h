#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Weapons/CWeaponStructures.h"
#include "CWeaponAsset.generated.h"

UCLASS()
class U2211_STARTCPPGAME_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
	FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCEquipment> EquipmentClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCDoAction> DoActionClass;

	UPROPERTY(EditAnywhere)
	TArray<FDoActionData> DoActionDatas;

public:
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE class UCEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class UCDoAction* GetDoAction() { return DoAction; }

public:
	UCWeaponAsset();

	void BeginPlay(class ACharacter* InOwner);

private:
	UPROPERTY()
	class ACAttachment* Attachment;

	UPROPERTY()
	class UCEquipment* Equipment;

	UPROPERTY()
	class UCDoAction* DoAction;
};
