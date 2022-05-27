//#pragma once
////#include "Container/Array.h"
////#include "Object.h"
////#include "Vector3.h"
////#include "Transform.h"
////#include "Vector3W.h"
////#include "Resource.h"
//
//#include "Container/Array.h "
//#include "Object.h"
//#include "Math/Vector3.h"
//#include "Math/Transform.h"
//#include "Math/Vector4.h"
//
//
//namespace Matrix
//{
//	//#define  TYPE_ADD_TO_UI
//	template <typename T>
//	struct TIsVSIntType
//	{
//		enum
//		{
//			Value = false
//		};
//	};
//	template <>
//	struct TIsVSIntType<int>
//	{
//		enum
//		{
//			Value = true
//		};
//	};
//
//	template <typename T>
//	struct TIsVSUintType
//	{
//		enum
//		{
//			Value = false
//		};
//	};
//	template <>
//	struct TIsVSUintType<unsigned int>
//	{
//		enum
//		{
//			Value = true
//		};
//	};
//
//	template <typename T>
//	struct TIsVSUCharType
//	{
//		enum
//		{
//			Value = false
//		};
//	};
//	template <>
//	struct TIsVSUCharType<unsigned char>
//	{
//		enum
//		{
//			Value = true
//		};
//	};
//
//	template <typename T>
//	struct TIsVSTCharType
//	{
//		enum
//		{
//			Value = false
//		};
//	};
//	template <>
//	struct TIsVSTCharType<TCHAR>
//	{
//		enum
//		{
//			Value = true
//		};
//	};
//
//	template <typename T>
//	struct TIsVSRealType
//	{
//		enum
//		{
//			Value = false
//		};
//	};
//	template <>
//	struct TIsVSRealType<VSREAL>
//	{
//		enum
//		{
//			Value = true
//		};
//	};
//
//	class MATRIX_FUNCTION_API VSEditorElement
//	{
//	public:
//		VSEditorElement()
//		{
//		}
//		virtual ~VSEditorElement() = 0
//		{
//		}
//		virtual bool IsCollection()
//		{
//			return false;
//		}
//
//	protected:
//	};
//	class VSEditorProperty;
//	class MATRIX_FUNCTION_API VSEditorSingle : public VSEditorElement
//	{
//	public:
//		enum CUSTOM_UI_TYPE
//		{
//			CUT_CHECK,
//			CUT_LABLE,
//			CUT_TEXT,
//			CUT_COMBO,
//			CUT_SLIDER,
//			CUT_COLOR,
//			CUT_VIEW,
//			CUT_COLLECTION
//		};
//		VSEditorSingle(Container::MString& Name)
//		{
//			m_Name = Name;
//			m_pOwner = NULL;
//		}
//		virtual ~VSEditorSingle() = 0
//		{
//		}
//		void SetOwner(VSEditorProperty* pOwner)
//		{
//			m_pOwner = pOwner;
//		}
//		virtual void SetValue(void* pValue) = 0;
//		Container::MString& GetName()
//		{
//			return m_Name;
//		}
//
//	protected:
//		VSEditorProperty* m_pOwner;
//		Container::MString m_Name;
//	};
//	class MATRIX_FUNCTION_API VSECheckBox : public VSEditorSingle
//	{
//	public:
//		VSECheckBox(Container::MString& Name) : VSEditorSingle(Name)
//		{
//		}
//		virtual ~VSECheckBox() = 0
//		{
//		}
//		virtual void CallBackValue(bool Value);
//	};
//
//
//
//	class MATRIX_FUNCTION_API VSELable : public VSEditorSingle
//	{
//	public:
//		VSELable(Container::MString& Name) : VSEditorSingle(Name)
//		{
//		}
//		virtual ~VSELable() = 0
//		{
//		}
//		virtual void CallBackValue(Container::MString& Str);
//	};
//	class MATRIX_FUNCTION_API VSECombo : public VSEditorSingle
//	{
//	public:
//		VSECombo(Container::MString& Name) : VSEditorSingle(Name)
//		{
//		}
//		virtual ~VSECombo() = 0
//		{
//		}
//		virtual void AddOption(Container::MString& String) = 0;
//
//		virtual void CallBackValue(Container::MString& Str);
//		virtual void AddOption(Container::MArray<Container::MString>& VS) = 0;
//	};
//	class MATRIX_FUNCTION_API VSESlider : public VSEditorSingle // unsigned int
//	{
//	public:
//		VSESlider(Container::MString& Name) : VSEditorSingle(Name)
//		{
//		}
//		virtual ~VSESlider() = 0
//		{
//		}
//		virtual void SetRange(unsigned int uiMin, unsigned int uiMax, unsigned int uiStep) = 0
//		{
//			m_uiMax = uiMax;
//			m_uiMin = uiMin;
//			m_uiStep = uiStep;
//		}
//		unsigned int m_uiMax;
//		unsigned int m_uiMin;
//		unsigned int m_uiStep;
//		virtual void CallBackValue(unsigned int uiValue);
//	};
//	class MATRIX_FUNCTION_API VSEViewWindow : public VSEditorSingle
//	{
//	};
//	class MATRIX_FUNCTION_API VSEColorTable : public VSEditorSingle
//	{
//	public:
//		VSEColorTable(Container::MString& Name) : VSEditorSingle(Name)
//		{
//		}
//		virtual ~VSEColorTable()
//		{
//		}
//		virtual void CallBackValue(Math::ColorRGBA& Value);
//	};
//	class MATRIX_FUNCTION_API VSEText : public VSEditorSingle // VSREAL
//	{
//	public:
//		VSEText(Container::MString& Name) : VSEditorSingle(Name)
//		{
//		}
//		virtual ~VSEText()
//		{
//		}
//		virtual void CallBackValue(Container::MString& Str);
//	};
//
//	class MATRIX_FUNCTION_API VSECollection : public VSEditorSingle
//	{
//	public:
//		VSECollection(Container::MString& Name) : VSEditorSingle(Name)
//		{
//		}
//		~VSECollection()
//		{
//		}
//		virtual void AddElement(VSEditorElement* pElement)
//		{
//			ChildElement.AddElement(pElement);
//		}
//		Container::MArray<VSEditorElement*> ChildElement;
//		virtual bool IsCollection()
//		{
//			return true;
//		}
//	};
//
//	typedef VSEditorSingle* (*CreateEditorUIProperty)(VSEditorSingle::CUSTOM_UI_TYPE type, Container::MString Name);
//	class MATRIX_FUNCTION_API VSEditorUIPropertyCreator
//	{
//	public:
//		VSEditorUIPropertyCreator();
//		~VSEditorUIPropertyCreator();
//		static VSEditorUIPropertyCreator& GetInstance();
//
//		void Set(CreateEditorUIProperty pCreate);
//		VSEditorSingle* CreateUIProperty(VSEditorSingle::CUSTOM_UI_TYPE type, Container::MString Name);
//
//	protected:
//		CreateEditorUIProperty m_pCreate;
//	};
//	// 	VSEditorSingle* CreateEditorUIProperty(VSEditorSingle::CUSTOM_UI_TYPE type, Container::MString Name)
//	// 	{
//	// 		if (type == VSEditorSingle::CUSTOM_UI_TYPE::CUT_CHECK)
//	// 		{
//	// 			return MX_NEW QTCheckBox(Name);
//	// 		}
//	// 		else if (type == VSEditorSingle::CUSTOM_UI_TYPE::CUT_TEXT)
//	// 		{
//	// 			return MX_NEW QTText(Name);
//	// 		}
//	// 		else if (type == VSEditorSingle::CUSTOM_UI_TYPE::CUT_COLOR)
//	// 		{
//	// 			return MX_NEW QTColor(Name);
//	// 		}
//	// 		.........................................................................
//	// 	}
//	// you must set this macro
//#define SETCreateEditorUIProperty(F) VSEditorUIPropertyCreator::GetInstance().Set(F);
//#define CREATE_UI_PROPERTY(type, Name) VSEditorUIPropertyCreator::GetInstance().CreateUIProperty(type, Name);
//
//	class MATRIX_FUNCTION_API VSEditorProperty : public VSEditorElement
//	{
//	public:
//		VSEditorProperty(Container::MString& Name, VSObject* pOwner)
//		{
//			m_pName = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, Name);
//			m_pName->SetOwner(this);
//			m_pName->SetValue((void*)&Name);
//			m_pOwner = pOwner;
//		}
//		virtual ~VSEditorProperty()
//		{
//			ENGINE_DELETE(m_pName);
//			m_pOwner = NULL;
//		}
//		virtual void SetValue() = 0;
//		virtual bool CallBackValue(VSEditorSingle* pElem, void* pValue);
//
//	protected:
//		VSELable* m_pName;
//		VSObject* m_pOwner;
//	};
//
//	class MATRIX_FUNCTION_API VSEBoolProperty : public VSEditorProperty
//	{
//	public:
//		VSEBoolProperty(bool* b, Container::MString& Name, VSObject* pOwner)
//			: VSEditorProperty(Name, pOwner)
//		{
//			m_pCheckBox = (VSECheckBox*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_CHECK, Name);
//			m_pb = b;
//			m_pCheckBox->SetOwner(this);
//			SetValue();
//		}
//		virtual void SetValue()
//		{
//			m_pCheckBox->SetValue((void*)m_pb);
//		}
//		virtual ~VSEBoolProperty()
//		{
//			ENGINE_DELETE(m_pCheckBox);
//		}
//		virtual bool CallBackValue(VSEditorSingle* pElem, void* pValue)
//		{
//			if (pElem == m_pCheckBox)
//			{
//				(*m_pb) = *((bool*)pValue);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//
//			return false;
//		}
//
//	protected:
//		VSECheckBox* m_pCheckBox;
//		bool* m_pb;
//	};
//	class MATRIX_FUNCTION_API VSEResourceProperty : public VSEditorProperty
//	{
//	public:
//		VSEResourceProperty(VSResourceProxyBasePtr& pResource, Container::MString& Name, VSObject* pOwner)
//			: VSEditorProperty(Name, pOwner), m_pResource(pResource)
//		{
//			m_pView = (VSEViewWindow*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_VIEW, Name);
//			m_pView->SetOwner(this);
//			SetValue();
//		}
//		virtual void SetValue()
//		{
//			m_pView->SetValue((void*)m_pResource);
//		}
//		virtual ~VSEResourceProperty()
//		{
//			ENGINE_DELETE(m_pView);
//		}
//		virtual bool CallBackValue(VSEditorSingle* pElem, void* pValue)
//		{
//			if (pElem == m_pView)
//			{
//				m_pResource = *((VSResourceProxyBasePtr*)pValue);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			return false;
//		}
//
//	protected:
//		VSEViewWindow* m_pView;
//		VSResourceProxyBasePtr& m_pResource;
//	};
//
//	class MATRIX_FUNCTION_API VSEColorProperty : public VSEditorProperty
//	{
//	public:
//		VSEColorProperty(Math::ColorRGBA* pColor, Container::MString& Name, VSObject* pOwner)
//			: VSEditorProperty(Name, pOwner)
//		{
//			m_pColorTable = (VSEColorTable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_COLOR, Name);
//			m_pColorTable->SetOwner(this);
//			m_pColor = pColor;
//			SetValue();
//		}
//		virtual void SetValue()
//		{
//			m_pColorTable->SetValue((void*)m_pColor);
//		}
//		virtual ~VSEColorProperty()
//		{
//			ENGINE_DELETE(m_pColorTable);
//		}
//		virtual bool CallBackValue(VSEditorSingle* pElem, void* pValue)
//		{
//			if (pElem == m_pColorTable)
//			{
//				*m_pColor = *((Math::ColorRGBA*)pValue);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			return false;
//		}
//
//	protected:
//		VSEColorTable* m_pColorTable;
//		Math::ColorRGBA* m_pColor;
//	};
//
//	class MATRIX_FUNCTION_API VSEEnumProperty : public VSEditorProperty
//	{
//	public:
//		VSEEnumProperty(unsigned int* pData, Container::MString& Name, VSObject* pOwner)
//			: VSEditorProperty(Name, pOwner)
//		{
//			m_pData = pData;
//			m_pCombo = (VSECombo*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_COMBO, Name);
//			m_pCombo->SetOwner(this);
//			SetValue();
//		}
//		virtual void SetValue()
//		{
//			m_pCombo->SetValue((void*)m_pData);
//		}
//		virtual ~VSEEnumProperty()
//		{
//			ENGINE_DELETE(m_pCombo);
//		}
//		virtual bool CallBackValue(VSEditorSingle* pElem, void* pValue)
//		{
//			if (pElem == m_pCombo)
//			{
//				*m_pData = *((unsigned int*)pValue);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//
//			return false;
//		}
//		void AddEnumString(Container::MArray<Container::MString>& AS)
//		{
//			m_pCombo->AddOption(AS);
//		}
//
//	protected:
//		VSECombo* m_pCombo;
//		unsigned int* m_pData;
//	};
//	template <typename T>
//	class MATRIX_FUNCTION_API VSEValueProperty : public VSEditorProperty
//	{
//	public:
//		VSEValueProperty(T* pData, Container::MString& Name, VSObject* pOwner, bool bRange, T& Max, T& Min, T& Step)
//			: VSEditorProperty(Name, pOwner)
//		{
//			MATRIX_ENGINE_ASSERT(pData != NULL);
//			m_pText = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name);
//			m_pText->SetOwner(this);
//			m_fStep = Step;
//			if (bRange)
//			{
//				if (Min > Max)
//				{
//					Swap(Max, Min);
//				}
//				MATRIX_ENGINE_ASSERT(Max - Min > Step);
//				m_pSlider = (VSESlider*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_SLIDER, Name);
//				m_pSlider->SetOwner(this);
//				m_pSlider->SetRange(0, int((Max - Min) / Step), 1);
//			}
//			m_Min = Min;
//			m_Max = Max;
//			m_pData = pData;
//#ifdef TYPE_ADD_TO_UI
//			SetValue();
//#endif
//		}
//		virtual void GetValueString(Container::MString& IntString)
//		{
//#ifdef TYPE_ADD_TO_UI
//			if (TIsVSIntType<T>::Value)
//			{
//				IntString = IntToString(*m_pData);
//			}
//			else if (TIsVSUintType<T>::Value)
//			{
//				IntString = IntToString(*m_pData);
//			}
//			else if (TIsVSUCharType<T>::Value)
//			{
//				IntString = IntToString(*m_pData);
//			}
//			else if (TIsVSTCharType<T>::Value)
//			{
//				TCHAR tData[2];
//				tData[0] = *m_pData;
//				tData[1] = _T('\0');
//				Container::MString Temp(tData);
//				IntString = Temp;
//			}
//			else if (TIsVSRealType<T>::Value)
//			{
//				IntString = RealToString(*m_pData);
//			}
//#endif
//		}
//		virtual T GetStringValue(Container::MString& IntString)
//		{
//#ifdef TYPE_ADD_TO_UI
//			if (TIsVSIntType<T>::Value)
//			{
//				return (T)StringToInt(IntString);
//			}
//			else if (TIsVSUintType<T>::Value)
//			{
//				return (T)StringToInt(IntString);
//			}
//			else if (TIsVSUCharType<T>::Value)
//			{
//				return (T)StringToInt(IntString);
//			}
//			else if (TIsVSTCharType<T>::Value)
//			{
//				return (T)*IntString.GetBuffer();
//			}
//			else if (TIsVSRealType<T>::Value)
//			{
//				return (T)StringToReal(IntString);
//			}
//#endif
//			return T();
//		}
//		virtual void SetValue()
//		{
//			Container::MString IntString;
//			GetValueString(IntString);
//			m_pText->SetValue((void*)&IntString);
//			if (m_pSlider)
//			{
//				T Value = (*m_pData - m_Min) / m_fStep;
//				m_pSlider->SetValue((void*)&Value);
//			}
//		}
//		virtual ~VSEValueProperty()
//		{
//			ENGINE_DELETE(m_pSlider);
//			ENGINE_DELETE(m_pText);
//		}
//		virtual bool CallBackValue(VSEditorSingle* pElem, void* pValue)
//		{
//			if (pElem == m_pText)
//			{
//				Container::MString Data = *(Container::MString*)pValue;
//				T Value = GetStringValue(Data);
//				if (m_pSlider)
//				{
//					if (Value < m_Min)
//					{
//						Value = m_Min;
//					}
//					else if (Value > m_Max)
//					{
//						Value = m_Max;
//					}
//					*m_pData = Value;
//				}
//				else
//				{
//					*m_pData = Value;
//				}
//				SetValue();
//				VSEValueProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (m_pSlider && pElem == m_pSlider)
//			{
//				int Value = *(int*)pValue;
//				*m_pData = ((T)(Value * m_fStep)) + m_Min;
//				SetValue();
//				VSEValueProperty::CallBackValue(pElem, pValue);
//			}
//
//			return false;
//		}
//
//	public:
//		VSESlider* m_pSlider;
//		VSEText* m_pText;
//		T m_fStep;
//		T m_Max;
//		T m_Min;
//		T* m_pData;
//	};
//#ifndef TYPE_ADD_TO_UI
//	class MATRIX_FUNCTION_API VSEIntProperty : public VSEValueProperty<int>
//	{
//	public:
//		VSEIntProperty(int* pData, Container::MString& Name, VSObject* pOwner, bool bRange, int Max, int Min, int Step)
//			: VSEValueProperty(pData, Name, pOwner, bRange, Max, Min, Step)
//		{
//			SetValue();
//		}
//		virtual ~VSEIntProperty()
//		{
//		}
//		virtual void GetValueString(Container::MString& IntString)
//		{
//			IntString = IntToString(*m_pData);
//		}
//		virtual int GetStringValue(Container::MString& IntString)
//		{
//			return StringToInt(IntString);
//		}
//	};
//	class MATRIX_FUNCTION_API VSEUnsignedIntProperty : public VSEValueProperty<unsigned int>
//	{
//	public:
//		VSEUnsignedIntProperty(unsigned int* pData, Container::MString& Name, VSObject* pOwner, bool bRange, unsigned int Max, unsigned int Min, unsigned int Step)
//			: VSEValueProperty(pData, Name, pOwner, bRange, Max, Min, Step)
//		{
//			SetValue();
//		}
//		virtual ~VSEUnsignedIntProperty()
//		{
//		}
//		virtual void GetValueString(Container::MString& IntString)
//		{
//			IntString = IntToString(*m_pData);
//		}
//		virtual unsigned int GetStringValue(Container::MString& IntString)
//		{
//			return StringToInt(IntString);
//		}
//	};
//	class MATRIX_FUNCTION_API VSEUnsignedCharProperty : public VSEValueProperty<unsigned char>
//	{
//	public:
//		VSEUnsignedCharProperty(unsigned char* pData, Container::MString& Name, VSObject* pOwner, bool bRange, unsigned char Max, unsigned char Min, unsigned char Step)
//			: VSEValueProperty(pData, Name, pOwner, bRange, Max, Min, Step)
//		{
//			SetValue();
//		}
//		virtual ~VSEUnsignedCharProperty()
//		{
//		}
//		virtual void GetValueString(Container::MString& IntString)
//		{
//			IntString = IntToString(*m_pData);
//		}
//		virtual unsigned char GetStringValue(Container::MString& IntString)
//		{
//			return StringToInt(IntString);
//		}
//	};
//	class MATRIX_FUNCTION_API VSECharProperty : public VSEValueProperty<TCHAR>
//	{
//	public:
//		VSECharProperty(TCHAR* pData, Container::MString& Name, VSObject* pOwner, bool bRange, TCHAR Max, TCHAR Min, TCHAR Step)
//			: VSEValueProperty(pData, Name, pOwner, bRange, Max, Min, Step)
//		{
//			SetValue();
//		}
//		virtual void GetValueString(Container::MString& IntString)
//		{
//			TCHAR tData[2];
//			tData[0] = *m_pData;
//			tData[1] = _T('\0');
//			Container::MString Temp(tData);
//			IntString = Temp;
//		}
//		virtual TCHAR GetStringValue(Container::MString& IntString)
//		{
//			return *IntString.GetBuffer();
//		}
//		virtual ~VSECharProperty()
//		{
//		}
//	};
//	class MATRIX_FUNCTION_API VSERealProperty : public VSEValueProperty<VSREAL>
//	{
//	public:
//		VSERealProperty(VSREAL* pData, Container::MString& Name, VSObject* pOwner, bool bRange, VSREAL Max, VSREAL Min, VSREAL Step)
//			: VSEValueProperty(pData, Name, pOwner, bRange, Max, Min, Step)
//		{
//			SetValue();
//		}
//		virtual ~VSERealProperty()
//		{
//		}
//		virtual void GetValueString(Container::MString& IntString)
//		{
//			IntString = RealToString(*m_pData);
//		}
//		virtual VSREAL GetStringValue(Container::MString& IntString)
//		{
//			return StringToReal(IntString);
//		}
//	};
//#endif
//	class MATRIX_FUNCTION_API VSEVector3Property : public VSEditorProperty
//	{
//	public:
//		VSEVector3Property(Math::Vector3* pVector3, Container::MString& Name, VSObject* pOwner, bool bRange, Math::Vector3 Max, Math::Vector3 Min, Math::Vector3 Step)
//			: VSEditorProperty(Name, pOwner)
//		{
//			MATRIX_ENGINE_ASSERT(pVector3 != NULL);
//
//			if (bRange)
//			{
//				if (Min.x > Max.x)
//				{
//					Swap(Max.x, Min.x);
//				}
//				if (Min.y > Max.y)
//				{
//					Swap(Max.y, Min.y);
//				}
//				if (Min.z > Max.z)
//				{
//					Swap(Max.z, Min.z);
//				}
//				MATRIX_ENGINE_ASSERT(Max.x - Min.x > Step.x);
//				MATRIX_ENGINE_ASSERT(Max.y - Min.y > Step.y);
//				MATRIX_ENGINE_ASSERT(Max.z - Min.z > Step.z);
//			}
//			m_pVector3 = pVector3;
//			m_fStep = Step;
//			m_Min = Min;
//			m_Max = Max;
//
//			m_pNameX = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "X");
//			m_pNameY = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "Y");
//			m_pNameZ = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "Z");
//
//			m_pTextX = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "X");
//			m_pTextX->SetOwner(this);
//
//			m_pTextY = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "Y");
//			m_pTextY->SetOwner(this);
//
//			m_pTextZ = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "Z");
//			m_pTextZ->SetOwner(this);
//
//			if (bRange)
//			{
//				m_pSliderX = (VSESlider*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_SLIDER, Name + "X");
//				m_pSliderX->SetOwner(this);
//				m_pSliderX->SetRange(0, int((Max.x - Min.x) / Step.x), 1);
//
//				m_pSliderZ = (VSESlider*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_SLIDER, Name + "Z");
//				m_pSliderZ->SetOwner(this);
//				m_pSliderZ->SetRange(0, int((Max.z - Min.z) / Step.z), 1);
//
//				m_pSliderY = (VSESlider*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_SLIDER, Name + "Y");
//				m_pSliderY->SetOwner(this);
//				m_pSliderY->SetRange(0, int((Max.y - Min.y) / Step.y), 1);
//			}
//			SetValue();
//		}
//		virtual void SetValue()
//		{
//			VSREAL fDataY = m_pVector3->y;
//			Container::MString RealStringY = RealToString(fDataY);
//			m_pTextY->SetValue((void*)&RealStringY);
//
//			VSREAL fDataX = m_pVector3->x;
//			Container::MString RealStringX = RealToString(fDataX);
//			m_pTextX->SetValue((void*)&RealStringX);
//
//			VSREAL fDataZ = m_pVector3->z;
//			Container::MString RealStringZ = RealToString(fDataZ);
//			m_pTextZ->SetValue((void*)&RealStringZ);
//		}
//		virtual ~VSEVector3Property()
//		{
//			ENGINE_DELETE(m_pTextX);
//			ENGINE_DELETE(m_pTextY);
//			ENGINE_DELETE(m_pTextZ);
//
//			ENGINE_DELETE(m_pSliderX);
//			ENGINE_DELETE(m_pSliderY);
//			ENGINE_DELETE(m_pSliderZ);
//
//			ENGINE_DELETE(m_pNameX);
//			ENGINE_DELETE(m_pNameY);
//			ENGINE_DELETE(m_pNameZ);
//		}
//		virtual bool CallBackValue(VSEditorSingle* pElem, void* pValue)
//		{
//
//			if (pElem == m_pTextX)
//			{
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL Value = StringToReal(Data);
//
//				if (m_pSliderX)
//				{
//					if (Value < m_Min.x)
//					{
//						Value = m_Min.x;
//					}
//					else if (Value > m_Max.x)
//					{
//						Value = m_Max.x;
//					}
//					m_pVector3->x = Value;
//				}
//				else
//				{
//					m_pVector3->x = Value;
//				}
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (pElem == m_pTextY)
//			{
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL Value = StringToReal(Data);
//
//				if (m_pSliderY)
//				{
//					if (Value < m_Min.y)
//					{
//						Value = m_Min.y;
//					}
//					else if (Value > m_Max.y)
//					{
//						Value = m_Max.y;
//					}
//					m_pVector3->y = Value;
//				}
//				else
//				{
//					m_pVector3->y = Value;
//				}
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (pElem == m_pTextZ)
//			{
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL Value = StringToReal(Data);
//
//				if (m_pSliderZ)
//				{
//					if (Value < m_Min.z)
//					{
//						Value = m_Min.z;
//					}
//					else if (Value > m_Max.z)
//					{
//						Value = m_Max.z;
//					}
//					m_pVector3->z = Value;
//				}
//				else
//				{
//					m_pVector3->z = Value;
//				}
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (m_pSliderX && pElem == m_pSliderX)
//			{
//				int Value = *(int*)pValue;
//				m_pVector3->x = ((VSREAL)(Value * m_fStep.x)) + m_Min.x;
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//			}
//			else if (m_pSliderY && pElem == m_pSliderY)
//			{
//				int Value = *(int*)pValue;
//				m_pVector3->y = ((VSREAL)(Value * m_fStep.y)) + m_Min.y;
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//			}
//			else if (m_pSliderZ && pElem == m_pSliderZ)
//			{
//				int Value = *(int*)pValue;
//				m_pVector3->z = ((VSREAL)(Value * m_fStep.z)) + m_Min.z;
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//			}
//			return false;
//		}
//
//	protected:
//		Math::Vector3 m_fStep;
//		VSELable* m_pNameX;
//		VSESlider* m_pSliderX;
//		VSEText* m_pTextX;
//
//		VSELable* m_pNameY;
//		VSESlider* m_pSliderY;
//		VSEText* m_pTextY;
//
//		VSELable* m_pNameZ;
//		VSESlider* m_pSliderZ;
//		VSEText* m_pTextZ;
//
//		Math::Vector3* m_pVector3;
//		Math::Vector3 m_Max;
//		Math::Vector3 m_Min;
//	};
//	class MATRIX_FUNCTION_API VSETransformProperty : public VSEditorProperty // no range so no slider
//	{
//	public:
//		VSETransformProperty(VSTransform* pTransform, Container::MString& Name, VSObject* pOwner)
//			: VSEditorProperty(Name, pOwner)
//		{
//			m_pTransform = pTransform;
//
//			m_pTranslateName = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "Translate");
//			m_pRotationName = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "Rotation");
//			m_pScaleName = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "Scale");
//
//			m_pTranslateNameX = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "X");
//			m_pTranslateNameY = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "Y");
//			m_pTranslateNameZ = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "Z");
//
//			m_pRotationNameX = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "X");
//			m_pRotationNameY = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "Y");
//			m_pRotationNameZ = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "Z");
//
//			m_pScaleNameX = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "X");
//			m_pScaleNameY = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "Y");
//			m_pScaleNameZ = (VSELable*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_LABLE, "Z");
//
//			m_pTranslateTextX = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "TranslateX");
//			m_pTranslateTextX->SetOwner(this);
//
//			m_pTranslateTextY = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "TranslateY");
//			m_pTranslateTextY->SetOwner(this);
//
//			m_pTranslateTextZ = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "TranslateZ");
//			m_pTranslateTextZ->SetOwner(this);
//
//			m_pRotationTextX = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "RotationX");
//			m_pRotationTextX->SetOwner(this);
//
//			m_pRotationTextZ = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "RotationY");
//			m_pRotationTextZ->SetOwner(this);
//
//			m_pRotationTextY = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "RotationZ");
//			m_pRotationTextY->SetOwner(this);
//
//			m_pScaleTextX = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "ScaleX");
//			m_pScaleTextX->SetOwner(this);
//
//			m_pScaleTextY = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "ScaleX");
//			m_pScaleTextY->SetOwner(this);
//
//			m_pScaleTextZ = (VSEText*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_TEXT, Name + "ScaleX");
//			m_pScaleTextZ->SetOwner(this);
//			SetValue();
//		}
//		virtual void SetValue()
//		{
//			Math::Vector3 Tran = m_pTransform->GetTranslate();
//			VSREAL fTranDataX = Tran.x;
//			Container::MString RealStringTranX = RealToString(fTranDataX);
//			m_pTranslateTextX->SetValue((void*)&RealStringTranX);
//
//			VSREAL fTranDataY = Tran.y;
//			Container::MString RealStringTranY = RealToString(fTranDataY);
//			m_pTranslateTextY->SetValue((void*)&RealStringTranY);
//
//			VSREAL fTranDataZ = Tran.z;
//			Container::MString RealStringTranZ = RealToString(fTranDataZ);
//			m_pTranslateTextZ->SetValue((void*)&RealStringTranZ);
//
//			VSMatrix3X3 Mat = m_pTransform->GetRotate();
//			VSREAL X, Y, Z;
//			Mat.GetEuler(Z, X, Y);
//			;
//
//			Container::MString RealStringRotateX = RealToString(X);
//			m_pRotationTextX->SetValue((void*)&RealStringRotateX);
//
//			Container::MString RealStringRotateY = RealToString(Y);
//			m_pRotationTextY->SetValue((void*)&RealStringRotateY);
//
//			Container::MString RealStringRotateZ = RealToString(Z);
//			m_pRotationTextZ->SetValue((void*)&RealStringRotateZ);
//
//			Math::Vector3 Scale = m_pTransform->GetScale();
//
//			VSREAL fScaleDataX = Scale.x;
//			Container::MString RealStringScaleX = RealToString(fScaleDataX);
//			m_pScaleTextX->SetValue((void*)&RealStringScaleX);
//
//			VSREAL fScaleDataY = Scale.y;
//			Container::MString RealStringScaleY = RealToString(fScaleDataY);
//			m_pScaleTextY->SetValue((void*)&RealStringScaleY);
//
//			VSREAL fScaleDataZ = Scale.z;
//			Container::MString RealStringScaleZ = RealToString(fScaleDataZ);
//			m_pScaleTextZ->SetValue((void*)&RealStringScaleZ);
//		}
//		virtual ~VSETransformProperty()
//		{
//			ENGINE_DELETE(m_pTranslateTextX);
//			ENGINE_DELETE(m_pTranslateTextY);
//			ENGINE_DELETE(m_pTranslateTextZ);
//
//			ENGINE_DELETE(m_pRotationTextX);
//			ENGINE_DELETE(m_pRotationTextY);
//			ENGINE_DELETE(m_pRotationTextZ);
//
//			ENGINE_DELETE(m_pScaleTextX);
//			ENGINE_DELETE(m_pScaleTextY);
//			ENGINE_DELETE(m_pScaleTextZ);
//
//			ENGINE_DELETE(m_pTranslateName);
//			ENGINE_DELETE(m_pRotationName);
//			ENGINE_DELETE(m_pScaleName);
//
//			ENGINE_DELETE(m_pTranslateNameX);
//			ENGINE_DELETE(m_pTranslateNameY);
//			ENGINE_DELETE(m_pTranslateNameZ);
//
//			ENGINE_DELETE(m_pRotationNameX);
//			ENGINE_DELETE(m_pRotationNameY);
//			ENGINE_DELETE(m_pRotationNameZ);
//
//			ENGINE_DELETE(m_pScaleNameX);
//			ENGINE_DELETE(m_pScaleNameY);
//			ENGINE_DELETE(m_pScaleNameZ);
//		}
//		virtual bool CallBackValue(VSEditorSingle* pElem, void* pValue)
//		{
//			if (pElem == m_pTranslateTextX)
//			{
//				Math::Vector3 Tran = m_pTransform->GetTranslate();
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL fData = StringToReal(Data);
//				Math::Vector3 NewTran(fData, Tran.y, Tran.z);
//				m_pTransform->SetTranslate(NewTran);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (pElem == m_pTranslateTextY)
//			{
//				Math::Vector3 Tran = m_pTransform->GetTranslate();
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL fData = StringToReal(Data);
//				Math::Vector3 NewTran(Tran.x, fData, Tran.z);
//				m_pTransform->SetTranslate(NewTran);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (pElem == m_pTranslateTextZ)
//			{
//				Math::Vector3 Tran = m_pTransform->GetTranslate();
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL fData = StringToReal(Data);
//				Math::Vector3 NewTran(Tran.x, Tran.y, fData);
//				m_pTransform->SetTranslate(NewTran);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (pElem == m_pRotationTextX)
//			{
//				VSMatrix3X3 Mat = m_pTransform->GetRotate();
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL fData = StringToReal(Data);
//				VSREAL X, Y, Z;
//				Mat.GetEuler(Z, X, Y);
//				Mat.CreateEuler(Z, fData, Y);
//				m_pTransform->SetRotate(Mat);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (pElem == m_pRotationTextY)
//			{
//				VSMatrix3X3 Mat = m_pTransform->GetRotate();
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL fData = StringToReal(Data);
//				VSREAL X, Y, Z;
//				Mat.GetEuler(Z, X, Y);
//				Mat.CreateEuler(Z, X, fData);
//				m_pTransform->SetRotate(Mat);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (pElem == m_pRotationTextZ)
//			{
//				VSMatrix3X3 Mat = m_pTransform->GetRotate();
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL fData = StringToReal(Data);
//				VSREAL X, Y, Z;
//				Mat.GetEuler(Z, X, Y);
//				Mat.CreateEuler(fData, X, Y);
//				m_pTransform->SetRotate(Mat);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (pElem == m_pScaleTextX)
//			{
//				Math::Vector3 Scale = m_pTransform->GetScale();
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL fData = StringToReal(Data);
//				Math::Vector3 NewScale(fData, Scale.y, Scale.z);
//				m_pTransform->SetScale(NewScale);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (pElem == m_pScaleTextY)
//			{
//				Math::Vector3 Scale = m_pTransform->GetScale();
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL fData = StringToReal(Data);
//				Math::Vector3 NewScale(Scale.x, fData, Scale.z);
//				m_pTransform->SetScale(NewScale);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//			else if (pElem == m_pScaleTextZ)
//			{
//				Math::Vector3 Scale = m_pTransform->GetScale();
//				Container::MString Data = *(Container::MString*)pValue;
//				VSREAL fData = StringToReal(Data);
//				Math::Vector3 NewScale(Scale.x, Scale.y, fData);
//				m_pTransform->SetScale(NewScale);
//				SetValue();
//				VSEditorProperty::CallBackValue(pElem, pValue);
//				return true;
//			}
//
//			return false;
//		}
//
//	protected:
//		VSTransform* m_pTransform;
//		VSELable* m_pTranslateName;
//
//		VSELable* m_pTranslateNameX;
//		VSEText* m_pTranslateTextX;
//
//		VSELable* m_pTranslateNameY;
//		VSEText* m_pTranslateTextY;
//
//		VSELable* m_pTranslateNameZ;
//		VSEText* m_pTranslateTextZ;
//
//		VSELable* m_pRotationName;
//
//		VSELable* m_pRotationNameX;
//		VSEText* m_pRotationTextX;
//
//		VSELable* m_pRotationNameY;
//		VSEText* m_pRotationTextY;
//
//		VSELable* m_pRotationNameZ;
//		VSEText* m_pRotationTextZ;
//
//		VSELable* m_pScaleName;
//
//		VSELable* m_pScaleNameX;
//		VSEText* m_pScaleTextX;
//
//		VSELable* m_pScaleNameY;
//		VSEText* m_pScaleTextY;
//
//		VSELable* m_pScaleNameZ;
//		VSEText* m_pScaleTextZ;
//	};
//	class MATRIX_FUNCTION_API VSENoDefineProperty : public VSEditorProperty
//	{
//	public:
//		VSENoDefineProperty()
//			: VSEditorProperty(Container::MString::ms_StringNULL, NULL)
//		{
//		}
//		virtual ~VSENoDefineProperty()
//		{
//		}
//	};
//	template <typename T>
//	VSEditorElement* CreateEElement(T& Value, Container::MString& Name, VSObject* pOwner, bool bRange, T& Max, T& Min, T& fStep)
//	{
//		MATRIX_ENGINE_ASSERT(0);
//		return NULL;
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<Math::Vector3>(Math::Vector3& Value, Container::MString& Name, VSObject* pOwner, bool bRange, Math::Vector3& Max, Math::Vector3& Min, Math::Vector3& fStep)
//	{
//		return MX_NEW VSEVector3Property(&Value, Name, pOwner, bRange, Max, Min, fStep);
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<bool>(bool& Value, Container::MString& Name, VSObject* pOwner, bool bRange, bool& Max, bool& Min, bool& fStep)
//	{
//		return MX_NEW VSEBoolProperty(&Value, Name, pOwner);
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<VSTransform>(VSTransform& Value, Container::MString& Name, VSObject* pOwner, bool bRange, VSTransform& Max, VSTransform& Min, VSTransform& fStep)
//	{
//		return MX_NEW VSETransformProperty(&Value, Name, pOwner);
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<Math::ColorRGBA>(Math::ColorRGBA& Value, Container::MString& Name, VSObject* pOwner, bool bRange, Math::ColorRGBA& Max, Math::ColorRGBA& Min, Math::ColorRGBA& fStep)
//	{
//		return MX_NEW VSEColorProperty(&Value, Name, pOwner);
//	}
//#ifdef TYPE_ADD_TO_UI
//	template <>
//	inline VSEditorElement* CreateEElement<unsigned int>(unsigned int& Value, Container::MString& Name, VSObject* pOwner, bool bRange, unsigned int& Max, unsigned int& Min, unsigned int& fStep)
//	{
//		return MX_NEW VSValueProperty<unsigned int>(&Value, Name, pOwner, bRange, Max, Min, fStep);
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<int>(int& Value, Container::MString& Name, VSObject* pOwner, bool bRange, int& Max, int& Min, int& fStep)
//	{
//		return MX_NEW VSValueProperty<int>(&Value, Name, pOwner, bRange, Max, Min, fStep);
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<unsigned char>(unsigned char& Value, Container::MString& Name, VSObject* pOwner, bool bRange, unsigned char& Max, unsigned char& Min, unsigned char& fStep)
//	{
//		return MX_NEW VSValueProperty<unsigned char>(&Value, Name, pOwner, bRange, Max, Min, fStep);
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<TCHAR>(TCHAR& Value, Container::MString& Name, VSObject* pOwner, bool bRange, TCHAR& Max, TCHAR& Min, TCHAR& fStep)
//	{
//		return MX_NEW VSValueProperty<TCHAR>(&Value, Name, pOwner, bRange, Max, Min, fStep);
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<VSREAL>(VSREAL& Value, Container::MString& Name, VSObject* pOwner, bool bRange, VSREAL& Max, VSREAL& Min, VSREAL& fStep)
//	{
//		return MX_NEW VSValueProperty<VSREAL>(&Value, Name, pOwner, bRange, Max, Min, fStep);
//	}
//#else
//	template <>
//	inline VSEditorElement* CreateEElement<unsigned int>(unsigned int& Value, Container::MString& Name, VSObject* pOwner, bool bRange, unsigned int& Max, unsigned int& Min, unsigned int& fStep)
//	{
//		return MX_NEW VSEUnsignedIntProperty(&Value, Name, pOwner, bRange, Max, Min, fStep);
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<int>(int& Value, Container::MString& Name, VSObject* pOwner, bool bRange, int& Max, int& Min, int& fStep)
//	{
//		return MX_NEW VSEIntProperty(&Value, Name, pOwner, bRange, Max, Min, fStep);
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<unsigned char>(unsigned char& Value, Container::MString& Name, VSObject* pOwner, bool bRange, unsigned char& Max, unsigned char& Min, unsigned char& fStep)
//	{
//		return MX_NEW VSEUnsignedCharProperty(&Value, Name, pOwner, bRange, Max, Min, fStep);
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<TCHAR>(TCHAR& Value, Container::MString& Name, VSObject* pOwner, bool bRange, TCHAR& Max, TCHAR& Min, TCHAR& fStep)
//	{
//		return MX_NEW VSECharProperty(&Value, Name, pOwner, bRange, Max, Min, fStep);
//	}
//	template <>
//	inline VSEditorElement* CreateEElement<VSREAL>(VSREAL& Value, Container::MString& Name, VSObject* pOwner, bool bRange, VSREAL& Max, VSREAL& Min, VSREAL& fStep)
//	{
//		return MX_NEW VSERealProperty(&Value, Name, pOwner, bRange, Max, Min, fStep);
//	}
//#endif
//	/*to else
//	---------------------------------------------------
//	*/
//	MATRIX_FUNCTION_API VSEditorElement* CreateObjectEditorElement(VSObject* pObject, Container::MString& Name);
//	MATRIX_FUNCTION_API void ReleaseObjectEditorElement(VSECollection* Root);
//	template <typename T>
//	void CreateEditorElement(T& Value, VSObject* pOwner, VSECollection* pParent, Container::MString& Name, bool Range = false, T Max = T(), T Min = T(), T fStep = T())
//	{
//		if (TIsVSResourceProxyPointerType<T>::Value)
//		{
//			VSResourceProxyBasePtr& Temp = *(VSResourceProxyBasePtr*)(void*)&Value;
//			VSEResourceProperty* pEp = MX_NEW VSEResourceProperty(Temp, Name, pOwner);
//			pParent->AddElement(pEp);
//		}
//		else if (TIsVSPointerType<T>::Value)
//		{
//			VSObject*& TempSrc = *(VSObject**)(void*)&Value;
//			VSEditorElement* pEp = CreateObjectEditorElement(TempSrc, Name);
//			pParent->AddElement(pEp);
//		}
//		else if (TIsVSType<T>::Value)
//		{
//			VSObject* TempSrc = (VSObject*)&Value;
//			VSEditorElement* pEp = CreateObjectEditorElement(TempSrc, Name);
//			pParent->AddElement(pEp);
//		}
//		else if (TIsVSSmartPointerType<T>::Value)
//		{
//			VSObjectPtr& TempSrc = *(VSObjectPtr*)(void*)&Value;
//			VSEditorElement* pEp = CreateObjectEditorElement(TempSrc, Name);
//			pParent->AddElement(pEp);
//		}
//		else if (TIsCustomType<T>::Value)
//		{
//			VSCustomArchiveObject* TempSrc = (VSCustomArchiveObject*)(void*)&Value;
//			VSEditorElement* pEp = TempSrc->CreateEElement(Name, pOwner);
//			pParent->AddElement(pEp);
//		}
//		else if (TIsVSEnumType<T>::Value)
//		{
//		}
//		else
//		{
//			VSEditorElement* pEp = CreateEElement(Value, Name, pOwner, Range, Max, Min, fStep);
//			pParent->AddElement(pEp);
//		}
//	}
//	template <typename T, class VSMemManagerClass>
//	void CreateEditorElement(Container::MArray<T, VSMemManagerClass>& Value, VSObject* pOwner, VSECollection* pParent, Container::MString& Name, bool Range = false, T Max = T(), T Min = T(), T fStep = T())
//	{
//		VSECollection* pEc = NULL;
//		if (Value.GetNum() > 0)
//		{
//			pEc = (VSECollection*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_COLLECTION, Name);
//			pParent->AddElement(pEc);
//		}
//		for (unsigned int i = 0; i < Value.GetNum(); i++)
//		{
//			Container::MString NewName = Name + IntToString(i);
//			CreateEditorElement(Value[i], pOwner, pEc, NewName, Range, Max, Min, fStep);
//		}
//	}
//
//	template <class Key, class T, class VSMemManagerClass>
//	void CreateEditorElement(Container::MMap<Key, T, VSMemManagerClass>& Value, VSObject* pOwner, VSECollection* pParent, Container::MString& Name, bool Range = false, T Max = T(), T Min = T(), T fStep = T())
//	{
//		VSECollection* pEc = NULL;
//		if (Value.GetNum() > 0)
//		{
//			pEc = (VSECollection*)CREATE_UI_PROPERTY(VSEditorSingle::CUT_COLLECTION, Name);
//			pParent->AddElement(pEc);
//		}
//		for (unsigned int i = 0; i < Value.GetNum(); i++)
//		{
//			Container::MString NewNameKey = Name + _T(" Key");
//			Container::MString NewNameValue = Name + _T(" Value");
//			Container::MapElement<Key, T>& ElementDest = Value[i];
//			CreateEditorElement(ElementDest.Key, pOwner, pEc, NewNameKey);
//			CreateEditorElement(ElementDest.Value, pOwner, pEc, NewNameValue, Range, Max, Min, fStep);
//		}
//	}
//
//}
