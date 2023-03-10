/* Copyright (C) 2023 Ethan Brett - All Rights Reserved
*  This code is distributed for demonstration purposes only, and
*  should not be modified or redistributed.
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStaminaDepleted);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStaminaDecrement);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEV_2D_API UStaminaComponent : public UActorComponent
{

	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComponent();

private:
	FTimerHandle regenTimerHandle;

protected:
	//Character's Max Stamina
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaxStamina = 100;

	//Passive Stamina Regen Amount
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int passiveStaminaRegenAmount = 1;

	//Passive Stamina Regen rate
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float passiveRegenRate = 0.25f;

	//Character's Current Stamina Value.
	UPROPERTY(BlueprintReadOnly)
		int CurrentStamina = 100;

	//Can passive regen Stamina
	UPROPERTY(BlueprintReadWrite)
		bool canRegenDecrease = true;

	//Can passive regen Stamina
	UPROPERTY(BlueprintReadWrite)
		bool canRegenDeplete = true;

	// Called when the game starts
	virtual void BeginPlay() override;

	/**
	* DecrementStamina
	* 
	* Function used to lower CurrentStamina by a given amount, such as after an attack action
	* If the new value of CurrentStamina is <= 0, calls the OnStaminaDepleted event and sets CurrentStamina to 0
	* @param StaminaCost, int value by which to lower CurrentStamina
	*/
	UFUNCTION(BlueprintCallable)
		void DecrementStamina(int StaminaCost);

	/**
	* RegenerateStamina
	* 
	* Function used to increase Current Stamina by a given amount, for passive or item based regeneration
	* If the new value of CurrentStamina is > MaxStamina, sets CurrentStamina to MaxStamina
	* @param StaminaIncrease, int value by which to increase CurrentStamina
	*/
	UFUNCTION(BlueprintCallable)
		void RegenerateStamina(int StaminaIncrease);

	/**
	* StartPassiveRegen
	* 
	* Function uses timer to regenerate stamina at intervals. Do not use if passive regen is not desired.
	*/
	UFUNCTION(BlueprintCallable)
		void StartPassiveRegen();

	/**
	* PassivelyRegenerateStamina
	*
	* Function used to passively regenerate Stamina. Calls Regenerate stamina with
	* an StaminaIncrease equal to the passiveStaminaRegenAmount. Does nothing if canRegen == false.
	*/
	UFUNCTION()
		void PassivelyRegenerateStamina();

	/**
	* CheckStamina
	* 
	* Function used to check if a given int is greater or equal to the CurrentStamina
	* Currently not in use.
	* @param CompareVal, value to check against the CurrentStamina
	* @return isGreater, bool, returns true if the CompareVal is greater than or equal to the CurrentStamina
	*/
	UFUNCTION(BlueprintCallable)
		bool CheckStamina(int CompareVal);

	//Event for character-specific behavior for when stamina reaches 0;
	UPROPERTY(BlueprintAssignable, EditAnywhere)
		FStaminaDepleted OnStaminaDepleted;

	//Event for character-specific behavior for when stamina decreases;
	UPROPERTY(BlueprintAssignable, EditAnywhere)
		FStaminaDecrement OnStaminaDecrease;
};
