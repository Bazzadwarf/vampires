// Louis Hobbs | 2024-2025


#include "ProjectileWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "vampires/EnemyCharacter.h"
#include "vampires/PlayerCharacter.h"
#include "vampires/VampirePlayerController.h"
#include "../Weapon.h"
#include "Components/BoxComponent.h"

AProjectileWeapon::AProjectileWeapon()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Weapon"));
}

void AProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileWeapon::OnWeaponBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AProjectileWeapon::OnWeaponEndOverlap);

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

void AProjectileWeapon::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                             const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Add(Enemy);
	}
}

void AProjectileWeapon::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Remove(Enemy);
	}
}

void AProjectileWeapon::FireWeaponAction_Implementation()
{
	Super::FireWeaponAction_Implementation();

	remainingProjectilesToSpawn = ProjectilesPerActivation;
	GetWorldTimerManager().SetTimer(FireProjectileTimerHandler, this, &AProjectileWeapon::FireProjectile, ProjectileSpawningDelay, true, 0.0f);
}

void AProjectileWeapon::FireProjectile()
{
	remainingProjectilesToSpawn--;
	if (remainingProjectilesToSpawn == 0)
	{
		GetWorldTimerManager().ClearTimer(FireProjectileTimerHandler);
	}
}
