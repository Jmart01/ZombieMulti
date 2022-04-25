// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
UCLASS()
class ZOMBIEMULTI_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAttributeSetBase();
	
	
	
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Health);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UPROPERTY(BlueprintReadOnly, Category = "WeaponAmmo", ReplicatedUsing = OnRep_WeaponAmmo)
	FGameplayAttributeData WeaponAmmo;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, WeaponAmmo);

	UFUNCTION()
	virtual void OnRep_WeaponAmmo(const FGameplayAttributeData& OldWeaponAmmo);

	UPROPERTY(BlueprintReadOnly, Category="Current Weapon", ReplicatedUsing= ONRep_CurrentWeapon)
	FGameplayAttributeData CurrentWeapon;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, CurrentWeapon);

	UFUNCTION()
	virtual void OnRep_CurrentWeapon(const FGameplayAttributeData& OldWeapon);
};
