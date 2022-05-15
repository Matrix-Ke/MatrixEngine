#pragma once
namespace Matrix
{
	namespace Math
	{
		class Matrix3;
		class Vector3;
		class  MATRIX_MATH_API Quat
		{
		public:
			union
			{
				VSREAL m[4];
				struct
				{
					VSREAL x, y, z, w;
				};
			};

			Quat(void);
			Quat(VSREAL _x, VSREAL _y, VSREAL _z, VSREAL _w);
			void Set(VSREAL _x, VSREAL _y, VSREAL _z, VSREAL _w);
			//ͨ����ת�����ת�ǹ�����Ԫ��
			void CreateAxisAngle(const Vector3& Axis, VSREAL fAngle);
			//��ŷ���ǹ�����Ԫ��
			void  CreateEuler(VSREAL fRoll, VSREAL fPitch, VSREAL fYaw);
			//��λ��
			void  Normalize();
			//����
			Quat  GetConjugate()const;
			//�õ�ŷ����
			void  GetEulers(VSREAL& fRoll, VSREAL& fPitch, VSREAL& fYaw)const;
			//����Ԫ���õ��任����
			void  GetMatrix(Matrix3& Matrix)const;
			//�õ�����
			VSREAL GetLength(void)const;
			//ȡ����
			Quat GetInverse()const;
			//ȡ����ת�����ת��
			void GetAxisAngle(Vector3& Axis, VSREAL& fAngle)const;
			void    operator /= (VSREAL f);
			Quat operator /  (VSREAL f)const;

			void    operator *= (VSREAL f);
			Quat operator *  (VSREAL f)const;

			Quat operator *  (const Vector3& v) const;

			Quat operator *  (const Quat& q) const;
			void    operator *= (const Quat& q);

			void    operator += (const Quat& q);
			Quat operator +  (const Quat& q) const;

			void    operator -= (const Quat& q);
			Quat operator -  (const Quat& q) const;

			bool operator ==(const Quat& q)const;
			//����
			VSREAL Dot(const Quat& q)const;
			//����
			Quat operator ~(void) const;

			//��q2��q1��ת�����Ԫ��
			void Rotate(const Quat& q1, const Quat& q2);

			//��תһ������
			Vector3 Rotate(const Vector3& v)const;
			//��ֵ
			void Slerp(VSREAL t, const Quat& q1, const Quat& q2);
			//������2ά���Ͳ�ֵ
			void TriangleSlerp(VSREAL t1, VSREAL t2, const Quat& q1, const Quat& q2, const Quat& q3);
			//��Ԫ��������ֵ
			void Slerp(VSREAL t, const Quat& q1, const Quat& q2, const Quat& s1, const Quat& s2);
			void SlerpSValueOf(const Quat& q1, const Quat& q2, const Quat& q3);
			//����
			Quat Pow(VSREAL exp)const;
			//����eΪ�׵Ķ���
			Quat Ln()const;
			//����eΪ��ָ��
			Quat Exp()const;



		}; // class
		/*----------------------------------------------------------------*/
	}
}