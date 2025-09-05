// Louis Hobbs | 2024-2025


#include "OptionsMenuWidget.h"

#include "CustomButton.h"
#include "CustomComboBoxString.h"
#include "CustomSlider.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RHI.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Sound/SoundClass.h"

void UOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GenerateWindowTypeOptions();
	WindowTypeComboBox->OnSelectionChanged.AddDynamic(this, &UOptionsMenuWidget::OnWindowTypeSelectionChanged);
	WindowTypeComboBox->OnFocused.AddDynamic(this, &UOptionsMenuWidget::OnWindowTypeFocused);

	GenerateResolutionOptions();
	ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &UOptionsMenuWidget::OnResolutionSelectionChanged);
	ResolutionComboBox->OnFocused.AddDynamic(this, &UOptionsMenuWidget::OnResolutionFocused);

	GenerateDynamicResolutionOptions();
	DynamicResolutionComboBox->OnSelectionChanged.AddDynamic(
		this, &UOptionsMenuWidget::OnDynamicResolutionSelectionChanged);
	DynamicResolutionComboBox->OnFocused.AddDynamic(this, &UOptionsMenuWidget::OnDynamicResolutionFocused);

	GenerateVsyncOptions();
	VsyncComboBox->OnSelectionChanged.AddDynamic(this, &UOptionsMenuWidget::OnVsyncSelectionChanged);
	VsyncComboBox->OnFocused.AddDynamic(this, &UOptionsMenuWidget::OnVsyncFocused);

	GenerateRefreshRateOptions();
	RefreshRateComboBox->OnSelectionChanged.AddDynamic(this, &UOptionsMenuWidget::OnRefreshRateSelectionChanged);
	RefreshRateComboBox->OnFocused.AddDynamic(this, &UOptionsMenuWidget::OnRefreshRateFocused);

	GenerateAudioLevelOptions();
	MasterAudioSlider->OnValueChanged.AddDynamic(this, &UOptionsMenuWidget::OnAudioLeverValueChanged);
	MasterAudioSlider->OnFocused.AddDynamic(this, &UOptionsMenuWidget::OnAudioFocused);

	if (ResetToDefaultsButton)
	{
		ResetToDefaultsButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenuWidget::ResetToDefaultsOnClicked);
		ResetToDefaultsButton->OnFocused.AddDynamic(this, &UOptionsMenuWidget::OnResetToDefaultsFocused);
	}

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenuWidget::ReturnButtonOnClicked);
		ReturnButton->OnFocused.AddDynamic(this, &UOptionsMenuWidget::OnReturnButtonFocused);
	}

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, WindowTypeComboBox,
		                                               EMouseLockMode::LockAlways);
		PlayerController->bShowMouseCursor = true;
	}

	WindowTypeComboBox->SetKeyboardFocus();
}

FReply UOptionsMenuWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (CurrentFocus)
	{
		CurrentFocus->SetKeyboardFocus();
	}

	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UOptionsMenuWidget::GenerateWindowTypeOptions()
{
	WindowTypeComboBox->ComboBox->ClearOptions();
	WindowTypeComboBox->ComboBox->AddOption(LexToString(EWindowMode::Fullscreen));
	WindowTypeComboBox->ComboBox->AddOption(LexToString(EWindowMode::WindowedFullscreen));
	WindowTypeComboBox->ComboBox->AddOption(LexToString(EWindowMode::Windowed));
	WindowTypeComboBox->ComboBox->SetSelectedOption(LexToString(GEngine->GameUserSettings->GetFullscreenMode()));
}

void UOptionsMenuWidget::GenerateResolutionOptions()
{
	ResolutionComboBox->ComboBox->ClearOptions();

	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);
	for (FIntPoint Resolution : Resolutions)
	{
		ResolutionComboBox->ComboBox->AddOption(FString::FromInt(Resolution.X) + "x" + FString::FromInt(Resolution.Y));
	}

	FVector2D Resolution = FVector2D::ZeroVector;
	GEngine->GameViewport->GetViewportSize(Resolution);
	FString ResolutionString = FString::FromInt(Resolution.X) + "x" + FString::FromInt(Resolution.Y);
	if (ResolutionComboBox->ComboBox->FindOptionIndex(ResolutionString) == -1)
	{
		ResolutionComboBox->ComboBox->AddOption(ResolutionString);
	}

	ResolutionComboBox->ComboBox->SetSelectedOption(ResolutionString);
}

void UOptionsMenuWidget::GenerateDynamicResolutionOptions()
{
	DynamicResolutionComboBox->ComboBox->ClearOptions();
	DynamicResolutionComboBox->ComboBox->AddOption("Enabled");
	DynamicResolutionComboBox->ComboBox->AddOption("Disabled");

	if (GEngine->GameUserSettings->IsDynamicResolutionEnabled())
	{
		DynamicResolutionComboBox->ComboBox->SetSelectedOption("Enabled");
	}
	else
	{
		DynamicResolutionComboBox->ComboBox->SetSelectedOption("Disabled");
	}
}

void UOptionsMenuWidget::GenerateVsyncOptions()
{
	VsyncComboBox->ComboBox->ClearOptions();
	VsyncComboBox->ComboBox->AddOption("Enabled");
	VsyncComboBox->ComboBox->AddOption("Disabled");

	if (GEngine->GameUserSettings->IsVSyncEnabled())
	{
		VsyncComboBox->ComboBox->SetSelectedOption("Enabled");
	}
	else
	{
		VsyncComboBox->ComboBox->SetSelectedOption("Disabled");
	}
}

void UOptionsMenuWidget::GenerateRefreshRateOptions()
{
	RefreshRateComboBox->ComboBox->ClearOptions();

	TArray<uint32> RefreshRates;

	GetListOfUniqueRefreshRates(RefreshRates);

	for (uint32 RefreshRate : RefreshRates)
	{
		RefreshRateComboBox->ComboBox->AddOption(FString::FromInt(RefreshRate));
	}

	RefreshRateComboBox->ComboBox->AddOption("Unlimited");

	float FrameRateLimit = GEngine->GameUserSettings->GetFrameRateLimit();

	if (FrameRateLimit > 0.0f)
	{
		RefreshRateComboBox->ComboBox->SetSelectedOption(FString::FromInt(FrameRateLimit));
	}
	else
	{
		RefreshRateComboBox->ComboBox->SetSelectedOption("Unlimited");
	}
}

void UOptionsMenuWidget::GenerateAudioLevelOptions()
{
	if (MasterSoundClass)
	{
		float CurrentVolume = FMath::Clamp(MasterSoundClass->Properties.Volume, 0.0f, 1.0f);

		MasterAudioSlider->SliderBody->SetValue(CurrentVolume);

		int AudioLevel = CurrentVolume * 100.0f;
		MasterAudioTextBlock->SetText(FText::FromString(FString::FromInt(AudioLevel) + "%"));
	}
}

void UOptionsMenuWidget::OnResolutionFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(ResolutionComboBox);
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

void UOptionsMenuWidget::OnWindowTypeFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(WindowTypeComboBox);
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
	if (ResolutionComboBox->ComboBox->FindOptionIndex(ResolutionString) == -1)
	{
		ResolutionComboBox->ComboBox->AddOption(ResolutionString);
	}

	ResolutionComboBox->ComboBox->SetSelectedOption(ResolutionString);
}

void UOptionsMenuWidget::OnDynamicResolutionFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(DynamicResolutionComboBox);
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

void UOptionsMenuWidget::OnVsyncFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(VsyncComboBox);
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

void UOptionsMenuWidget::OnRefreshRateFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(RefreshRateComboBox);
}

void UOptionsMenuWidget::OnRefreshRateSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	GEngine->GameUserSettings->SetFrameRateLimit(FCString::Atoi(*SelectedItem));
	GEngine->GameUserSettings->ApplySettings(false);
}

void UOptionsMenuWidget::OnAudioFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(MasterAudioSlider);
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

void UOptionsMenuWidget::OnResetToDefaultsFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(ResetToDefaultsButton);
}

void UOptionsMenuWidget::ResetToDefaultsOnClicked()
{
	// Set Resolution to Monitor Res
	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);

	if (Resolutions.Num() > 0)
	{
		GEngine->GameUserSettings->SetScreenResolution(Resolutions.Last());
		FString ResolutionString = FString::FromInt(Resolutions.Last().X) + "x" +
			FString::FromInt(Resolutions.Last().Y);
		ResolutionComboBox->ComboBox->SetSelectedOption(ResolutionString);
	}
	else
	{
		// Fallback to 1080p
		GEngine->GameUserSettings->SetScreenResolution({1920, 1080});
		FString ResolutionString = FString::FromInt(1920) + "x" + FString::FromInt(1080);
		ResolutionComboBox->ComboBox->SetSelectedOption(ResolutionString);
	}

	// Set Fullscreen
	GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	WindowTypeComboBox->ComboBox->SetSelectedOption(LexToString(GEngine->GameUserSettings->GetFullscreenMode()));

	// Set Dynamic Resolution on
	GEngine->GameUserSettings->SetDynamicResolutionEnabled(true);
	DynamicResolutionComboBox->ComboBox->SetSelectedOption("Enabled");

	// Set VSync Off
	GEngine->GameUserSettings->SetVSyncEnabled(false);
	VsyncComboBox->ComboBox->SetSelectedOption("Disabled");

	// Set Refresh rate to monitor refresh rate
	TArray<uint32> RefreshRates;
	GetListOfUniqueRefreshRates(RefreshRates);
	GEngine->GameUserSettings->SetFrameRateLimit(RefreshRates.Last());
	RefreshRateComboBox->ComboBox->SetSelectedOption(FString::FromInt(RefreshRates.Last()));

	// Set Audio Volume to 50%
	MasterSoundClass->Properties.Volume = 0.5f;
	MasterAudioTextBlock->SetText(FText::FromString(FString::FromInt(50) + "%"));
	MasterAudioSlider->SliderBody->SetValue(0.5f);

	// Save Settings
	GEngine->GameUserSettings->ApplySettings(false);
}

void UOptionsMenuWidget::OnReturnButtonFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(ReturnButton);
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
