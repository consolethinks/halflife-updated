#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CAmbientSimple : public CBaseEntity
{
public:
    void Spawn() override;
    void Precache() override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
};

LINK_ENTITY_TO_CLASS(ambient_simple, CAmbientSimple);

void CAmbientSimple::Spawn()
{
    if (!pev->targetname)
    {
        ALERT(at_warning, "ambient_simple instance is unnamed, deleting...\n");
        UTIL_Remove(this);
        return;
    }

    if (!pev->noise)
    {
        ALERT(at_warning, "ambient_simple instance has no sound file to play, deleting...\n");
        UTIL_Remove(this);
        return;
    }
    Precache();
}

void CAmbientSimple::Precache()
{
    PRECACHE_SOUND(STRING(pev->noise));
}

void CAmbientSimple::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
    EMIT_SOUND(edict(), CHAN_STATIC, STRING(pev->noise), 1.0f, ATTN_NORM);
}