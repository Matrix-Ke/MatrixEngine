#pragma once
#include "Math.h"
#include "Vector3.h"
#include "Controller.h"
namespace Matrix
{
    class VSStream;
    class MATRIX_FUNCTION_API VSFreeCameraController : public VSController
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSFreeCameraController();
        virtual ~VSFreeCameraController();
        VSREAL m_RotXDelta;
        VSREAL m_RotYDelta;
        VSREAL m_RotZDelta;
        VSREAL m_MoveDelta;
        VSVector3 m_MoveDirection;
        virtual bool UpdateEx(double dAppTime);
    };
    DECLARE_Ptr(VSFreeCameraController);
    VSTYPE_MARCO(VSFreeCameraController);

}
