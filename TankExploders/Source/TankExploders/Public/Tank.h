// Copyright BigD Games

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //jdeo- must put new #includes about the generated.h 


UCLASS()
class TANKEXPLODERS_API ATank : public APawn
{
	GENERATED_BODY()

private:
	ATank();



public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	int32 CurrentHealth = MaxHealth;

	// called by engine when actor damage is dealt -jdeo
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	// return current health as a percentage of starting health between 0 and 1 -jdeo
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;


};
