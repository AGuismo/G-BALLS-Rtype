#include "Bonus.h"
#include "Player.h"

using namespace game;

////////////
//        //
// ABonus //
//        //
////////////

ABonus::ABonus(game::Dir dir, game::Pos pos, game::ID id, game::TypeBuff type) :
Entity(game::BONUS, std::vector<game::Pos>(pos), 1, dir, id), _typeb(type)
{
}

ABonus::~ABonus()
{

}

///////////////
//           //
// ExtraLife //
//           //
///////////////

ExtraLife::ExtraLife(game::Dir dir, game::Pos pos, game::ID id) :
ABonus(dir, pos, id, game::EXTRALIFE)
{}

ExtraLife::~ExtraLife()
{}

void ExtraLife::applyBuff(Player *p)
{
	p->extraLife(true);
}

////////////
//        //
//	Pow	  //
//        //
////////////

Pow::Pow(game::Dir dir, game::Pos pos, game::ID id) :
ABonus(dir, pos, id, game::POW)
{}

Pow::~Pow()
{}

void Pow::applyBuff(Player *p)
{
	p->pow(p->pow() + 1);
}