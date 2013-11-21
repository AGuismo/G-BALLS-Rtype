#ifndef ENUMOBJECT
# define	ENUMOBJECT
# include	<string>

enum ObjType
{
	PLAYER1 = 0,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	SBYDOS1,
	LAYER1,
	LAYER2,
	LAYER3,
	LAYER4,
	LAYER5,
	LAYER6,
	NORMAL_BANG,
	BIG_BANG
};

enum Action
{
	Left = 0,
	Right,
	Up,
	Down,
	Nothing,
	Fire,
	Destroy
};

enum LookDirection
{
	North = 0,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthOuest,
	Ouest,
	NorthOuest,
	Unset
};


#endif // !ENUMOBJECT
