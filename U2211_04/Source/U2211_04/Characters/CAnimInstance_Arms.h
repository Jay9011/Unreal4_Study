#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapons/CWeaponComponent.h"
#include "CAnimInstance_Arms.generated.h"

UCLASS()
class U2211_04_API UCAnimInstance_Arms : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapons")
	EWeaponType WeaponType = EWeaponType::Max;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapons")
	FTransform ArmsLeftHandTransform;
	
public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType);

private:
	class ACPlayer* OwnerCharacter;
	class UCWeaponComponent* Weapon;

};
