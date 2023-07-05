#include "OG_PlayerCharacter.h"


#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AOG_PlayerCharacter::AOG_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(34.f, 88.f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 500.f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetOffset = FVector(0.f, 0.f, 100.f);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 300.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 350.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 700.f;
	GetCharacterMovement()->SetWalkableFloorAngle(60);
	
}

void AOG_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AOG_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &AOG_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AOG_PlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AOG_PlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AOG_PlayerCharacter::StopJumping);
}

void AOG_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOG_PlayerCharacter::MoveForward(float Axis)
{
	if (Controller == NULL || Axis == 0.f) return;
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Axis);
}

void AOG_PlayerCharacter::MoveRight(float Axis)
{
	if (Controller == NULL || Axis == 0.f) return;
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}

void AOG_PlayerCharacter::Jump()
{
	if (Controller == NULL) return;
	Super::Jump();
}

void AOG_PlayerCharacter::StopJumping()
{
	if (Controller == NULL) return;
	Super::StopJumping();
}
