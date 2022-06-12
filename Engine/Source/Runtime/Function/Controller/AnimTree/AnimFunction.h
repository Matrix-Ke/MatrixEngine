#pragma once

#include "Controller.h"
#include "AnimTree.h"
#include "AnimBaseFunction.h"
#include "AnimAtom.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSAnimFunction : public VSAnimBaseFunction
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY
    public:
        virtual ~VSAnimFunction() = 0;
        //必须判断是否是SkeletonMeshNode,必须有skelecton
        VSAnimFunction(const VSUsedName &ShowName, VSAnimTree *pAnimTree);
        virtual bool Update(double dAppTime);
        virtual bool IsSupportSimpleInstance();

    protected:
        VSAnimFunction();

    public:
        Container::MArray<VSAnimAtom> m_BoneOutput;
        VSAnimAtom m_RootAtom;

    public:
        virtual bool SetObject(MObject *pObject);
    };
    DECLARE_Ptr(VSAnimFunction);
    VSTYPE_MARCO(VSAnimFunction);

}
