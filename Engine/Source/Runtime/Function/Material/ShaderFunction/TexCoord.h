// #pragma once
// #include "Material/ShaderFunction/ShaderFunction.h"
// namespace Matrix
// {
//     class MStream;
//     class MATRIX_FUNCTION_API VSTexCoord : public VSShaderFunction
//     {
//         // RTTI
//         DECLARE_RTTI;
//         // PRIORITY
//         DECLARE_INITIAL
//     public:
//         VSTexCoord(const VSUsedName &ShowName, VSMaterial *pMaterial);
//         virtual ~VSTexCoord();
//         virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
//         virtual void ResetInShaderName(MaterialShaderPara &MSPara);

//     protected:
//         VSTexCoord();
//         unsigned int m_uiTexCoordIndex;

//     public:
//         enum // TexCoord Index
//         {
//             TI_1,
//             TI_2,
//             TI_MAX
//         };
//         inline void SetTexCoordIndex(unsigned int uiIndex)
//         {
//             if (uiIndex >= TI_MAX)
//             {
//                 return;
//             }
//             m_uiTexCoordIndex = uiIndex;
//         }
//     };
//     DECLARE_Ptr(VSTexCoord);
//     VSTYPE_MARCO(VSTexCoord);
// }
