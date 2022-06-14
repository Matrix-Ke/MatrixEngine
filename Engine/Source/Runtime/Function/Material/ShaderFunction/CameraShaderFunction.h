// #pragma once
// #include "Material/ShaderFunction/ShaderFunction.h"
// namespace Matrix
// {
//     class MStream;

//     class MATRIX_FUNCTION_API VSViewWorldDir : public VSShaderFunction
//     {
//         // RTTI
//         DECLARE_RTTI;
//         // PRIORITY
//         DECLARE_INITIAL
//     public:
//         VSViewWorldDir(const VSUsedName &ShowName, VSMaterial *pMaterial);
//         virtual ~VSViewWorldDir();
//         virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
//         virtual void ResetInShaderName(MaterialShaderPara &MSPara);

//     protected:
//         VSViewWorldDir();
//     };
//     DECLARE_Ptr(VSViewWorldDir);
//     VSTYPE_MARCO(VSViewWorldDir);

//     class MATRIX_FUNCTION_API VSCameraWorldPos : public VSShaderFunction
//     {
//         // RTTI
//         DECLARE_RTTI;
//         // PRIORITY
//         DECLARE_INITIAL
//     public:
//         VSCameraWorldPos(const VSUsedName &ShowName, VSMaterial *pMaterial);
//         virtual ~VSCameraWorldPos();
//         virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
//         virtual void ResetInShaderName(MaterialShaderPara &MSPara);

//     protected:
//         VSCameraWorldPos();
//     };
//     DECLARE_Ptr(VSCameraWorldPos);
//     VSTYPE_MARCO(VSCameraWorldPos);

// }
