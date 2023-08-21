#include "extdll.h"
#include "util.h"
#include "cbase.h"

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
    string_t target;
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
    if (FStrEq(pkvd->szKeyName, "target"))
    {
        target = ALLOC_STRING(pkvd->szValue);
        return true;
    }
    return CBaseEntity::KeyValue(pkvd);
}

void CFuncExploder::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{

}