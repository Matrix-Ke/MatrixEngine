#include "Vector4.h"
#include "Matrix4.h"
using namespace Matrix::Math;

HalfVector4::HalfVector4()
{
    x = 0, y = 0, z = 0, w = 0;
}
HalfVector4::HalfVector4(unsigned short _x, unsigned short _y, unsigned short _z, unsigned short _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}
HalfVector4 HalfVector4::operator+(const HalfVector4 &v) const
{
    Vector4 v1 = HalfToFloat(*this);
    Vector4 v2 = HalfToFloat(v);
    return HalfVector4(FloatToHalf(v1 + v2));
}
HalfVector4 HalfVector4::operator*(VSREAL f) const
{
    Vector4 v1 = HalfToFloat(*this) * f;
    return HalfVector4(FloatToHalf(v1));
}
/*----------------------------------------------------------------*/
Vector4::Vector4(void)
{
    x = 0, y = 0, z = 0, w = 1.0f;
}
/*----------------------------------------------------------------*/
Vector4::Vector4(VSREAL _x, VSREAL _y, VSREAL _z, VSREAL _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}
/*----------------------------------------------------------------*/
Vector4::Vector4(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
    r = (R * (VSREAL)1.0) / 255;
    g = (G * (VSREAL)1.0) / 255;
    b = (B * (VSREAL)1.0) / 255;
    a = (A * (VSREAL)1.0) / 255;
}
/*----------------------------------------------------------------*/
Vector4::Vector4(const Vector3 &V)
{

    Set(V);
}
/*----------------------------------------------------------------*/
void Vector4::CreateFromARGB(DWORD ARGB)
{
    unsigned char a, r, g, b;
    DWCOLORGetARGB(ARGB, a, r, g, b);
    *this = Vector4(r, g, b, a);
}
void Vector4::CreateFromBGRA(DWORD BGRA)
{
    unsigned char a, r, g, b;
    DWCOLORGetBGRA(BGRA, a, r, g, b);
    *this = Vector4(r, g, b, a);
}
void Vector4::CreateFromRGBA(DWORD RGBA)
{
    unsigned char a, r, g, b;
    DWCOLORGetRGBA(RGBA, a, r, g, b);
    *this = Vector4(r, g, b, a);
}
void Vector4::CreateFromABGR(DWORD ABGR)
{
    unsigned char a, r, g, b;
    DWCOLORGetABGR(ABGR, a, r, g, b);
    *this = Vector4(r, g, b, a);
}
/*----------------------------------------------------------------*/
Vector4 Vector4::operator*(const Matrix4 &m) const
{
    Vector4 vcResult;

#ifdef VS_SSE
    {
        VSVectorRegister _v = VectorLoad(this->m);
        VSVectorRegister _m0 = VectorLoad(&m.m[0]);
        VSVectorRegister _m1 = VectorLoad(&m.m[4]);
        VSVectorRegister _m2 = VectorLoad(&m.m[8]);
        VSVectorRegister _m3 = VectorLoad(&m.m[12]);
        // Splat x,y,z and w
        VSVectorRegister VTempX = VectorReplicate(_v, 0);
        VSVectorRegister VTempY = VectorReplicate(_v, 1);
        VSVectorRegister VTempZ = VectorReplicate(_v, 2);
        VSVectorRegister VTempW = VectorReplicate(_v, 3);
        // Mul by the matrix
        VTempX = VectorMultiply(VTempX, _m0);
        VTempY = VectorMultiply(VTempY, _m1);
        VTempZ = VectorMultiply(VTempZ, _m2);
        VTempW = VectorMultiply(VTempW, _m3);
        // Add them all together
        VTempX = VectorAdd(VTempX, VTempY);
        VTempZ = VectorAdd(VTempZ, VTempW);
        VTempX = VectorAdd(VTempX, VTempZ);

        VectorStore(VTempX, &vcResult);
    }
#else
    {
        vcResult.x = x * m._00 + y * m._10 + z * m._20 + w * m._30;
        vcResult.y = x * m._01 + y * m._11 + z * m._21 + w * m._31;
        vcResult.z = x * m._02 + y * m._12 + z * m._22 + w * m._32;
        vcResult.w = x * m._03 + y * m._13 + z * m._23 + w * m._33;
    }
#endif

    return vcResult;
}
/*----------------------------------------------------------------*/
void Vector4::operator+=(const Vector4 &v)
{

    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
}
/*----------------------------------------------------------------*/
void Vector4::operator-=(const Vector4 &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
}
/*----------------------------------------------------------------*/
void Vector4::operator*=(const Vector4 &v)
{

    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
}
/*----------------------------------------------------------------*/
void Vector4::operator/=(const Vector4 &v)
{

    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
}
/*----------------------------------------------------------------*/
void Vector4::operator*=(VSREAL f)
{

    x *= f;
    y *= f;
    z *= f;
    w *= f;
}
/*----------------------------------------------------------------*/
void Vector4::operator/=(VSREAL f)
{

    x /= f;
    y /= f;
    z /= f;
    w /= f;
}
/*----------------------------------------------------------------*/
void Vector4::operator+=(VSREAL f)
{

    x += f;
    y += f;
    z += f;
    w += f;
}
/*----------------------------------------------------------------*/
void Vector4::operator-=(VSREAL f)
{

    x -= f;
    y -= f;
    z -= f;
    w -= f;
}
/*----------------------------------------------------------------*/
Vector4 Vector4::operator*(VSREAL f) const
{
    return Vector4(x * f, y * f, z * f, w * f);
}
/*----------------------------------------------------------------*/
Vector4 Vector4::operator/(VSREAL f) const
{

    return Vector4(x / f, y / f, z / f, w / f);
}
/*----------------------------------------------------------------*/
Vector4 Vector4::operator+(VSREAL f) const
{
    return Vector4(x + f, y + f, z + f, w + f);
}
/*----------------------------------------------------------------*/
Vector4 Vector4::operator-(VSREAL f) const
{

    return Vector4(x - f, y - f, z - f, w - f);
}
/*----------------------------------------------------------------*/
Vector4 Vector4::operator+(const Vector4 &v) const
{

    return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}
/*----------------------------------------------------------------*/
Vector4 Vector4::operator-(const Vector4 &v) const
{

    return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}
/*----------------------------------------------------------------*/
Vector4 Vector4::operator*(const Vector4 &v) const
{

    return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
}
/*----------------------------------------------------------------*/
Vector4 Vector4::operator/(const Vector4 &v) const
{

    return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}
/*----------------------------------------------------------------*/
bool Vector4::operator==(const Vector4 &v) const
{
    // 	for (unsigned int i = 0 ; i < 4 ; i++)
    // 	{
    // 		if (ABS(m[i] - v.m[i]) > EPSILON_E4)
    // 		{
    // 			return false;
    // 		}
    // 	}
    // 	return true;
    return (ABS(x - v.x) < EPSILON_E4 &&
            ABS(y - v.y) < EPSILON_E4 &&
            ABS(z - v.z) < EPSILON_E4 &&
            ABS(w - v.w) < EPSILON_E4);
}
/*----------------------------------------------------------------*/
DWORD Vector4::GetDWARGB() const
{
    unsigned char R, G, B, A;
    GetUCColor(A, R, G, B);

    return (DWORD)(((((A)&0xff) << 24) | (((R)&0xff) << 16) | (((G)&0xff) << 8) | ((B)&0xff)));
}
/*----------------------------------------------------------------*/
DWORD Vector4::GetDWRGBA() const
{
    unsigned char R, G, B, A;
    GetUCColor(A, R, G, B);

    return (DWORD)(((((R)&0xff) << 24) | (((G)&0xff) << 16) | (((B)&0xff) << 8) | ((A)&0xff)));
}
/*----------------------------------------------------------------*/
DWORD Vector4::GetDWBGRA() const
{
    unsigned char R, G, B, A;
    GetUCColor(A, R, G, B);
    return ((DWORD)((((B)&0xff) << 24) | (((G)&0xff) << 16) | (((R)&0xff) << 8) | ((A)&0xff)));
}
/*----------------------------------------------------------------*/
DWORD Vector4::GetDWABGR() const
{
    unsigned char R, G, B, A;
    GetUCColor(A, R, G, B);
    return ((DWORD)((((A)&0xff) << 24) | (((B)&0xff) << 16) | (((G)&0xff) << 8) | ((R)&0xff)));
}
/*----------------------------------------------------------------*/
void Vector4::GetUCColor(unsigned char &A, unsigned char &R, unsigned char &G, unsigned char &B) const
{
    A = (unsigned char)(a * 255);
    R = (unsigned char)(r * 255);
    G = (unsigned char)(g * 255);
    B = (unsigned char)(b * 255);
}
/*----------------------------------------------------------------*/
