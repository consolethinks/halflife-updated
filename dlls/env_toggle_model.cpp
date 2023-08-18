#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CEnvToggleModel : public CBaseEntity
{
public:
    void Spawn() override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pInflictor, USE_TYPE useType, float value) override;
};

LINK_ENTITY_TO_CLASS( env_toggle_model, CEnvToggleModel );

void CEnvToggleModel::Spawn()
{
    if (!pev->model)
    {
        ALERT( at_console, "env_toggle_model has no model specified!\n");
        UTIL_Remove(this);
        return;
    }

    PRECACHE_MODEL(STRING(pev->model));
    SET_MODEL(edict(), STRING(pev->model));

    pev->movetype = MOVETYPE_NONE;
    pev->solid = SOLID_NOT; // or SOLID_BBOX
}

void CEnvToggleModel::Use(CBaseEntity* pActivator, CBaseEntity* pInflictor, USE_TYPE useType, float value)
{
    pev->effects ^= EF_NODRAW; // XOR
}
