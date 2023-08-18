#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CFuncFader : public CBaseEntity
{
public:
    void Spawn() override;
    void EXPORT FadeOutThink();
    void EXPORT FadeInThink();
};

LINK_ENTITY_TO_CLASS( func_fader, CFuncFader );

void CFuncFader::Spawn()
{
    SET_MODEL(edict(), STRING(pev->model));
    pev->solid = SOLID_BSP;
    pev->movetype = MOVETYPE_PUSHSTEP;

    // mapper sets rendermode
    pev->renderamt = 128; // 50% transparency

    SetThink(&CFuncFader::FadeOutThink);
    pev->nextthink = 1.5f;
}

void CFuncFader::FadeOutThink()
{
    pev->renderamt -= 1.0f;
    if (pev->renderamt <= 0.0f)
    {
        pev->renderamt = 0.0f;
        SetThink(&CFuncFader::FadeInThink);
    }
    pev->nextthink = gpGlobals->time + 0.02f;
}

void CFuncFader::FadeInThink()
{
    pev->renderamt += 1.0f;
    if (pev->renderamt >= 255.0f)
    {
        pev->renderamt = 255.0f;
        SetThink(&CFuncFader::FadeOutThink);
    }
    pev->nextthink = gpGlobals->time + 0.02f;
}