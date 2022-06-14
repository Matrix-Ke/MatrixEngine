// #pragma once
// #include "Material/ShaderFunction/ShaderFunction.h"
// #include "Render/Texture/TexAllState.h"
// namespace Matrix
// {
//     class MStream;
//     class MATRIX_FUNCTION_API VSTexSampler : public VSShaderFunction
//     {
//         // RTTI
//         DECLARE_RTTI;
//         DECLARE_INITIAL_NO_CLASS_FACTORY;

//     public:
//         virtual ~VSTexSampler() = 0;
//         virtual unsigned int GetTexType() const = 0;
//         VSTexSampler(const VSUsedName &ShowName, VSMaterial *pMaterial);
//         inline VSTexAllStateR *GetTexture() const
//         {
//             return m_pTexAllState;
//         }
//         inline void SetTexture(VSTexAllStateR *pTexture)
//         {
//             m_pTexAllState = pTexture;
//         }
//         virtual bool GetInputValueString(Container::MString &InputString, MaterialShaderPara &MSPara) const;
//         virtual bool GetDeclareString(Container::MString &OutString, unsigned int uiRegisterID, MaterialShaderPara &MSPara) const;
//         virtual void SetTexCoordLevel(unsigned int uiTexCoordLevel)
//         {
//             m_uiTexCoordLevel = uiTexCoordLevel;
//         }
//         inline unsigned int GetTexCoordLevel() const
//         {
//             return m_uiTexCoordLevel;
//         }
//         inline void SetVEDecode(unsigned char uiVEDecode)
//         {
//             m_uiVEDecode = uiVEDecode;
//         }
//         inline void SetVESRGB(unsigned char uiVESRGB)
//         {
//             m_uiVESRGB = uiVESRGB;
//         }

//         inline unsigned char GetVEDecode() const
//         {
//             return m_uiVEDecode;
//         }
//         inline unsigned char GetVESRGB() const
//         {
//             return m_uiVESRGB;
//         }
//         inline unsigned char GetSamplerSource() const
//         {
//             return m_uiSamplerSource;
//         }
//         inline void SetSimplerSource(unsigned char SamplerSource)
//         {
//             if (SamplerSource >= VSEngineFlag::SS_MAX)
//             {
//                 SamplerSource = VSEngineFlag::SS_FROM_TEXTURE;
//             }
//             m_uiSamplerSource = SamplerSource;
//         }
//         virtual bool GetOutputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const = 0;

//     protected:
//         VSTexSampler();

//     protected:
//         VSTexAllStateRPtr m_pTexAllState;
//         unsigned char m_uiTexCoordLevel;
//         unsigned char m_uiVEDecode;
//         unsigned char m_uiVESRGB;
//         unsigned int m_uiSamplerSource;
//     };
//     DECLARE_Ptr(VSTexSampler);
//     VSTYPE_MARCO(VSTexSampler);
// }
