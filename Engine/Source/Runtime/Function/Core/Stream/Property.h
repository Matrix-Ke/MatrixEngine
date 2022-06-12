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
    //属性反射（property reflection）就是要把类里面的属性信息收集起来,其实就是进行属性信息收集
    //将收集的属性信息存放到RTTI中，也可以另外新建类俩存放。其实真正的目的是实现序列化存储，UI绑定。
    // PT_ENUM 表示枚举类型，它在 UI 绑定的时候有所不同，要把枚举里面的选项列出来。
    // PT_DATA 指的是存放数据的指针，也就是说，这个指针指向一块内存数据，用于序列化存储，并不涉及 UI 绑定。
    //将 PT_ARRAY、PT_MAP 单列出来是因为它们是容器，访问内部数据的接口并不相同。
    // PT_VALUE 则表示除上述 4 种之外的所有数据类型。
    class VSProperty
    {
    public:
        enum // Property Type
        {
            PT_VALUE, //表示其他 5 种之外的所有数据类型
            PT_ENUM,  //表示枚举类型
            PT_DATA,  //指的是存放数据的指针
            PT_ARRAY, //容器单列出来是因为它们是容器，访问内部数据的接口并不相同。
            PT_MAP,   //容器单列出来是因为它们是容器，访问内部数据的接口并不相同。
            PT_MAX
        };
        // Flag 表示这个属性有什么作用
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
        // property要么属于某个rtti要么属于function的。
        VSRtti *m_pRttiOwner;
        VSFunction *m_pFunctionOwner;
        VSUsedName m_Name;
        unsigned int m_uiFlag;
        unsigned int m_uiElementOffset; //在owner结构中元素相对的偏移量
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

    // VSDataProperty来存储数据的，可以存储固定长度的和不定长度的数据。
    // m_uiDataNum 不是 0，那么就使用固定长度的数据，m_bDynamicCreate 用来表示数据缓存是否动态创建。
    //如果 m_uiDataNum 是 0，那么就使用不定长度的数据，用户就要在类里面加入表示这个长度的属性，m_uiNumElementOffset 则表示这个属性的偏移量
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
                // dataProperty是指针数据，
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
        bool m_bDynamicCreate;    //是否是动态创建
        unsigned int m_uiDataNum; // data的数量
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
        //在游戏世界中充斥着大量的 MObject 对象，如果从世界的根节点去遍历所有 MObject对象的属性，再进一步判断，随着 MObject 对象增多以及 MObject 对象之间依赖增多，
        //这个递归过程会消耗大量的时间。为了拒绝查找毫无意义的联系，这里加入了一个标志位VSProperty::F_NO_USE_GC，用来标记这个属性是否需要进一步查找联系。
        //一般情况下，引擎的开发者和使用者也是分开的，引擎使用者集中在抽象世界，所以大部分需要联系查找的属性在世界空间，
        //默认情况下注册一个属性是要做联系查找的，而引擎空间中可以不进行联系查找，引擎开发者有责任管理好 MObject 对象的创建和销毁
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
        //分类创建 5 个 PropertyCreator 类。这 5 个类可以归结成创建 PT_ENUM、PT_DATA、PT_VALUE 这 3 种类型的属性。
        //其中 PT_VALUE 是用模板来实现的，PT_MAP 和 PT_ARRAY 是 PT_DATA 模板的特化。
        // VSEnumProperty 和 VSDataProperty 没有必要一定要一个创造器（creator），它们传进来的参数没办法和模板融合在一起，
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
    //函数反射的基本目的就是收集类函数的所有相关信息，以函数名称和连续数据块作为参数就可以访问对应函数
    //第一步，收集函数相关的信息，包括函数名、函数所在的类、函数的参数个数以及类型、函数的返回类型。
    //第二步，既然要以连续数据作为参数，那么就要有能力拆解连续数据，还要能调用函数
    class VSFunction
    {
    public:
        enum // Flag
        {
            F_DEFAULT = 0X00,
            F_CLIENT = 0X01,
            F_SERVER = 0X02,
            F_REFLECT_UI = 0X04, //提供给UI调用
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
        // IsSame 用来判断两个函数是否相同，这里的判断相当粗略，只判断了所属类、名字、参数个数、参数大小，
        //  并没有具体去判断参数的类型，不过这样已经足够了。在真正判断的时候，如果没有指定参数个数，找到一个匹配的就终止遍历；
        //如果指定了参数个数，就要检查参数个数是否一样。
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
        FunctionTemplatePtr ObjectFun; //函数指针 ObjectFun，是关键数据

    protected:
        VSRtti *m_pOwner;                                //记录函数属于哪个类
        VSUsedName m_Name;                               //记录函数名称
        unsigned int m_uiFlag;                           //记录函数的用途
        Container::MArray<VSProperty *> m_PropertyArray; //从左向右记录参数的属性
        VSProperty *m_pReturnProperty;                   //记录返回值，如果无返回值则为空
        unsigned int m_uiTotalSize;                      //记录参数量的总大小
    };

}
