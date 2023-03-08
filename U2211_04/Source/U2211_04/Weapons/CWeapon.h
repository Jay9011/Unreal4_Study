#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

UCLASS()
class U2211_04_API ACWeapon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Equip")
	FName HolsterSocketName;

	UPROPERTY(EditDefaultsOnly, Category="Equip")
	class UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category="Equip")
	float EquipMontage_PlayRate = 1;

	UPROPERTY(EditDefaultsOnly, Category="Equip")
	FName RightHandSocketName;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Hit")
	float HitDistance = 3000;

	UPROPERTY(EditDefaultsOnly, Category="Hit")
	class UMaterialInstanceConstant* HitDecal;

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

protected:
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;

public:
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	bool CanEquip();
	void Equip();
	virtual void Begin_Equip();
	virtual void End_Equip();

public:
	bool CanUnequip();
	virtual void Unequip();

public:
	bool CanFire();
	void Begin_Fire();
	void End_Fire();

private:
	void OnFiring();

private:
	class ACPlayer* Owner;

private:
	bool bEquipping;
	bool bInAim;
	bool bFiring;
	bool bReload;
	bool bAutoFire = true;
};
