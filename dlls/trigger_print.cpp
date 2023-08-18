#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CTriggerPrint : public CBaseEntity
{
public:
    void Spawn() override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
    bool KeyValue(KeyValueData* pkvd) override;

    bool Save(CSave& save) override;
    bool Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];
private:
    ALERT_TYPE printMode = at_console;
};

TYPEDESCRIPTION CTriggerPrint::m_SaveData[] =
{
    DEFINE_FIELD( CTriggerPrint, printMode, FIELD_INTEGER )
};

IMPLEMENT_SAVERESTORE( CTriggerPrint, CBaseEntity );
LINK_ENTITY_TO_CLASS( trigger_print, CTriggerPrint );

void CTriggerPrint::Spawn()
{
    // do nothing at all here
}

void CTriggerPrint::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
    ALERT( printMode, "%s\n", STRING( pev->message ));
}

bool CTriggerPrint::KeyValue(KeyValueData* pkvd)
{
    if (FStrEq(pkvd->szKeyName, "print_mode"))
    {
        int value = atoi(pkvd->szValue);
        if (value >= 0 && value <= 5)
        {
            printMode = static_cast<ALERT_TYPE>(value);
            return true;
        }
        return false;
    }
    return CBaseEntity::KeyValue(pkvd);
}