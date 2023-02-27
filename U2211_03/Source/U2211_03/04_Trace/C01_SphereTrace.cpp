#include "04_Trace/C01_SphereTrace.h"

#include "Global.h"
#include "Particles/ParticleSystemComponent.h"

AC01_SphereTrace::AC01_SphereTrace()
{
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle");


	UParticleSystem* particle;
	CHelpers::GetAsset<UParticleSystem>(&particle, "ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_thunder.P_ky_hit_thunder'");

	Particle->SetTemplate(particle);
	Particle->bAutoActivate = false;
	Particle->SetRelativeScale3D(FVector(2));

}

void AC01_SphereTrace::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC01_SphereTrace::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FVector location = GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(EObjectTypeQuery::ObjectTypeQuery4);

	TArray<AActor*> ignores;
	TArray<FHitResult> HitResults;


	bool b = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), location, location, 300.f, 
															  types, false, ignores, DrawDebug, 
															  HitResults, true, 
															  FLinearColor::Red, FLinearColor::Green, DrawDuration);

	CheckFalse(b)

	Particle->ResetParticles();
	Particle->SetActive(true);

	for (const FHitResult& hitResult : HitResults)
	{
		UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
		if (!!mesh && mesh->IsSimulatingPhysics())
		{
			mesh->AddRadialImpulse(location, 1000, (MaxMass - mesh->GetMass()) * ImpulseAmount, ERadialImpulseFalloff::RIF_Linear);

		}
	}
}
