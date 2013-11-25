#ifndef ENUMOBJECT
# define	ENUMOBJECT
# include	<string>

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
	SouthWest,
	West,
	NorthWest,
	Unset
};


#endif // !ENUMOBJECT
