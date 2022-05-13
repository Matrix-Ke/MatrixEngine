#pragma once
#include "VSVector3.h"
#include "VSVector3W.h"
#include "VSMatrix3X3.h"
//#include "VSPlane3.h"
namespace Matrix
{
	namespace Math
	{
		//����
		class  MATRIX_MATH_API VSMatrix3X3W
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

			VSMatrix3X3W(void);
			VSMatrix3X3W(VSREAL m00, VSREAL m01, VSREAL m02, VSREAL m03,
				VSREAL m10, VSREAL m11, VSREAL m12, VSREAL m13,
				VSREAL m20, VSREAL m21, VSREAL m22, VSREAL m23,
				VSREAL m30, VSREAL m31, VSREAL m32, VSREAL m33);


			//��3*3���󴴽�
			void CreateFrom3X3(const VSMatrix3X3& Mat);
			//ƽ�ƾ���
			void CreateTranslate(VSREAL dx, VSREAL dy, VSREAL dz);
			void CreateTranslate(const VSVector3& V);
			//�����任����
			void CreateInWorldObject(const VSVector3& U, const VSVector3& V, const VSVector3& N, const VSVector3& Point);

			//��������Ʊ任����; 
			//@parameter: �����λ��
			void CreateFromBillboard(const VSVector3& vcPos, const VSMatrix3X3& CameraRotMatrix, bool bAxisY);					//�������������,�Ƿ�ֻ��Y����ת
			//�����������(�����Ӽ�����) 
			//$parameter   ���λ�� ,�۲췽�� ,�����������(����Ŀ��λ��)
			bool CreateFromLookDir(const VSVector3& vcPos, const VSVector3& vcDir, const VSVector3& vcWorldUp = VSVector3(0, 1, 0));

			//@parameter 
			bool CreateFromLookAt(const VSVector3& vcPos, const VSVector3& vcLookAt, const VSVector3& vcWorldUp = VSVector3(0, 1, 0));
			//����͸��ͶӰ����
			//@parameter:  X�����Ž� ,���߱� ,�������� ,Զ������
			bool CreatePerspective(VSREAL fFov, VSREAL fAspect, VSREAL fZN, VSREAL fZF);
			//��������ͶӰ����  
			//@parameter�� ��,�ߣ� ���ü��棬 Զ�ü���
			bool CreateOrthogonal(VSREAL fW,
				VSREAL fH,
				VSREAL fZN,
				VSREAL fZF);
			//�����ӿھ���
			bool CreateViewPort(VSREAL fX, VSREAL fY, VSREAL fWidth, VSREAL fHeight, VSREAL fMinz, VSREAL fMaxz);
			//void CreatePointLightPlaneShadow(const VSVector3 & LightPoint,const VSPlane3 &Plane);
			//void CreateInfiniteLightPlaneShadow(const VSVector3 & LightDir,const VSPlane3 &Plane);
			VSMatrix3X3W operator *(VSREAL f)const;
			VSMatrix3X3W operator +(VSREAL f)const;
			VSMatrix3X3W operator -(VSREAL f)const;
			VSMatrix3X3W operator +(const VSMatrix3X3W& Matirx)const;
			VSMatrix3X3W operator -(const VSMatrix3X3W& Matirx)const;

			void operator *= (VSREAL f);
			void operator += (VSREAL f);
			void operator -= (VSREAL f);
			void operator += (const VSMatrix3X3W& Matirx);
			void operator -= (const VSMatrix3X3W& Matirx);

			bool operator ==(const VSMatrix3X3W& v)const;

			//�����3*3���� ��ת��������
			void Add3X3(const VSMatrix3X3& Mat);
			//����ƽ��
			void AddTranslate(const VSVector3& V);
			void AddTranslate(VSREAL dx, VSREAL dy, VSREAL dz);


			///*********************************** inline *************************************/

			inline void Identity(void);											//��λ����
			inline void SetZero();
			inline void TransposeOf(const VSMatrix3X3W& Matrix);				//ת��
			inline void InverseOf(const VSMatrix3X3W& Mat);						//����

			inline VSMatrix3X3W GetTranspose()const;							//ת��
			inline VSMatrix3X3W GetInverse()const;								//����

			inline VSVector3 GetTranslation(void)const;							//�õ�ƽ����
			inline void Get3X3(VSMatrix3X3& Mat)const;							//�õ�3*3����
			inline VSMatrix3X3W operator * (const VSMatrix3X3W& Matirx)const;   // �������
			inline VSVector3 operator * (const VSVector3& vc)const;				// �����������
			inline VSVector3W operator * (const VSVector3W& vc)const;			// �����������


			//Ӧ��3X3����
			inline VSVector3 Apply3X3(const VSVector3& v)const;
			//Ӧ��ƽ��
			inline VSVector3 ApplyTranlaste(const VSVector3& Point)const;

			//���л������
			void GetRowVector(VSVector3W Row[4])const;
			//�����е�����
			void GetColumnVector(VSVector3W Column[4])const;

			void GetRowVector(VSVector3W& Row0, VSVector3W& Row1, VSVector3W& Row2, VSVector3W& Row3)const;
			void GetColumnVector(VSVector3W& Column0, VSVector3W& Column1, VSVector3W& Column2, VSVector3W& Column3)const;
			const static VSMatrix3X3W ms_Materix3X3WIdentity;
			const static VSMatrix3X3W ms_3DMax_To_Engine;
		}; // class

#include "VSMatrix3X3W.inl"
	}
}