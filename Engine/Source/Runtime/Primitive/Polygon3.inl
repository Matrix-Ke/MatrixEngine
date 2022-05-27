inline void Polygon3::Set(const Matrix::Math::Vector3 *pPoint, unsigned int PointNum)
{
    if (!pPoint || !PointNum)
        return;

    m_PointNum = PointNum;
    m_IndexNum = 3 * (m_PointNum - 2);

    MX_ENGINE_DELETEA(m_pPoint);
    MX_ENGINE_DELETEA(m_pIndex);
    m_pPoint = MX_NEW Matrix::Math::Vector3[m_PointNum];
    m_pIndex = MX_NEW VSUSHORT_INDEX[m_IndexNum];
    Core::MXMemcpy(m_pPoint, pPoint, sizeof(Matrix::Math::Vector3) * PointNum);

    m_Flag = 1;

    unsigned int I0, I1, I2;
    for (unsigned int nLoop = 0; nLoop < (m_PointNum - 2); nLoop++)
    {
        if (nLoop == 0)
        {
            I0 = 0;
            I1 = 1;
            I2 = 2;
        }
        else
        {
            I1 = I2;
            I2++;
        }

        m_pIndex[(nLoop * 3)] = I0;
        m_pIndex[(nLoop * 3) + 1] = I1;
        m_pIndex[(nLoop * 3) + 2] = I2;
    }

    Matrix::Math::Vector3 vcEdge0 = m_pPoint[1] - m_pPoint[0];
    Matrix::Math::Vector3 vcEdge1;
    //计算所在平面,直到找到不平行的两个线段为止。
    for (unsigned int i = 2; i < PointNum; i++)
    {
        vcEdge1 = m_pPoint[i] - m_pPoint[0];

        vcEdge0.Normalize();
        vcEdge1.Normalize();

        //测试是否平行
        VSREAL dot = vcEdge0.Dot(vcEdge1);
        if (Math::ABS(dot) < VSREAL_1)
            break;
    } // for

    Matrix::Math::Vector3 N;
    N.Cross(vcEdge0, vcEdge1);
    Plane3::Set(N, m_pPoint[0]);
}
/*----------------------------------------------------------------*/
inline unsigned int Polygon3::GetPointNum() const
{
    return m_PointNum;
}
/*----------------------------------------------------------------*/
inline unsigned int Polygon3::GetIndexNum() const
{
    return m_IndexNum;
}
/*----------------------------------------------------------------*/
inline const Matrix::Math::Vector3 *const Polygon3::GetpPoint() const
{

    return m_pPoint;
}
/*----------------------------------------------------------------*/
inline const VSUSHORT_INDEX *const Polygon3::GetpIndex() const
{
    return m_pIndex;
}
/*----------------------------------------------------------------*/
inline unsigned int Polygon3::GetFlag() const
{
    return m_Flag;
}
/*----------------------------------------------------------------*/