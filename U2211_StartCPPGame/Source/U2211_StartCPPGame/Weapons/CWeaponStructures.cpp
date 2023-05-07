#include "Weapons/CWeaponStructures.h"
#include "Global.h"

#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Animation/AnimMontage.h"

void FDoActionData::DoAction(ACharacter* InOwner)
{
	UCMovementComponent* movement = CHelpers::GetComponent<UCMovementComponent>(InOwner);

	if (!!movement)
	{
		if (bFixedCamera)
			movement->EnableFixedCamera();

		if (bCanMove == false)
			movement->Stop();
	} // Movement

	if (!!Montage)
	{
		InOwner->PlayAnimMontage(Montage, PlayRate);
	} // Montage
}

/**
 * 데미지 전달
 *
 * @param InAttacker 
 * @param InAttackCauser 
 * @param InOther 
 */
void FHitData::SendDamage(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOther)
{
	FActionDamageEvent e;
	e.HitData = this;

	InOther->TakeDamage(20, e, InAttacker->GetController(), InAttackCauser);
}

void FHitData::PlayMontage(ACharacter* InOwner)
{
   if (!!Montage)
      InOwner->PlayAnimMontage(Montage, PlayRate);
}
