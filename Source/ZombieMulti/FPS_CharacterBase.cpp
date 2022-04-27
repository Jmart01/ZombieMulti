// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"
#include "GameplayAbilityBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComp.h"
#include <GameplayEffectTypes.h>
#include "Net/UnrealNetwork.h"

// Sets default values
AFPS_CharacterBase::AFPS_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerEye = CreateDefaultSubobject<UCameraComponent>("PlayerEye");
	PlayerEye->SetupAttachment(GetCapsuleComponent());
	//PlayerEye->AddRelativeLocation(FVector(-39.65f,1.75f,64.0f));
	PlayerEye->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	Attributes = CreateDefaultSubobject<UAttributeSetBase>("Attributes");
	
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

UAbilitySystemComponent* AFPS_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AFPS_CharacterBase::InitializeAttributes()
{
	if(AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
		if(SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void AFPS_CharacterBase::GiveAbilities()
{
	if(HasAuthority() && AbilitySystemComponent)
	{
		for(TSubclassOf<UGameplayAbilityBase>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(StartupAbility,1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID),this));
		}
	}
}

void AFPS_CharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
	GiveAbilities();
}

void AFPS_CharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	InitializeAttributes();

	if(AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel","EAbilityInputID",
			static_cast<int32>(EAbilityInputID::Confirm),
			static_cast<int32>(EAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent,Binds);
	}
}

void AFPS_CharacterBase::BroadCastMovement()
{
	if(HasAuthority())
	{
		float CurrentSpeed = GetCharacterMovement()->GetLastUpdateVelocity().Size();
		if(PreviousSpeed == 0 && CurrentSpeed !=0)
		{
			OnMoved.Broadcast();
		}
		if(PreviousSpeed != 0 && CurrentSpeed == 0)
		{
			OnStopedMoving.Broadcast();
		}
		PreviousSpeed = CurrentSpeed;
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

	if(AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel","EAbilityInputID",
			static_cast<int32>(EAbilityInputID::Confirm),
			static_cast<int32>(EAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent,Binds);
	}
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
	if(amount > 0)
	{
		FVector RightDir = PlayerEye->GetRightVector();
		AddMovementInput(RightDir);
	}
	else if(amount < 0)
	{
		FVector LeftDir = PlayerEye->GetRightVector();
		AddMovementInput(-LeftDir);
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

