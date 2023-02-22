#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay(); // �θ� �Լ� ȣ��

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter)	// OwnerCharacter �� ���ٸ� ���� ��尡 �ƴ϶�� ������
								// ���� ������ ���� �ʽ��ϴ�.

	Speed = OwnerCharacter->GetVelocity().Size2D();

}
