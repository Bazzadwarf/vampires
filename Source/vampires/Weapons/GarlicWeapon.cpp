// Louis Hobbs | 2024-2025


#include "GarlicWeapon.h"
#include "Components/SphereComponent.h"
#include "vampires/EnemyCharacter.h"
#include "vampires/HealthComponent.h"

AGarlicWeapon::AGarlicWeapon()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(150.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Weapon"));
	
	Damage = 51.0f;
	Range = SphereComponent->GetScaledSphereRadius();
}

void AGarlicWeapon::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGarlicWeapon::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AGarlicWeapon::OnEndOverlap);
}

void AGarlicWeapon::FireWeaponAction_Implementation()
{
}

void AGarlicWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		FOverlappedEnemy overlappedEnemy = FOverlappedEnemy(Enemy);


		GetWorldTimerManager().SetTimer(overlappedEnemy.OverlappedTimerHandle,
		                                FTimerDelegate::CreateUObject(this, &AGarlicWeapon::GarlicFireWeaponAction,
		                                                              overlappedEnemy),
		                                WeaponCooldown,
		                                true);
		OverlappedEnemies.Add(overlappedEnemy);
	}
}

void AGarlicWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		for (int i = 0; i < OverlappedEnemies.Num(); i++)
		{
			if (Enemy == OverlappedEnemies[i].OverlappedEnemyCharacter)
			{
				GetWorldTimerManager().ClearTimer(OverlappedEnemies[i].OverlappedTimerHandle);
				OverlappedEnemies.RemoveAt(i);
				return;
			}
		}
	}
}

void AGarlicWeapon::GarlicFireWeaponAction(FOverlappedEnemy EnemyCharacter)
{
	UHealthComponent* EnemyHealthComponent = EnemyCharacter.OverlappedEnemyCharacter->GetHealthComponent();

	if (EnemyHealthComponent == nullptr)
	{
		return;
	}

	AController* ownerController = nullptr;
	if (AVampireCharacter* character = Cast<AVampireCharacter>(GetOwner()))
	{
		ownerController = character->GetController();
	}

	EnemyHealthComponent->TakeDamage(EnemyCharacter.OverlappedEnemyCharacter, Damage, nullptr,
	                                 ownerController, this);
	
	if (!EnemyHealthComponent->GetIsDead())
	{
		FVector Direction = EnemyCharacter.OverlappedEnemyCharacter->GetActorLocation() - this->GetActorLocation();
		Direction.Normalize();
		Direction.Z = 0.0f;
		float distance = SphereComponent->GetScaledSphereRadius();
		Direction *= distance;
		EnemyCharacter.OverlappedEnemyCharacter->SetActorLocation(
			EnemyCharacter.OverlappedEnemyCharacter->GetActorLocation() + Direction);
	}
}

bool AGarlicWeapon::UpgradeWeapon_Implementation()
{
	if (!Super::UpgradeWeapon_Implementation()) return false;

	switch (CurrentLevel)
	{
		case 1:
			Range *= 1.4f;
			SphereComponent->SetSphereRadius(Range);
			Damage += 2.0f;
			break;
		case 2:
			WeaponCooldown -= 0.1f;
			Damage += 1;
			break;
		case 3:
			Range *= 1.2f;
			SphereComponent->SetSphereRadius(Range);
			Damage += 1.0f;
			break;
		case 4:
			WeaponCooldown -= 0.1f;
			Damage += 2;
			break;
		case 5:
			Range *= 1.2f;
			SphereComponent->SetSphereRadius(Range);
			Damage += 1.0f;
			break;
		case 6:
			WeaponCooldown -= 0.1f;
			Damage += 1;
			break;
		case 7:
			Range *= 1.2f;
			SphereComponent->SetSphereRadius(Range);
			Damage += 1.0f;
			break;
		default:
			return false;
	}

	ResetWeaponTimer();
	return true;
}
