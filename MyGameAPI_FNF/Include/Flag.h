#pragma once

enum EKeyState
{
	KeyState_Down,
	KeyState_Push,
	KeyState_Up,
	KeyState_Max
};

enum class ETexture_Type
{
	Atlas,
	Frame
};

enum class ECollider_Type
{
	Box,
	Sphere,
	Point
};

enum ECollision_Channel
{
	Channel_Object,
	Channel_Player,
	Channel_Monster,
	Channel_PlayerAttack,
	Channel_MonsterAttack,
	Channel_Max
};

enum class ECollision_State
{
	Ignore,
	Collision
};

enum class EButton_State
{
	Normal,
	MouseOn,
	Click,
	Disable,
	End
};

enum class EObject_Type
{
	GameObject,
	Character,
	NoteBack,
	Note,
	Effect,
	Text
};

enum class ETileOption
{
	Normal,
	Wall,
	Slow,
	End
};

enum class ETileEditMode
{
	Option,
	Image,
	End
};

enum class ENote_Type:int {
	Left = 0,
	Down,
	Up,
	Right
};

enum class ESong_Difficulty:int {
	Easy = 0,
	Normal,
	Hard,
	End
};

enum class ENote_Owner:bool {
	Player = true,
	Enemy = false
};

enum class ENote_Rate:int {
	Sick,
	Good,
	Bad,
	Shit
};

enum class EGame_Rate  {
	Great,
	Sick,
	Good,
	Meh,
	Failed
};