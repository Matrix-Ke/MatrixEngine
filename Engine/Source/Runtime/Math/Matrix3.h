#pragma once
#include "Vector3.h"
#include "Quat.h"

namespace Matrix
{
    namespace Math
    {
        //矩阵
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
            void CreateRotX(VSREAL a);                               // 绕x旋转
            void CreateRotY(VSREAL a);                               // 绕y旋转
            void CreateRotZ(VSREAL a);                               // 绕z旋转
            void CreateEuler(VSREAL Roll, VSREAL Pitch, VSREAL Yaw); // 绕z x and y构建，欧拉角  -pi <= y z <= pi  -pi/2 < x < pi/2
            void CreateAxisAngle(const Vector3 &vAxis, VSREAL a);    //绕vAxis旋转a弧度
            //创建旋转矩阵
            void CreateRot(const Vector3 &U, const Vector3 &V, const Vector3 &N);
            //创建缩放矩阵
            void CreateScale(VSREAL fX, VSREAL fY, VSREAL fZ);

            void CreateScale(const Vector3 &Axis, VSREAL fScale);
            //得到eluer角度
            void GetEuler(VSREAL &Yaw, VSREAL &Pitch, VSREAL &Roll) const;
            //得到旋转轴和旋转角
            void GetAxisAngle(Vector3 &Axis, VSREAL &fAngle) const;
            //得到四元数
            Quat GetQuat() const;
            //线性插值
            void LineInterpolation(VSREAL t, const Matrix3 &M1, const Matrix3 &M2);
            //球形插值
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
            //按行获得向量
            void GetRowVector(Vector3 Row[3]) const;
            //按行列得向量
            void GetColumnVector(Vector3 Column[3]) const;

            void GetRowVector(Vector3 &Row0, Vector3 &Row1, Vector3 &Row2) const;
            void GetColumnVector(Vector3 &Column0, Vector3 &Column1, Vector3 &Column2) const;
            //按UVN获得
            void GetUVN(Vector3 UVN[3]) const;
            void GetUVN(Vector3 &U, Vector3 &V, Vector3 &N) const;
            //求特征值，特征向量
            void GetEigenSystem(VSREAL EigenValue[3], Vector3 Eigen[3]) const;
            /*********************************** inline *************************************/
            inline void Identity(void);                            //单位矩阵
            inline void TransposeOf(const Matrix3 &Matirx);        //转置
            inline void InverseOf(const Matrix3 &Matirx);          //求逆
            inline VSREAL Det() const;                             //求判别式
            inline Matrix3 operator*(const Matrix3 &Matirx) const; // 矩阵相乘
            inline Vector3 operator*(const Vector3 &vc) const;     // 矩阵和向量乘

            //一个行向量 一个列向量构造
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