#pragma once
#include "Function/FunctionCore.h"
#include "Core/Type.h"
#include "Container/Map.h"


namespace Matrix
{
	class MObject;
	class MStream;
	class VSEditorElement;
	//��֧��ָ�����л�����֧��postload �� postclone
	//���Ա�����VSType ��֧�ֵ�
	class MATRIX_FUNCTION_API VSCustomArchiveObject : public Core::MemoryObject
	{
	public:
		VSCustomArchiveObject();
		virtual ~VSCustomArchiveObject();
		virtual void Archive(MStream& Stream) = 0;
		virtual void CopyFrom(VSCustomArchiveObject*, Container::MMap<MObject*, MObject*>& CloneMap) = 0;
		virtual VSEditorElement* CreateEElement(Container::MString& Name, MObject* pOwner);
	};
	CUSTOMTYPE_MARCO(VSCustomArchiveObject)
}
