#include "Matrix3.h"
#include "CMathInterface.h"

using namespace Matrix::Math;

const Matrix3 Matrix3::ms_CameraViewRight = Matrix3(0.0f, 0.0f, -1.0f,
                                                    0.0f, 1.0f, 0.0f,
                                                    1.0f, 0.0f, 0.0f);
const Matrix3 Matrix3::ms_CameraViewLeft = Matrix3(0.0f, 0.0f, 1.0f,
                                                   0.0f, 1.0f, 0.0f,
                                                   -1.0f, 0.0f, 0.0f);
const Matrix3 Matrix3::ms_CameraViewUp = Matrix3(1.0f, 0.0f, 0.0f,
                                                 0.0f, 0.0f, -1.0f,
                                                 0.0f, 1.0f, 0.0f);
const Matrix3 Matrix3::ms_CameraViewDown = Matrix3(1.0f, 0.0f, 0.0f,
                                                   0.0f, 0.0f, 1.0f,
                                                   0.0f, -1.0f, 0.0f);
const Matrix3 Matrix3::ms_CameraViewFront = Matrix3(1.0f, 0.0f, 0.0f,
                                                    0.0f, 1.0f, 0.0f,
                                                    0.0f, 0.0f, 1.0f);
const Matrix3 Matrix3::ms_CameraViewBack = Matrix3(-1.0f, 0.0f, 0.0f,
                                                   0.0f, 1.0f, 0.0f,
                                                   0.0f, 0.0f, -1.0f);
const Matrix3 Matrix3::ms_Identity;
const Matrix3 Matrix3::ms_3DMax_To_Engine = Matrix3(1.0f, 0.0f, 0.0f,
                                                    0.0f, 0.0f, 1.0f,
                                                    0.0f, 1.0f, 0.0f);
/*----------------------------------------------------------------*/
Matrix3::Matrix3(void)
{
    Identity();
}
/*----------------------------------------------------------------*/
Matrix3::Matrix3(VSREAL m00, VSREAL m01, VSREAL m02,
                 VSREAL m10, VSREAL m11, VSREAL m12,
                 VSREAL m20, VSREAL m21, VSREAL m22)
{
    _00 = m00;
    _01 = m01;
    _02 = m02;
    _10 = m10;
    _11 = m11;
    _12 = m12;
    _20 = m20;
    _21 = m21;
    _22 = m22;
}
/*----------------------------------------------------------------*/
void Matrix3::CreateRotX(VSREAL a)
{
    VSREAL fCos = COS(a);
    VSREAL fSin = SIN(a);

    _11 = fCos;
    _12 = fSin;
    _21 = -fSin;
    _22 = fCos;

    _00 = 1.0f;
    _01 = _02 = _10 = _20 = 0.0f;
}
/*----------------------------------------------------------------*/

void Matrix3::CreateRotY(VSREAL a)
{
    VSREAL fCos = COS(a);
    VSREAL fSin = SIN(a);

    _00 = fCos;
    _02 = -fSin;
    _20 = fSin;
    _22 = fCos;

    _11 = 1.0f;
    _01 = _12 = _10 = _21 = 0.0f;
}
/*----------------------------------------------------------------*/

void Matrix3::CreateRotZ(VSREAL a)
{
    VSREAL fCos = COS(a);
    VSREAL fSin = SIN(a);

    _00 = fCos;
    _01 = fSin;
    _10 = -fSin;
    _11 = fCos;

    _22 = 1.0f;
    _02 = _12 = _20 = _21 = 0.0f;
}
/*----------------------------------------------------------------*/

void Matrix3::CreateEuler(VSREAL Z, VSREAL X, VSREAL Y)
{
    VSREAL SX, SY, SZ, CX, CY, CZ;

    SZ = SIN(Z);
    CZ = COS(Z);
    SY = SIN(Y);
    CY = COS(Y);
    SX = SIN(X);
    CX = COS(X);

    _00 = CY * CZ + SX * SY * SZ;
    _01 = CX * SZ;
    _02 = -SY * CZ + SX * CY * SZ;
    _10 = -CY * SZ + SX * SY * CZ;
    _11 = CX * CZ;
    _12 = SY * SZ + SX * CY * CZ;
    ;
    _20 = CX * SY;
    _21 = -SX;
    _22 = CX * CY;
}
/*----------------------------------------------------------------*/

void Matrix3::CreateAxisAngle(const Vector3 &_vcAxis, VSREAL a)
{
    Vector3 vcAxis = _vcAxis;
    VSREAL fCos = COS(a);
    VSREAL fSin = SIN(a);
    VSREAL fSum = 1.0f - fCos;

    if (vcAxis.GetSqrLength() != 1.0)
        vcAxis.Normalize();

    VSREAL xx = vcAxis.x * vcAxis.x;
    VSREAL yy = vcAxis.y * vcAxis.y;
    VSREAL zz = vcAxis.z * vcAxis.z;

    VSREAL xy = vcAxis.x * vcAxis.y;
    VSREAL yz = vcAxis.y * vcAxis.z;
    VSREAL xz = vcAxis.z * vcAxis.x;

    VSREAL zs = vcAxis.z * fSin;
    VSREAL ys = vcAxis.y * fSin;
    VSREAL xs = vcAxis.x * fSin;

    _00 = xx * fSum + fCos;
    _01 = xy * fSum + zs;
    _02 = xz * fSum - ys;

    _10 = xy * fSum - zs;
    _11 = yy * fSum + fCos;
    _12 = yz * fSum + xs;

    _20 = xz * fSum + ys;
    _21 = yz * fSum - xs;
    _22 = zz * fSum + fCos;
}
/*----------------------------------------------------------------*/
void Matrix3::CreateRot(const Vector3 &U, const Vector3 &V, const Vector3 &N)
{
    _00 = U.x;
    _01 = U.y;
    _02 = U.z;

    _10 = V.x;
    _11 = V.y;
    _12 = V.z;

    _20 = N.x;
    _21 = N.y;
    _22 = N.z;
}
/*----------------------------------------------------------------*/
void Matrix3::GetEuler(VSREAL &Roll, VSREAL &Pitch, VSREAL &Yaw) const
{
    if (_21 > 1.0f)
        Pitch = -VSPI2;
    else if (_21 < -1.0f)
        Pitch = VSPI2;
    else
        Pitch = ASIN(-_21);

    if (fabs(_21) > VSREAL_1)
    {
        Yaw = 0;
        Roll = ATAN2(-_10, _00);
    }
    else
    {
        Roll = ATAN2(_01, _11);
        Yaw = ATAN2(_20, _22);
    }
}
/*----------------------------------------------------------------*/
Quat Matrix3::GetQuat() const
{
    VSREAL x, y, z, w;
    VSREAL fTemp[4];
    int iflag = 0;
    fTemp[0] = _00 + _11 + _22;
    fTemp[1] = _00 - _11 - _22;
    fTemp[2] = _11 - _00 - _22;
    fTemp[3] = _22 - _00 - _11;
    VSREAL fBig = fTemp[0];
    for (int i = 1; i < 4; i++)
    {
        if (fBig < fTemp[i])
        {
            fBig = fTemp[i];
            iflag = i;
        }
    }
    fBig = SQRT(fBig + 1.0f) * 0.5f;
    VSREAL fMult = 0.25f / fBig;
    switch (iflag)
    {
    case 0:
        w = fBig;
        x = (_12 - _21) * fMult;
        y = (_20 - _02) * fMult;
        z = (_01 - _10) * fMult;
        break;
    case 1:
        x = fBig;
        w = (_12 - _21) * fMult;
        y = (_01 + _10) * fMult;
        z = (_20 + _02) * fMult;
        break;
    case 2:
        y = fBig;
        w = (_20 - _02) * fMult;
        x = (_01 + _10) * fMult;
        z = (_12 + _21) * fMult;
        break;
    case 3:
        z = fBig;
        w = (_01 - _10) * fMult;
        x = (_20 + _02) * fMult;
        y = (_12 + _21) * fMult;
        break;
    }
    return Quat(x, y, z, w);
}
/*----------------------------------------------------------------*/
void Matrix3::GetAxisAngle(Vector3 &Axis, VSREAL &fAngle) const
{
    fAngle = ACOS(Clamp((_00 + _11 + _22 - 1) * 0.5f, 1.0f, -1.0f));
    if (fAngle < VSPI - EPSILON_E4)
    {
        Vector3 Temp;
        Temp.Set(M[1][2] - M[2][1], M[2][0] - M[0][2], M[0][1] - M[1][0]);
        Temp.Normalize();
        Axis = Temp;
    }
    else
    {
        int flag = 0;
        VSREAL fMax = _00;
        if (fMax < _11)
        {
            fMax = _11;
            flag = 1;
        }
        if (fMax < _22)
        {
            fMax = _22;
            flag = 2;
        }

        if (flag == 0)
        {
            VSREAL wTemp = SQRT(_00 - _11 - _22 + 1) * 0.5f;
            VSREAL InWTemp = 1.0f / wTemp;
            Axis.m[0] = wTemp;
            Axis.m[1] = M[0][1] * 0.5f * InWTemp;
            Axis.m[2] = M[0][2] * 0.5f * InWTemp;
        }
        else if (flag == 1)
        {
            VSREAL wTemp = SQRT(_11 - _00 - _22 + 1) * 0.5f;
            VSREAL InWTemp = 1.0f / wTemp;
            Axis.m[1] = wTemp;
            Axis.m[0] = M[0][1] * 0.5f * InWTemp;
            Axis.m[2] = M[1][2] * 0.5f * InWTemp;
        }
        else
        {
            VSREAL wTemp = SQRT(_22 - _00 - _11 + 1) * 0.5f;
            VSREAL InWTemp = 1.0f / wTemp;
            Axis.m[2] = wTemp;
            Axis.m[0] = M[0][2] * 0.5f * InWTemp;
            Axis.m[1] = M[1][2] * 0.5f * InWTemp;
        }
    }
}
/*----------------------------------------------------------------*/
Matrix3 Matrix3::operator+(VSREAL f) const
{
    Matrix3 Temp;

    Temp.m[0] = m[0] + f;
    Temp.m[1] = m[1] + f;
    Temp.m[2] = m[2] + f;
    Temp.m[3] = m[3] + f;
    Temp.m[4] = m[4] + f;
    Temp.m[5] = m[5] + f;
    Temp.m[6] = m[6] + f;
    Temp.m[7] = m[7] + f;
    Temp.m[8] = m[8] + f;

    return Temp;
}
/*----------------------------------------------------------------*/
Matrix3 Matrix3::operator-(VSREAL f) const
{
    Matrix3 Temp;

    Temp.m[0] = m[0] - f;
    Temp.m[1] = m[1] - f;
    Temp.m[2] = m[2] - f;
    Temp.m[3] = m[3] - f;
    Temp.m[4] = m[4] - f;
    Temp.m[5] = m[5] - f;
    Temp.m[6] = m[6] - f;
    Temp.m[7] = m[7] - f;
    Temp.m[8] = m[8] - f;

    return Temp;
}
/*----------------------------------------------------------------*/
Matrix3 Matrix3::operator*(VSREAL f) const
{
    Matrix3 Temp;

    Temp.m[0] = m[0] * f;
    Temp.m[1] = m[1] * f;
    Temp.m[2] = m[2] * f;
    Temp.m[3] = m[3] * f;
    Temp.m[4] = m[4] * f;
    Temp.m[5] = m[5] * f;
    Temp.m[6] = m[6] * f;
    Temp.m[7] = m[7] * f;
    Temp.m[8] = m[8] * f;

    return Temp;
}
/*----------------------------------------------------------------*/
Matrix3 Matrix3::operator+(const Matrix3 &Matirx) const
{

    Matrix3 Temp;

    Temp.m[0] = m[0] + Matirx.m[0];
    Temp.m[1] = m[1] + Matirx.m[1];
    Temp.m[2] = m[2] + Matirx.m[2];
    Temp.m[3] = m[3] + Matirx.m[3];
    Temp.m[4] = m[4] + Matirx.m[4];
    Temp.m[5] = m[5] + Matirx.m[5];
    Temp.m[6] = m[6] + Matirx.m[6];
    Temp.m[7] = m[7] + Matirx.m[7];
    Temp.m[8] = m[8] + Matirx.m[8];

    return Temp;
}
/*----------------------------------------------------------------*/
Matrix3 Matrix3::operator-(const Matrix3 &Matirx) const
{
    Matrix3 Temp;

    Temp.m[0] = m[0] - Matirx.m[0];
    Temp.m[1] = m[1] - Matirx.m[1];
    Temp.m[2] = m[2] - Matirx.m[2];
    Temp.m[3] = m[3] - Matirx.m[3];
    Temp.m[4] = m[4] - Matirx.m[4];
    Temp.m[5] = m[5] - Matirx.m[5];
    Temp.m[6] = m[6] - Matirx.m[6];
    Temp.m[7] = m[7] - Matirx.m[7];
    Temp.m[8] = m[8] - Matirx.m[8];

    return Temp;
}
/*----------------------------------------------------------------*/
void Matrix3::GetRowVector(Vector3 Row[3]) const
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            Row[i].m[j] = M[i][j];
    }
}
/*----------------------------------------------------------------*/
void Matrix3::GetColumnVector(Vector3 Column[3]) const
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            Column[i].m[j] = M[j][i];
    }
}
/*----------------------------------------------------------------*/
void Matrix3::LineInterpolation(VSREAL t, const Matrix3 &M1, const Matrix3 &M2)
{
    *this = M2 * t + M1 * (1.0f - t);
}
/*----------------------------------------------------------------*/
void Matrix3::Slerp(VSREAL t, const Matrix3 &M1, const Matrix3 &M2)
{
    Matrix3 M1Transpose, Temp;
    M1Transpose.TransposeOf(M1);
    Temp = M1Transpose * M2;
    VSREAL fAnagle;
    Vector3 Axis;
    Temp.GetAxisAngle(Axis, fAnagle);
    // Temp.Identity();
    Temp.CreateAxisAngle(Axis, fAnagle * t);
    *this = M1 * Temp;
}
/*----------------------------------------------------------------*/
void Matrix3::operator+=(VSREAL f)
{
    m[0] = m[0] + f;
    m[1] = m[1] + f;
    m[2] = m[2] + f;
    m[3] = m[3] + f;
    m[4] = m[4] + f;
    m[5] = m[5] + f;
    m[6] = m[6] + f;
    m[7] = m[7] + f;
    m[8] = m[8] + f;
}
/*----------------------------------------------------------------*/
void Matrix3::operator-=(VSREAL f)
{

    m[0] = m[0] - f;
    m[1] = m[1] - f;
    m[2] = m[2] - f;
    m[3] = m[3] - f;
    m[4] = m[4] - f;
    m[5] = m[5] - f;
    m[6] = m[6] - f;
    m[7] = m[7] - f;
    m[8] = m[8] - f;
}
/*----------------------------------------------------------------*/
void Matrix3::operator*=(VSREAL f)
{

    m[0] = m[0] * f;
    m[1] = m[1] * f;
    m[2] = m[2] * f;
    m[3] = m[3] * f;
    m[4] = m[4] * f;
    m[5] = m[5] * f;
    m[6] = m[6] * f;
    m[7] = m[7] * f;
    m[8] = m[8] * f;
}
/*----------------------------------------------------------------*/
void Matrix3::operator+=(const Matrix3 &Matirx)
{

    m[0] = m[0] + Matirx.m[0];
    m[1] = m[1] + Matirx.m[1];
    m[2] = m[2] + Matirx.m[2];
    m[3] = m[3] + Matirx.m[3];
    m[4] = m[4] + Matirx.m[4];
    m[5] = m[5] + Matirx.m[5];
    m[6] = m[6] + Matirx.m[6];
    m[7] = m[7] + Matirx.m[7];
    m[8] = m[8] + Matirx.m[8];
}
/*----------------------------------------------------------------*/
void Matrix3::operator-=(const Matrix3 &Matirx)
{

    m[0] = m[0] - Matirx.m[0];
    m[1] = m[1] - Matirx.m[1];
    m[2] = m[2] - Matirx.m[2];
    m[3] = m[3] - Matirx.m[3];
    m[4] = m[4] - Matirx.m[4];
    m[5] = m[5] - Matirx.m[5];
    m[6] = m[6] - Matirx.m[6];
    m[7] = m[7] - Matirx.m[7];
    m[8] = m[8] - Matirx.m[8];
}
/*----------------------------------------------------------------*/
bool Matrix3::operator==(const Matrix3 &v) const
{
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
        {
            if (ABS(M[i][j] - v.M[i][j]) > EPSILON_E4)
            {
                return false;
            }
        }
    }
    return true;
}
/*----------------------------------------------------------------*/
void Matrix3::GetRowVector(Vector3 &Row0, Vector3 &Row1, Vector3 &Row2) const
{
    Row0.x = M[0][0];
    Row0.y = M[0][1];
    Row0.z = M[0][2];
    Row1.x = M[1][0];
    Row1.y = M[1][1];
    Row1.z = M[1][2];
    Row2.x = M[2][0];
    Row2.y = M[2][1];
    Row2.z = M[2][2];
}
/*----------------------------------------------------------------*/
void Matrix3::GetColumnVector(Vector3 &Column0, Vector3 &Column1, Vector3 &Column2) const
{
    Column0.x = M[0][0];
    Column0.y = M[1][0];
    Column0.z = M[2][0];
    Column1.x = M[0][1];
    Column1.y = M[1][1];
    Column1.z = M[2][1];
    Column2.x = M[0][2];
    Column2.y = M[1][2];
    Column2.z = M[2][2];
}
/*----------------------------------------------------------------*/
void Matrix3::GetUVN(Vector3 UVN[3]) const
{
    UVN[0].x = M[0][0];
    UVN[0].y = M[0][1];
    UVN[0].z = M[0][2];
    UVN[1].x = M[1][0];
    UVN[1].y = M[1][1];
    UVN[1].z = M[1][2];
    UVN[2].x = M[2][0];
    UVN[2].y = M[2][1];
    UVN[2].z = M[2][2];
}
/*----------------------------------------------------------------*/
void Matrix3::GetUVN(Vector3 &U, Vector3 &V, Vector3 &N) const
{
    U.x = M[0][0];
    U.y = M[0][1];
    U.z = M[0][2];
    V.x = M[1][0];
    V.y = M[1][1];
    V.z = M[1][2];
    N.x = M[2][0];
    N.y = M[2][1];
    N.z = M[2][2];
}
/*----------------------------------------------------------------*/
void Matrix3::CreateScale(VSREAL fX, VSREAL fY, VSREAL fZ)
{
    Identity();
    _00 = fX;
    _11 = fY;
    _22 = fZ;
}
/*----------------------------------------------------------------*/
void Matrix3::CreateScale(const Vector3 &Axis, VSREAL fScale)
{
    Vector3 NorAxis = Axis;
    NorAxis.Normalize();
    VSREAL a = fScale - 1.0f;

    VSREAL ax = a * NorAxis.x;
    VSREAL ay = a * NorAxis.y;
    VSREAL az = a * NorAxis.z;

    M[0][0] = ax * NorAxis.x - 1.0f;
    M[1][1] = ay * NorAxis.y - 1.0f;
    M[2][2] = az * NorAxis.z - 1.0f;

    M[0][1] = M[1][0] = ax * NorAxis.y;
    M[0][2] = M[2][0] = ax * NorAxis.z;
    M[1][2] = M[2][1] = ay * NorAxis.z;
}
/*----------------------------------------------------------------*/
void Matrix3::GetEigenSystem(VSREAL EigenValue[3], Vector3 Eigen[3]) const
{
    VSREAL Max;
    unsigned int p, q;
    VSREAL r;
    VSREAL t;
    VSREAL cos, sin;
    Matrix3 Temp, TempTranspose, EigenMatrix, A;
    A = *this;
    do
    {
        //ȡ�����ֵ
        Max = A.M[0][2];
        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = i; j < 3; j++)
            {
                if (i != j)
                {
                    if (ABS(A.M[i][j]) > ABS(Max))
                    {
                        Max = A.M[i][j];
                        p = i;
                        q = j;
                    }
                }
            }
        }
        if (ABS(Max) < EPSILON_E4)
            break;
        r = (A.M[p][p] - A.M[q][q]) / Max;
        if (r > EPSILON_E4)
            t = 1.0f / (ABS(r) + SQRT(r * r + 1));
        else if (r < -EPSILON_E4)
            t = -1.0f / (ABS(r) + SQRT(r * r + 1));
        else
            t = 1.0f;
        cos = 1.0f / SQRT(1 + t * t);
        sin = t * cos;
        Temp.M[0][0] = cos;
        Temp.M[0][1] = -sin;
        Temp.M[0][2] = 0;
        Temp.M[1][0] = sin;
        Temp.M[1][1] = cos;
        Temp.M[1][2] = 0;
        Temp.M[2][0] = 0;
        Temp.M[2][1] = 0;
        Temp.M[2][2] = 1;

        EigenMatrix = EigenMatrix * Temp;
        TempTranspose.TransposeOf(Temp);

        A = TempTranspose * A * Temp;

    } while (ABS(Max) > EPSILON_E4);

    for (unsigned int i = 0; i < 3; i++)
    {
        EigenValue[i] = A.M[i][i];
    }
    EigenMatrix.GetUVN(Eigen);
}
void Matrix3::GetScale(Vector3 &Scale) const
{
    Vector3 RowVector[3];
    GetRowVector(RowVector);

    for (unsigned int i = 0; i < 3; i++)
    {
        Scale.m[i] = RowVector[i].GetLength();
        RowVector[i] /= Scale.m[i];
    }
}
void Matrix3::GetScaleAndRotator(Vector3 &Scale)
{
    Vector3 RowVector[3];
    GetRowVector(RowVector);

    for (unsigned int i = 0; i < 3; i++)
    {
        Scale.m[i] = RowVector[i].GetLength();
        RowVector[i] /= Scale.m[i];
    }
    *this = Matrix3(RowVector[0].x, RowVector[0].y, RowVector[0].z,
                    RowVector[1].x, RowVector[1].y, RowVector[1].z,
                    RowVector[2].x, RowVector[2].y, RowVector[2].z);
}
void Matrix3::CreateFromDirection(Vector3 &Direction, const Vector3 &Up)
{
    Vector3 vcTemp, vcUp;
    Vector3 Dir = Direction;
    Dir.Normalize();

    //���㳯������Ϸ�����,��ΪDirΪ��λ����,����fDotΪvcWorld��
    // Dir�ϵ�ͶӰ
    VSREAL fDot = Up.Dot(Dir);
    //����ͶӰ����,�����Dir��ͬ������
    vcTemp = Dir * fDot;
    //����������ƽ��4���η������up
    /*
    /|
    worldup-->   / |<---up
    /__|__
    vcTemp
    */
    vcUp = Up - vcTemp;

    //�������
    VSREAL fL = vcUp.GetLength();

    // ����Ϊ0,˵�� Direction��worldUp����ƽ��,���Ǽ���Ϊ0.
    if (fL < EPSILON_E4)
    {
        Vector3 vcY;
        //����ѡ����������,����up����
        vcY.Set(0.0f, 1.0f, 0.0f);

        vcTemp = Dir * Direction.y;
        vcUp = vcY - vcTemp;

        fL = vcUp.GetLength();

        // ����Ϊ0,˵�� Direction��worldUp����ƽ��,���Ǽ���Ϊ0.
        if (fL < EPSILON_E4)
        {
            //����ѡ����������,����up����
            vcY.Set(0.0f, 0.0f, 1.0f);

            vcTemp = Dir * Dir.z;
            vcUp = vcY - vcTemp;

            fL = vcUp.GetLength();
            if (fL < EPSILON_E4)
                return;
        }
    }
    //��λ��
    vcUp /= fL;

    Vector3 vcRight;
    vcRight.Cross(vcUp, Dir);
    CreateRot(vcRight, vcUp, Dir);
}