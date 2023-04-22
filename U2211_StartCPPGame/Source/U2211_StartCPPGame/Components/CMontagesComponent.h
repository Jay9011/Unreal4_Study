#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Components/CStateComponent.h"
#include "CMontagesComponent.generated.h"

USTRUCT()
struct FMontagesData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EStateType Type;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U2211_STARTCPPGAME_API UCMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "DataTable")
	UDataTable* DataTable;

public:	
	UCMontagesComponent();

protected:
	virtual void BeginPlay() override;

public:
	void PlayBackStepMode();

private:
	void PlayAnimMontage(EStateType InType);

private:
	class ACharacter* OwnerCharacter;
	FMontagesData* Datas[(int32)EStateType::Max];

};
