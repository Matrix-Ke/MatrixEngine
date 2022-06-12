#pragma once
#include "NodeComponent.h"
#include "Vector3.h"
#include "Matrix3X3.h"
#include "Matrix3X3W.h"
#include "Plane3.h"

namespace Matrix
{
    class VSRenderer;
    typedef struct VSVIEWPORT_TYPE
    {
        VSREAL XMin;
        VSREAL YMin;
        VSREAL XMax;
        VSREAL YMax;
        VSREAL ZMin;
        VSREAL ZMax;
        bool bChangeAspect;
        void Reset()
        {
            XMin = 0.0f;
            YMin = 0.0f;
            XMax = 1.0f;
            YMax = 1.0f;
            ZMin = 0.0f;
            ZMax = 1.0f;
            bChangeAspect = false;
        }
        VSVIEWPORT_TYPE()
        {
            Reset();
        }
    } VSViewPort;
    class VSStream;
    class MATRIX_FUNCTION_API VSCamera : public VSNodeComponent
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        friend class VSViewFamily;
        VSCamera();
        virtual ~VSCamera();
        enum // Camera Plane
        {
            CP_RIGHT,
            CP_LEFT,
            CP_TOP,
            CP_BOTTOM,
            CP_FAR,
            CP_NEAR,
            CP_MAX = 6
        };
        inline const VSMatrix3X3W &GetViewMatrix() const;
        void CreateFromEuler(const VSVector3 &Pos, VSREAL RotX, VSREAL RotY, VSREAL RotZ);
        void CreateFromLookDir(const VSVector3 &Pos,
                               const VSVector3 &vcDir,
                               const VSVector3 &vcUp = VSVector3(0, 1, 0));
        void CreateFromLookAt(const VSVector3 &vcPos,
                              const VSVector3 &vcLookAt,
                              const VSVector3 &vcUp = VSVector3(0, 1, 0));
        void CreateFromLookDirWorld(const VSVector3 &Pos,
                                    const VSVector3 &vcDir,
                                    const VSVector3 &vcUp = VSVector3(0, 1, 0));
        void CreateFromLookAtWorld(const VSVector3 &vcPos,
                                   const VSVector3 &vcLookAt,
                                   const VSVector3 &vcUp = VSVector3(0, 1, 0));
        bool SetPerspectiveFov(VSREAL fFov,   // X�����Ž�
                               VSREAL Aspect, //���߱�
                               VSREAL fZN,    //��������
                               VSREAL fZF);   //Զ������
        bool SetAspect(VSREAL Aspect);

        bool SetOrthogonal(VSREAL fW,   //��
                           VSREAL fH,   //��
                           VSREAL fZN,  //��������
                           VSREAL fZF); //Զ������
        inline const VSMatrix3X3W &GetProjMatrix() const;
        inline bool AddViewPort(const VSViewPort &ViewPort); //�ӿ�
        inline VSViewPort *GetViewPort(unsigned int i) const;
        inline unsigned int GetViewPortNum() const
        {
            return m_ViewPort.GetNum();
        }
        void GetFrustumPoint(VSVector3 Point[8]);
        VSAABB3 GetFrustumAABB();
        void GetPlane(VSPlane3 Plane[VSCamera::CP_MAX]) const;
        inline VSREAL GetZFar() const
        {
            return m_ZFar;
        }
        inline VSREAL GetZNear() const
        {
            return m_ZNear;
        }
        inline VSREAL GetAspect() const
        {
            return m_Aspect;
        }
        inline VSREAL GetFov() const
        {
            return m_Fov;
        }
        inline VSViewFamily *GetViewFamily(unsigned int uiID)
        {
            if (uiID < m_ViewFamilyArray.GetNum())
            {
                return m_ViewFamilyArray[uiID];
            }
            return NULL;
        }
        inline unsigned int GetViewFamilyNum()
        {
            return m_ViewFamilyArray.GetNum();
        }
        inline void ClearProject()
        {
            m_ProjMat.Identity();
        }
        void AddCustomCullPlane(const VSPlane3 &P);
        void ClearCustomCullPlane();
        VSArray<VSPlane3> m_CustomCullPlane;
        virtual void UpdateCameraState(double dAppTime);
        VSREAL GetProjectScreenSize(const VSAABB3 &WorldAABB);

    public:
        VSREAL m_RotX; //�ھֲ�����ϵ�µ�EULER��(��ת��)
        VSREAL m_RotY;
        VSREAL m_RotZ;

        bool m_bEnableOcclusionQuery;
        bool m_bEnableStreamResource;
        VSREAL m_fStreamBias;

    protected:
        friend class VSFreeCameraController;
        friend class VS1stCameraController;
        friend class VSSpatial;
        friend class VSScene;
        friend class VSSceneManager;
        friend class VSViewFamily;
        friend class VSLight;
        VSArray<VSViewPort> m_ViewPort;
        VSMatrix3X3W m_ViewMat; //�������
        VSMatrix3X3W m_ProjMat;

        VSREAL m_Fov;
        VSREAL m_Aspect;
        VSREAL m_ZFar;
        VSREAL m_ZNear;
        VSArrayOrder<VSViewFamily *> m_ViewFamilyArray;

        void AddViewFamily(VSViewFamily *pViewFamily);

        void DeleteViewFamily(VSViewFamily *pViewFamily);

    public:
        virtual void UpdateTransform(double dAppTime); //���±任��Ϣ
    public:
        static bool InitialDefaultState();
        static bool TerminalDefaultState();

    protected:
        static VSPointer<VSCamera> ms_Default;

    public:
        friend class VSProjLight;
        static const VSCamera *GetDefault()
        {
            return ms_Default;
        }
    };

#include "VSCamera.inl"
    DECLARE_Ptr(VSCamera);
    VSTYPE_MARCO(VSCamera);
};