#include "Weapons/CWeapon_AK47.h"

#include "Global.h"
#include "CMagazine.h"
#include "Animation/AnimMontage.h"
#include "Camera/CameraShake.h"
#include "Characters/CPlayer.h"
#include "Widget/CUserWidget_CrossHair.h"
#include "Components/StaticMeshComponent.h"

ACWeapon_AK47::ACWeapon_AK47()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47/SK_KA47.SK_KA47'");
	Mesh->SetSkeletalMesh(mesh);


	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Sight, "Sight", Mesh, "DotSight");

	UStaticMesh* staticMesh;
	CHelpers::GetAsset<UStaticMesh>(&staticMesh, "StaticMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/Accessories/SM_T4_Sight.SM_T4_Sight'");
	Sight->SetStaticMesh(staticMesh);
	Sight->SetRelativeScale3D(FVector(1.0f, 0.95f, 1.0f));
	Sight->SetCollisionProfileName("NoCollision");

	// Equip
	{
		HolsterSocketName = "Rifle_AK47_Holster";

		CHelpers::GetAsset<UAnimMontage>(&EquipMontage,
										 "AnimMontage'/Game/Character/Animations/Rifle_Equip_AK47_Montage.Rifle_Equip_AK47_Montage'");
		EquipMontage_PlayRate = 2.0f;
		RightHandSocketName = "Rifle_AK47_RightHand";
		LeftHandSocketName = "Rifle_AK47_LeftHand";
	}

	// Aim
	{
		BaseData.TargetArmLength = 200;
		BaseData.SocketOffset = FVector(0, 50, 15);
		BaseData.FieldOfView = 90;

		AimData.TargetArmLength = 30;
		AimData.SocketOffset = FVector(-55, 0, 10);
		AimData.FieldOfView = 55;

		LeftHandLocation = FVector(-35.0f, 15.5f, 4.0f);
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

void ACWeapon_AK47::Begin_Equip()
{
	if (LeftHandSocketName.IsValid())
		CHelpers::AttachTo(this, Owner->GetMesh(), LeftHandSocketName);
}

void ACWeapon_AK47::End_Equip()
{
	Super::Begin_Equip();
	Super::End_Equip();

}
