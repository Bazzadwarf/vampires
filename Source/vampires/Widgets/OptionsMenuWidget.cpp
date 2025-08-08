// Louis Hobbs | 2024-2025


#include "OptionsMenuWidget.h"

#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RHI.h"

void UOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GenerateWindowTypeOptions();
	WindowTypeComboBox->OnSelectionChanged.AddDynamic(this, &UOptionsMenuWidget::OnWindowTypeSelectionChanged);

	GenerateResolutionOptions();
	ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &UOptionsMenuWidget::OnResolutionSelectionChanged);

	GenerateDynamicResolutionOptions();
	DynamicResolutionComboBox->OnSelectionChanged.AddDynamic(
		this, &UOptionsMenuWidget::OnDynamicResolutionSelectionChanged);

	GenerateVsyncOptions();
	VsyncComboBox->OnSelectionChanged.AddDynamic(this, &UOptionsMenuWidget::OnVsyncSelectionChanged);

	GenerateRefreshRateOptions();
	RefreshRateComboBox->OnSelectionChanged.AddDynamic(this, &UOptionsMenuWidget::OnRefreshRateSelectionChanged);

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenuWidget::ReturnButtonOnClicked);
		ReturnButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenuWidget::PlayClickedSound);

		ReturnButton->OnHovered.AddUniqueDynamic(this, &UOptionsMenuWidget::PlayHoveredSound);
		ReturnButton->OnHovered.AddUniqueDynamic(this, &UOptionsMenuWidget::ReturnTextBlockHoveredDelegate);

		ReturnButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsMenuWidget::ReturnTextBlockUnhoveredDelegate);
		ReturnButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsMenuWidget::PlayUnhoveredSound);
	}
}

void UOptionsMenuWidget::GenerateWindowTypeOptions()
{
	WindowTypeComboBox->ClearOptions();
	WindowTypeComboBox->AddOption(LexToString(EWindowMode::Fullscreen));
	WindowTypeComboBox->AddOption(LexToString(EWindowMode::WindowedFullscreen));
	WindowTypeComboBox->AddOption(LexToString(EWindowMode::Windowed));
	WindowTypeComboBox->SetSelectedOption(LexToString(GEngine->GameUserSettings->GetFullscreenMode()));
}

void UOptionsMenuWidget::GenerateResolutionOptions()
{
	ResolutionComboBox->ClearOptions();

	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);
	for (FIntPoint Resolution : Resolutions)
	{
		ResolutionComboBox->AddOption(FString::FromInt(Resolution.X) + "x" + FString::FromInt(Resolution.Y));
	}

	FVector2D Resolution = FVector2D::ZeroVector;
	GEngine->GameViewport->GetViewportSize(Resolution);
	FString ResolutionString = FString::FromInt(Resolution.X) + "x" + FString::FromInt(Resolution.Y);
	if (ResolutionComboBox->FindOptionIndex(ResolutionString) == -1)
	{
		ResolutionComboBox->AddOption(ResolutionString);
	}

	ResolutionComboBox->SetSelectedOption(ResolutionString);
}

void UOptionsMenuWidget::GenerateDynamicResolutionOptions()
{
	DynamicResolutionComboBox->ClearOptions();
	DynamicResolutionComboBox->AddOption("Enabled");
	DynamicResolutionComboBox->AddOption("Disabled");

	if (GEngine->GameUserSettings->IsDynamicResolutionEnabled())
	{
		DynamicResolutionComboBox->SetSelectedOption("Enabled");
	}
	else
	{
		DynamicResolutionComboBox->SetSelectedOption("Disabled");
	}
}

void UOptionsMenuWidget::GenerateVsyncOptions()
{
	VsyncComboBox->ClearOptions();
	VsyncComboBox->AddOption("Enabled");
	VsyncComboBox->AddOption("Disabled");

	if (GEngine->GameUserSettings->IsVSyncEnabled())
	{
		VsyncComboBox->SetSelectedOption("Enabled");
	}
	else
	{
		VsyncComboBox->SetSelectedOption("Disabled");
	}
}

void UOptionsMenuWidget::GenerateRefreshRateOptions()
{
	RefreshRateComboBox->ClearOptions();

	FScreenResolutionArray ScreenResolutions;
	RHIGetAvailableResolutions(ScreenResolutions, false);
	TArray<uint32> RefreshRates;
	for (FScreenResolutionRHI ScreenResolution : ScreenResolutions)
	{
		RefreshRates.AddUnique(ScreenResolution.RefreshRate);
	}

	RefreshRates.Sort();
	for (uint32 RefreshRate : RefreshRates)
	{
		RefreshRateComboBox->AddOption(FString::FromInt(RefreshRate));
	}

	RefreshRateComboBox->AddOption("Unlimited");

	float FrameRateLimit = GEngine->GameUserSettings->GetFrameRateLimit();

	if (FrameRateLimit > 0.0f)
	{
		RefreshRateComboBox->SetSelectedOption(FString::FromInt(FrameRateLimit));
	}
	else
	{
		RefreshRateComboBox->SetSelectedOption("Unlimited");
	}
}

void UOptionsMenuWidget::OnResolutionSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	FString Horizontal;
	FString Vertical;
	SelectedItem.Split("x", &Horizontal, &Vertical);

	int32 HorizontalInt = FCString::Atoi(*Horizontal);
	int32 VerticalInt = FCString::Atoi(*Vertical);

	if (HorizontalInt > 0 && VerticalInt > 0)
	{
		GEngine->GameUserSettings->SetScreenResolution({HorizontalInt, VerticalInt});
	}

	GEngine->GameUserSettings->ApplySettings(false);
}


void UOptionsMenuWidget::OnWindowTypeSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == LexToString(EWindowMode::Fullscreen))
	{
		SetWindowModeFullscreen();
	}
	else if (SelectedItem == LexToString(EWindowMode::WindowedFullscreen))
	{
		SetWindowModeWindowedFullscreen();
	}
	else if (SelectedItem == LexToString(EWindowMode::Windowed))
	{
		SetWindowModeWindowed();
	}
}

void UOptionsMenuWidget::SetWindowModeFullscreen()
{
	GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	GEngine->GameUserSettings->ApplySettings(false);
}

void UOptionsMenuWidget::SetWindowModeWindowedFullscreen()
{
	GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	GEngine->GameUserSettings->ApplySettings(false);
}

void UOptionsMenuWidget::SetWindowModeWindowed()
{
	GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
	GEngine->GameUserSettings->ApplySettings(false);

	FVector2D Resolution = FVector2D::ZeroVector;
	GEngine->GameViewport->GetViewportSize(Resolution);

	FString ResolutionString = FString::FromInt(Resolution.X) + "x" + FString::FromInt(Resolution.Y);
	if (ResolutionComboBox->FindOptionIndex(ResolutionString) == -1)
	{
		ResolutionComboBox->AddOption(ResolutionString);
	}

	ResolutionComboBox->SetSelectedOption(ResolutionString);
}

void UOptionsMenuWidget::OnDynamicResolutionSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == "Enabled")
	{
		GEngine->GameUserSettings->SetDynamicResolutionEnabled(true);
	}
	else if (SelectedItem == "Disabled")
	{
		GEngine->GameUserSettings->SetDynamicResolutionEnabled(false);
	}

	GEngine->GameUserSettings->ApplySettings(false);
}

void UOptionsMenuWidget::OnVsyncSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == "Enabled")
	{
		GEngine->GameUserSettings->SetVSyncEnabled(true);
	}
	else if (SelectedItem == "Disabled")
	{
		GEngine->GameUserSettings->SetVSyncEnabled(false);
	}

	GEngine->GameUserSettings->ApplySettings(false);
}

void UOptionsMenuWidget::OnRefreshRateSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	GEngine->GameUserSettings->SetFrameRateLimit(FCString::Atoi(*SelectedItem));
	GEngine->GameUserSettings->ApplySettings(false);
}

void UOptionsMenuWidget::ReturnButtonOnClicked()
{
	if (MainMenuMenuWidget)
	{
		RemoveFromParent();

		UUserWidget* SelectWeaponWidget = CreateWidget<UUserWidget, APlayerController*>(
			UGameplayStatics::GetPlayerController(GetWorld(), 0), MainMenuMenuWidget);

		if (SelectWeaponWidget)
		{
			SelectWeaponWidget->AddToViewport();
		}
	}
}
