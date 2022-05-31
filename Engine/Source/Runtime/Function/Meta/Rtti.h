#pragma once

#include "Function/FunctionCore.h"
#include "RttiMacro.h"
#include "InitialMacro.h"
#include "Priority.h"
#include "ObjName.h"

#include "Core/MemoryManager.h"
#include "Container/String.h"
#include "Container/Array.h"


namespace Matrix
{
	// namespace Function
	//{
	class MObject;
	typedef MObject* (*CreateObjectFun)();
	class VSProperty;
	class VSFunction;

	class MATRIX_FUNCTION_API VSRtti : public Matrix::Core::MemoryObject
	{
		// PRIORITY������ȼ����򣬳�ʼ�����򣬽���ĳ�ʼ�����������ٺ���ע�ᵽ��ʼ����������
		DECLARE_PRIORITY

		DECLARE_INITIAL_ONLY
	public:
		VSRtti(const TCHAR* pcRttiName, VSRtti* pBase, CreateObjectFun COF);
		~VSRtti();

		inline const Container::MString& GetName() const;
		inline bool IsSameType(const VSRtti& Type) const;
		inline bool IsDerived(const VSRtti& Type) const;
		inline VSRtti* GetBase() const
		{
			return m_pBase;
		}
		VSProperty* GetProperty(unsigned int uiIndex) const;
		VSProperty* GetProperty(const Container::MString& PropertyName) const;
		unsigned int GetPropertyNum() const;

		void AddProperty(VSProperty* pProperty);
		void AddProperty(VSRtti& Rtti);

		friend class MObject;
		typedef MObject* (*CreateObjectFun)();
		void ClearProperty();

		VSFunction* GetFunction(unsigned int uiIndex) const;
		unsigned int GetFunctionNum() const;
		void AddFunction(VSFunction* pProperty);
		void AddFunction(VSRtti& Rtti);
		void ClearFunction();

		static const VSRtti* GetRttiByName(const VSUsedName& RttiName);

	private:
		Container::MString m_cRttiName;
		VSRtti* m_pBase;
		Container::MArray<VSProperty*> m_PropertyArray; //����������� 
		Container::MArray<VSFunction*> m_FunctionArray; //���function
		CreateObjectFun m_CreateFun;

		static Container::MMapOrder<VSUsedName, VSRtti*> ms_RttiMap;

		static Container::MArray<VSRtti*>& GetRttiArray()
		{
			static Container::MArray<VSRtti*> ms_RttiArray;
			return ms_RttiArray;
		}
		//ÿ����ʵ��һ����ʼ�����������ٺ����������ʼ�������������ľ�̬��Ա����
		static bool InitialDefaultState();
		static bool TerminalDefaultState();
	};
#include "Rtti.inl"
	//};
};