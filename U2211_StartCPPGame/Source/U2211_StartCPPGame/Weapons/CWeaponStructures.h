#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructures.generated.h"

USTRUCT()
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

	UPROPERTY(EditAnywhere)
	bool bUseControlRotation = true;
};
/// �� Struct ���� ����ȭ �ϱ� ���ؼ��� UCLASS() �� �����մϴ�.
UCLASS()
class U2211_STARTCPPGAME_API UCWeaponStructures : public UObject
{
	GENERATED_BODY()
};
