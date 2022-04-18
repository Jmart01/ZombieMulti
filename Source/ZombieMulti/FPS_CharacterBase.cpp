// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_CharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFPS_CharacterBase::AFPS_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerEye = CreateDefaultSubobject<UCameraComponent>("PlayerEye");
	PlayerEye->SetupAttachment(GetRootComponent());
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
}

// Called when the game starts or when spawned
void AFPS_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFPS_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPS_CharacterBase::BroadCastMovement()
{
	if(HasAuthority())
	{
		float CurrentSpeed = GetCharacterMovement()->GetLastUpdateVelocity().Size();
		if(PreviousSpeed == 0 && CurrentSpeed !=0)
		{
			
		}
	}
}

// Called to bind functionality to input
void AFPS_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	ensure(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPS_CharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPS_CharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AFPS_CharacterBase::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPS_CharacterBase::LookUp);
}

void AFPS_CharacterBase::MoveForward(float amount)
{
	if(amount != 0)
	{
		FVector ViewLoc;
		FRotator ViewRot;
		GetController()->GetPlayerViewPoint(ViewLoc, ViewRot);
		FVector ForwardDir = ViewRot.Vector();
		AddMovementInput(ForwardDir, amount);
	}
}

void AFPS_CharacterBase::MoveRight(float amount)
{
	if(amount != 0)
	{
		FVector RightDir = PlayerEye->GetRightVector();
		AddMovementInput(RightDir);
	}
}

void AFPS_CharacterBase::Turn(float amount)
{
	AddControllerYawInput(amount);
}

void AFPS_CharacterBase::LookUp(float amount)
{
	AddControllerPitchInput(amount);
}

