#pragma once
#include "Object.h"
#include "Delegate.h"
namespace Matrix
{

    typedef VSDelegateEvent<void(void)> TriggerAnimEventType;

    class MStream;
    class VSController;

    class MATRIX_FUNCTION_API VSTimeEvent : public MObject
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY
    public:
        virtual ~VSTimeEvent() = 0;
        inline VSController *GetObject() const;

        VSTimeEvent();
        VSTimeEvent(VSController *pController);
        virtual void Trigger();

    public:
        bool m_bEnable;
        VSREAL m_fTriggerPercent;
        TriggerAnimEventType m_TriggerAnimEvent;

    protected:
        VSController *m_pController;
    };
    DECLARE_Ptr(VSTimeEvent);
    VSTYPE_MARCO(VSTimeEvent);

}
