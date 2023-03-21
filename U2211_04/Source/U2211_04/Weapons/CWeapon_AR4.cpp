#include "Weapons/CWeapon_AR4.h"

#include "Global.h"
#include "CMagazine.h"
#include "Animation/AnimMontage.h"
#include "Camera/CameraShake.h"
#include "Widget/CUserWidget_CrossHair.h"

ACWeapon_AR4::ACWeapon_AR4()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	// Equip
	{
		HolsterSocketName = "Rifle_AR4_Holster";

		CHelpers::GetAsset<UAnimMontage>(&EquipMontage,
										 "AnimMontage'/Game/Character/Animations/Rifle_Equip_AR4_Montage.Rifle_Equip_AR4_Montage'");
		EquipMontage_PlayRate = 2.0f;
		RightHandSocketName = "Rifle_AR4_RightHand";
	}

	// Aim
	{
		BaseData.TargetArmLength = 200;
		BaseData.SocketOffset = FVector(0, 50, 15);
		BaseData.FieldOfView = 90;

		AimData.TargetArmLength = 80;
		AimData.SocketOffset = FVector(0, 55, 10);
		AimData.FieldOfView = 65;

		LeftHandLocation = FVector(-32.5f, 15.5f, 7.0f);
	}

	// Fire
	{
		AutoFireInterval = 0.15f;
	}

	// Recoil
	{
		CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass,
												"Blueprint'/Game/Weapons/BP_CameraShake_AR4.BP_CameraShake_AR4_C'");
		RecoilAngle = 0.75f;
		RecoilRate = 0.05f;
		SpreadSpeed = 2.0f;
		MaxSpreadAlignment = 2.0f;
	}

	// UI
	{
		CHelpers::GetClass<UCUserWidget_CrossHair>(&CrossHairClass, "WidgetBlueprint'/Game/Widgets/WB_CrossHair.WB_CrossHair_C'");

	}

	// Magazine
	{
		MaxMagazineCount = 30;
		CHelpers::GetAsset<UAnimMontage>(&ReloadMontage, "AnimMontage'/Game/Character/Animations/Rifile_Reload_Montage.Rifile_Reload_Montage'");
		ReloadMontage_PlayRate = 1.5f;
		MagazineBoneName = "b_gun_mag";
		MagazineSocketName = "Rifle_Magazine";
		CHelpers::GetClass<ACMagazine>(&MagazineClass, "Blueprint'/Game/Weapons/BP_CMagazine_AR4.BP_CMagazine_AR4_C'");
	}
}
