#include "Components/CMontagesComponent.h"
#include "Global.h"

#include "GameFramework/Character.h"

// #define LOG_UCMontageComponent 1

UCMontagesComponent::UCMontagesComponent()
{

}


void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	if(DataTable == nullptr)
	{
		GLog->Log(ELogVerbosity::Error, "DataTable is not Selected");

		return;
	}

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	TArray<FMontagesData*> datas;
	DataTable->GetAllRows<FMontagesData>("", datas);

	for(int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (FMontagesData* data : datas)
		{
			if((EStateType)i == data->Type)
			{
				Datas[i] = data;

				continue;
			}
		}//for(data)
	}//for(i)


#if LOG_UCMontageComponent
	for (FMontagesData* data : datas)
	{
		if(data == nullptr)
			continue;

		FString str;
		str.Append(StaticEnum<EStateType>()->GetValueAsString(data->Type));
		str.Append(" / ");
		str.Append(data->Montage->GetPathName());

		CLog::Log(str);
	}
#endif

}

void UCMontagesComponent::PlayBackStepMode()
{
	PlayAnimMontage(EStateType::BackStep);
}

void UCMontagesComponent::PlayAnimMontage(EStateType InType)
{
	CheckNull(OwnerCharacter)

	FMontagesData* data = Datas[(int32)InType];

	if (data == nullptr)
	{
		GLog->Log(ELogVerbosity::Error, "None Montages data");
		return;
	}

	if (data->Montage == nullptr)
	{
		GLog->Log(ELogVerbosity::Error, "None Montages");
		return;
	}

	OwnerCharacter->PlayAnimMontage(data->Montage, data->PlayRate);

}
