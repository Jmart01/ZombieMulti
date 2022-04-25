// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"

UAttributeSetBase::UAttributeSetBase()
{
	
}

void UAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, WeaponAmmo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, CurrentWeapon, COND_None, REPNOTIFY_Always);
}

void UAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Health, OldHealth);
}

void UAttributeSetBase::OnRep_WeaponAmmo(const FGameplayAttributeData& OldWeaponAmmo)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, WeaponAmmo, OldWeaponAmmo);
}

void UAttributeSetBase::OnRep_CurrentWeapon(const FGameplayAttributeData& OldWeapon)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, CurrentWeapon, OldWeapon);
}


