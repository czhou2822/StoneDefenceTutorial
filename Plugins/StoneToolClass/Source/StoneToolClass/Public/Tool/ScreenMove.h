#pragma once

#include "CoreMinimal.h"

enum EScreenMoveState
{
	Screen_None,

	Screen_Up,
	Screen_Down,
	Screen_Right,
	Screen_Left,
	
	Screen_RightAndUp,
	Screen_RightAndDown,
	Screen_LeftAndUp,
	Screen_LeftAndDown,
	
	Screen_Max

};

class APlayerController;

struct STONETOOLCLASS_API FScreenMoveUnits
{

	/**
	@param PlayerController 
	@param ScreenMoveSpeed
	@return                     was it moved successfully?  
	*/
	bool ListenScreenMove(APlayerController* PlayerController, const float &ScreenMoveSpeed);

	/*
	get current movement state
	@param PlayerController      current player controller
	@return						 return the current movement state
	*/
	EScreenMoveState CursorMove(const APlayerController* PlayerController);

	/*
	have the pawn to move with the mouse position
	@param PlayerController     current player controller
	@param ScreenMoveState      current screen state
	@param ScreenMoveSpeed      Speed of the movement of the screen
	*/
	bool MoveDirection(APlayerController* PlayerController, EScreenMoveState ScreenMoveState, const float &ScreenMoveSpeed);

};