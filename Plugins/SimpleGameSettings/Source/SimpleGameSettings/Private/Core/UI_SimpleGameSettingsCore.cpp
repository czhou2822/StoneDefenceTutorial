#include "SimpleGameSettings/Public/Core/UI_SimpleGameSettingsCore.h"
#include "SimpleGameSettingsMacro.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "Components/TextBlock.h"

void UUI_SimpleGameSettingsCore::UpdateAttribute(USlider* NewSlider, UTextBlock* NewBlock)
{
	float FloatNumber = NewSlider->GetValue() * 10.f;
	FString StringFloatNumberText = FString::Printf(TEXT("%.2f"), FloatNumber);

	NewBlock->SetText(FText::FromString(StringFloatNumberText));

}

void UUI_SimpleGameSettingsCore::BindChangedValue(USlider* NewSlider)
{
	NewSlider->OnValueChanged.AddDynamic(this, &UUI_SimpleGameSettingsCore::ChangedValue);
}

void UUI_SimpleGameSettingsCore::BindSelectionChanged(UComboBoxString* BoxString)
{
	BoxString->OnSelectionChanged.AddDynamic(this, &UUI_SimpleGameSettingsCore::SelectionChanged);

}

void UUI_SimpleGameSettingsCore::SetSettingsLevel(USlider* InSlider, TFunction<void(int32 InLevel)> InFunc)
{

	InFunc(InSlider->GetValue() * SCAL_ABILITY_QUALITY_LEVEL);
}

void UUI_SimpleGameSettingsCore::LoadSettingsLevel(USlider* InSlider, TFunction<float()> InFunc)
{

	InSlider->SetValue(InFunc() / (float)SCAL_ABILITY_QUALITY_LEVEL);

}

void UUI_SimpleGameSettingsCore::LoadBoxString(UComboBoxString* InBoxString, TFunction<FString()> InFunc)
{
	InBoxString->SetSelectedOption(InFunc());
}
 