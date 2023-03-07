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

