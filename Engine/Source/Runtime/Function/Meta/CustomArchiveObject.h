#pragma once
#include "Function/FunctionCore.h"
#include "Type.h"
#include "Container/Map.h"


namespace Matrix
{
	class VSObject;
	class VSStream;
	class VSEditorElement;
	//��֧��ָ�����л�����֧��postload �� postclone
	//���Ա�����VSType ��֧�ֵ�
	class MATRIX_FUNCTION_API VSCustomArchiveObject : public Core::MemoryObject
	{
	public:
		VSCustomArchiveObject();
		virtual ~VSCustomArchiveObject();
		virtual void Archive(VSStream& Stream) = 0;
		virtual void CopyFrom(VSCustomArchiveObject*, Container::MMap<VSObject*, VSObject*>& CloneMap) = 0;
		virtual VSEditorElement* CreateEElement(Container::MString& Name, VSObject* pOwner);
	};
	CUSTOMTYPE_MARCO(VSCustomArchiveObject)
}
