#ifndef ENUMOBJECT
# define	ENUMOBJECT


enum ObjType
{
	PLAYER1 = 0,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	SBYDOS1
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
	NorthOuest
};


#endif // !ENUMOBJECT
