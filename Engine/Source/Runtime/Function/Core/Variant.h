#pragma once
#include "MemManager.h"
#include "Core/Object.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector3W.h"
#include "Matrix3X3.h"
#include "Matrix3X3W.h"

namespace Matrix
{
    class MATRIX_FUNCTION_API VSVariant : public Core::MemoryObject
    {
    public:
        enum
        {
            V_NULL,
            V_BOOL,
            V_INT,
            V_REAL,
            V_VECTOR2,
            V_VECTOR3,
            V_VECTOR3W,
            V_MATRIX3X3,
            V_MATRIX3X3W,
            V_STRING,
            V_OBJECT,
            V_MAX
        };
        VSVariant(unsigned int Type);
        ~VSVariant();
        VSVariant(bool b);
        VSVariant(int i);
        VSVariant(VSREAL f);
        VSVariant(const VSVector2 &v);
        VSVariant(const Math::Vector3 &v);
        VSVariant(const Math::Vector4 &v);
        VSVariant(const Math::Matrix3 &m);
        VSVariant(const VSMatrix3X3W &m);
        VSVariant(MObject *p);
        VSVariant(const TCHAR *s);
        VSVariant(const VSVariant &Va);

        VSVariant &operator=(const VSVariant &Va);
        VSVariant &operator=(bool b);
        VSVariant &operator=(int i);
        VSVariant &operator=(VSREAL f);
        VSVariant &operator=(const VSVector2 &v);
        VSVariant &operator=(const Math::Vector3 &v);
        VSVariant &operator=(const Math::Vector4 &v);
        VSVariant &operator=(const Math::Matrix3 &m);
        VSVariant &operator=(const VSMatrix3X3W &m);
        VSVariant &operator=(MObject *p);
        VSVariant &operator=(const TCHAR *s);

        bool operator==(const VSVariant &rhs) const;
        bool operator==(bool b) const;
        bool operator==(int i) const;
        bool operator==(VSREAL f) const;
        bool operator==(const VSVector2 &v) const;
        bool operator==(const Math::Vector3 &v) const;
        bool operator==(const Math::Vector4 &v) const;
        bool operator==(const Math::Matrix3 &m) const;
        bool operator==(const VSMatrix3X3W &m) const;
        bool operator==(const MObject *p) const;
        bool operator==(const TCHAR *s) const;

        unsigned int GetType() const;
        bool IsValid() const;
        bool GetBool() const;
        int GetInt() const;
        VSREAL GetReal() const;
        const VSVector2 &GetVector2() const;
        const Math::Vector3 &GetVector3() const;
        const Math::Vector4 &GetVector3W() const;
        const Math::Matrix3 &GetMatrix3X3() const;
        const VSMatrix3X3W &GetMatrix3X3W() const;
        const TCHAR *GetString() const;
        MObject *GetObjectPtr() const;

        void Clear();

        bool GetValueToString(Container::MString &outVal) const;
        bool SetValueFromString(const Container::MString &inVal);
        static unsigned int MapVariantType(const Container::MString &inType);
        static Container::MString MapVariantString(unsigned int inType);

    private:
        unsigned int m_uiType;
        union
        {
            bool m_bB;
            int m_iI;
            VSREAL m_fVec[16];
            void *m_pP;
        };
        static TCHAR *ms_VariantMap[V_MAX];
    };
}
