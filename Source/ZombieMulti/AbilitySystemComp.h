// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemComp.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ZOMBIEMULTI_API UAbilitySystemComp : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void TryActivateAbility(class AFirstPersonCharacter_C* AbilityCaster);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AbilityCooldownTag;

	//float GetCoolDownTime()
protected:
	virtual void CommitAbility();
	virtual bool bCanCastAbility();
	class AFirstPersonCharacter_C* Caster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AmmoAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GrenadeAmount;
	
};
