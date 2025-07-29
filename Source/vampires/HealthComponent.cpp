// Louis Hobbs | 2024-2025


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                  AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamagedActor == nullptr || IsDead || !CanDamage)
	{
		return;
	}

	CurrentHealth -= Damage;

	OnDamaged.Broadcast({DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser});

	if (CurrentHealth <= 0.0f)
	{
		IsDead = true;
		OnDeath.Broadcast({DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser});
	}
}

void UHealthComponent::IncrementHealth(float Value)
{
	CurrentHealth += Value;

	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

void UHealthComponent::SetMaxHealth(float Value)
{
	MaxHealth = Value;
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

void UHealthComponent::SetCurrentHealth(float Value)
{
	CurrentHealth = Value;

	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void UHealthComponent::ResetHealth()
{
	CurrentHealth = MaxHealth;
	IsDead = false;
}

void UHealthComponent::RecoverHealth(float value)
{
	// TODO: We might want to add some extra checking here
	IncrementHealth(value);
}

bool UHealthComponent::GetIsDead()
{
	return IsDead;
}

void UHealthComponent::SetIsDead(bool bIsDead)
{
	IsDead = bIsDead;
}

bool UHealthComponent::GetCanDamage()
{
	return CanDamage;
}

void UHealthComponent::SetCanDamage(bool bCanDamage)
{
	CanDamage = bCanDamage;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	ResetHealth();

	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::TakeDamage);
}
