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
			//通过旋转轴和旋转角构造四元数
			void CreateAxisAngle(const Vector3& Axis, VSREAL fAngle);
			//由欧拉角构造四元数
			void  CreateEuler(VSREAL fRoll, VSREAL fPitch, VSREAL fYaw);
			//单位化
			void  Normalize();
			//求共轭
			Quat  GetConjugate()const;
			//得到欧拉角
			void  GetEulers(VSREAL& fRoll, VSREAL& fPitch, VSREAL& fYaw)const;
			//从四元数得到变换矩阵
			void  GetMatrix(Matrix3& Matrix)const;
			//得到长度
			VSREAL GetLength(void)const;
			//取得逆
			Quat GetInverse()const;
			//取得旋转轴和旋转角
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
			//求点积
			VSREAL Dot(const Quat& q)const;
			//求共轭
			Quat operator ~(void) const;

			//求q2绕q1旋转后的四元数
			void Rotate(const Quat& q1, const Quat& q2);

			//旋转一个向量
			Vector3 Rotate(const Vector3& v)const;
			//插值
			void Slerp(VSREAL t, const Quat& q1, const Quat& q2);
			//三角形2维球型插值
			void TriangleSlerp(VSREAL t1, VSREAL t2, const Quat& q1, const Quat& q2, const Quat& q3);
			//四元数样条插值
			void Slerp(VSREAL t, const Quat& q1, const Quat& q2, const Quat& s1, const Quat& s2);
			void SlerpSValueOf(const Quat& q1, const Quat& q2, const Quat& q3);
			//求幂
			Quat Pow(VSREAL exp)const;
			//求以e为底的对数
			Quat Ln()const;
			//求以e为底指数
			Quat Exp()const;



		}; // class
		/*----------------------------------------------------------------*/
	}
}