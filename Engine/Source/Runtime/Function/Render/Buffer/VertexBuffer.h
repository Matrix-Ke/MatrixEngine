#pragma once
#include "Core/Object.h"
#include "Render/MemBind.h"
#include "Render/BindLockInterface.h"
#include "Render/Buffer/DataBuffer.h"
#include "Math/CMathInterface.h"
#include "Render/Buffer/VertexFormat.h"
namespace Matrix
{
	class MStream;
	/*
	* 并非实际的数据类， 而是记录顶点信息
	*/
	class MATRIX_FUNCTION_API VSVertexBuffer : public VSMemBind, public VSBindLockInterface
	{
		// PRIORITY

		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		friend class VSVertexFormat;
		friend class VSResourceManager;
		VSVertexBuffer(bool bIsStatic);
		VSVertexBuffer(Container::MArray<VSVertexFormat::VERTEXFORMAT_TYPE>& FormatArray, unsigned int uiNum);
		virtual ~VSVertexBuffer();
		bool SetData(VSDataBuffer* pData, unsigned int uiVF);
		inline VSDataBuffer* GetData(unsigned int uiVF, unsigned int uiLevel) const;
		inline unsigned int GetLevel(unsigned int uiVF) const;

		inline VSDataBuffer* GetPositionData(unsigned int uiLevel) const;
		inline VSDataBuffer* GetNormalData(unsigned int uiLevel) const;
		inline VSDataBuffer* GetPSizeData() const;
		inline VSDataBuffer* GetColorData(unsigned int uiLevel) const;
		inline VSDataBuffer* GetBlendWeightData() const;
		inline VSDataBuffer* GetBlendIndicesData(unsigned int uiLevel) const;
		inline VSDataBuffer* GetTangentData() const;
		inline VSDataBuffer* GetBinormalData() const;
		inline VSDataBuffer* GetFogData() const;
		inline VSDataBuffer* GetVertexIDData() const;
		inline VSDataBuffer* GetTexCoordData(unsigned int uiLevel) const;
		inline VSDataBuffer* GetMaterialInstanceData(unsigned int uiLevel) const;

		inline unsigned int GetPositionLevel() const;
		inline unsigned int GetColorLevel() const;
		inline unsigned int GetNormalLevel() const;
		inline unsigned int GetTexCoordLevel() const;
		inline unsigned int GetMaterialInstanceLevel() const;
		inline unsigned int GetBlendIndicesLevel() const;
		inline unsigned int GetVertexNum() const;
		bool GetVertexFormat(Container::MArray<VSVertexFormat::VERTEXFORMAT_TYPE>& FormatArray);

		inline VSVertexFormat* GetVertexFormat() const;
		inline unsigned int GetOneVertexSize() const;
		inline bool GetLockDataOffset(unsigned int uiVF, unsigned int uiLevel, unsigned int& uiOffset) const;
		inline void* GetLockData(unsigned int uiVF, unsigned int uiLevel) const;
		inline void* GetLockPositionData(unsigned int uiLevel) const;
		inline void* GetLockNormalData(unsigned int uiLevel) const;
		inline void* GetLockPSizeData() const;
		inline void* GetLockColorData(unsigned int uiLevel) const;
		inline void* GetLockBlendWeightData() const;
		inline void* GetLockBlendIndicesData(unsigned int uiLevel) const;
		inline void* GetLockTangentData() const;
		inline void* GetLockBinormalData() const;
		inline void* GetLockFogData() const;
		inline void* GetLockVertexIDData() const;
		inline void* GetLockTexCoordData(unsigned int uiLevel) const;
		inline void* GetLockMaterialInstanceData(unsigned int uiLevel) const;

		virtual unsigned int GetByteSize() const;

		inline bool HavePositionInfo(unsigned int uiLevel) const;
		inline bool HaveNormalInfo(unsigned int uiLevel) const;
		inline bool HavePSizeInfo() const;
		inline bool HaveColorInfo(unsigned int uiLevel) const;
		inline bool HaveBlendWeightInfo() const;
		inline bool HaveBlendIndicesInfo(unsigned int uiLevel) const;
		inline bool HaveTangentInfo() const;
		inline bool HaveBinormalInfo() const;
		inline bool HaveFogInfo() const;
		inline bool HaveVertexIDInfo() const;
		inline bool HaveTexCoordInfo(unsigned int uiLevel) const;
		inline bool HaveMaterialInstanceInfo(unsigned int uiLevel) const;

		unsigned int GetSemanticsNum(unsigned int uiSemantics) const; //GetSemanticsNum 得到对应语义层数
		unsigned int GetSemanticsChannel(unsigned int uiSemantics, unsigned int uiLevel) const; //GetSemanticsChannel 得到对应语义层的通道个数
		unsigned int GetSemanticsDataType(unsigned int uiSemantics, unsigned int uiLevel) const; //GetSemanticsDataType 得到对应语义层的数据类型

		inline unsigned int PositionChannel(unsigned int uiLevel) const;
		inline unsigned int NormalChannel(unsigned int uiLevel) const;
		inline unsigned int PSizeChannel() const;
		inline unsigned int ColorChannel(unsigned int uiLevel) const;
		inline unsigned int BlendWeightChannel() const;
		inline unsigned int BlendIndicesChannel(unsigned int uiLevel) const;
		inline unsigned int TangentChannel() const;
		inline unsigned int BinormalChannel() const;
		inline unsigned int FogChannel() const;
		inline unsigned int VertexIDChannel() const;
		inline unsigned int TexCoordChannel(unsigned int uiLevel) const;
		inline unsigned int MaterialInstanceChannel(unsigned int uiLevel) const;
		inline unsigned int NormalDataType(unsigned int uiLevel) const;
		inline unsigned int TangentDataType() const;
		inline unsigned int BinormalDataType() const;

		//都要重新实现
	public:
		virtual bool LoadResource(VSRenderer* pRender);
		void* Lock();
		void UnLock();
		inline void* GetLockDataPtr() const
		{
			return m_pLockData;
		}
		virtual void ClearInfo();

	protected:
		virtual bool OnLoadResource(VSResourceIdentifier*& pID);


	protected:
		friend class VSVertexFormat;
		friend class VSGeometry;
		VSVertexBuffer();
		Container::MArray<VSDataBufferPtr> m_pData[VSVertexFormat::VF_MAX]; //m_pData 存放顶点数据
		unsigned int m_uiVertexNum; //m_uiVertexNum 表示顶点个数，所有的数据缓冲区里面包含的元素个数都要和顶点个数相等
		unsigned int m_uiOneVertexSize; //m_uiOneVertexSize 表示每个顶点数据的大小；
		VSVertexFormatPtr m_pVertexFormat;
		void* m_pLockData;

	};
	DECLARE_Ptr(VSVertexBuffer);
	VSTYPE_MARCO(VSVertexBuffer);


#include "VertexBuffer.inl"

}
