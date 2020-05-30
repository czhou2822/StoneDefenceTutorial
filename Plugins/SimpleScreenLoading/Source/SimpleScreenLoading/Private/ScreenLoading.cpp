#include "SimpleScreenLoading/Public/ScreenLoading.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include  "Widgets/Notifications/SProgressBar.h"


void SScreenLoading::Construct(const FArguments& InArgs, const FString & InMapName)
{
	MapName = InMapName;
	ChildSlot
		[
			SNew(SProgressBar)
			.Percent(this, &SScreenLoading::GetProgress)
		];
}

TOptional<float> SScreenLoading::GetProgress() const
{
	// -1 ----- -1
	float LoadPrecentage = GetAsyncLoadPercentage(*MapName);

	return LoadPrecentage * 0.01f;
}