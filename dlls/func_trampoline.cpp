#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "explode.h"

class CFuncTrampoline : public CBaseEntity
{
public:
    void Spawn() override;
    void Touch( CBaseEntity* pOther ) override;
};

LINK_ENTITY_TO_CLASS( func_trampoline, CFuncTrampoline );

void CFuncTrampoline::Spawn()
{
    pev->movetype = MOVETYPE_NONE;
    pev->solid = SOLID_TRIGGER; // this entity won't be solid, it triggers an upwards push
    SET_MODEL( edict(), STRING( pev->model) );
    PRECACHE_SOUND("vox/launch.wav");
}

void CFuncTrampoline::Touch( CBaseEntity* pOther )
{
    // entities that touch this will go up with the negative multiple of speed
    pOther->pev->velocity.z *= -1.0f*pev->speed;

    // Gravitate towards center
    Vector direction = ((pev->origin + (pev->maxs + pev->mins)*0.5f) - (pOther->pev->origin + (pOther->pev->maxs + pOther->pev->mins) * 0.5f)).Normalize();
    pOther->pev->velocity.x += direction.x*20;
    pOther->pev->velocity.y += direction.y*20;

    // make trampoline sound
    EMIT_SOUND(ENT(pev), CHAN_ITEM, "vox/launch.wav", 1.0f, ATTN_NORM);
}