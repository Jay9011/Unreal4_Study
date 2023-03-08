#include "Weapons/CWeapon_AR4.h"

#include "Global.h"
#include "Animation/AnimMontage.h"

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


}
