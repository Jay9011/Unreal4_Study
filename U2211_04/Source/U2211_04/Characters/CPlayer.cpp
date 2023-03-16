#include "CPlayer.h"

#include "CAnimInstance.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapons/CWeaponComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &Weapon, "Weapon");


	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));


	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/ABP_Character.ABP_Character_C'");
	GetMesh()->SetAnimClass(animInstance);

	GetCharacterMovement()->MaxWalkSpeed = 400;

	SpringArm->SetRelativeLocation(FVector(0, 0, 150));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 300;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = false;

	Camera->SetRelativeLocation(FVector(-30, 0, 0));
	Camera->bUsePawnControlRotation = false;

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetController<APlayerController>()->PlayerCameraManager->ViewPitchMin = PitchRange.X;
	GetController<APlayerController>()->PlayerCameraManager->ViewPitchMax = PitchRange.Y;

}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACPlayer::OffRun);


	PlayerInputComponent->BindAction("AR4", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::SetAR4Mode);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::Begin_Fire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::End_Fire);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::Begin_Aim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::End_Aim);

	PlayerInputComponent->BindAction("AutoFire", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::ToggleAutoFire);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::Reload);

}

void ACPlayer::OnMoveForward(float InAxisValue)
{
	const FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxisValue);

}

void ACPlayer::OnMoveRight(float InAxisValue)
{
	const FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxisValue);

}

void ACPlayer::OnHorizontalLook(float InAxisValue)
{
	AddControllerYawInput(InAxisValue);

}

void ACPlayer::OnVerticalLook(float InAxisValue)
{
	AddControllerPitchInput(InAxisValue);

}

void ACPlayer::OnRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;

}

void ACPlayer::OffRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
}
