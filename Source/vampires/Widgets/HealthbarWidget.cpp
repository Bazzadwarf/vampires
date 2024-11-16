// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthbarWidget.h"

#include "Kismet/GameplayStatics.h"
#include "vampires/PlayerCharacter.h"
#include "Components/ProgressBar.h"
#include "vampires/HealthComponent.h"
#include "vampires/VampireCharacter.h"

void UHealthbarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UHealthComponent* healthComponent = player->GetHealthComponent();
	healthComponent->OnDamaged.BindUFunction(this, "UpdateHealthBar");
	UpdateHealthBar();
}

void UHealthbarWidget::UpdateHealthBar()
{
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	float percent = player->GetHealthComponent()->GetCurrentHealth() / player->GetHealthComponent()->GetMaxHealth();
	HealthBar->SetPercent(percent);
}
