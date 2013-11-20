#pragma once

#include "Entity.h"

class Game;

namespace game
{
  class Player;

  class ABonus : public Entity
  {
  public:
    ABonus(game::Dir dir, game::Pos pos, game::ID id, game::TypeBuff type);
    ~ABonus();

    virtual void applyBuff(Player *p) = 0;
	TypeBuff typeb() { return _typeb; };
  protected:
    game::TypeBuff _typeb;

    friend class ::Game;
    friend class ::Referee;
  };

  static const TypeBuff EXTRALIFE = 1;
  static const TypeBuff POW = 2;

  class ExtraLife : public ABonus
  {
  public:
    ExtraLife(game::Dir dir, game::Pos pos, game::ID id);
    ~ExtraLife();

    void applyBuff(Player *p);
  };

  class Pow : public ABonus
  {
  public:
    Pow(game::Dir dir, game::Pos pos, game::ID id);
    ~Pow();

    void applyBuff(Player *p);
  };
}
