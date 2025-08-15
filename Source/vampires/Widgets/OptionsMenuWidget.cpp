// Louis Hobbs | 2024-2025


#include "OptionsMenuWidget.h"

#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RHI.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Sound/SoundClass.h"

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

	GenerateAudioLevelOptions();
	MasterAudioSlider->OnValueChanged.AddDynamic(this, &UOptionsMenuWidget::OnAudioLeverValueChanged);

	if (ResetToDefaultsButton)
	{
		ResetToDefaultsButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenuWidget::ResetToDefaultsOnClicked);
		ResetToDefaultsButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenuWidget::PlayClickedSound);

		ResetToDefaultsButton->OnHovered.AddUniqueDynamic(this, &UOptionsMenuWidget::PlayHoveredSound);
		ResetToDefaultsButton->OnHovered.AddUniqueDynamic(this, &UOptionsMenuWidget::ResetToDefaultsTextBlockHoveredDelegate);

		ResetToDefaultsButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsMenuWidget::ResetToDefaultsTextBlockUnhoveredDelegate);
		ResetToDefaultsButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsMenuWidget::PlayUnhoveredSound);
	}
	
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

	TArray<uint32> RefreshRates;
	
	GetListOfUniqueRefreshRates(RefreshRates);
	
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

void UOptionsMenuWidget::GenerateAudioLevelOptions()
{
	if (MasterSoundClass)
	{
		float CurrentVolume = FMath::Clamp(MasterSoundClass->Properties.Volume, 0.0f, 1.0f);

		MasterAudioSlider->SetValue(CurrentVolume);

		int AudioLevel = CurrentVolume * 100.0f;
		MasterAudioTextBlock->SetText(FText::FromString(FString::FromInt(AudioLevel) + "%"));
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

void UOptionsMenuWidget::OnAudioLeverValueChanged(float Value)
{
	if (MasterSoundClass)
	{
		MasterSoundClass->Properties.Volume = FMath::Clamp(Value, 0.0f, 1.0f);

		int AudioLevel = FMath::Clamp(Value, 0.0f, 1.0f) * 100.0f;
		
		MasterAudioTextBlock->SetText(FText::FromString(FString::FromInt(AudioLevel) + "%"));
	}
}

void UOptionsMenuWidget::ResetToDefaultsOnClicked()
{
	// Set Resolution to Monitor Res
	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);

	if (Resolutions.Num() > 0)
	{
		GEngine->GameUserSettings->SetScreenResolution(Resolutions.Last());
		FString ResolutionString = FString::FromInt(Resolutions.Last().X) + "x" + FString::FromInt(Resolutions.Last().Y);
		ResolutionComboBox->SetSelectedOption(ResolutionString);
	}
	else
	{
		// Fallback to 1080p
		GEngine->GameUserSettings->SetScreenResolution({1920, 1080});
		FString ResolutionString = FString::FromInt(1920) + "x" + FString::FromInt(1080);
		ResolutionComboBox->SetSelectedOption(ResolutionString);
	}
	
	// Set Fullscreen
	GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	WindowTypeComboBox->SetSelectedOption(LexToString(GEngine->GameUserSettings->GetFullscreenMode()));

	// Set Dynamic Resolution on
	GEngine->GameUserSettings->SetDynamicResolutionEnabled(true);
	DynamicResolutionComboBox->SetSelectedOption("Enabled");

	// Set VSync Off
	GEngine->GameUserSettings->SetVSyncEnabled(false);
	VsyncComboBox->SetSelectedOption("Disabled");

	// Set Refresh rate to monitor refresh rate
	TArray<uint32> RefreshRates;
	GetListOfUniqueRefreshRates(RefreshRates);
	GEngine->GameUserSettings->SetFrameRateLimit(RefreshRates.Last());
	RefreshRateComboBox->SetSelectedOption(FString::FromInt(RefreshRates.Last()));

	// Set Audio Volume to 50%
	MasterSoundClass->Properties.Volume = 0.5f;
	MasterAudioTextBlock->SetText(FText::FromString(FString::FromInt(50) + "%"));
	MasterAudioSlider->SetValue(0.5f);

	// Save Settings
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

void UOptionsMenuWidget::GetListOfUniqueRefreshRates(TArray<uint32>& RefreshRates)
{
	FScreenResolutionArray ScreenResolutions;
	RHIGetAvailableResolutions(ScreenResolutions, false);
	for (FScreenResolutionRHI ScreenResolution : ScreenResolutions)
	{
		RefreshRates.AddUnique(ScreenResolution.RefreshRate);
	}

	RefreshRates.Sort();
}
