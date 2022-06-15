#pragma once
#include "World/Actor/ReflectCameraActor.h"
#include "World/Actor/CameraActor.h"
#include "PostEffect/PostEffectSet.h"
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
        void SetPlane(Primitive::Plane3 Plane);

    protected:
        VSCameraActor *m_pTargetCameraActor;
        Primitive::Plane3 m_Plane;
    };
    DECLARE_Ptr(VSReflectCameraActor);
    VSTYPE_MARCO(VSReflectCameraActor);
}
