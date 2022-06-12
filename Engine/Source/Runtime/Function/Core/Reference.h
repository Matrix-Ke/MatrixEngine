#pragma once

#include "Function/FunctionCore.h"
#include "Pointer.h"
#include "Platform/MemoryManager.h"

namespace Matrix
{
	class MATRIX_FUNCTION_API VSReference
	{

	public:
		template <class T>
		friend class VSPointer;
		friend class VSVariant;
		VSReference();
		virtual ~VSReference() = 0;
		// SmartPointer
	public:
		int GetRef() const { return m_iReference; }

	protected:
		void IncreRef()
		{
			Matrix::Core::MXLockedIncrement((long*)&m_iReference);
		}
		void DecreRef()
		{
			Matrix::Core::MXLockedDecrement((long*)&m_iReference);
			if (!m_iReference)
				MX_DELETE this;
		}
		int m_iReference;
	};

};
