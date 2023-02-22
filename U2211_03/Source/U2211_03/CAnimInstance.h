#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class U2211_03_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	// Preview �� ���� ���ؼ� EditAnywhere �� ����ؾ� �մϴ�.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Speed;

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACharacter* OwnerCharacter;
};
