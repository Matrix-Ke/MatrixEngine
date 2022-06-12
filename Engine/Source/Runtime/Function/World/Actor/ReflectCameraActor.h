#pragma once
#include "ReflectCameraActor.h"
#include "CameraActor.h"
#include "PostEffectSet.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSReflectCameraActor : public VSCameraActor
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;

    public:
        VSReflectCameraActor();
        virtual ~VSReflectCameraActor();
        DECLARE_INITIAL

        virtual void Update(double dAppTime);

        void SetTargetCameraActor(VSCameraActor *pCameraActor);
        void SetPlane(VSPlane3 Plane);

    protected:
        VSCameraActor *m_pTargetCameraActor;
        VSPlane3 m_Plane;
    };
    DECLARE_Ptr(VSReflectCameraActor);
    VSTYPE_MARCO(VSReflectCameraActor);
}
