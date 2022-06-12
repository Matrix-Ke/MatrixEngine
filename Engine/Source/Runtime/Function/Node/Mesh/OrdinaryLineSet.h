#pragma once
#include "LineSet.h"
#include "Curve3.h"
#include "Curve3Subdivision.h"
#include "Line3.h"
#include "Ray3.h"
#include "Segment3.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSOrdinaryLineSet : public VSLineSet
    {
    public:
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL

    public:
        VSOrdinaryLineSet(VSControlCurve3 *pControlCurve, VSCurve3Subdivision *pSubidvision);
        VSOrdinaryLineSet(const VSLine3 &Line);
        VSOrdinaryLineSet(const VSRay3 &Ray);
        VSOrdinaryLineSet(const VSSegment3 &Segment);
        virtual ~VSOrdinaryLineSet();

    protected:
        VSOrdinaryLineSet();
    };
    DECLARE_Ptr(VSOrdinaryLineSet);
    VSTYPE_MARCO(VSOrdinaryLineSet);

};
