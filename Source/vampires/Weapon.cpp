// Louis Hobbs | 2024-2025


#include "Weapon.h"

#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "VampirePlayerController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Weapon"));
	SetRootComponent(BoxComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnWeaponEndOverlap);

	FViewport::ViewportResizedEvent.AddUObject(this, &AWeapon::ResizeBoxComponent);

	ResizeBoxComponent(GEngine->GameViewport->Viewport, -2);

	GetWorldTimerManager().SetTimer(WeaponTimerHandle, this, &AWeapon::FireWeaponAction, WeaponCooldown, true);
}

void AWeapon::ResetWeaponTimer()
{
	GetWorldTimerManager().ClearTimer(WeaponTimerHandle);
	GetWorldTimerManager().SetTimer(WeaponTimerHandle, this, &AWeapon::FireWeaponAction, WeaponCooldown, true);
}

void AWeapon::FireWeaponAction_Implementation()
{
	// This should be overridden in child weapon classes

	if (WeaponActivatedSoundBase)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), WeaponActivatedSoundBase);
	}
}

bool AWeapon::UpgradeWeapon_Implementation()
{
	if (CurrentLevel < MaxLevel)
	{
		CurrentLevel++;
		return true;
	}

	return false;
}

void AWeapon::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Add(Enemy);
	}
}

void AWeapon::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Remove(Enemy);
	}
}

void AWeapon::ResizeBoxComponent(FViewport* Viewport, const uint32 Unused)
{
	if (!GEngine->GameViewport)
	{
		return;
	}

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

	float width = FVector::Dist(TopLeft, TopRight) / 2;
	float height = FVector::Dist(TopLeft, BottomLeft) / 2;

	// I am using the unused flag to work around a bug where the DeprojectScreenPositionToWorld doesn't match the
	// values that I am expecting, in that they are way too small, for any other resize event we can skip this nonsense.
	if (Unused == -2)
	{
		width *= 266.666;
		height *= 266.666;
	}

	BoxComponent->SetBoxExtent(FVector(height, width, 200.0f));
}
