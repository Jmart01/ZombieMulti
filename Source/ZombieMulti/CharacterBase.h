// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "CharacterBase.generated.h"

UCLASS()
class ZOMBIEMULTI_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected://Components
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* PlayerEyeSpringArm;
	UCameraComponent* PlayerEye;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected://Inputs
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float amount);
	void MoveRight(float amount);
	void Turn(float amount);
	void LookUp(float amount);

};
