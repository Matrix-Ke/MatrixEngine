#pragma once
#include "Core/Object.h"
namespace Matrix
{
	class MStream;
	/*
	* VSDataBuffer 类实际是一个存放数据的数组，需要标注数据格式和每个数据里面通道（channel）的个数。
	*/
	class MATRIX_FUNCTION_API VSDataBuffer : public MObject
	{
		// PRIORITY

		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		/*
		* eg: DT_FLOAT32_3 表示有符号浮点型，它有 3 个通道。带“U”字母的表示无符号的类型，带“N”字母的表示在着色器里面它会被归一化，
		*/
		enum	//Data Type
		{
			DT_FLOAT32_1,//32 位浮点数在寄存器中扩展为(value1, 0, 0, 1) 
			DT_FLOAT32_2,//两个 32 位浮点数在寄存器中扩展为(value1, value2, 0, 1) 
			DT_FLOAT32_3,//3 个 32 位浮点数在寄存器中扩展为(value1, value2, value3, 1)
			DT_FLOAT32_4,//4 个 32 位浮点数在寄存器中扩展为(value1, value2, value3, value4) 

			DT_USHORT, // Index buffer
			DT_UINT,   // Index buffer

			DT_UBYTE4,  // 4D unsigned byte
			DT_UBYTE4N, // Each of 4 bytes is normalized by dividing to 255.0

			DT_SHORT2,   // 2D signed short expanded to (value, value, 0., 1.)
			DT_SHORT2N,  // 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
			DT_USHORT2N, // 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)

			DT_SHORT4,   // 4D signed short expanded to (value, value, value, value)
			DT_SHORT4N,  // 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
			DT_USHORT4N, // 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)

			DT_FLOAT16_2, // Two 16-bit floating point values, expanded to (value, value, 0, 1)
			DT_FLOAT16_4, // Four 16-bit floating point values

			DT_COLOR, // 4D packed unsigned bytes mapped to 0. to 1. range
					  // Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
					  DT_SINT,
					  DT_SINT2,
					  DT_SINT3,
					  DT_SINT4,

					  DT_UINT2,
					  DT_UINT3,
					  DT_UINT4,

					  DT_FLOAT16_1,
					  DT_UBYTE, // use byte address buffer

					  DT_STRUCT = 127, // use struct buffer
					  DT_MAXNUM = 128
		};

		virtual ~VSDataBuffer();
		VSDataBuffer();

	public:
		inline unsigned int GetDT() const { return m_uiDT; }
		inline unsigned int GetStride() const { return m_uiDT == DT_STRUCT ? m_uiStructStride : ms_uiDataTypeByte[m_uiDT]; }
		inline unsigned int GetChannel() const { return ms_uiDataTypeChannel[m_uiDT]; }
		inline unsigned int GetNum() const { return m_uiNum; }
		inline unsigned int GetSize() const { return GetStride() * m_uiNum; }
		inline void* GetData() const { return m_pData; }
		inline unsigned int GetStructStride() const { return m_uiStructStride; }
		//如果你添加数据通道数大于规定数则返回0
		bool SetData(const void* pData, unsigned int uiNum, unsigned int uiDT, unsigned int uiStructStride = 0);
		//如果你添加数据通道数大于规定数则返回0
		bool AddData(const void* pData, unsigned int uiNum, unsigned int uiDT, unsigned int uiStructStride = 0);
		bool CreateEmptyBuffer(unsigned int uiNum, unsigned int uiDT, unsigned int uiStructStride = 0);
		static unsigned int ms_uiDataTypeByte[DT_MAXNUM];
		static unsigned int ms_uiDataTypeChannel[DT_MAXNUM];

	protected:
		unsigned int m_uiDT; //表示数据类型
		unsigned int m_uiNum; //m_uiNum 表示数据元素个数
		unsigned char* m_pData; //m_pData 表示数据基地址
		unsigned int m_uiSize; //m_uiSize表示数据量大小
		unsigned int m_uiStructStride;

	};
	DECLARE_Ptr(VSDataBuffer);
	VSTYPE_MARCO(VSDataBuffer);
}
