#pragma once
#include "Controller.h"
#include "AnimTree.h"
#include "PutNode.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSAnimBaseFunction : public VSController
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY
    public:
        friend class VSAnimTree;
        virtual ~VSAnimBaseFunction() = 0;
        VSAnimBaseFunction(const VSUsedName &ShowName, VSAnimTree *pAnimTree);

        virtual bool Update(double dAppTime);
        virtual void ClearFlag();

    protected:
        VSAnimBaseFunction();

    protected:
        Container::MArray<VSInputNode *> m_pInput;
        Container::MArray<VSOutputNode *> m_pOutput;
        VSAnimTree *m_pOwner;
        VSUsedName m_ShowName;

        bool m_bIsVisited;
        bool m_bNoLeafStart;

        inline void SetOwner(VSAnimTree *pOwner)
        {
            ENGINE_ASSERT(pOwner);
            m_pOwner = pOwner;
        }
        friend class VSAnimMainFunction;
        Container::MArray<ANIM_INSTANCE_DATA> m_AnimDataInstance;
        static void GetAnimDataInstance(VSAnimBaseFunction *pSource, VSAnimBaseFunction *pTarget, VSREAL fWeight);

        virtual void SetOnlyUpdateRootMotion(bool bOnlyUpdateRootMotion)
        {
            m_bOnlyUpdateRootMotion = bOnlyUpdateRootMotion;
        }

    public:
        void GetAnimInstanceData(Container::MArray<ANIM_INSTANCE_DATA> &InstanceData)
        {
            InstanceData.Clear();
            for (unsigned int i = 0; i < m_AnimDataInstance.GetNum(); i++)
            {
                if (m_AnimDataInstance[i].fAlpha > EPSILON_E3)
                {
                    InstanceData.AddElement(m_AnimDataInstance[i]);
                }
            }
        }
        virtual bool IsSupportSimpleInstance() { return false; }
        VSSkeletonMeshNode *GetSkeletonMeshNode() const;
        VSInputNode *GetInputNode(unsigned int uiNodeID) const;
        VSInputNode *GetInputNode(const Container::MString &NodeName) const;

        VSOutputNode *GetOutputNode(unsigned int uiNodeID) const;
        VSOutputNode *GetOutputNode(const Container::MString &NodeName) const;

        inline const VSUsedName &GetShowName() const
        {
            return m_ShowName;
        }
        virtual void SetPara(void *pPara){};

        virtual bool IsLeafNode();
        void GetLeafArray(Container::MArray<VSAnimBaseFunction *> &LeafNode);

        void EnableLeafStart();
        void NoLeafStart();
        bool m_bOnlyUpdateRootMotion;
        bool m_bHaveRootMotion;
    };
    DECLARE_Ptr(VSAnimBaseFunction);
    VSTYPE_MARCO(VSAnimBaseFunction);
}
