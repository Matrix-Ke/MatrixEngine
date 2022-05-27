#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "OtherMath.h"

/*
	正变换的变换顺序是S,R,T

*/

namespace Matrix
{
	namespace Math
	{
		class VSStream;
		class MATRIX_MATH_API VSTransform
		{

		private:
			Matrix4 m_mCombine;
			Matrix4 m_mCombineInverse;
			void Combine();
			Vector3 m_fScale;
			Matrix3 m_mRotate;
			Vector3 m_vTranslate;
			bool m_bIsCombine;
			bool m_bIsHaveInverse;

		public:
			VSTransform();
			~VSTransform();

			inline const Matrix4& GetCombine();
			inline const Matrix4& GetCombineInverse();
			inline const Vector3& GetScale() const;
			inline const Vector3& GetTranslate() const;
			inline const Matrix3& GetRotate() const;
			inline void GetDir(Vector3& Dir, Vector3& Up, Vector3& Right) const;
			inline void SetScale(const Vector3& fScale);
			inline void SetTranslate(const Vector3& Translate);
			inline void SetRotate(const Matrix3& Rotate);

			enum // Transform type
			{
				TT_POS,
				TT_DIR,
				TT_MAX
			};
			void ApplyForward(const Vector3& In, Vector3& Out, unsigned int uiTransformType);
			enum // Transform Flag
			{
				TF_SCALE = 1,
				TF_ROTATE = 2,
				TF_TRANSFORM = 4,
				TF_ALL = TF_SCALE | TF_TRANSFORM | TF_ROTATE
			};
			void Product(const VSTransform& t1, const VSTransform& t2, unsigned int TransformFlag = TF_ALL);
			void Inverse(VSTransform& Out) const;
			void ApplyInverse(const Vector3& In, Vector3& Out, unsigned int uiTransformType);

			void SetMatrix(const Matrix4& VSMat);

			void Interpolation(const VSTransform& t1, const VSTransform& t2, VSREAL t);

			void Indetity();
			const static VSTransform ms_Indetity;
		};

#include "Transform.inl"
	}
};
