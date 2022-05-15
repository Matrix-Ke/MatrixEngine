#pragma once
#include "Vector3.h"
#include "Quat.h"

namespace Matrix
{
    namespace Math
    {
        //����
        class MATRIX_MATH_API Matrix3
        {
        public:
            union
            {
                VSREAL m[9];
                struct
                {
                    VSREAL _00, _01, _02;
                    VSREAL _10, _11, _12;
                    VSREAL _20, _21, _22;
                };
                VSREAL M[3][3];
            };

            Matrix3(void);
            Matrix3(VSREAL m00, VSREAL m01, VSREAL m02,
                    VSREAL m10, VSREAL m11, VSREAL m12,
                    VSREAL m20, VSREAL m21, VSREAL m22);

            void CreateFromDirection(Vector3 &Direction, const Vector3 &Up = Vector3(0, 1, 0));
            void CreateRotX(VSREAL a);                               // ��x��ת
            void CreateRotY(VSREAL a);                               // ��y��ת
            void CreateRotZ(VSREAL a);                               // ��z��ת
            void CreateEuler(VSREAL Roll, VSREAL Pitch, VSREAL Yaw); // ��z x and y������ŷ����  -pi <= y z <= pi  -pi/2 < x < pi/2
            void CreateAxisAngle(const Vector3 &vAxis, VSREAL a);    //��vAxis��תa����
            //������ת����
            void CreateRot(const Vector3 &U, const Vector3 &V, const Vector3 &N);
            //�������ž���
            void CreateScale(VSREAL fX, VSREAL fY, VSREAL fZ);

            void CreateScale(const Vector3 &Axis, VSREAL fScale);
            //�õ�eluer�Ƕ�
            void GetEuler(VSREAL &Yaw, VSREAL &Pitch, VSREAL &Roll) const;
            //�õ���ת�����ת��
            void GetAxisAngle(Vector3 &Axis, VSREAL &fAngle) const;
            //�õ���Ԫ��
            Quat GetQuat() const;
            //���Բ�ֵ
            void LineInterpolation(VSREAL t, const Matrix3 &M1, const Matrix3 &M2);
            //���β�ֵ
            void Slerp(VSREAL t, const Matrix3 &M1, const Matrix3 &M2);
            Matrix3 operator*(VSREAL f) const;
            Matrix3 operator+(VSREAL f) const;
            Matrix3 operator-(VSREAL f) const;
            Matrix3 operator+(const Matrix3 &Matirx) const;
            Matrix3 operator-(const Matrix3 &Matirx) const;

            void operator*=(VSREAL f);
            void operator+=(VSREAL f);
            void operator-=(VSREAL f);
            void operator+=(const Matrix3 &Matirx);
            void operator-=(const Matrix3 &Matirx);

            bool operator==(const Matrix3 &v) const;
            //���л������
            void GetRowVector(Vector3 Row[3]) const;
            //�����е�����
            void GetColumnVector(Vector3 Column[3]) const;

            void GetRowVector(Vector3 &Row0, Vector3 &Row1, Vector3 &Row2) const;
            void GetColumnVector(Vector3 &Column0, Vector3 &Column1, Vector3 &Column2) const;
            //��UVN���
            void GetUVN(Vector3 UVN[3]) const;
            void GetUVN(Vector3 &U, Vector3 &V, Vector3 &N) const;
            //������ֵ����������
            void GetEigenSystem(VSREAL EigenValue[3], Vector3 Eigen[3]) const;
            /*********************************** inline *************************************/
            inline void Identity(void);                            //��λ����
            inline void TransposeOf(const Matrix3 &Matirx);        //ת��
            inline void InverseOf(const Matrix3 &Matirx);          //����
            inline VSREAL Det() const;                             //���б�ʽ
            inline Matrix3 operator*(const Matrix3 &Matirx) const; // �������
            inline Vector3 operator*(const Vector3 &vc) const;     // �����������

            //һ�������� һ������������
            inline void CreateFromTwoVector(const Vector3 &v1, const Vector3 &v2);
            inline void SetZero();
            void GetScale(Vector3 &Scale) const;
            void GetScaleAndRotator(Vector3 &Scale);
            const static Matrix3 ms_CameraViewRight;
            const static Matrix3 ms_CameraViewLeft;
            const static Matrix3 ms_CameraViewUp;
            const static Matrix3 ms_CameraViewDown;
            const static Matrix3 ms_CameraViewFront;
            const static Matrix3 ms_CameraViewBack;
            const static Matrix3 ms_Identity;
            const static Matrix3 ms_3DMax_To_Engine;

        }; // class

#include "Matrix3.inl"
    }
}