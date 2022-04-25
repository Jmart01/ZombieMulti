// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZombieMulti.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEMULTI_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UGameplayAbilityBase();
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
	EAbilityInputID AbilityInputID = EAbilityInputID::None;
};
