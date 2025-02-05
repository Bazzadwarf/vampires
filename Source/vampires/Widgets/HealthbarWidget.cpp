// Louis Hobbs | 2024-2025


#include "HealthbarWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "vampires/HealthComponent.h"
#include "vampires/VampireCharacter.h"

void UHealthbarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (UHealthComponent* healthComponent = character->FindComponentByClass<UHealthComponent>())
		{
			healthComponent->OnDamaged.AddDynamic(this, &UHealthbarWidget::UpdateHealthBar);
			UpdateHealthBar({});
		}
	}
}

void UHealthbarWidget::UpdateHealthBar(FDamageInfo damageInfo)
{
	if (ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (UHealthComponent* healthComponent = character->FindComponentByClass<UHealthComponent>())
		{
			float percent = healthComponent->GetCurrentHealth() / healthComponent->GetMaxHealth();
			HealthBar->SetPercent(percent);
		}
	}
}
