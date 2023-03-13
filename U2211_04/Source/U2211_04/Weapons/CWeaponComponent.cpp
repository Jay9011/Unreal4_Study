#include "Weapons/CWeaponComponent.h"

#include "Global.h"
#include "CWeapon.h"
#include "Characters/CPlayer.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACPlayer>(GetOwner());
	CheckNull(Owner)

	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	for (TSubclassOf<ACWeapon> weaponClass : WeaponClasses)
	{
		if(!!weaponClass)
		{
			ACWeapon* weapon = Owner->GetWorld()->SpawnActor<ACWeapon>(weaponClass, params);
			Weapons.Add(weapon);
		}///if(!!weaponClass)
	}///for(TSubclassOf<ACWeapon> weaponClass : WeaponClasses)
}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UCWeaponComponent::IsInAim()
{
	CheckNullResult(GetCurrWeapon(), false)

	return GetCurrWeapon()->IsInAim();
}

bool UCWeaponComponent::IsFiring()
{
	CheckNullResult(GetCurrWeapon(), false)

	return GetCurrWeapon()->IsFiring();
}

FVector UCWeaponComponent::GetLeftHandLocation()
{
	CheckNullResult(GetCurrWeapon(), FVector::ZeroVector)

	return GetCurrWeapon()->GetLeftHandLocation();
}

void UCWeaponComponent::Begin_Equip()
{
	CheckNull(GetCurrWeapon())
	GetCurrWeapon()->Begin_Equip();
}

void UCWeaponComponent::End_Equip()
{
	CheckNull(GetCurrWeapon())
	GetCurrWeapon()->End_Equip();
}

void UCWeaponComponent::Begin_Fire()
{
	CheckNull(GetCurrWeapon())
	CheckFalse(GetCurrWeapon()->CanFire())

	GetCurrWeapon()->Begin_Fire();

}

void UCWeaponComponent::End_Fire()
{
	CheckNull(GetCurrWeapon())

	GetCurrWeapon()->End_Fire();
}

void UCWeaponComponent::Begin_Aim()
{
	CheckNull(GetCurrWeapon())
	CheckFalse(GetCurrWeapon()->CanAim())

	GetCurrWeapon()->Begin_Aim();
}

void UCWeaponComponent::End_Aim()
{
	CheckNull(GetCurrWeapon())

	GetCurrWeapon()->End_Aim();
}

ACWeapon* UCWeaponComponent::GetCurrWeapon()
{
	CheckTrueResult(IsUnarmedMode(), nullptr)

	return Weapons[static_cast<int32>(Type)];
}


void UCWeaponComponent::SetUnarmedMode()
{
	CheckFalse(GetCurrWeapon()->CanUnequip())

	GetCurrWeapon()->Unequip();
	ChangeType(EWeaponType::Max);

}

void UCWeaponComponent::SetAR4Mode()
{
	SetMode(EWeaponType::AR4);

}

void UCWeaponComponent::SetMode(EWeaponType InType)
{
	if (Type == InType)
	{
		SetUnarmedMode();

		return;
	}
	else if(IsUnarmedMode() == false)
	{
		CheckFalse(GetCurrWeapon()->CanUnequip())
		GetCurrWeapon()->Unequip();
	}

	const int32 typeIndex = static_cast<int32>(InType);

	CheckNull(Weapons[typeIndex])
	CheckFalse(Weapons[typeIndex]->CanEquip())

	Weapons[typeIndex]->Equip();

	ChangeType(InType);

}

void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType prevType = Type;
	Type = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(prevType, InType);

}

