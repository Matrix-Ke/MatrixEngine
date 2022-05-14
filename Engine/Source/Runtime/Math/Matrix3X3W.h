#pragma once
#include "Vector3.h"
#include "Vector3W.h"
#include "Matrix3X3.h"

namespace Matrix
{
	namespace Math
	{
		//矩阵
		class MATRIX_MATH_API Matrix4
		{
		public:
			union
			{
				VSREAL m[16];
				struct
				{
					VSREAL _00, _01, _02, _03;
					VSREAL _10, _11, _12, _13;
					VSREAL _20, _21, _22, _23;
					VSREAL _30, _31, _32, _33;
				};
				VSREAL M[4][4];
			};

			Matrix4(void);
			Matrix4(VSREAL m00, VSREAL m01, VSREAL m02, VSREAL m03,
				VSREAL m10, VSREAL m11, VSREAL m12, VSREAL m13,
				VSREAL m20, VSREAL m21, VSREAL m22, VSREAL m23,
				VSREAL m30, VSREAL m31, VSREAL m32, VSREAL m33);

			//用3*3矩阵创建
			void CreateFrom3X3(const Matrix3& Mat);
			//平移矩阵
			void CreateTranslate(VSREAL dx, VSREAL dy, VSREAL dz);
			void CreateTranslate(const Vector3& V);
			//建立变换矩阵
			void CreateInWorldObject(const Vector3& U, const Vector3& V, const Vector3& N, const Vector3& Point);

			//建立广告牌变换矩阵;
			//@parameter: 广告牌位置
			void CreateFromBillboard(const Vector3& vcPos, const Matrix3& CameraRotMatrix, bool bAxisY); //相机或其他矩阵,是否只绕Y轴旋转
			//够建相机矩阵(根据视见方向)
			//$parameter   相机位置 ,观察方向 ,够建相机矩阵(根据目标位置)
			bool CreateFromLookDir(const Vector3& vcPos, const Vector3& vcDir, const Vector3& vcWorldUp = Vector3(0, 1, 0));

			//@parameter
			bool CreateFromLookAt(const Vector3& vcPos, const Vector3& vcLookAt, const Vector3& vcWorldUp = Vector3(0, 1, 0));
			//建立透视投影矩阵
			//@parameter:  X方向张角 ,宽高比 ,近剪裁面 ,远剪裁面
			bool CreatePerspective(VSREAL fFov, VSREAL fAspect, VSREAL fZN, VSREAL fZF);
			//建立正交投影矩阵
			//@parameter： 宽,高， 近裁剪面， 远裁剪面
			bool CreateOrthogonal(VSREAL fW,
				VSREAL fH,
				VSREAL fZN,
				VSREAL fZF);
			//建立视口矩阵
			bool CreateViewPort(VSREAL fX, VSREAL fY, VSREAL fWidth, VSREAL fHeight, VSREAL fMinz, VSREAL fMaxz);
			// void CreatePointLightPlaneShadow(const Vector3 & LightPoint,const Plane3 &Plane);
			// void CreateInfiniteLightPlaneShadow(const Vector3 & LightDir,const Plane3 &Plane);
			Matrix4 operator*(VSREAL f) const;
			Matrix4 operator+(VSREAL f) const;
			Matrix4 operator-(VSREAL f) const;
			Matrix4 operator+(const Matrix4& Matirx) const;
			Matrix4 operator-(const Matrix4& Matirx) const;

			void operator*=(VSREAL f);
			void operator+=(VSREAL f);
			void operator-=(VSREAL f);
			void operator+=(const Matrix4& Matirx);
			void operator-=(const Matrix4& Matirx);

			bool operator==(const Matrix4& v) const;

			//加入把3*3矩阵 旋转或者缩放
			void Add3X3(const Matrix3& Mat);
			//添加平移
			void AddTranslate(const Vector3& V);
			void AddTranslate(VSREAL dx, VSREAL dy, VSREAL dz);

			///*********************************** inline *************************************/

			inline void Identity(void); //单位矩阵
			inline void SetZero();
			inline void TransposeOf(const Matrix4& Matrix); //转置
			inline void InverseOf(const Matrix4& Mat);      //求逆

			inline Matrix4 GetTranspose() const; //转置
			inline Matrix4 GetInverse() const;   //求逆

			inline Vector3 GetTranslation(void) const;                     //得到平移量
			inline void Get3X3(Matrix3& Mat) const;                      //得到3*3部分
			inline Matrix4 operator*(const Matrix4& Matirx) const; // 矩阵相乘
			inline Vector3 operator*(const Vector3& vc) const;           // 矩阵和向量乘
			inline Vector4 operator*(const Vector4& vc) const;         // 矩阵和向量乘

			//应用3X3部分
			inline Vector3 Apply3X3(const Vector3& v) const;
			//应用平移
			inline Vector3 ApplyTranlaste(const Vector3& Point) const;

			//按行获得向量
			void GetRowVector(Vector4 Row[4]) const;
			//按行列得向量
			void GetColumnVector(Vector4 Column[4]) const;

			void GetRowVector(Vector4& Row0, Vector4& Row1, Vector4& Row2, Vector4& Row3) const;
			void GetColumnVector(Vector4& Column0, Vector4& Column1, Vector4& Column2, Vector4& Column3) const;
			const static Matrix4 ms_Materix3X3WIdentity;
			const static Matrix4 ms_3DMax_To_Engine;
		}; // class

#include "Matrix3X3W.inl"
	}
}