// Louis Hobbs | 2024-2025


#include "HealthbarWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "vampires/HealthComponent.h"
#include "vampires/VampireCharacter.h"

void UHealthbarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (UHealthComponent* HealthComponent = Character->FindComponentByClass<UHealthComponent>())
		{
			HealthComponent->OnDamaged.AddDynamic(this, &UHealthbarWidget::UpdateHealthBar);
			UpdateHealthBar({});
		}
	}
}

void UHealthbarWidget::UpdateHealthBar(FDamageInfo DamageInfo)
{
	if (ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (UHealthComponent* HealthComponent = Character->FindComponentByClass<UHealthComponent>())
		{
			float percent = HealthComponent->GetCurrentHealth() / HealthComponent->GetMaxHealth();
			HealthBar->SetPercent(percent);
		}
	}
}
