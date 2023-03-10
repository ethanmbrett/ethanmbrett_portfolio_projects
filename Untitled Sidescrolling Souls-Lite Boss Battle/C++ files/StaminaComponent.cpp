/* Copyright (C) 2023 Ethan Brett - All Rights Reserved
*  This code is distributed for demonstration purposes only, and
*  should not be modified or redistributed.
*/


#include "StaminaComponent.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina = MaxStamina;
	// ...
	
}

void UStaminaComponent::DecrementStamina(int StaminaCost)
{
	CurrentStamina -= StaminaCost;
	if (CurrentStamina <= 0)
	{
		OnStaminaDepleted.Broadcast();
		CurrentStamina = 0;
	}
	else
	{
		OnStaminaDecrease.Broadcast();
	}
}

void UStaminaComponent::RegenerateStamina(int StaminaIncrease)
{
	CurrentStamina += StaminaIncrease;
	if (CurrentStamina > MaxStamina)
	{
		CurrentStamina = MaxStamina;
	}
}

void UStaminaComponent::StartPassiveRegen()
{
	GetWorld()->GetTimerManager().SetTimer(regenTimerHandle, this, &UStaminaComponent::PassivelyRegenerateStamina, passiveRegenRate, true, 0.0f);
}

void UStaminaComponent::PassivelyRegenerateStamina()
{
	if (canRegenDecrease && canRegenDeplete)
	{
		RegenerateStamina(passiveStaminaRegenAmount);
	}
}

bool UStaminaComponent::CheckStamina(int compareVal)
{
	bool isGreater = false;
	if (compareVal >= CurrentStamina)
	{
		isGreater = true;
	}
	return isGreater;
}


