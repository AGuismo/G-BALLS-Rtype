#include "Bonus.h"
#include "Player.h"

using namespace game;

////////////
//        //
// ABonus //
//        //
////////////

ABonus::ABonus(game::Dir dir, game::Pos pos, game::ID id, game::TypeBuff type) :
Entity(requestCode::game::server::BONUS, std::vector<game::Pos>(1, pos), 1, dir, id), _typeb(type)
{
#if defined(DEBUG)
  std::cout << "A bonus has been discovered" << std::endl;
#endif
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
ABonus(dir, pos, id, requestCode::game::server::VITALITY_BONUS)
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
ABonus(dir, pos, id, requestCode::game::server::POWER_BONUS)
{}

Pow::~Pow()
{}

void Pow::applyBuff(Player *p)
{
	p->pow(p->pow() + 1);
}
