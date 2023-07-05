#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "OG_PlayerCharacter.generated.h"

UCLASS()
class OCTOGAMES_API AOG_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	AOG_PlayerCharacter();
	
private:
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* CameraComponent;
	
public:	
	virtual void Tick(float DeltaTime) override;
	
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	virtual void Jump() override;
	virtual void StopJumping() override;
};
