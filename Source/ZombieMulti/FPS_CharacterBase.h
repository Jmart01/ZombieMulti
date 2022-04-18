// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "FPS_CharacterBase.generated.h"

UCLASS()
class ZOMBIEMULTI_API AFPS_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UFUNCTION(Client, Reliable)
	//void SpawnInGameUI();
//************************************Components*****************************
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* PlayerEye;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SkeletalMesh;

	//*********************inputs************************
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float amount);
	void MoveRight(float amount);
	void Turn(float amount);
	void LookUp(float amount);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void BroadCastMovement();
private:
	float PreviousSpeed;
};
