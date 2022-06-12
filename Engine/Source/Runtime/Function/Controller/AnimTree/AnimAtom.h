#pragma once
#include "Matrix3X3W.h"
#include "Graphic.h"
#include "Transform.h"
/*


*/
namespace Matrix
{
    class MATRIX_FUNCTION_API VSAnimAtom
    {
    public:
        VSAnimAtom(const Math::Vector3 &fScale, const Math::Vector3 &Pos, const VSQuat &Rotator)
            : m_fScale(fScale), m_Pos(Pos), m_Rotator(Rotator)
        {
        }
        VSAnimAtom()
        {
            Identity();
        }
        ~VSAnimAtom()
        {
        }
        Math::Vector3 m_fScale;
        Math::Vector3 m_Pos;
        VSQuat m_Rotator;
        void GetMatrix(VSMatrix3X3W &OutMatrix) const;
        void Interpolation(const VSAnimAtom &Atom1, const VSAnimAtom Atom2, VSREAL t);
        void Identity();
        void FromTransform(const Math::VSTransform &T);
        void FromMatrix(const VSMatrix3X3W &m);
        void ParitialBlend(const VSAnimAtom &Atom, float f);
        void FastParitialBlend(const VSAnimAtom &Atom, float f);

        void operator*=(VSREAL f);
        void operator+=(const VSAnimAtom &Atom);
        void operator-=(const VSAnimAtom &Atom);

        static VSAnimAtom ms_Identity;
        static VSAnimAtom ms_FastBlendZero;
        static Math::VSTransform VSEngineFrom3DMax(const VSAnimAtom &AtomIn3DMax);
        Math::VSTransform GetTransfrom() const;
    };
    MATRIX_FUNCTION_API VSAnimAtom operator+(const VSAnimAtom &Atom1, const VSAnimAtom Atom2);
    MATRIX_FUNCTION_API VSAnimAtom operator-(const VSAnimAtom &Atom1, const VSAnimAtom Atom2);
    MATRIX_FUNCTION_API VSAnimAtom operator*(const VSAnimAtom &Atom, VSREAL f);
    MATRIX_FUNCTION_API VSAnimAtom FastParitialMul(const VSAnimAtom &Atom, VSREAL f);
}
