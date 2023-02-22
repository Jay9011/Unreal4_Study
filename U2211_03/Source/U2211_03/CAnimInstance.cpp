#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay(); // 부모 함수 호출

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter)	// OwnerCharacter 가 없다면 게임 모드가 아니라는 뜻으로
								// 이하 진행을 하지 않습니다.

	Speed = OwnerCharacter->GetVelocity().Size2D();

}
