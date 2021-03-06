// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerEyeSpringArm = CreateDefaultSubobject<USpringArmComponent>("PlayerSpringArm");
	PlayerEye = CreateDefaultSubobject<UCameraComponent>("PlayerEye");
	PlayerEyeSpringArm->SetupAttachment(GetRootComponent());
	PlayerEye->SetupAttachment(PlayerEyeSpringArm, USpringArmComponent::SocketName);
	PlayerEyeSpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0,600,0);
	//SetReplicates(true);
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	ensure(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterBase::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterBase::LookUp);
}

void ACharacterBase::MoveForward(float amount)
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

void ACharacterBase::MoveRight(float amount)
{
	if(amount != 0)
	{
		FVector RightDir = PlayerEye->GetRightVector();
		AddMovementInput(RightDir, amount);
	}
}

void ACharacterBase::Turn(float amount)
{
	AddControllerYawInput(amount);
}

void ACharacterBase::LookUp(float amount)
{
	AddControllerPitchInput(amount);
}

