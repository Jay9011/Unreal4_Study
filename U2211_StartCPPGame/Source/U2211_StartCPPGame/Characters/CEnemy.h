#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/ICharacter.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class U2211_STARTCPPGAME_API ACEnemy : public ACharacter
	// Interface
	, public IICharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Color")
	FLinearColor OriginColor = FLinearColor::White;

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UCWeaponComponent* Weapon;

	UPROPERTY(VisibleDefaultsOnly)
	class UCMovementComponent* Movement;

	UPROPERTY(VisibleDefaultsOnly)
	class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
	class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
	class UCStatusComponent* Status;

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

public:
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	void Hitted();

public:
	void End_Hitted() override;

private:
	UFUNCTION()
	void RestoreColor();

private:
	void Dead();

public:
	void End_Dead() override;

private:
	struct FDamageData
	{
		float Power;
		class ACharacter* Character;
		class AActor* Causer;

		struct FActionDamageEvent* Event;
	} Damage;

	FTimerHandle RestoreColor_TimerHandle;
};
