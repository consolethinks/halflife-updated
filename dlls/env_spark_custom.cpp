#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CEnvSparkCustom : public CBaseEntity
{
public:
    void Think() override;
    void Use( CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value ) override;
private:
    bool canSpark = false;
};

LINK_ENTITY_TO_CLASS( env_spark_custom, CEnvSparkCustom );

void CEnvSparkCustom::Think()
{
    if ( canSpark )
    {
        UTIL_Sparks( pev->origin ); // Sparks will be emitted at the entity's position
    }

    // wait x seconds before "thinking" again
    pev->nextthink = gpGlobals->time + pev->speed;
}

void CEnvSparkCustom::Use( CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value )
{
    canSpark = !canSpark;
    // Think immediately
    pev->nextthink = gpGlobals->time;
}