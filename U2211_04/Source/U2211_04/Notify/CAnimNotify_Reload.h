#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_Reload.generated.h"

UENUM()
enum class EReloadActionType : uint8
{
	Eject, Spawn, Load, End,
};

UCLASS()
class U2211_04_API UCAnimNotify_Reload : public UAnimNotify
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Action")
	EReloadActionType ActionType;

public:
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
