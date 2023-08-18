#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CEnvFollower : public CBaseEntity
{
public:
    void Spawn() override;
    void Think() override;
};

LINK_ENTITY_TO_CLASS( env_follower, CEnvFollower );

void CEnvFollower::Spawn()
{
    PRECACHE_MODEL("sprites/glow01.spr");
    SET_MODEL(edict(), "sprites/glow01.spr");

    pev->rendermode = kRenderTransAdd;
    pev->renderamt = 255;

    pev->movetype = MOVETYPE_FLY;
    pev->solid = SOLID_NOT;

    pev->effects = EF_DIMLIGHT;

    pev->nextthink = 1.5f;
}

void CEnvFollower::Think()
{
    CBaseEntity* player = CBaseEntity::Instance(g_engfuncs.pfnPEntityOfEntIndex(1));

    pev->velocity = player->pev->origin - pev->origin;

    pev->nextthink = gpGlobals->time + 0.02f;
}
