#include "Characters/CAnimInstance_Arms.h"
#include "Global.h"
#include "Characters/CPlayer.h"


void UCAnimInstance_Arms::NativeBeginPlay()
{
	Super::NativeBeginPlay(); // 부모 함수 호출

	OwnerCharacter = Cast<ACPlayer>(TryGetPawnOwner());
	CheckNull(OwnerCharacter)

	Weapon = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	if(!!Weapon)
		Weapon->OnWeaponTypeChanged.AddDynamic(this, &UCAnimInstance_Arms::OnWeaponTypeChanged);
}

void UCAnimInstance_Arms::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter)
}

void UCAnimInstance_Arms::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	WeaponType = InNewType;
}
