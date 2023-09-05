#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "explode.h"

class CFuncExploder : public CBaseEntity
{
public:
    void Spawn() override;
    bool KeyValue(KeyValueData* pkvd) override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;

    bool Save(CSave& save) override;
    bool Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];
private:
    string_t target = 0;
};

LINK_ENTITY_TO_CLASS(func_exploder, CFuncExploder);

TYPEDESCRIPTION CFuncExploder::m_SaveData[] =
{
    DEFINE_FIELD( CFuncExploder, target, FIELD_STRING )
};

IMPLEMENT_SAVERESTORE(CFuncExploder, CBaseEntity);

void CFuncExploder::Spawn()
{
    
}

bool CFuncExploder::KeyValue(KeyValueData* pkvd)
{
    ALERT(at_console, "KEYVALUE WAS CALLED!!\n");
    if (FStrEq(pkvd->szKeyName, "target_explode"))
    {
        target = ALLOC_STRING(pkvd->szValue);
        return true;
    }
    return CBaseEntity::KeyValue(pkvd);
}

void CFuncExploder::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
    /*
     * NOTE: you can register all the entities in advance in an array and save them too
     *       eg. in buttons.cpp for CMultiSource 
     * TODO: do that instead of the stuff below!
    */ 
    CBaseEntity* pEntity = nullptr;
    while (pEntity = UTIL_FindEntityByTargetname(pEntity, STRING(target)))
    {
        Vector position = pEntity->Center();
        Vector angles = pEntity->pev->angles;
        UTIL_Remove(pEntity);
        ExplosionCreate(position, angles, edict(), 200, true);
    }
}