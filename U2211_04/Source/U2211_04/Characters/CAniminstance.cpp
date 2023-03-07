#include "CAnimInstance.h"
#include "Global.h"
#include "Characters/CPlayer.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay(); // 부모 함수 호출

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

	CheckNull(OwnerCharacter)	// OwnerCharacter 가 없다면 게임 모드가 아니라는 뜻으로
								// 이하 진행을 하지 않습니다.

	Speed = OwnerCharacter->GetVelocity().Size2D();
	// Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());

	// UKismetMathLibrary::Conv_VectorToRotator(OwnerCharacter->GetVelocity());	// RotationFromXVector
	FRotator actorRotationFromVelocity = OwnerCharacter->GetVelocity().ToOrientationRotator();	// 캐릭터가 바라보는 방향을 기준으로 하지 않고 캐릭터가 움직이는 방향을 기준으로 해야 옆걸음질 및 뒷걸음질이 가능하다!!
	FRotator controlRotation = OwnerCharacter->GetControlRotation();
	FRotator deltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(actorRotationFromVelocity, controlRotation);

	PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, deltaRotation, DeltaSeconds, 25);

	Direction = PrevRotation.Yaw;

}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	WeaponType = InNewType;
}
