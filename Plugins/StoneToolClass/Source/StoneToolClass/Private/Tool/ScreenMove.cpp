#include "Tool/ScreenMove.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

bool FScreenMoveUnits::ListenScreenMove(APlayerController* PlayerController, const float &ScreenMoveSpeed)
{
	return MoveDirection(PlayerController, CursorMove(PlayerController), ScreenMoveSpeed);
}

EScreenMoveState FScreenMoveUnits::CursorMove(const APlayerController* PlayerController)
{
	if (PlayerController)
	{
		//screen size
		int32 SizeX = INDEX_NONE;
		int32 SizeY = INDEX_NONE;

		//mouse position
		float MousePositionX = 0.f;
		float MousePositionY = 0.f;

		PlayerController->GetViewportSize(SizeX, SizeY);
		PlayerController->GetMousePosition(MousePositionX, MousePositionY);

//		UE_LOG(LogTemp, Warning, TEXT("X: %s, Y: %s"), *FString::SanitizeFloat(MousePositionX), *FString::SanitizeFloat(MousePositionY));

		if (MousePositionX >= 0 && MousePositionX <= SizeX &&
			MousePositionY >= 0 && MousePositionY <= SizeY)
		{
			if (FMath::IsNearlyEqual(MousePositionX, 0.0f, 5.f) && FMath::IsNearlyEqual(MousePositionY, 0.0f, 5.f))
			{
				return EScreenMoveState::Screen_LeftAndUp;
			}
			else if (FMath::IsNearlyEqual(MousePositionX, SizeX, 5.f) && FMath::IsNearlyEqual(MousePositionY, SizeY, 5.f))
			{
				return EScreenMoveState::Screen_RightAndDown;
			}
			else if (FMath::IsNearlyEqual(MousePositionX, SizeX, 5.f) && FMath::IsNearlyEqual(MousePositionY, 0.f, 5.f))
			{
				return EScreenMoveState::Screen_RightAndUp;
			}
			else if (FMath::IsNearlyEqual(MousePositionX, 0.f, 5.f) && FMath::IsNearlyEqual(MousePositionY, SizeY, 5.f))
			{
				return EScreenMoveState::Screen_LeftAndDown;
			}


			else if (FMath::IsNearlyEqual(MousePositionX, 0.0f, 5.f))
			{
				return EScreenMoveState::Screen_Left;
			}
			else if (FMath::IsNearlyEqual(MousePositionY, 0.0f, 5.f))
			{
				return EScreenMoveState::Screen_Up;
			}
			else if (FMath::IsNearlyEqual(MousePositionY, SizeY, 5.f))
			{
				return EScreenMoveState::Screen_Down;
			}
			else if (FMath::IsNearlyEqual(MousePositionX, SizeX, 5.f))
			{
				return EScreenMoveState::Screen_Right;
			}
		}
		
	}

	return EScreenMoveState::Screen_None;

}

bool FScreenMoveUnits::MoveDirection(APlayerController* PlayerController, EScreenMoveState ScreenMoveState, const float &ScreenMoveSpeed)
{
	FVector OffsetValue = FVector::ZeroVector;

	if (PlayerController &&
		PlayerController->GetPawn())
	{
		switch (ScreenMoveState)
		{
		case Screen_Up:
			OffsetValue = FVector(ScreenMoveSpeed, 0.0f, 0.0f);
			break;
		case Screen_Down:
			OffsetValue = FVector(-ScreenMoveSpeed, 0.0f, 0.0f);
			break;
		case Screen_Right:
			OffsetValue = FVector(0.f, ScreenMoveSpeed, 0.0f);
			break;
		case Screen_Left:
			OffsetValue = FVector(0.f, -ScreenMoveSpeed, 0.0f);
			break;
		case Screen_RightAndUp:
			OffsetValue = FVector(ScreenMoveSpeed, ScreenMoveSpeed, 0.0f);
			break;
		case Screen_RightAndDown:
			OffsetValue = FVector(-ScreenMoveSpeed, ScreenMoveSpeed, 0.0f);
			break;
		case Screen_LeftAndUp:
			OffsetValue = FVector(ScreenMoveSpeed, -ScreenMoveSpeed, 0.0f);
			break;
		case Screen_LeftAndDown:
			OffsetValue = FVector(-ScreenMoveSpeed, -ScreenMoveSpeed, 0.0f);
			break;
		}

		PlayerController->GetPawn()->AddActorWorldOffset(OffsetValue);
	}


	return OffsetValue != FVector::ZeroVector;
}
