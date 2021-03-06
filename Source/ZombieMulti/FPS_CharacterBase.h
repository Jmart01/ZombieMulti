// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "FPS_CharacterBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovedDelegate);
UCLASS()
class ZOMBIEMULTI_API AFPS_CharacterBase: public ACharacter, public IAbilitySystemInterface
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	UCameraComponent* PlayerEye;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Camera, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UAttributeSetBase* Attributes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animation)
	UAnimInstance* AnimInstance;


	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USceneComponent* MuzzleLocation;

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
	FOnMovedDelegate OnMoved;
	FOnMovedDelegate OnStopedMoving;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();
	virtual void GiveAbilities();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category= "Gameplay Ability System")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category=" Gameplay Ability System")
	TArray<TSubclassOf<class UGameplayAbilityBase>> DefaultAbilities;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Ammo")
	int AmmoinClip;
	
	
	void BroadCastMovement();

	UFUNCTION(BlueprintImplementableEvent)
	void SetModels();
private:
	float PreviousSpeed;
};
