// Louis Hobbs | 2024-2025


#include "PentagramWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "vampires/VampirePlayerController.h"
#include "../PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "vampires/EnemyCharacter.h"
#include "vampires/Pickup.h"

APentagramWeapon::APentagramWeapon()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Sphere Component"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Weapon"));

	WeaponCooldown = 90.0f;
}

void APentagramWeapon::FireWeaponAction_Implementation()
{
	Super::FireWeaponAction_Implementation();

	for (int i = OverlappedPickups.Num() - 1; i >= 0; i--)
	{
		OverlappedPickups[i]->Destroy();
	}

	for (int i = OverlappedEnemies.Num() - 1; i >= 0; i--)
	{
		OverlappedEnemies[i]->Destroy();
	}
}

bool APentagramWeapon::UpgradeWeapon_Implementation()
{
	if (!Super::UpgradeWeapon_Implementation())
	{
		return false;
	}

	switch (CurrentLevel)
	{
	case 1:
		WeaponCooldown -= 5.0f;
		break;
	case 2:
		WeaponCooldown -= 5.0f;
		break;
	case 3:
		WeaponCooldown -= 5.0f;
		break;
	case 4:
		WeaponCooldown -= 5.0f;
		break;
	case 5:
		WeaponCooldown -= 5.0f;
		break;
	case 6:
		WeaponCooldown -= 2.5f;
		break;
	case 7:
		WeaponCooldown -= 2.5f;
		break;
	default:
		return false;
	}

	ResetWeaponTimer();

	return true;
}

void APentagramWeapon::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                            const FHitResult& SweepResult)
{
	if (APickup* Pickup = Cast<APickup>(OtherActor))
	{
		OverlappedPickups.Add(Pickup);
	}
	else
	{
		Super::OnWeaponBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
		                            SweepResult);
	}
}

void APentagramWeapon::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (APickup* Pickup = Cast<APickup>(OtherActor))
	{
		OverlappedPickups.Remove(Pickup);
	}
	else
	{
		Super::OnWeaponEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	}
}
