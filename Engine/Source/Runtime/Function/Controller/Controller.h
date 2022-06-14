#pragma once
#include "Core/Object.h"
#include "Controller/AnimTree/TimeEvent.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSStartAnimEvent : public VSTimeEvent
    {
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSStartAnimEvent();
        ~VSStartAnimEvent();
        VSStartAnimEvent(VSController *pController);
    };
    DECLARE_Ptr(VSStartAnimEvent);
    VSTYPE_MARCO(VSStartAnimEvent);

    class MATRIX_FUNCTION_API VSEndAnimEvent : public VSTimeEvent
    {
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSEndAnimEvent();
        ~VSEndAnimEvent();
        VSEndAnimEvent(VSController *pController);
    };
    DECLARE_Ptr(VSEndAnimEvent);
    VSTYPE_MARCO(VSEndAnimEvent);

    class MATRIX_FUNCTION_API VSController : public MObject
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY
    public:
        virtual ~VSController() = 0;
        inline MObject *GetObject() const;
        virtual bool Update(double dAppTime);
        virtual bool UpdateEx(double aAppTime);

        enum // Repeat Type
        {
            RT_NONE,
            RT_CLAMP,
            RT_WRAP,
            RT_CYCLE,
            RT_REVEERSE_CLAMP,
            RT_REVEERSE_WRAP,
            RT_REVEERSE_CYCLE,
            RT_MAX
        };
        unsigned int m_uiRepeatType;

        double m_dMinTime;
        double m_dMaxTime;
        double m_dPhase;
        double m_dFrequency;

        static double GetTime(double fTime, double fMin, double fMax, unsigned int uiRepeatType);

    public:
        friend class MObject;
        VSController();
        virtual bool SetObject(MObject *pObject);
        double GetControlTime(double dAppTime);

        MObject *m_pObject;
        double m_dNowAnimTime;
        double m_dLastAppTime;
        double m_dLastAnimTime;
        double m_dIntervalTime;
        double m_dIntervalAnimTime;
        double m_dTimeSum;
        double m_dStartSystemTime;
        bool m_bStart;

        inline void ClearTime();
        void AddTimeEvent(VSTimeEvent *pTimeEvent);
        void DeleteTimeEvent(VSTimeEvent *pTimeEvent);
        void SetEnable(bool Enable);

        void AddTriggerStart(TriggerAnimEventType::Handler handler);

        void AddTriggerStop(TriggerAnimEventType::Handler handler);

        void AddTriggerEnd(TriggerAnimEventType::Handler handler);

        void AddTriggerBeginStart(TriggerAnimEventType::Handler handler);

    public:
        bool m_bIsVisibleUpdate;

    protected:
        Container::MArray<VSTimeEventPtr> m_TimeEventArray;
        void TimeEvent(double dAppTime);
        VSREAL m_fInnerTimeScale;
        bool m_bEnable;
        TriggerAnimEventType m_TriggerBeginStart;
        TriggerAnimEventType m_TriggerStop;
    };
#include "VSController.inl"
    DECLARE_Ptr(VSController);
    VSTYPE_MARCO(VSController);

}
