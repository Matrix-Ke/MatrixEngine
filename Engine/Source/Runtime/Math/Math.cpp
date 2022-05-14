#include "Math.h"
#include "Vector3.h"
#include "Vector3W.h"
#include "Matrix3X3.h"
#include "Quat.h"

using namespace Matrix::Math;

VSREAL VSMathInstance::GetFastSin(unsigned int i)
{
    return FastSin[i];
}
VSREAL VSMathInstance::GetFastCos(unsigned int i)
{
    return FastCos[i];
}

void VSMathInstance::VSInitCRCTable()
{
#define POLYNOMIAL 0x04c11db7L
    int i, j;
    unsigned int crc_accum;
    for (i = 0; i < 256; i++)
    {
        crc_accum = ((unsigned int)i << 24);
        for (j = 0; j < 8; j++)
        {
            if (crc_accum & 0x80000000L)
                crc_accum = (crc_accum << 1) ^ POLYNOMIAL;
            else
                crc_accum = (crc_accum << 1);
        }
        CRCTable[i] = crc_accum;
    }
}
unsigned int VSMathInstance::CRC32Compute(const void *pData, unsigned int uiDataSize)
{
    unsigned int uiResult;

    if (uiDataSize == 0)
        return 0;

    const unsigned char *pDataTemp = (const unsigned char *)pData;
    uiResult = *pDataTemp++ << 24;
    if (uiDataSize > 1)
    {
        uiResult |= *pDataTemp++ << 16;
        if (uiDataSize > 2)
        {
            uiResult |= *pDataTemp++ << 8;
            if (uiDataSize > 3)
                uiResult |= *pDataTemp++;
        }
    }
    uiResult = ~uiResult;

    for (unsigned int i = 4; i < uiDataSize; i++)
    {
        uiResult = (uiResult << 8 | *pDataTemp++) ^ CRCTable[uiResult >> 24];
    }

    return ~uiResult;
}
VSMathInstance::VSMathInstance()
{
    VSInitCRCTable();
    for (unsigned int i = 0; i <= 360; i++)
    {
        VSREAL iRadian = AngleToRadian(VSREAL(i));
        FastSin[i] = SIN(iRadian);
        FastCos[i] = COS(iRadian);
    }
}
VSMathInstance::~VSMathInstance()
{
}

/*----------------------------------------------------------------*/

bool Matrix::Math::VSInitMath()
{
    VSMathInstance::GetMathInstance();
    return 1;
}

bool Matrix::Math::IsUniformScale(VSREAL fScale)
{
    if (ABS(fScale - 1.0f) < EPSILON_E4)
    {
        return true;
    }
    return false;
}
bool Matrix::Math::IsZeroTranslate(const VSVector3 &Translate)
{
    if (Translate.GetSqrLength() < EPSILON_E4)
    {
        return true;
    }
    return false;
}
bool Matrix::Math::IsIdentityRotate(const VSMatrix3X3 &Rotate)
{
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
        {
            if (i != j)
            {
                if (ABS(Rotate.M[i][j]) > EPSILON_E4)
                {
                    return false;
                }
            }
            else
            {
                if (ABS(Rotate.M[i][j] - 1.0f) > EPSILON_E4)
                {
                    return false;
                }
            }
        }
    }
    return true;
}
bool Matrix::Math::IsIdentityRotate(const VSQuat &Rotate)
{
    VSVector3 R(Rotate.x, Rotate.y, Rotate.z);
    if (R.GetSqrLength() < EPSILON_E4)
    {
        return true;
    }
    return false;
}
VSREAL Matrix::Math::LineInterpolation(VSREAL t1, VSREAL t2, VSREAL t)
{
    return t1 + (t2 - t1) * t;
}
VSVector3 Matrix::Math::LineInterpolation(const VSVector3 &t1, const VSVector3 &t2, VSREAL t)
{
    return t1 + (t2 - t1) * t;
}
VSQuat Matrix::Math::LineInterpolation(const VSQuat &t1, const VSQuat &t2, VSREAL t)
{
    VSREAL fCos = t2.Dot(t1);
    VSQuat Temp = t1;
    if (fCos < 0.0f)
    {
        Temp = t1 * (-1.0f);
    }
    return Temp + (t2 - Temp) * t;
}
VSVector3W Matrix::Math::LineInterpolation(const VSVector3W &t1, const VSVector3W &t2, VSREAL t)
{
    return t1 + (t2 - t1) * t;
}