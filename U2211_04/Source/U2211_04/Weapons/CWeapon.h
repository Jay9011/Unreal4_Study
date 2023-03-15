#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

USTRUCT()
struct FWeaponAimData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float TargetArmLength;

	UPROPERTY(EditAnywhere)
	FVector SocketOffset;

	UPROPERTY(EditAnywhere)
	float FieldOfView;

public:
	void SetData(class ACharacter* InOwner);
	void SetDataByNoneCurve(class ACharacter* InOwner);
};

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

	UPROPERTY(EditDefaultsOnly, Category="Hit")
	class UParticleSystem* HitParticle;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Aim")
	FWeaponAimData BaseData;

	UPROPERTY(EditDefaultsOnly, Category="Aim")
	FWeaponAimData AimData;

	UPROPERTY(EditDefaultsOnly, Category="Aim")
	class UCurveFloat* AimCurve;

	UPROPERTY(EditDefaultsOnly, Category="Aim")
	float AimingSpeed = 200;

	UPROPERTY(EditDefaultsOnly, Category="Aim")
	FVector LeftHandLocation;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Fire")
	class UParticleSystem* FlashParticle;

	UPROPERTY(EditDefaultsOnly, Category="Fire")
	class UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category="Fire")
	class USoundWave* FireSound;

	UPROPERTY(EditDefaultsOnly, Category="Fire")
	float AutoFireInterval = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category="Fire")
	TSubclassOf<class ACBullet> BulletClass;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Recoil")
	TSubclassOf<class UMatineeCameraShake> CameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category="Recoil")
	float RecoilAngle = 0.75f;

	UPROPERTY(EditDefaultsOnly, Category="Recoil")
	float RecoilRate = 0.05f;

	UPROPERTY(EditDefaultsOnly, Category="Recoil")
	float SpreadSpeed;

	UPROPERTY(EditDefaultsOnly, Category="Recoil")
	float MaxSpreadAlignment;

protected:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class UCUserWidget_CrossHair> CrossHairClass;

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

protected:
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;

private:
	UPROPERTY(VisibleAnywhere)
	class UTimelineComponent* Timeline;

public:
	FORCEINLINE bool IsInAim() { return bInAim; }
	FORCEINLINE bool IsFiring() { return bFiring; }
	FORCEINLINE bool IsAutoFire() { return bAutoFire; }
	FORCEINLINE FVector GetLeftHandLocation() { return LeftHandLocation; }

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
	UFUNCTION()
	void OnFiring();

public:
	bool CanAim();
	virtual void Begin_Aim();
	virtual void End_Aim();

public:
	void ToggleAutoFire();
	
private:
	UFUNCTION()
	void OnAiming(float Output);

private:
	class ACPlayer* Owner;

private:
	bool bEquipping;
	bool bInAim;
	bool bFiring;
	bool bReload;
	bool bAutoFire = true;

private:
	FTimerHandle AutoFireHandle;

	// FTimerDynamicDelegate Delegate;

protected:
	class UCUserWidget_CrossHair* CrossHair;

private:
	float CurrSpreadRadius;
	float LastAddSpreadTime;

};
