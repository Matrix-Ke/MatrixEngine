#pragma once
#include "Math.h"
#include "Vector3.h"
#include "Controller.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VS1stCameraController : public VSController
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VS1stCameraController();
        virtual ~VS1stCameraController();
        VSREAL m_RotXDelta;
        VSREAL m_RotYDelta;
        VSREAL m_MoveXDelta;
        VSREAL m_MoveYDelta;
        VSREAL m_MoveZDelta;
        virtual bool UpdateEx(double dAppTime);
    };
    DECLARE_Ptr(VS1stCameraController);
    VSTYPE_MARCO(VS1stCameraController);

}
