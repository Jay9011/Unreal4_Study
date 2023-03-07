#include "CAnimInstance.h"
#include "Global.h"
#include "Characters/CPlayer.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay(); // �θ� �Լ� ȣ��

	OwnerCharacter = Cast<ACPlayer>(TryGetPawnOwner());
	CheckNull(OwnerCharacter)

	// UActorComponent* comp = OwnerCharacter->GetComponentByClass(UCWeaponComponent::StaticClass());
	// Weapon = Cast<UCWeaponComponent>(comp);
	Weapon = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	if(!!Weapon)
		Weapon->OnWeaponTypeChanged.AddDynamic(this, &UCAnimInstance::OnWeaponTypeChanged);
	
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter)	// OwnerCharacter �� ���ٸ� ���� ��尡 �ƴ϶�� ������
								// ���� ������ ���� �ʽ��ϴ�.

	Speed = OwnerCharacter->GetVelocity().Size2D();
	// Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());

	// UKismetMathLibrary::Conv_VectorToRotator(OwnerCharacter->GetVelocity());	// RotationFromXVector
	FRotator actorRotationFromVelocity = OwnerCharacter->GetVelocity().ToOrientationRotator();	// ĳ���Ͱ� �ٶ󺸴� ������ �������� ���� �ʰ� ĳ���Ͱ� �����̴� ������ �������� �ؾ� �������� �� �ް������� �����ϴ�!!
	FRotator controlRotation = OwnerCharacter->GetControlRotation();
	FRotator deltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(actorRotationFromVelocity, controlRotation);

	PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, deltaRotation, DeltaSeconds, 25);

	Direction = PrevRotation.Yaw;

}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	WeaponType = InNewType;
}
