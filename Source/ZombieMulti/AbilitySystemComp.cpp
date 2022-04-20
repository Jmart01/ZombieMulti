// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystemComp.h"

void UAbilitySystemComp::TryActivateAbility(AFirstPersonCharacter_C* AbilityCaster)
{
	Caster = AbilityCaster;

	if(bCanCastAbility())
	{
		//Caster
	}
}

void UAbilitySystemComp::CommitAbility()
{
	
}

bool UAbilitySystemComp::bCanCastAbility()
{
	//temporary
	return true;
}

