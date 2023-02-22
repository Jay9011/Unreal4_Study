
#include "CTestActor.h"

DEFINE_LOG_CATEGORY_STATIC(GP, Display, All)

ACTestActor::ACTestActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACTestActor::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Blue, TEXT("Test_AddOnScreenDebugMessage"));
	UE_LOG(GP, Display, L"%s", TEXT("Test_UE_Log"));
}

void ACTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

