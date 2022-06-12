#pragma once
#include "TriangleSet.h"
#include "AABB3.h"
#include "OBB3.h"
#include "Surface3.h"
#include "Surface3Subdivision.h"
#include "Polygon3.h"
#include "Sphere3.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSOrdinaryTriangleSet : public VSTriangleSet
    {
    public:
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSOrdinaryTriangleSet(const Primitive::AABB3 &AABB);
        VSOrdinaryTriangleSet(const VSOBB3 &OBB);
        VSOrdinaryTriangleSet(const VSSphere3 &Sphere);
        VSOrdinaryTriangleSet(VSSurface3 *pSurface, VSSurface3Subdivision *pSubidvision);
        VSOrdinaryTriangleSet(const VSPlane3 &Plane);
        VSOrdinaryTriangleSet(const VSTriangle3 &Triangle);
        VSOrdinaryTriangleSet(const VSRectangle3 &Rectangle);
        VSOrdinaryTriangleSet(const VSPolygon3 &Polyon);
        virtual ~VSOrdinaryTriangleSet();

    protected:
        VSOrdinaryTriangleSet();
    };
    DECLARE_Ptr(VSOrdinaryTriangleSet);
    VSTYPE_MARCO(VSOrdinaryTriangleSet);
};
