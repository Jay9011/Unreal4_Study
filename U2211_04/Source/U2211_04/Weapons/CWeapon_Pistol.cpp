#include "Weapons/CWeapon_Pistol.h"

#include "Global.h"
#include "CMagazine.h"
#include "CWeaponComponent.h"
#include "Animation/AnimMontage.h"
#include "Camera/CameraShake.h"
#include "Characters/CPlayer.h"
#include "Widget/CUserWidget_CrossHair.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"


ACWeapon_Pistol::ACWeapon_Pistol()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Pistols_A.Pistols_A'");
	Mesh->SetSkeletalMesh(mesh);


	// Equip
	{
		HolsterSocketName = NAME_None;

		CHelpers::GetAsset<UAnimMontage>(&EquipMontage,
										 "AnimMontage'/Game/Character/Animations/Pistol_Equip_Montage.Pistol_Equip_Montage'");
		EquipMontage_PlayRate = 2.0f;
		RightHandSocketName = "Pistol_RightHand";
	}

	// Aim
	{
		BaseData.TargetArmLength = 200;
		BaseData.SocketOffset = FVector(0, 50, 15);
		BaseData.FieldOfView = 90;

		AimData.TargetArmLength = 30;
		AimData.SocketOffset = FVector(-55, 50, 10);
		AimData.FieldOfView = 55;

		LeftHandLocation = FVector(0.0f, 15.0f, 0.0f);
	}

	// Fire
	{
		AutoFireInterval = 0.3f;
	}

	// Recoil
	{
		CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass,
												"Blueprint'/Game/Weapons/BP_CameraShake_Pistol.BP_CameraShake_Pistol_C'");
		RecoilAngle = 1.5f;
		RecoilRate = 0.08f;
		SpreadSpeed = 8.0f;
		MaxSpreadAlignment = 8.0f;
	}

	// UI
	{
		CHelpers::GetClass<UCUserWidget_CrossHair>(&CrossHairClass, "WidgetBlueprint'/Game/Widgets/WB_CrossHair.WB_CrossHair_C'");
	}

	// Magazine
	{
		MaxMagazineCount = 5;
		CHelpers::GetAsset<UAnimMontage>(&ReloadMontage, "AnimMontage'/Game/Character/Animations/Pistol_Reload_Montage.Pistol_Reload_Montage'");
		ReloadMontage_PlayRate = 1.5f;
		MagazineBoneName = "b_gun_mag";
		MagazineSocketName = "Pistol_Magazine";
		CHelpers::GetClass<ACMagazine>(&MagazineClass, "Blueprint'/Game/Weapons/BP_CMagazine_Pistol.BP_CMagazine_Pistol_C'");
	}

	//Arms
	{
		ArmsMeshTransform.SetLocation(FVector(0, 5.1f, -156.6));
		ArmsMeshTransform.SetRotation(FQuat(FRotator(0, -4.8f, 0)));

		ArmsLeftHandTransform.SetLocation(FVector(0, 11, 0));
		ArmsLeftHandTransform.SetRotation(FQuat(FRotator(0, 180, 180)));
	}
}

void ACWeapon_Pistol::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetVisibility(false);
}

void ACWeapon_Pistol::Begin_Equip()
{
	Super::Begin_Equip();

	Mesh->SetVisibility(true);
	Owner->GetArms()->SetRelativeTransform(ArmsMeshTransform);
}

void ACWeapon_Pistol::Unequip()
{
	Super::Unequip();

	Mesh->SetVisibility(false);
}

void ACWeapon_Pistol::Begin_Aim()
{
	Super::Begin_Aim();

	if(!!CrossHair)
		CrossHair->SetVisibility(ESlateVisibility::Collapsed);

	Owner->GetMesh()->SetVisibility(false);
	Owner->GetBackpack()->SetVisibility(false);
	Owner->GetArms()->SetVisibility(true);

	CHelpers::AttachTo(this, Owner->GetArms(), RightHandSocketName);

	CHelpers::GetComponent<UCWeaponComponent>(Owner)->OnWeaponAim_Arms_Begin.Broadcast(this);
}

void ACWeapon_Pistol::End_Aim()
{
	Super::End_Aim();

	if(!!CrossHair)
		CrossHair->SetVisibility(ESlateVisibility::HitTestInvisible);

	Owner->GetMesh()->SetVisibility(true);
	Owner->GetBackpack()->SetVisibility(true);
	Owner->GetArms()->SetVisibility(false);

	CHelpers::AttachTo(this, Owner->GetMesh(), RightHandSocketName);

	CHelpers::GetComponent<UCWeaponComponent>(Owner)->OnWeaponAim_Arms_End.Broadcast();
}
