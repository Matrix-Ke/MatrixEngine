// #pragma once
// #include "Pass/Pass.h"

// namespace Matrix
// {
//     class VSMaterialInstance;
//     class MATRIX_FUNCTION_API VSMaterialPass : public VSPass
//     {
//         // RTTI
//         DECLARE_RTTI;
//         DECLARE_INITIAL

//     public:
//         VSMaterialPass();
//         virtual ~VSMaterialPass();

//     public:
//         inline void AddLight(VSLight *pLight)
//         {
//             if (pLight)
//             {
//                 for (unsigned int i = 0; i < m_Light.GetNum(); i++)
//                 {
//                     if (m_Light[i] == pLight)
//                     {
//                         return;
//                     }
//                 }
//                 m_Light.AddElement(pLight);
//             }
//         }

//         virtual unsigned int GetPassType()
//         {
//             return PT_MATERIAL;
//         }

//     protected:
//         Container::MArray<VSLight *> m_Light;
//         VSRenderState m_RenderSceondPassUsed;

//     public:
//     public:
//         virtual bool Draw(VSRenderer *pRenderer);
//     };
//     DECLARE_Ptr(VSMaterialPass);
//     VSTYPE_MARCO(VSMaterialPass);
// }
