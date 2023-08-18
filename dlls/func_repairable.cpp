#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CFuncRepairable : public CBaseEntity
{
public:
    void Spawn() override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
    bool TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) override;
    void Think() override;

    int ObjectCaps() override { return FCAP_IMPULSE_USE; }
};

LINK_ENTITY_TO_CLASS( func_repairable, CFuncRepairable );

void CFuncRepairable::Spawn()
{
    pev->takedamage = true;
    pev->health = 100;

    pev->solid = SOLID_BSP;
    pev->movetype = MOVETYPE_PUSHSTEP; // MOVETYPE_NONE doesn't work
    SET_MODEL( edict(), STRING( pev->model ) );

    // this'll be necessary if initial health can be configured
    pev->nextthink = gpGlobals->time + 1.5f;
}

void CFuncRepairable::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
    pev->health += 5;
    if ( pev->health > 100 ) pev->health = 100;
}

bool CFuncRepairable::TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType)
{
    if (bitsDamageType & DMG_CLUB)
    {
        // max. health is 100!
        pev->health += flDamage;
        if (pev->health > 100) pev->health = 100;

        ALERT( at_console, "I AM HEALED %f\n", pev->health);

        return false;
    }

    // min. health is 0!
    flDamage > pev->health ? pev->health = 0 : pev->health -= flDamage;

    ALERT( at_console, "I AM DAMAGED %f\n", pev->health);

    return true;
}

void CFuncRepairable::Think()
{
    if (pev->health < 90)
    {
        ALERT( at_console, "THINK %f\n", pev->health);
        UTIL_Sparks( pev->origin );
    }

    pev->nextthink += gpGlobals->time + (pev->health / 100.0f) + 0.05f; // max. frequency is 20Hz!
}