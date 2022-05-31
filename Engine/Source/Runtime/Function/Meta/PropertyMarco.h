/********************************************************************************/
//dummyPtr����ʾ�� A ��һ��ָ�������
//�� varName����ʾ���� A �е����Ա�������
//�� reflectName����ʾҪ��������ֻ��߰� UI �༭������ʾ�����֡�
//�� varNumName����ʾ����Ԫ�صĸ��������� A �ĳ�Ա������
//�� Num���Ǳ������ǹ̶������Ԫ�ظ�����
//�� #���ں������ʾ�����������ĸ�����ַ�����
//��(size_t)((char*)&(dummyPtr->varName) - (char*)dummyPtr)����ʾ���� varName ���� A �о����׵�ַ��ƫ������dummyPtr����ָ��
#define REGISTER_PROPERTY(varName,reflectName,flag) \
 	{ \
 		activeProperty = PropertyCreator::GetAutoPropertyCreator(dummyPtr->varName).CreateProperty( \
 						_T(#reflectName), *pRtti, (unsigned int)((char*)&(dummyPtr->varName) - (char*)dummyPtr),flag ); \
 		pRtti->AddProperty(activeProperty); \
 	}
#define REGISTER_PROPERTY_RANGE(varName,reflectName,High,Low,Step,flag) \
 	{ \
 		activeProperty = PropertyCreator::GetAutoPropertyCreator(dummyPtr->varName).CreateProperty( \
 						_T(#reflectName), *pRtti, (unsigned int)((char*)&(dummyPtr->varName) - (char*)dummyPtr),High,Low,Step,flag ); \
 		pRtti->AddProperty(activeProperty); \
 	}
#define REGISTER_PROPERTY_DATA(varName,varNumName,reflectName) \
 	{ \
 		activeProperty = PropertyCreator::GetAutoPropertyCreator(dummyPtr->varName,dummyPtr->varNumName).CreateProperty( \
 						_T(#reflectName), *pRtti, (unsigned int)((char*)&(dummyPtr->varName) - (char*)dummyPtr),(unsigned int)((char*)&(dummyPtr->varNumName) - (char*)dummyPtr) ); \
 		pRtti->AddProperty(activeProperty); \
 	}
#define REGISTER_PROPERTY_FIXED_DATA(varName,Num,reflectName,isDynamicCreate) \
 	{ \
 		unsigned int CountType = 0; \
 		activeProperty = PropertyCreator::GetAutoPropertyCreator(dummyPtr->varName,CountType).CreateProperty( \
 						_T(#reflectName), *pRtti, (unsigned int)((char*)&(dummyPtr->varName) - (char*)dummyPtr),Num,isDynamicCreate ); \
 		pRtti->AddProperty(activeProperty); \
 	}
#define REGISTER_ENUM_PROPERTY(varName,enumName,reflectName,flag) \
 	{ \
 		activeProperty = PropertyCreator::CreateEnumProperty( \
 						dummyPtr->varName,_T(#reflectName), _T(#enumName),*pRtti, (unsigned int)((char*)&(dummyPtr->varName) - (char*)dummyPtr),flag ); \
 		pRtti->AddProperty(activeProperty); \
 	}
 /********************************************************************************/
#define BEGIN_ADD_ENUM \
 	if(!pRttiTemp) \
 	{
 /********************************************************************************/
#define END_ADD_ENUM  }
#define CHANGE_PROPERTY_FLAG(reflectName,flag) \
 	{\
 		VSProperty* p = pRtti->GetProperty(_T(#reflectName));\
 		if(p) \
 		{ \
 			p->SetFlag(flag); \
 		}\
 	}
#define ADD_PROPERTY_FLAG(reflectName,flag) \
 	{\
 		VSProperty* p = pRtti->GetProperty(_T(#reflectName));\
 		if(p) \
 		{ \
 			p->SetFlag( p->GetFlag() | flag); \
 		}\
 	}
 /********************************************************************************/
#define NO_PROPERTY(classname) \
 	bool classname::InitialProperty(VSRtti *) \
 	{ \
 		return true; \
 	} \
 	bool classname::TerminalProperty() \
 	{ \
 		ms_Type.ClearProperty(); \
 		return true; \
 	}
 /********************************************************************************/
#define BEGIN_ADD_PROPERTY(classname,baseclassname) \
 	bool classname::TerminalProperty() \
 	{ \
 		ms_Type.ClearProperty(); \
 		return true; \
 	} \
 	bool classname::InitialProperty(VSRtti * pRtti) \
 	{ \
 		classname* dummyPtr = NULL; \
 		VSProperty * activeProperty = NULL; \
 		VSRtti * pRttiTemp = pRtti; \
 		if(!pRtti) \
 		{ \
 			pRtti = &ms_Type; \
 		} \
 		baseclassname::InitialProperty(pRtti);
/********************************************************************************/
#define BEGIN_ADD_PROPERTY_ROOT(classname) \
 	bool classname::TerminalProperty() \
 	{ \
 		ms_Type.ClearProperty(); \
 		return true; \
 	} \
 	bool classname::InitialProperty(VSRtti * pRtti) \
 	{ \
 		classname* dummyPtr = NULL; \
 		VSProperty * activeProperty = NULL; \
 		if(!pRtti) \
 		{ \
 			pRtti = &ms_Type; \
 		}
 /********************************************************************************/
#define END_ADD_PROPERTY \
 		return true; \
 	}





#define ADD_FUNCTION(FunctionName) \
 	VSFunction * pFun = MX_NEW VSFunction(rtti, _T(#FunctionName), Flag); \
 	pFun->SetTotalSize(sizeof(Name)); \
 	pFun->ObjectFun = FunctionTemplate_Temp;
#define ADD_RETURN_TYPE(Retype)\
 	{ \
 		Retype Temp = Retype(); \
 		activeProperty = PropertyCreator::GetAutoPropertyCreator(Temp).CreateFunctionProperty(\
 		_T("Return"), *pFun, 0, 0); \
 		pFun->SetReturnType(activeProperty); \
 	}
#define REGISTER_FUNCTION_PROPERTY(reflectName) \
 	{ \
 		activeProperty = PropertyCreator::GetAutoPropertyCreator(dummyPtr->reflectName).CreateFunctionProperty(\
 		_T(#reflectName), *pFun, (unsigned int)((char*)&(dummyPtr->reflectName) - (char*)dummyPtr), 0); \
 		pFun->AddProperty(activeProperty); \
 	}
#define  Get_FUN_PROPERTY_VALUE(Num) \
 	pFun->GetProperty(Num)->GetValueAddress(para)
#define  RETURN_FUN(classname,FunctionName,...) \
 	((classname *)p)->FunctionName(##__VA_ARGS__);
#define BEGIN_REGISTER_FUNCTION_NOPARAMETER(classname,FunctionName,uiFlag,Retype) \
 { \
 	class Template_##FunctionName \
 	{ \
 	public: \
 		~Template_##FunctionName() \
 		{ \
 		} \
 		static void FunctionTemplate_Temp(MObject * p, VSFunction * pFun, void * para, void *ret) \
 		{ \
 			if (ret && !pFun->IsReturnVoid()) \
 			{ \
 				*((Retype *)ret) = RETURN_FUN(classname, FunctionName,); \
 			} \
 			else \
 			{ \
 				RETURN_FUN(classname, FunctionName,); \
 			} \
 		} \
 		Template_##FunctionName(VSRtti & rtti,unsigned int Flag) \
 		{ \
 			ADD_FUNCTION(FunctionName) \
 			VSProperty * activeProperty = NULL; \
 			ADD_RETURN_TYPE(Retype)\
 			rtti.AddFunction(pFun); \
 		} \
 	};\
 	Template_##FunctionName _Template_##FunctionName(*pRtti, uiFlag); \
 }
#define BEGIN_REGISTER_VOID_FUNCTION_NOPARAMETER(classname,FunctionName,uiFlag) \
 { \
 	class Template_##FunctionName \
 	{ \
 	public: \
 		~Template_##FunctionName() \
 		{ \
 		} \
 		static void FunctionTemplate_Temp(MObject * p, VSFunction * pFun, void * para, void *ret) \
 		{ \
 			RETURN_FUN(classname, FunctionName,); \
 		} \
 		Template_##FunctionName(VSRtti & rtti,unsigned int Flag) \
 		{ \
 			ADD_FUNCTION(FunctionName) \
 			rtti.AddFunction(pFun); \
 		} \
 	};\
 	Template_##FunctionName _Template_##FunctionName(*pRtti, uiFlag); \
 }
#define BEGIN_REGISTER_FUNCTION_ONEPARAMETER(classname,FunctionName,uiFlag,Retype,ValType1,ValName1) \
 { \
 	class Template_##FunctionName \
 	{ \
 	public: \
 		~Template_##FunctionName() \
 		{ \
 		} \
 		struct Name \
 		{ \
 			ValType1 In##ValName1; \
 		}; \
 		static void FunctionTemplate_Temp(MObject * p, VSFunction * pFun, void * para, void *ret) \
 		{ \
 			ValType1 In##ValName1 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(0)); \
 			if (ret && !pFun->IsReturnVoid()) \
 			{ \
 				*((Retype *)ret) = RETURN_FUN(classname, FunctionName, In##ValName1); \
 			} \
 			else \
 			{ \
 				RETURN_FUN(classname, FunctionName, In##ValName1); \
 			} \
 		} \
 		Template_##FunctionName(VSRtti & rtti,unsigned int Flag) \
 		{ \
 			ADD_FUNCTION(FunctionName) \
 			VSProperty * activeProperty = NULL; \
 			ADD_RETURN_TYPE(Retype)\
 			Name * dummyPtr = NULL; \
 			REGISTER_FUNCTION_PROPERTY(In##ValName1) \
 			rtti.AddFunction(pFun); \
 		} \
 	};\
 	Template_##FunctionName _Template_##FunctionName(*pRtti, uiFlag); \
 }

#define BEGIN_REGISTER_VOID_FUNCTION_ONEPARAMETER(classname,FunctionName,uiFlag,ValType1,ValName1) \
 { \
 	class Template_##FunctionName \
 	{ \
 	public: \
 		~Template_##FunctionName() \
 		{ \
 		} \
 		struct Name \
 		{ \
 			ValType1 In##ValName1; \
 		}; \
 		static void FunctionTemplate_Temp(MObject * p, VSFunction * pFun, void * para, void *ret) \
 		{ \
 			ValType1 In##ValName1 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(0)); \
 			RETURN_FUN(classname, FunctionName, In##ValName1); \
 		} \
 		Template_##FunctionName(VSRtti & rtti,unsigned int Flag) \
 		{ \
 			ADD_FUNCTION(FunctionName) \
 			VSProperty * activeProperty = NULL; \
 			Name * dummyPtr = NULL; \
 			REGISTER_FUNCTION_PROPERTY(In##ValName1) \
 			rtti.AddFunction(pFun); \
 		} \
 	};\
 	Template_##FunctionName _Template_##FunctionName(*pRtti, uiFlag); \
 }

#define BEGIN_REGISTER_FUNCTION_TWOPARAMETER(classname,FunctionName,uiFlag,Retype,ValType1,ValName1,ValType2,ValName2) \
 { \
 	class Template_##FunctionName \
 	{ \
 	public: \
 		~Template_##FunctionName() \
 		{ \
 		} \
 		struct Name \
 		{ \
 			ValType1 In##ValName1; \
 			ValType2 In##ValName2; \
 		}; \
 		static void FunctionTemplate_Temp(MObject * p, VSFunction * pFun, void * para, void *ret) \
 		{ \
 			ValType1 In##ValName1 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(0)); \
 			ValType2 In##ValName2 = *((ValType2 *)Get_FUN_PROPERTY_VALUE(1)); \
 			if (ret && !pFun->IsReturnVoid()) \
 			{ \
 				*((Retype *)ret) = RETURN_FUN(classname, FunctionName, ValName1,ValName2); \
 			} \
 			else \
 			{ \
 				RETURN_FUN(classname, FunctionName, In##ValName1,In##ValName2); \
 			} \
 		} \
 		Template_##FunctionName(VSRtti & rtti,unsigned int Flag) \
 		{ \
 			ADD_FUNCTION(FunctionName) \
 			VSProperty * activeProperty = NULL; \
 			ADD_RETURN_TYPE(Retype)\
 			Name * dummyPtr = NULL; \
 			REGISTER_FUNCTION_PROPERTY(In##ValName1) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName2) \
 			rtti.AddFunction(pFun); \
 		} \
 	};\
 	Template_##FunctionName _Template_##FunctionName(*pRtti, uiFlag); \
 }

#define BEGIN_REGISTER_VOID_FUNCTION_TWOPARAMETER(classname,FunctionName,uiFlag,ValType1,ValName1,ValType2,ValName2) \
 { \
 	class Template_##FunctionName \
 	{ \
 	public: \
 		~Template_##FunctionName() \
 		{ \
 		} \
 		struct Name \
 		{ \
 			ValType1 In##ValName1; \
 			ValType2 In##ValName2; \
 		}; \
 		static void FunctionTemplate_Temp(MObject * p, VSFunction * pFun, void * para, void *ret) \
 		{ \
 			ValType1 In##ValName1 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(0)); \
 			ValType2 In##ValName2 = *((ValType2 *)Get_FUN_PROPERTY_VALUE(1)); \
 			RETURN_FUN(classname, FunctionName, In##ValName1,In##ValName2); \
 		} \
 		Template_##FunctionName(VSRtti & rtti,unsigned int Flag) \
 		{ \
 			ADD_FUNCTION(FunctionName) \
 			VSProperty * activeProperty = NULL; \
 			Name * dummyPtr = NULL; \
 			REGISTER_FUNCTION_PROPERTY(In##ValName1) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName2) \
 			rtti.AddFunction(pFun); \
 		} \
 	};\
 	Template_##FunctionName _Template_##FunctionName(*pRtti, uiFlag); \
 }

#define BEGIN_REGISTER_FUNCTION_THREEPARAMETER(classname,FunctionName,uiFlag,Retype,ValType1,ValName1,ValType2,ValName2,ValType3,ValName3) \
 { \
 	class Template_##FunctionName \
 	{ \
 	public: \
 		~Template_##FunctionName_() \
 		{ \
 		} \
 		struct Name \
 		{ \
 			ValType1 In##ValName1; \
 			ValType2 In##ValName2; \
 			ValType3 In##ValName3; \
 		}; \
 		static void FunctionTemplate_Temp(MObject * p, VSFunction * pFun, void * para, void *ret) \
 		{ \
 			ValType1 In##ValName1 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(0)); \
 			ValType2 In##ValName2 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(1)); \
 			ValType3 In##ValName3 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(2)); \
 			if (ret && !pFun->IsReturnVoid()) \
 			{ \
 				*((Retype *)ret) = RETURN_FUN(classname, FunctionName, In##ValName1,In##ValName2,In##ValName3); \
 			} \
 			else \
 			{ \
 				RETURN_FUN(classname, FunctionName, In##ValName1,In##ValName2,In##ValName3); \
 			} \
 		} \
 		Template_##FunctionName(VSRtti & rtti,unsigned int Flag) \
 		{ \
 			ADD_FUNCTION(FunctionName) \
 			VSProperty * activeProperty = NULL; \
 			ADD_RETURN_TYPE(Retype)\
 			Name * dummyPtr = NULL; \
 			REGISTER_FUNCTION_PROPERTY(In##ValName1) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName2) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName3) \
 			rtti.AddFunction(pFun); \
 		} \
 	};\
 	Template_##FunctionName _Template_##FunctionName(*pRtti, uiFlag); \
 }

#define BEGIN_REGISTER_VOID_FUNCTION_THREEPARAMETER(classname,FunctionName,uiFlag,ValType1,ValName1,ValType2,ValName2,ValType3,ValName3) \
 { \
 	class Template_##FunctionName \
 	{ \
 	public: \
 		~Template_##FunctionName() \
 		{ \
 		} \
 		struct Name \
 		{ \
 			ValType1 In##ValName1; \
 			ValType2 In##ValName2; \
 			ValType3 In##ValName3; \
 		}; \
 		static void FunctionTemplate_Temp(MObject * p, VSFunction * pFun, void * para, void *ret) \
 		{ \
 			ValType1 In##ValName1 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(0)); \
 			ValType2 In##ValName2 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(1)); \
 			ValType3 In##ValName3 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(2)); \
 			RETURN_FUN(classname, FunctionName, In##ValName1,In##ValName2,In##ValName3); \
 		} \
 		Template_##FunctionName(VSRtti & rtti,unsigned int Flag) \
 		{ \
 			ADD_FUNCTION(FunctionName) \
 			VSProperty * activeProperty = NULL; \
 			Name * dummyPtr = NULL; \
 			REGISTER_FUNCTION_PROPERTY(In##ValName1) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName2) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName3) \
 			rtti.AddFunction(pFun); \
 		} \
 	};\
 	Template_##FunctionName _Template_##FunctionName(*pRtti, uiFlag); \
 }

#define BEGIN_REGISTER_FUNCTION_FOURPARAMETER(classname,FunctionName,uiFlag,Retype,ValType1,ValName1,ValType2,ValName2,ValType3,ValName3,ValType4,ValName4) \
 { \
 	class Template_##FunctionName \
 	{ \
 	public: \
 		~Template_##FunctionName() \
 		{ \
 		} \
 		struct Name \
 		{ \
 			ValType1 In##ValName1; \
 			ValType2 In##ValName2; \
 			ValType3 In##ValName3; \
 			ValType4 In##ValName4; \
 		}; \
 		static void FunctionTemplate_Temp(MObject * p, VSFunction * pFun, void * para, void *ret) \
 		{ \
 			ValType1 In##ValName1 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(0)); \
 			ValType2 In##ValName2 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(1)); \
 			ValType3 In##ValName3 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(2)); \
 			ValType4 In##ValName4 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(3)); \
 			if (ret && !pFun->IsReturnVoid()) \
 			{ \
 				*((Retype *)ret) = RETURN_FUN(classname, FunctionName, In##ValName1,In##ValName2,In##ValName3,In##ValName4); \
 			} \
 			else \
 			{ \
 				RETURN_FUN(classname, FunctionName, In##ValName1,In##ValName2,In##ValName3,In##ValName4); \
 			} \
 		} \
 		Template_##FunctionName(VSRtti & rtti,unsigned int Flag) \
 		{ \
 			ADD_FUNCTION(FunctionName) \
 			VSProperty * activeProperty = NULL; \
 			ADD_RETURN_TYPE(Retype)\
 			Name * dummyPtr = NULL; \
 			REGISTER_FUNCTION_PROPERTY(In##ValName1) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName2) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName3) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName4) \
 			rtti.AddFunction(pFun); \
 		} \
 	};\
 	Template_##FunctionName _Template_##FunctionName(*pRtti, uiFlag); \
 }

#define BEGIN_REGISTER_VOID_FUNCTION_FOURPARAMETER(classname,FunctionName,uiFlag,ValType1,ValName1,ValType2,ValName2,ValType3,ValName3,ValType4,ValName4) \
 { \
 	class Template_##FunctionName \
 	{ \
 	public: \
 		~Template_##FunctionName() \
 		{ \
 		} \
 		struct Name \
 		{ \
 			ValType1 In##ValName1; \
 			ValType2 In##ValName2; \
 			ValType3 In##ValName3; \
 			ValType4 In##ValName4; \
 		}; \
 		static void FunctionTemplate_Temp(MObject * p, VSFunction * pFun, void * para, void *ret) \
 		{ \
 			ValType1 In##ValName1 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(0)); \
 			ValType2 In##ValName2 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(1)); \
 			ValType3 In##ValName3 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(2)); \
 			ValType4 In##ValName4 = *((ValType1 *)Get_FUN_PROPERTY_VALUE(3)); \
 			RETURN_FUN(classname, FunctionName, In##ValName1,In##ValName2,In##ValName3,In##ValName4); \
 		} \
 		Template_##FunctionName(VSRtti & rtti,unsigned int Flag) \
 		{ \
 			ADD_FUNCTION(FunctionName) \
 			VSProperty * activeProperty = NULL; \
 			Name * dummyPtr = NULL; \
 			REGISTER_FUNCTION_PROPERTY(In##ValName1) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName2) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName3) \
 			REGISTER_FUNCTION_PROPERTY(In##ValName4) \
 			rtti.AddFunction(pFun); \
 		} \
 	};\
 	Template_##FunctionName _Template_##FunctionName(*pRtti, uiFlag); \
 }