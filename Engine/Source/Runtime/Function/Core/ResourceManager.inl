template <class T>
bool VSResourceManager::GetNextMipData(const T* pInData, unsigned int uiInDataWidth, unsigned int uiInDataHeight,
	T* pOutData, unsigned int uiChannel)
{
	ENGINE_ASSERT(pInData && pOutData);
	if (!pInData || !pOutData)
	{
		return false;
	}

	unsigned int uiOutDataWidth = uiInDataWidth >> 1;
	if (!uiOutDataWidth)
	{
		uiOutDataWidth = 1;
	}
	unsigned int uiOutDataHeight = uiInDataHeight >> 1;
	if (!uiOutDataHeight)
	{
		uiOutDataHeight = 1;
	}
	for (unsigned int i = 0; i < uiOutDataWidth; i++)
	{
		unsigned int uiRow0 = i * 2;
		unsigned int uiRow1 = i * 2 + 1;

		if (uiRow1 >= uiInDataWidth)
		{
			uiRow1 = uiInDataWidth - 1;
		}
		for (unsigned int j = 0; j < uiOutDataHeight; j++)
		{

			unsigned int uiCol0 = j * 2;
			unsigned int uiCol1 = j * 2 + 1;
			if (uiCol1 >= uiInDataHeight)
			{
				uiCol1 = uiInDataHeight - 1;
			}

			for (unsigned int k = 0; k < uiChannel; k++)
			{
				pOutData[(j + i * uiOutDataHeight) * uiChannel + k] = (T)((pInData[(uiCol0 + uiRow0 * uiInDataHeight) * uiChannel + k] + pInData[(uiCol1 + uiRow0 * uiInDataHeight) * uiChannel + k] + pInData[(uiCol0 + uiRow1 * uiInDataHeight) * uiChannel + k] + pInData[(uiCol1 + uiRow1 * uiInDataHeight) * uiChannel + k]) * 0.25f);
			}
		}
	}
	return true;
}
template <class T>
bool VSResourceManager::GetNextMipData(const T* pInData, unsigned int uiInDataWidth, unsigned int uiInDataHeight, unsigned int uiInDataLength,
	T* pOutData, unsigned int uiChannel)
{
	ENGINE_ASSERT(pInData && pOutData);
	if (!pInData || !pOutData)
	{
		return false;
	}

	unsigned int uiOutDataWidth = uiInDataWidth >> 1;
	if (!uiOutDataWidth)
	{
		uiOutDataWidth = 1;
	}
	unsigned int uiOutDataHeight = uiInDataHeight >> 1;
	if (!uiOutDataHeight)
	{
		uiOutDataHeight = 1;
	}
	unsigned int uiOutDataLength = uiInDataLength >> 1;
	if (!uiOutDataLength)
	{
		uiOutDataLength = 1;
	}
	for (unsigned int s = 0; s < uiOutDataLength; s++)
	{
		unsigned int uiL0 = s * 2;
		unsigned int uiL1 = s * 2 + 1;

		if (uiL1 >= uiOutDataLength)
		{
			uiL1 = uiOutDataLength - 1;
		}

		for (unsigned int i = 0; i < uiOutDataWidth; i++)
		{
			unsigned int uiRow0 = i * 2;
			unsigned int uiRow1 = i * 2 + 1;

			if (uiRow1 >= uiInDataWidth)
			{
				uiRow1 = uiInDataWidth - 1;
			}
			for (unsigned int j = 0; j < uiOutDataHeight; j++)
			{

				unsigned int uiCol0 = j * 2;
				unsigned int uiCol1 = j * 2 + 1;
				if (uiCol1 >= uiInDataHeight)
				{
					uiCol1 = uiInDataHeight - 1;
				}

				for (unsigned int k = 0; k < uiChannel; k++)
				{
					pOutData[(j + i * uiOutDataHeight + s * uiOutDataHeight * uiOutDataWidth) * uiChannel + k] = (T)((pInData[(uiCol0 + uiRow0 * uiInDataHeight + uiL0 * uiInDataHeight * uiInDataWidth) * uiChannel + k] +
						pInData[(uiCol1 + uiRow0 * uiInDataHeight + uiL0 * uiInDataHeight * uiInDataWidth) * uiChannel + k] +
						pInData[(uiCol0 + uiRow1 * uiInDataHeight + uiL0 * uiInDataHeight * uiInDataWidth) * uiChannel + k] +
						pInData[(uiCol1 + uiRow1 * uiInDataHeight + uiL0 * uiInDataHeight * uiInDataWidth) * uiChannel + k] +
						pInData[(uiCol0 + uiRow0 * uiInDataHeight + uiL1 * uiInDataHeight * uiInDataWidth) * uiChannel + k] +
						pInData[(uiCol1 + uiRow0 * uiInDataHeight + uiL1 * uiInDataHeight * uiInDataWidth) * uiChannel + k] +
						pInData[(uiCol0 + uiRow1 * uiInDataHeight + uiL1 * uiInDataHeight * uiInDataWidth) * uiChannel + k] +
						pInData[(uiCol1 + uiRow1 * uiInDataHeight + uiL1 * uiInDataHeight * uiInDataWidth) * uiChannel + k]) *
						0.125f);
				}
			}
		}
	}

	return true;
}
template <class T>
VSTexAllState* VSResourceManager::Create2DTexture(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType,
	unsigned int uiMipLevel, T* pBuffer, bool bSRGB)
{
	if (!uiWidth || !uiHeight)
	{
		return NULL;
	}
	if ((!IsTwoPower(uiWidth) || !IsTwoPower(uiHeight)) && !VSRenderer::ms_pRenderer->IsSupportFeature(VSRenderer::SF_NoPow2Texture))
	{
		ENGINE_ASSERT(0);
		return NULL;
	}
	VSTexAllState* pTexAllState = MX_NEW VSTexAllState();
	VS2DTexture* pTexture = MX_NEW VS2DTexture(uiWidth, uiHeight, uiFormatType, uiMipLevel, 1, bSRGB);
	if (!pTexture)
	{
		return NULL;
	}
	if (pBuffer)
	{
		pTexture->CreateRAMData();
		T* pDestBuffer = (T*)pTexture->GetBuffer(0);
		Core::MXMemcpy(pDestBuffer, pBuffer, pTexture->GetByteSize(0));

		T* pLast = (T*)pTexture->GetBuffer(0);
		for (unsigned int i = 1; i < pTexture->GetMipLevel(); i++)
		{
			T* pNow = (T*)pTexture->GetBuffer(i);

			if (!VSResourceManager::GetNextMipData(pLast, pTexture->GetWidth(i - 1), pTexture->GetHeight(i - 1), pNow, pTexture->GetChannelPerPixel()))
			{
				ENGINE_DELETE(pTexture);
				return NULL;
			}
			pLast = (T*)pTexture->GetBuffer(i);
		}
	}

	pTexAllState->SetTexture(pTexture);

	return pTexAllState;
}

template <class T>
VSTexAllState* VSResourceManager::Create1DTexture(unsigned int uiWidth, unsigned int uiFormatType,
	unsigned int uiMipLevel, T* pBuffer, bool bSRGB)
{
	if (!uiWidth)
	{
		return NULL;
	}
	if (!IsTwoPower(uiWidth) && !VSRenderer::ms_pRenderer->IsSupportFeature(VSRenderer::SF_NoPow2Texture))
	{
		ENGINE_ASSERT(0);
		return NULL;
	}
	VSTexAllState* pTexAllState = MX_NEW VSTexAllState();
	VS1DTexture* pTexture = MX_NEW VS1DTexture(uiWidth, uiFormatType, uiMipLevel, 1, bSRGB);
	if (!pTexture)
	{
		return NULL;
	}
	if (pBuffer)
	{
		pTexture->CreateRAMData();

		T* pDestBuffer = (T*)pTexture->GetBuffer(0);
		Core::MXMemcpy(pDestBuffer, pBuffer, pTexture->GetByteSize(0));

		T* pLast = (T*)pTexture->GetBuffer(0);
		for (unsigned int i = 1; i < pTexture->GetMipLevel(); i++)
		{
			T* pNow = (T*)pTexture->GetBuffer(i);

			if (!VSResourceManager::GetNextMipData(pLast, pTexture->GetWidth(i - 1), pTexture->GetHeight(i - 1), pNow, pTexture->GetChannelPerPixel()))
			{
				ENGINE_DELETE(pTexture);
				return NULL;
			}
			pLast = (T*)pTexture->GetBuffer(i);
		}
	}

	pTexAllState->SetTexture(pTexture);

	return pTexAllState;
}
template <class T>
VSTexAllState* VSResourceManager::CreateCubTexture(unsigned int uiWidth, unsigned int uiFormatType,
	unsigned int uiMipLevel, T* pBuffer, bool bSRGB)
{
	if (!uiWidth)
	{
		return NULL;
	}
	if (!IsTwoPower(uiWidth))
	{
		ENGINE_ASSERT(0);
		return NULL;
	}
	VSTexAllState* pTexAllState = MX_NEW VSTexAllState();
	VSCubeTexture* pTexture = MX_NEW VSCubeTexture(uiWidth, uiFormatType, uiMipLevel, 1, bSRGB);
	if (!pTexture)
	{
		return NULL;
	}
	if (pBuffer)
	{
		pTexture->CreateRAMData();

		T* pDestBuffer = (T*)pTexture->GetBuffer(0);
		Core::MXMemcpy(pDestBuffer, pBuffer, pTexture->GetByteSize(0));

		for (unsigned int s = 0; s < VSCubeTexture::F_MAX; s++)
		{
			T* pLast = (T*)pTexture->GetBuffer(0, s);
			for (unsigned int i = 1; i < pTexture->GetMipLevel(); i++)
			{
				T* pNow = (T*)pTexture->GetBuffer(i, s);

				if (!VSResourceManager::GetNextMipData(pLast, pTexture->GetWidth(i - 1), pTexture->GetHeight(i - 1), pNow, pTexture->GetChannelPerPixel()))
				{
					ENGINE_DELETE(pTexture);
					return NULL;
				}
				pLast = (T*)pTexture->GetBuffer(i, s);
			}
		}
	}

	pTexAllState->SetTexture(pTexture);

	return pTexAllState;
}
template <class T>
VSTexAllState* VSResourceManager::Create3DTexture(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiLength, unsigned int uiFormatType,
	unsigned int uiMipLevel, T* pBuffer, bool bSRGB)
{
	if (!uiWidth || !uiHeight || !uiLength)
	{
		return NULL;
	}
	if (!IsTwoPower(uiWidth) || !IsTwoPower(uiHeight) || !IsTwoPower(uiLength))
	{
		ENGINE_ASSERT(0);
		return NULL;
	}
	VSTexAllState* pTexAllState = MX_NEW VSTexAllState();
	VS3DTexture* pTexture = MX_NEW VS3DTexture(uiWidth, uiHeight, uiLength, uiFormatType, uiMipLevel, 1, bSRGB);
	if (!pTexture)
	{
		return NULL;
	}
	if (pBuffer)
	{
		pTexture->CreateRAMData();

		T* pDestBuffer = (T*)pTexture->GetBuffer(0);
		Core::MXMemcpy(pDestBuffer, pBuffer, pTexture->GetByteSize(0));

		T* pLast = (T*)pTexture->GetBuffer(0);
		for (unsigned int i = 1; i < pTexture->GetMipLevel(); i++)
		{
			T* pNow = (T*)pTexture->GetBuffer(i);

			if (!VSResourceManager::GetNextMipData(pLast, pTexture->GetWidth(i - 1), pTexture->GetHeight(i - 1), pTexture->GetLength(i - 1), pNow, pTexture->GetChannelPerPixel()))
			{
				ENGINE_DELETE(pTexture);
				return NULL;
			}
			pLast = (T*)pTexture->GetBuffer(i);
		}
	}

	pTexAllState->SetTexture(pTexture);

	return pTexAllState;
}