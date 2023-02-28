#include "04_Trace/C03_MultiTrace.h"

#include "Global.h"
#include "Components/TextRenderComponent.h"

// #define LOG_AC03_MultiTrace true

AC03_MultiTrace::AC03_MultiTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

	CreateTextRender()

}

void AC03_MultiTrace::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC03_MultiTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector start = GetActorLocation();
	FVector start1 = FVector(start.X + 50, start.Y, start.Z);
	FVector start2 = FVector(start.X - 50, start.Y, start.Z);

	FVector end1 = start1 + GetActorForwardVector() * 600;
	FVector end2 = start2 + GetActorForwardVector() * 600;

	TArray<AActor*> ignores;
	TArray<FHitResult> hitResult1;
	TArray<FHitResult> hitResult2;

	UKismetSystemLibrary::LineTraceMulti(GetWorld(), start1, end1, ETraceTypeQuery::TraceTypeQuery1, false, ignores,
										 EDrawDebugTrace::ForOneFrame, hitResult1, true);


	TArray<TEnumAsByte<EObjectTypeQuery>> queries;
	queries.Add(EObjectTypeQuery::ObjectTypeQuery1);

	UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(), start2, end2, queries, false, ignores,
												   EDrawDebugTrace::ForOneFrame, hitResult2, true);

#if LOG_AC03_MultiTrace

  	TotalTime += DeltaTime;
	if (TotalTime >= 2.0f)
	{
		TotalTime -= 2.0f;

		CLog::Log("---- Channel ----");
		for (const FHitResult& hitResult : hitResult1)
			CLog::Log(hitResult.GetActor()->GetName());

		CLog::Log("---- Objects ----");
		for (const FHitResult& hitResult : hitResult2)
			CLog::Log(hitResult.GetActor()->GetName());

	}
#endif
}

