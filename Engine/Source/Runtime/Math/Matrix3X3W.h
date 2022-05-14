#pragma once
#include "Vector3.h"
#include "Vector3W.h"
#include "Matrix3X3.h"

namespace Matrix
{
	namespace Math
	{
		//����
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

			//��3*3���󴴽�
			void CreateFrom3X3(const Matrix3& Mat);
			//ƽ�ƾ���
			void CreateTranslate(VSREAL dx, VSREAL dy, VSREAL dz);
			void CreateTranslate(const Vector3& V);
			//�����任����
			void CreateInWorldObject(const Vector3& U, const Vector3& V, const Vector3& N, const Vector3& Point);

			//��������Ʊ任����;
			//@parameter: �����λ��
			void CreateFromBillboard(const Vector3& vcPos, const Matrix3& CameraRotMatrix, bool bAxisY); //�������������,�Ƿ�ֻ��Y����ת
			//�����������(�����Ӽ�����)
			//$parameter   ���λ�� ,�۲췽�� ,�����������(����Ŀ��λ��)
			bool CreateFromLookDir(const Vector3& vcPos, const Vector3& vcDir, const Vector3& vcWorldUp = Vector3(0, 1, 0));

			//@parameter
			bool CreateFromLookAt(const Vector3& vcPos, const Vector3& vcLookAt, const Vector3& vcWorldUp = Vector3(0, 1, 0));
			//����͸��ͶӰ����
			//@parameter:  X�����Ž� ,��߱� ,�������� ,Զ������
			bool CreatePerspective(VSREAL fFov, VSREAL fAspect, VSREAL fZN, VSREAL fZF);
			//��������ͶӰ����
			//@parameter�� ��,�ߣ� ���ü��棬 Զ�ü���
			bool CreateOrthogonal(VSREAL fW,
				VSREAL fH,
				VSREAL fZN,
				VSREAL fZF);
			//�����ӿھ���
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

			//�����3*3���� ��ת��������
			void Add3X3(const Matrix3& Mat);
			//���ƽ��
			void AddTranslate(const Vector3& V);
			void AddTranslate(VSREAL dx, VSREAL dy, VSREAL dz);

			///*********************************** inline *************************************/

			inline void Identity(void); //��λ����
			inline void SetZero();
			inline void TransposeOf(const Matrix4& Matrix); //ת��
			inline void InverseOf(const Matrix4& Mat);      //����

			inline Matrix4 GetTranspose() const; //ת��
			inline Matrix4 GetInverse() const;   //����

			inline Vector3 GetTranslation(void) const;                     //�õ�ƽ����
			inline void Get3X3(Matrix3& Mat) const;                      //�õ�3*3����
			inline Matrix4 operator*(const Matrix4& Matirx) const; // �������
			inline Vector3 operator*(const Vector3& vc) const;           // �����������
			inline Vector4 operator*(const Vector4& vc) const;         // �����������

			//Ӧ��3X3����
			inline Vector3 Apply3X3(const Vector3& v) const;
			//Ӧ��ƽ��
			inline Vector3 ApplyTranlaste(const Vector3& Point) const;

			//���л������
			void GetRowVector(Vector4 Row[4]) const;
			//�����е�����
			void GetColumnVector(Vector4 Column[4]) const;

			void GetRowVector(Vector4& Row0, Vector4& Row1, Vector4& Row2, Vector4& Row3) const;
			void GetColumnVector(Vector4& Column0, Vector4& Column1, Vector4& Column2, Vector4& Column3) const;
			const static Matrix4 ms_Materix3X3WIdentity;
			const static Matrix4 ms_3DMax_To_Engine;
		}; // class

#include "Matrix3X3W.inl"
	}
}