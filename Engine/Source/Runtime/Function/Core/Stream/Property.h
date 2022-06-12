#pragma once
#include "Core/Rtti.h"
//#include "Stream/PropertyMarco.h"

#include "PropertyMarco.h"
#include "Core/ObjName.h"
#include "Type.h"
#include "Stream.h"
#include "EditorProperty.h"
#include "EnumTrans.h"

#include "Platform/Core.h"
#include "Container/Array.h "
#include "Container/Map.h"

namespace Matrix
{

    template <class T>
    inline bool operator<(const T &v1, const T &v2)
    {
        return false;
    }
    template <class T>
    inline bool operator>(const T &v1, const T &v2)
    {
        return false;
    }
    class VSFunction;
    // Value Point Resource Struct Enum
    //���Է��䣨property reflection������Ҫ���������������Ϣ�ռ�����,��ʵ���ǽ���������Ϣ�ռ�
    //���ռ���������Ϣ��ŵ�RTTI�У�Ҳ���������½�������š���ʵ������Ŀ����ʵ�����л��洢��UI�󶨡�
    // PT_ENUM ��ʾö�����ͣ����� UI �󶨵�ʱ��������ͬ��Ҫ��ö�������ѡ���г�����
    // PT_DATA ָ���Ǵ�����ݵ�ָ�룬Ҳ����˵�����ָ��ָ��һ���ڴ����ݣ��������л��洢�������漰 UI �󶨡�
    //�� PT_ARRAY��PT_MAP ���г�������Ϊ�����������������ڲ����ݵĽӿڲ�����ͬ��
    // PT_VALUE ���ʾ������ 4 ��֮��������������͡�
    class VSProperty
    {
    public:
        enum // Property Type
        {
            PT_VALUE, //��ʾ���� 5 ��֮���������������
            PT_ENUM,  //��ʾö������
            PT_DATA,  //ָ���Ǵ�����ݵ�ָ��
            PT_ARRAY, //�������г�������Ϊ�����������������ڲ����ݵĽӿڲ�����ͬ��
            PT_MAP,   //�������г�������Ϊ�����������������ڲ����ݵĽӿڲ�����ͬ��
            PT_MAX
        };
        // Flag ��ʾ���������ʲô����
        enum // Flag
        {
            F_NONE = 0X00,
            F_SAVE_LOAD = 0X01,
            F_CLONE = 0X02,
            F_COPY = 0X04,
            F_SAVE_LOAD_CLONE = 0X03,
            F_SAVE_LOAD_COPY = 0X05,
            F_REFLECT_NAME = 0X08,
            F_NO_USE_GC = 0X10,
            F_MAX
        };
        VSProperty()
        {
            m_pRttiOwner = NULL;
            m_pFunctionOwner = NULL;
            m_uiFlag = 0;
            m_uiElementOffset = 0;
        }
        VSProperty(VSRtti &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiFlag)
            : m_pRttiOwner(&Owner)
        {
            m_Name = Name;
            m_uiElementOffset = uiElementOffset;
            m_uiFlag = uiFlag;
            m_pFunctionOwner = NULL;
        }
        VSProperty(VSFunction &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiFlag)
            : m_pFunctionOwner(&Owner)
        {
            m_Name = Name;
            m_uiElementOffset = uiElementOffset;
            m_uiFlag = uiFlag;
            m_pRttiOwner = NULL;
        }
        virtual ~VSProperty()
        {
        }
        virtual unsigned int GetPropertyType() const = 0;
        inline VSRtti *GetRtti() const
        {
            return m_pRttiOwner;
        }
        inline VSFunction *GetFunction() const
        {
            return m_pFunctionOwner;
        }
        inline const VSUsedName &GetName() const
        {
            return m_Name;
        }
        virtual void *GetValueAddress(void *pObj) const
        {
            return (void *)(((unsigned char *)pObj) + m_uiElementOffset);
        }
        virtual bool Archive(MStream &Stream, void *pObj) = 0;
        virtual VSProperty *GetInstance() = 0;
        virtual void CloneData(void *pSrcObj, void *pDestObj, Container::MMap<MObject *, MObject *> &CloneMap) = 0;
        virtual void CopyData(void *pSrcObj, void *pDestObj) = 0;
        // todo editor property
        // virtual void AddEditorElement(void* pSrcObj, VSECollection* pParent, Container::MString& Name) = 0;
        virtual bool Clone(VSProperty *p)
        {
            if ((p->GetRtti() == GetRtti() && GetRtti()) || (p->GetFunction() == GetFunction() && GetFunction()))
            {
                m_Name = p->m_Name;
                m_uiFlag = p->m_uiFlag;
                m_uiElementOffset = p->m_uiElementOffset;
                return true;
            }

            return false;
        }
        void SetOwner(VSRtti &Owner)
        {
            m_pRttiOwner = &Owner;
        }
        void SetOwner(VSFunction &Function)
        {
            m_pFunctionOwner = &Function;
        }
        unsigned int GetFlag() const
        {
            return m_uiFlag;
        }
        void SetFlag(unsigned int uiFlag)
        {
            m_uiFlag = uiFlag;
        }

    protected:
        // propertyҪô����ĳ��rttiҪô����function�ġ�
        VSRtti *m_pRttiOwner;
        VSFunction *m_pFunctionOwner;
        VSUsedName m_Name;
        unsigned int m_uiFlag;
        unsigned int m_uiElementOffset; //��owner�ṹ��Ԫ����Ե�ƫ����
    };
    template <typename T>
    class VSEnumProperty : public VSProperty
    {
    public:
        VSEnumProperty()
        {
            MATRIX_ENGINE_ASSERT(sizeof(T) == 4);
        }
        VSEnumProperty(VSRtti &Owner, const VSUsedName &Name, const VSUsedName &EnumName, unsigned int uiElementOffset, unsigned int uiFlag)
            : VSProperty(Owner, Name, uiElementOffset, uiFlag)
        {
            MATRIX_ENGINE_ASSERT(sizeof(T) == 4);
            m_EnumName = EnumName;
        }
        VSEnumProperty(VSFunction &Owner, const VSUsedName &Name, const VSUsedName &EnumName, unsigned int uiElementOffset, unsigned int uiFlag)
            : VSProperty(Owner, Name, uiElementOffset, uiFlag)
        {
            MATRIX_ENGINE_ASSERT(sizeof(T) == 4);
            m_EnumName = EnumName;
        }
        virtual ~VSEnumProperty()
        {
        }
        virtual bool Clone(VSProperty *p)
        {
            VSEnumProperty *Temp = (VSEnumProperty *)p;
            if (!VSProperty::Clone(Temp))
                return false;
            m_EnumName = Temp->m_EnumName;
            return true;
        }
        virtual bool SetValue(void *pObj, unsigned int &pDataSrc) const
        {

            *(unsigned int *)(((unsigned char *)pObj) + m_uiElementOffset) = pDataSrc;
            return true;
        }
        virtual bool GetValue(void *pObj, unsigned int &pDataDest) const
        {
            pDataDest = *(unsigned int *)(((unsigned char *)pObj) + m_uiElementOffset);
            return true;
        }
        virtual bool GetValue(const void *pObj, unsigned int &pDataDest) const
        {
            pDataDest = *(const unsigned int *)(((const char *)pObj) + m_uiElementOffset);
            return true;
        }
        virtual unsigned int &Value(void *pObj) const
        {
            return *(unsigned int *)(((const char *)pObj) + m_uiElementOffset);
        }
        virtual bool Archive(MStream &Stream, void *pObj)
        {
            Stream.Archive(Value(pObj));
            return true;
        }
        virtual void CloneData(void *pSrcObj, void *pDestObj, Container::MMap<MObject *, MObject *> &CloneMap)
        {
            Value(pDestObj) = Value(pSrcObj);
        }
        virtual void CopyData(void *pSrcObj, void *pDestObj)
        {
            Value(pDestObj) = Value(pSrcObj);
        }
        // todo editor property
        // virtual void AddEditorElement(void* pSrcObj, VSECollection* pParent, Container::MString& Name)
        //{
        //	VSEEnumProperty* pEp = MX_NEW VSEEnumProperty((unsigned int*)(((const char*)pSrcObj) + m_uiElementOffset), Name, (MObject*)pSrcObj);
        //	pParent->AddElement(pEp);
        //	Container::MArray<Container::MString> AS;
        //	Container::MString EnumName = m_EnumName.GetString();
        //	GET_ENUMARRAY(EnumName, AS);
        //	pEp->AddEnumString(AS);
        // }
        virtual VSProperty *GetInstance()
        {
            return MX_NEW VSEnumProperty();
        }
        VSUsedName &GetEnumName()
        {
            return m_EnumName;
        }
        virtual unsigned int GetPropertyType() const
        {
            return PT_ENUM;
        }

    protected:
        VSUsedName m_EnumName;
    };

    // VSDataProperty���洢���ݵģ����Դ洢�̶����ȵĺͲ������ȵ����ݡ�
    // m_uiDataNum ���� 0����ô��ʹ�ù̶����ȵ����ݣ�m_bDynamicCreate ������ʾ���ݻ����Ƿ�̬������
    //��� m_uiDataNum �� 0����ô��ʹ�ò������ȵ����ݣ��û���Ҫ������������ʾ������ȵ����ԣ�m_uiNumElementOffset ���ʾ������Ե�ƫ����
    template <typename T, typename CountType>
    class VSDataProperty : public VSProperty
    {
    public:
        VSDataProperty(VSRtti &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiDataNum, bool bDynamicCreate)
            : VSProperty(Owner, Name, uiElementOffset, F_SAVE_LOAD_CLONE | F_NO_USE_GC)
        {
            m_uiDataNum = uiDataNum;
            m_bDynamicCreate = bDynamicCreate;
        }
        VSDataProperty(VSFunction &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiDataNum, bool bDynamicCreate)
            : VSProperty(Owner, Name, uiElementOffset, F_SAVE_LOAD_CLONE | F_NO_USE_GC)
        {
            m_uiDataNum = uiDataNum;
            m_bDynamicCreate = bDynamicCreate;
        }
        VSDataProperty()
        {
        }
        VSDataProperty(VSRtti &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiNumElementOffset)
            : VSProperty(Owner, Name, uiElementOffset, F_SAVE_LOAD_CLONE | F_NO_USE_GC)
        {
            m_uiDataNum = 0;
            m_bDynamicCreate = true;
            m_uiNumElementOffset = uiNumElementOffset;
        }
        virtual unsigned int GetPropertyType() const
        {
            return PT_DATA;
        }
        // todo editor property
        // virtual void AddEditorElement(void* pSrcObj, VSECollection* pParent, Container::MString& Name)
        //{
        //	return;
        // }
        virtual void CopyData(void *pSrcObj, void *pDestObj)
        {
            MATRIX_ENGINE_ASSERT(0);
        }
        virtual void CloneData(void *pSrcObj, void *pDestObj, Container::MMap<MObject *, MObject *> &CloneMap)
        {
            T *SrcValueAddres = *(T **)GetValueAddress(pSrcObj);

            if (m_uiDataNum > 0)
            {
                T **Temp = (T **)GetValueAddress(pDestObj);
                if (m_bDynamicCreate)
                {
                    *Temp = MX_NEW T[m_uiDataNum];
                    Core::MXMemcpy((void *)(*Temp), (void *)SrcValueAddres, m_uiDataNum * sizeof(T));
                }
                else
                {
                    Core::MXMemcpy((void *)(*Temp), (void *)SrcValueAddres, m_uiDataNum * sizeof(T));
                }
            }
            else
            {
                T **Temp = (T **)GetValueAddress(pDestObj);

                void *SrcNumOffset = (void *)(((unsigned char *)pSrcObj) + m_uiNumElementOffset);
                void *DestNumOffset = (void *)(((unsigned char *)pDestObj) + m_uiNumElementOffset);
                *(CountType *)DestNumOffset = *(CountType *)SrcNumOffset;
                CountType uiNum = *(CountType *)SrcNumOffset;

                *Temp = MX_NEW T[uiNum];
                Core::MXMemcpy((void *)(*Temp), (void *)SrcValueAddres, uiNum * sizeof(T));
            }
        }
        virtual bool Archive(MStream &Stream, void *pObj)
        {
            unsigned int uiStreamFlag = Stream.GetStreamFlag();
            if (uiStreamFlag == MStream::AT_SAVE)
            {
                T *ValueAddres = *(T **)GetValueAddress(pObj);

                if (m_uiDataNum > 0)
                {
                    Stream.Write(ValueAddres, m_uiDataNum * sizeof(T));
                }
                else
                {
                    void *NumOffset = (void *)(((unsigned char *)pObj) + m_uiNumElementOffset);
                    CountType uiNum = *(CountType *)NumOffset;
                    Stream.Write(NumOffset, sizeof(CountType));
                    Stream.Write(ValueAddres, uiNum * sizeof(T));
                }
            }
            else if (uiStreamFlag == MStream::AT_LOAD)
            {
                // dataProperty��ָ�����ݣ�
                T **Temp = (T **)GetValueAddress(pObj);
                if (m_uiDataNum > 0)
                {
                    if (m_bDynamicCreate)
                    {
                        *Temp = MX_NEW T[m_uiDataNum];
                        Stream.Read((void *)(*Temp), m_uiDataNum * sizeof(T));
                    }
                    else
                    {
                        Stream.Read((void *)(*Temp), m_uiDataNum * sizeof(T));
                    }
                }
                else
                {
                    void *NumOffset = (void *)(((unsigned char *)pObj) + m_uiNumElementOffset);
                    Stream.Read(NumOffset, sizeof(CountType));
                    CountType uiNum = *(CountType *)NumOffset;
                    if (uiNum)
                    {
                        *Temp = MX_NEW T[uiNum];
                        Stream.Read((void *)(*Temp), uiNum * sizeof(T));
                    }
                }
            }
            else if (uiStreamFlag == MStream::AT_SIZE)
            {
                if (m_uiDataNum > 0)
                {
                    Stream.AddBufferSize(m_uiDataNum * sizeof(T));
                }
                else
                {
                    void *NumOffset = (void *)(((unsigned char *)pObj) + m_uiNumElementOffset);
                    CountType uiNum = *(CountType *)NumOffset;
                    Stream.AddBufferSize(sizeof(CountType));
                    Stream.AddBufferSize(uiNum * sizeof(T));
                }
            }
            return true;
        }
        virtual VSProperty *GetInstance()
        {
            return MX_NEW VSDataProperty<T, CountType>();
        }
        virtual bool Clone(VSProperty *p)
        {
            VSDataProperty<T, CountType> *Temp = (VSDataProperty<T, CountType> *)p;
            if (!VSProperty::Clone(Temp))
                return false;
            m_bDynamicCreate = Temp->m_bDynamicCreate;
            m_uiDataNum = Temp->m_uiDataNum;
            m_uiNumElementOffset = Temp->m_uiNumElementOffset;
            return true;
        }

    protected:
        bool m_bDynamicCreate;    //�Ƿ��Ƕ�̬����
        unsigned int m_uiDataNum; // data������
        unsigned int m_uiNumElementOffset;
    };

    template <typename T>
    class VSValueBaseProperty : public VSProperty
    {
    public:
        VSValueBaseProperty()
        {
        }
        VSValueBaseProperty(VSRtti &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiFlag, bool Range = false, T HighValue = T(), T LowValue = T(), T fStep = T())
            : VSProperty(Owner, Name, uiElementOffset, uiFlag)
        {
            m_LowValue = LowValue;
            m_HightValue = HighValue;
            m_fStep = fStep;
            m_bRange = Range;
        }
        VSValueBaseProperty(VSFunction &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiFlag, bool Range = false, T HighValue = T(), T LowValue = T(), T fStep = T())
            : VSProperty(Owner, Name, uiElementOffset, uiFlag)
        {
            m_LowValue = LowValue;
            m_HightValue = HighValue;
            m_fStep = fStep;
            m_bRange = Range;
        }
        virtual ~VSValueBaseProperty()
        {
        }
        virtual bool Clone(VSProperty *p)
        {
            VSValueBaseProperty<T> *Temp = (VSValueBaseProperty<T> *)p;
            if (!VSProperty::Clone(Temp))
                return false;
            m_LowValue = Temp->m_LowValue;
            m_HightValue = Temp->m_HightValue;
            return true;
        }

    protected:
        T m_LowValue;
        T m_HightValue;
        T m_fStep;
        bool m_bRange;
    };
    template <typename T>
    class VSValueProperty : public VSValueBaseProperty<T>
    {
    public:
        VSValueProperty()
        {
        }
        VSValueProperty(VSRtti &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiFlag, bool Range = false, T HighValue = T(), T LowValue = T(), T fStep = T())
            : VSValueBaseProperty(Owner, Name, uiElementOffset, uiFlag, Range, HighValue, LowValue, fStep)
        {
        }
        VSValueProperty(VSFunction &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiFlag, bool Range = false, T HighValue = T(), T LowValue = T(), T fStep = T())
            : VSValueBaseProperty(Owner, Name, uiElementOffset, uiFlag, Range, HighValue, LowValue, fStep)
        {
        }
        virtual ~VSValueProperty()
        {
        }
        virtual unsigned int GetPropertyType() const
        {
            return PT_VALUE;
        }
        virtual bool SetValue(void *pObj, T &pDataSrc) const
        {

            if (pDataSrc > m_HightValue || pDataSrc < m_LowValue)
            {
                return false;
            }

            *(T *)(((unsigned char *)pObj) + m_uiElementOffset) = pDataSrc;
            return true;
        }
        virtual bool GetValue(void *pObj, T &pDataDest) const
        {
            pDataDest = *(T *)(((unsigned char *)pObj) + m_uiElementOffset);
            return true;
        }
        virtual bool GetValue(const void *pObj, T &pDataDest) const
        {
            pDataDest = *(const T *)(((const char *)pObj) + m_uiElementOffset);
            return true;
        }
        virtual T &Value(void *pObj) const
        {
            return *(T *)(((const char *)pObj) + m_uiElementOffset);
        }
        virtual bool Archive(MStream &Stream, void *pObj)
        {
            Stream.Archive(Value(pObj));
            return true;
        }
        virtual void CloneData(void *pSrcObj, void *pDestObj, Container::MMap<MObject *, MObject *> &CloneMap)
        {
            Copy(Value(pDestObj), Value(pSrcObj), CloneMap);
        }
        virtual void CopyData(void *pSrcObj, void *pDestObj)
        {
            Value(pDestObj) = Value(pSrcObj);
        }
        // virtual void AddEditorElement(void* pSrcObj, VSECollection* pParent, Container::MString& Name)
        //{
        //	CreateEditorElement(Value(pSrcObj), (MObject*)pSrcObj, pParent, Name, m_bRange, m_HightValue, m_LowValue, m_fStep);
        // }
        virtual VSProperty *GetInstance()
        {
            return MX_NEW VSValueProperty<T>();
        }
    };

    template <typename ArrayType, typename T>
    class VSArrayProperty : public VSValueBaseProperty<T>
    {
    public:
        VSArrayProperty()
        {
        }
        VSArrayProperty(VSRtti &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiFlag, bool Range = false, T HighValue = T(), T LowValue = T(), T fStep = T())
            : VSValueBaseProperty(Owner, Name, uiElementOffset, uiFlag, Range, HighValue, LowValue, fStep)
        {
        }
        VSArrayProperty(VSFunction &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiFlag, bool Range = false, T HighValue = T(), T LowValue = T(), T fStep = T())
            : VSValueBaseProperty(Owner, Name, uiElementOffset, uiFlag, Range, HighValue, LowValue, fStep)
        {
        }
        virtual ~VSArrayProperty()
        {
        }
        virtual unsigned int GetPropertyType() const
        {
            return PT_ARRAY;
        }
        inline ArrayType &GetContainer(void *pObj) const
        {
            return (*(ArrayType *)(((unsigned char *)pObj) + m_uiElementOffset));
        }
        inline bool AddElement(void *pObj, unsigned int uiIndex, T &pDataSrc)
        {
            GetContainer(pObj).AddElement(pDataSrc);
            return true;
        }
        inline bool Erase(void *pObj, unsigned int i)
        {
            GetContainer(pObj).Erase(i);
        }
        virtual bool SetValue(void *pObj, unsigned int uiIndex, T &pDataSrc) const
        {

            if (pDataSrc > m_HightValue || pDataSrc < m_LowValue)
            {
                return false;
            }
            (GetContainer(pObj)[uiIndex]) = pDataSrc;
            return true;
        }
        virtual bool GetValue(void *pObj, unsigned int uiIndex, T &pDataDest) const
        {
            pDataDest = (GetContainer(pObj)[uiIndex]);
            return true;
        }
        virtual bool Archive(MStream &Stream, void *pObj)
        {
            Stream.Archive(GetContainer(pObj));
            return true;
        }
        virtual void CloneData(void *pSrcObj, void *pDestObj, Container::MMap<MObject *, MObject *> &CloneMap)
        {
            Copy(GetContainer(pDestObj), GetContainer(pSrcObj), CloneMap);
        }
        virtual void CopyData(void *pSrcObj, void *pDestObj)
        {
            GetContainer(pDestObj) = GetContainer(pSrcObj);
        }
        // todo editor property
        // virtual void AddEditorElement(void* pSrcObj, VSECollection* pParent, Container::MString& Name)
        //{
        //	CreateEditorElement(GetContainer(pSrcObj), (MObject*)pSrcObj, pParent, Name, m_bRange, m_HightValue, m_LowValue, m_fStep);
        // }
        virtual VSProperty *GetInstance()
        {
            return MX_NEW VSArrayProperty<ArrayType, T>();
        }
    };

    template <typename MapType, typename KEY, typename VALUE>
    class VSMapProperty : public VSValueBaseProperty<VALUE>
    {
    public:
        VSMapProperty(VSRtti &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiFlag, bool Range = false, VALUE HighValue = VALUE(), VALUE LowValue = VALUE(), VALUE fStep = VALUE())
            : VSValueBaseProperty(Owner, Name, uiElementOffset, uiFlag, Range, HighValue, LowValue, fStep)
        {
        }
        VSMapProperty(VSFunction &Owner, const VSUsedName &Name, unsigned int uiElementOffset, unsigned int uiFlag, bool Range = false, VALUE HighValue = VALUE(), VALUE LowValue = VALUE(), VALUE fStep = VALUE())
            : VSValueBaseProperty(Owner, Name, uiElementOffset, uiFlag, Range, HighValue, LowValue, fStep)
        {
        }
        VSMapProperty()
        {
        }
        virtual ~VSMapProperty()
        {
        }
        virtual unsigned int GetPropertyType() const
        {
            return PT_MAP;
        }
        inline MapType &GetContainer(void *pObj) const
        {
            return (*(MapType *)(((unsigned char *)pObj) + m_uiElementOffset));
        }
        inline bool AddElement(void *pObj, unsigned int uiIndex, Container::MapElement<KEY, VALUE> &pDataSrc)
        {
            GetContainer(pObj).AddElement(pDataSrc);
            return true;
        }
        inline bool Erase(void *pObj, unsigned int i)
        {
            GetContainer(pObj).Erase(i);
        }
        virtual bool SetValue(void *pObj, unsigned int uiIndex, KEY &Key, VALUE &Value) const
        {

            if (Value > m_HightValue || Value < m_LowValue)
            {
                return false;
            }

            Container::MapElement<KEY, VALUE> Temp(Key, Value);
            (GetContainer(pObj)[uiIndex]) = Temp;
            return true;
        }
        virtual bool GetValue(void *pObj, unsigned int uiIndex, Container::MapElement<KEY, VALUE> &pDataDest) const
        {
            pDataDest = (GetContainer(pObj)[uiIndex]);
            return true;
        }
        virtual bool Archive(MStream &Stream, void *pObj)
        {
            Stream.Archive(GetContainer(pObj));
            return true;
        }
        virtual void CloneData(void *pSrcObj, void *pDestObj, Container::MMap<MObject *, MObject *> &CloneMap)
        {
            Copy(GetContainer(pDestObj), GetContainer(pSrcObj), CloneMap);
        }
        virtual void CopyData(void *pSrcObj, void *pDestObj)
        {
            GetContainer(pDestObj) = GetContainer(pSrcObj);
        }
        // todo editor property
        // virtual void AddEditorElement(void* pSrcObj, VSECollection* pParent, Container::MString& Name)
        //{
        //	CreateEditorElement(GetContainer(pSrcObj), (MObject*)pSrcObj, pParent, Name, m_bRange, m_HightValue, m_LowValue, m_fStep);
        // }
        virtual VSProperty *GetInstance()
        {
            return MX_NEW VSMapProperty<MapType, KEY, VALUE>();
        }
    };

    template <class T, class CountType>
    struct DataPropertyCreator
    {
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, unsigned int NumOffset)
        {

            return MX_NEW VSDataProperty<T, CountType>(Owner, Name, Offset, NumOffset);
        }
        VSProperty *CreateFunctionProperty(const VSUsedName &Name, VSFunction &Owner, unsigned int Offset, unsigned int NumOffset)
        {

            return MX_NEW VSDataProperty<T, CountType>(Owner, Name, Offset, NumOffset);
        }
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, unsigned int uiDataNum, bool bDynamicCreate)
        {

            return MX_NEW VSDataProperty<T, CountType>(Owner, Name, Offset, uiDataNum, bDynamicCreate);
        }
    };

    template <class T>
    struct AutoPropertyCreator
    {
        //����Ϸ�����г���Ŵ����� MObject �������������ĸ��ڵ�ȥ�������� MObject��������ԣ��ٽ�һ���жϣ����� MObject ���������Լ� MObject ����֮���������࣬
        //����ݹ���̻����Ĵ�����ʱ�䡣Ϊ�˾ܾ����Һ����������ϵ�����������һ����־λVSProperty::F_NO_USE_GC�����������������Ƿ���Ҫ��һ��������ϵ��
        //һ������£�����Ŀ����ߺ�ʹ����Ҳ�Ƿֿ��ģ�����ʹ���߼����ڳ������磬���Դ󲿷���Ҫ��ϵ���ҵ�����������ռ䣬
        //Ĭ�������ע��һ��������Ҫ����ϵ���ҵģ�������ռ��п��Բ�������ϵ���ң����濪���������ι���� MObject ����Ĵ���������
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, unsigned int uiFlag)
        {
            if (!(TIsVSPointerType<T>::Value || TIsVSSmartPointerType<T>::Value || TIsCustomType<T>::Value || TIsVSType<T>::Value))
            {
                uiFlag |= VSProperty::F_NO_USE_GC;
            }
            return MX_NEW VSValueProperty<T>(Owner, Name, Offset, uiFlag);
        }
        VSProperty *CreateFunctionProperty(const VSUsedName &Name, VSFunction &Owner, unsigned int Offset, unsigned int uiFlag)
        {

            return MX_NEW VSValueProperty<T>(Owner, Name, Offset, uiFlag);
        }
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, T HighValue, T LowValue, VSREAL fStep, unsigned int uiFlag)
        {
            if (!(TIsVSPointerType<T>::Value || TIsVSSmartPointerType<T>::Value || TIsCustomType<T>::Value || TIsVSType<T>::Value))
            {
                uiFlag |= VSProperty::F_NO_USE_GC;
            }
            return MX_NEW VSValueProperty<T>(Owner, Name, Offset, uiFlag, true, HighValue, LowValue, fStep);
        }
    };

    template <class T, class VSMemManagerClass>
    struct AutoPropertyCreator<Container::MArray<T, VSMemManagerClass>>
    {
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, unsigned int uiFlag)
        {
            if (!(TIsVSPointerType<T>::Value || TIsVSSmartPointerType<T>::Value || TIsCustomType<T>::Value || TIsVSType<T>::Value || ValueBase<T>::NeedsConstructor))
            {
                uiFlag |= VSProperty::F_NO_USE_GC;
            }
            return MX_NEW VSArrayProperty<Container::MArray<T, VSMemManagerClass>, T>(Owner, Name, Offset, uiFlag);
        }
        VSProperty *CreateFunctionProperty(const VSUsedName &Name, VSFunction &Owner, unsigned int Offset, unsigned int uiFlag)
        {

            return MX_NEW VSArrayProperty<Container::MArray<T, VSMemManagerClass>, T>(Owner, Name, Offset, uiFlag);
        }
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, T HighValue, T LowValue, T fStep, unsigned int uiFlag)
        {
            if (!(TIsVSPointerType<T>::Value || TIsVSSmartPointerType<T>::Value || TIsCustomType<T>::Value || TIsVSType<T>::Value || ValueBase<T>::NeedsConstructor))
            {
                uiFlag |= VSProperty::F_NO_USE_GC;
            }
            return MX_NEW VSArrayProperty<Container::MArray<T, VSMemManagerClass>, T>(Owner, Name, Offset, uiFlag, HighValue, LowValue, fStep);
        }
    };

    template <class T, class VSMemManagerClass>
    struct AutoPropertyCreator<Container::MArrayOrder<T, VSMemManagerClass>>
    {
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, unsigned int uiFlag)
        {
            if (TIsVSUsedNameType<T>::Value)
            {
                uiFlag |= VSProperty::F_NO_USE_GC;
            }
            return MX_NEW VSArrayProperty<Container::MArrayOrder<T, VSMemManagerClass>, T>(Owner, Name, Offset, uiFlag);
        }
        VSProperty *CreateFunctionProperty(const VSUsedName &Name, VSFunction &Owner, unsigned int Offset, unsigned int uiFlag)
        {

            return MX_NEW VSArrayProperty<Container::MArrayOrder<T, VSMemManagerClass>, T>(Owner, Name, Offset, uiFlag);
        }
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, T HighValue, T LowValue, VSREAL fStep, unsigned int uiFlag)
        {
            if (TIsVSUsedNameType<T>::Value)
            {
                uiFlag |= VSProperty::F_NO_USE_GC;
            }
            return MX_NEW VSArrayProperty<Container::MArrayOrder<T, VSMemManagerClass>, T>(Owner, Name, Offset, uiFlag, HighValue, LowValue, fStep);
        }
    };

    template <class KEY, class VALUE, class VSMemManagerClass>
    struct AutoPropertyCreator<Container::MMap<KEY, VALUE, VSMemManagerClass>>
    {
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, unsigned int uiFlag)
        {

            return MX_NEW VSMapProperty<Container::MMap<KEY, VALUE, VSMemManagerClass>, KEY, VALUE>(Owner, Name, Offset, uiFlag);
        }
        VSProperty *CreateFunctionProperty(const VSUsedName &Name, VSFunction &Owner, unsigned int Offset, unsigned int uiFlag)
        {

            return MX_NEW VSMapProperty<Container::MMap<KEY, VALUE, VSMemManagerClass>, KEY, VALUE>(Owner, Name, Offset, uiFlag);
        }
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, VALUE HighValue, VALUE LowValue, VSREAL fStep, unsigned int uiFlag)
        {

            return MX_NEW VSMapProperty<Container::MMap<KEY, VALUE, VSMemManagerClass>, KEY, VALUE>(Owner, Name, Offset, uiFlag, HighValue, LowValue, fStep);
        }
    };

    template <class KEY, class VALUE, class VSMemManagerClass>
    struct AutoPropertyCreator<Container::MMapOrder<KEY, VALUE, VSMemManagerClass>>
    {
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, unsigned int uiFlag)
        {

            return MX_NEW VSMapProperty<Container::MMapOrder<KEY, VALUE, VSMemManagerClass>, KEY, VALUE>(Owner, Name, Offset, uiFlag);
        }
        VSProperty *CreateFunctionProperty(const VSUsedName &Name, VSFunction &Owner, unsigned int Offset, unsigned int uiFlag)
        {

            return MX_NEW VSMapProperty<Container::MMapOrder<KEY, VALUE, VSMemManagerClass>, KEY, VALUE>(Owner, Name, Offset, uiFlag);
        }
        VSProperty *CreateProperty(const VSUsedName &Name, VSRtti &Owner, unsigned int Offset, VALUE HighValue, VALUE LowValue, VSREAL fStep, unsigned int uiFlag)
        {

            return MX_NEW VSMapProperty<Container::MMapOrder<KEY, VALUE, VSMemManagerClass>, KEY, VALUE>(Owner, Name, Offset, uiFlag, HighValue, LowValue, fStep);
        }
    };

    class PropertyCreator
    {
    public:
        //���ഴ�� 5 �� PropertyCreator �ࡣ�� 5 ������Թ��ɴ��� PT_ENUM��PT_DATA��PT_VALUE �� 3 �����͵����ԡ�
        //���� PT_VALUE ����ģ����ʵ�ֵģ�PT_MAP �� PT_ARRAY �� PT_DATA ģ����ػ���
        // VSEnumProperty �� VSDataProperty û�б�Ҫһ��Ҫһ����������creator�������Ǵ������Ĳ���û�취��ģ���ں���һ��
        template <class ValueType>
        static AutoPropertyCreator<ValueType> &GetAutoPropertyCreator(ValueType &valueTypeDummyRef)
        {
            static AutoPropertyCreator<ValueType> apc;
            return apc;
        }
        template <class ValueType, class CountType>
        static DataPropertyCreator<ValueType, CountType> &GetAutoPropertyCreator(ValueType *&valueTypeDummyRef, CountType &valueNumTypeDummyRef)
        {
            static DataPropertyCreator<ValueType, CountType> apc;
            return apc;
        }
        template <class ValueType>
        static VSProperty *CreateEnumProperty(ValueType &valueTypeDummyRef, const VSUsedName &Name, const VSUsedName &EnumName, VSRtti &Owner, unsigned int Offset, unsigned int uiFlag)
        {
            return MX_NEW VSEnumProperty<ValueType>(Owner, Name, EnumName, Offset, uiFlag | VSProperty::F_NO_USE_GC);
        }
    };
    typedef void (*FunctionTemplatePtr)(MObject *p, VSFunction *pFun, void *para, void *ret);
    //��������Ļ���Ŀ�ľ����ռ��ຯ�������������Ϣ���Ժ������ƺ��������ݿ���Ϊ�����Ϳ��Է��ʶ�Ӧ����
    //��һ�����ռ�������ص���Ϣ���������������������ڵ��ࡢ�����Ĳ��������Լ����͡������ķ������͡�
    //�ڶ�������ȻҪ������������Ϊ��������ô��Ҫ����������������ݣ���Ҫ�ܵ��ú���
    class VSFunction
    {
    public:
        enum // Flag
        {
            F_DEFAULT = 0X00,
            F_CLIENT = 0X01,
            F_SERVER = 0X02,
            F_REFLECT_UI = 0X04, //�ṩ��UI����
            F_MAX
        };
        VSFunction()
        {
            m_pReturnProperty = NULL;
            ObjectFun = NULL;
        }
        ~VSFunction()
        {
            for (unsigned int i = 0; i < m_PropertyArray.GetNum(); i++)
            {
                if (m_PropertyArray[i])
                {
                    ENGINE_DELETE(m_PropertyArray[i])
                }
            }
            ENGINE_DELETE(m_pReturnProperty);
        }
        VSFunction(VSRtti &Owner, const VSUsedName &Name, unsigned int uiFlag)
            : m_pOwner(&Owner)
        {
            m_Name = Name;
            m_uiFlag = uiFlag;
            m_pReturnProperty = NULL;
            ObjectFun = NULL;
        }
        inline VSRtti *GetRtti() const
        {
            return m_pOwner;
        }
        inline const VSUsedName &GetName() const
        {
            return m_Name;
        }
        virtual bool Clone(VSFunction *f)
        {
            if ((f->GetRtti() == GetRtti() && GetRtti()))
            {
                m_Name = f->m_Name;
                m_uiFlag = f->m_uiFlag;
                for (unsigned int i = 0; i < m_PropertyArray.GetNum(); i++)
                {
                    VSProperty *p = f->m_PropertyArray[i]->GetInstance();
                    m_PropertyArray.AddElement(p);
                    p->Clone(f->m_PropertyArray[i]);
                }
                return true;
            }
            return false;
        }
        virtual VSFunction *GetInstance()
        {
            return MX_NEW VSFunction();
        }
        void SetOwner(VSRtti &Owner)
        {
            m_pOwner = &Owner;
        }
        unsigned int GetFlag() const
        {
            return m_uiFlag;
        }
        void AddProperty(VSProperty *P)
        {
            m_PropertyArray.AddElement(P);
        }
        VSProperty *GetProperty(unsigned int i)
        {
            return m_PropertyArray[i];
        }
        unsigned int GetPropertyNum() const
        {
            return m_PropertyArray.GetNum();
        }
        void SetReturnType(VSProperty *p)
        {
            m_pReturnProperty = p;
        }
        bool IsReturnVoid()
        {
            return !m_pReturnProperty;
        }
        void SetTotalSize(unsigned int uiTotalSize)
        {
            m_uiTotalSize = uiTotalSize;
        }
        // IsSame �����ж����������Ƿ���ͬ��������ж��൱���ԣ�ֻ�ж��������ࡢ���֡�����������������С��
        //  ��û�о���ȥ�жϲ��������ͣ����������Ѿ��㹻�ˡ��������жϵ�ʱ�����û��ָ�������������ҵ�һ��ƥ��ľ���ֹ������
        //���ָ���˲�����������Ҫ�����������Ƿ�һ����
        bool IsSame(VSFunction *p)
        {
            if (m_pOwner != p->m_pOwner)
            {
                return false;
            }
            else if (m_Name != p->m_Name)
            {
                return false;
            }
            else if (m_uiTotalSize != p->m_uiTotalSize)
            {
                return false;
            }
            else if (m_PropertyArray.GetNum() != p->m_PropertyArray.GetNum())
            {
                return false;
            }
            else
            {
                return true;
            }
        }

    public:
        FunctionTemplatePtr ObjectFun; //����ָ�� ObjectFun���ǹؼ�����

    protected:
        VSRtti *m_pOwner;                                //��¼���������ĸ���
        VSUsedName m_Name;                               //��¼��������
        unsigned int m_uiFlag;                           //��¼��������;
        Container::MArray<VSProperty *> m_PropertyArray; //�������Ҽ�¼����������
        VSProperty *m_pReturnProperty;                   //��¼����ֵ������޷���ֵ��Ϊ��
        unsigned int m_uiTotalSize;                      //��¼���������ܴ�С
    };

}
