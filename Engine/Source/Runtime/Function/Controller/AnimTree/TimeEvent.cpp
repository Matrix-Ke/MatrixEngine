#include "TimeEvent.h"
#include "Stream.h"
#include "GraphicInclude.h"
using namespace Matrix;
IMPLEMENT_RTTI_NoCreateFun(VSTimeEvent, MObject)
    IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(VSTimeEvent)
        IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
    BEGIN_ADD_PROPERTY(VSTimeEvent, MObject)
        REGISTER_PROPERTY(m_bEnable, Enable, VSProperty::F_SAVE_LOAD_CLONE);
REGISTER_PROPERTY(m_pController, Controller, VSProperty::F_SAVE_LOAD_CLONE);
REGISTER_PROPERTY(m_fTriggerPercent, TriggerPercent, VSProperty::F_SAVE_LOAD_CLONE);
END_ADD_PROPERTY
VSTimeEvent::VSTimeEvent()
{
    m_bEnable = true;
    m_pController = NULL;
    m_fTriggerPercent = 0.0f;
}
VSTimeEvent::~VSTimeEvent()
{
    m_pController = NULL;
}
VSTimeEvent::VSTimeEvent(VSController *pController)
{
    m_pController = pController;
}
void VSTimeEvent::Trigger()
{
    m_TriggerAnimEvent();
}