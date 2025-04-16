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

void APentagramWeapon::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APentagramWeapon::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APentagramWeapon::OnEndOverlap);

	FVector TopLeft, TopLeftDir;
	FVector TopRight, TopRightDir;
	FVector BottomLeft, BottomLeftDir;
	FVector BottomRight, BottomRightDir;

	FVector2d ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	AVampirePlayerController* PlayerController = Cast<AVampirePlayerController>(
		UGameplayStatics::GetPlayerController(PlayerCharacter, 0));

	PlayerController->DeprojectScreenPositionToWorld(0, 0, TopLeft, TopLeftDir);
	PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X, 0, TopRight, TopRightDir);
	PlayerController->DeprojectScreenPositionToWorld(0, ViewportSize.Y, BottomLeft, BottomLeftDir);
	PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X, ViewportSize.Y, BottomRight, BottomRightDir);

	float width = FVector::Dist(TopLeft, TopRight) * 60;
	float height = FVector::Dist(TopLeft, BottomLeft) * 60;
	BoxComponent->SetBoxExtent(FVector(height, width, 200.0f));
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
	if (!Super::UpgradeWeapon_Implementation()) return false;

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

void APentagramWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Add(Enemy);
	}
	else if (APickup* Pickup = Cast<APickup>(OtherActor))
	{
		OverlappedPickups.Add(Pickup);
	}
}

void APentagramWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Remove(Enemy);
	}
	else if (APickup* Pickup = Cast<APickup>(OtherActor))
	{
		OverlappedPickups.Remove(Pickup);
	}
}
