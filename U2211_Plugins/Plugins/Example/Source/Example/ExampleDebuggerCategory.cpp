#include "ExampleDebuggerCategory.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

FExampleDebuggerCategory::FExampleDebuggerCategory()
{
	bShowOnlyWithDebugActor = false;
}

FExampleDebuggerCategory::~FExampleDebuggerCategory()
{
}

TSharedRef<FGameplayDebuggerCategory> FExampleDebuggerCategory::MakeInstance()
{
	return MakeShareable(new FExampleDebuggerCategory());
}

void FExampleDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	// GLog->Log(OwnerPC->GetPawn()->GetName());

	// if (!!DebugActor)
	// 	GLog->Log(DebugActor->GetName());

	ACharacter* player = OwnerPC->GetPawn<ACharacter>();
	if (player == nullptr) return;

	// Player
	{
		PlayerPawnData.bDraw = true;
		PlayerPawnData.Name = player->GetName();
		PlayerPawnData.Location = player->GetActorLocation();
		PlayerPawnData.Forward = player->GetActorForwardVector();
	}

	// Forward Actor
	{
		FHitResult hitResult;

		FVector start = PlayerPawnData.Location;
		FVector end = start + player->GetActorForwardVector() * TraceDistance;

		FCollisionQueryParams params;
		params.AddIgnoredActor(player);

		player->GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, params);

		if (hitResult.bBlockingHit)
		{
			ForwardActorData.bDraw = true;
			ForwardActorData.Name = hitResult.GetActor()->GetName();
			ForwardActorData.Location = hitResult.GetActor()->GetActorLocation();
			ForwardActorData.Forward = hitResult.GetActor()->GetActorForwardVector();
		}
	}

	// DebugActor
	if (!!DebugActor)
	{
		DebugActorData.bDraw = true;
		DebugActorData.Name = DebugActor->GetName();
		DebugActorData.Location = DebugActor->GetActorLocation();
		DebugActorData.Forward = DebugActor->GetActorForwardVector();
	}
}

void FExampleDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	FVector start = PlayerPawnData.Location;
	FVector end = PlayerPawnData.Location + PlayerPawnData.Forward * TraceDistance;

	DrawDebugLine(OwnerPC->GetWorld(), start, end, FColor::Red);
}
