#include "WaveFile.h"


WaveFile::WaveFile()
{
	m_pwfx = NULL;
	m_hmmio = NULL;
	m_pResourceBuffer = NULL;
	m_dwSize = 0;
	m_bIsReadingFromMemory = FALSE;
}



WaveFile::~WaveFile()
{
	Close();

	if (!m_bIsReadingFromMemory)
		SAFE_DELETE_ARRAY(m_pwfx);
}



HRESULT WaveFile::Open(LPTSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags)
{
	HRESULT hr;

	m_dwFlags = dwFlags;
	m_bIsReadingFromMemory = FALSE;

	if (m_dwFlags == WAVEFILE_READ)
	{
		if (strFileName == NULL)
			return E_INVALIDARG;
		SAFE_DELETE_ARRAY(m_pwfx);

		m_hmmio = mmioOpen(strFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);

		if (NULL == m_hmmio)
		{
			HRSRC   hResInfo;
			HGLOBAL hResData;
			DWORD   dwSize;
			VOID*   pvRes;

			if (NULL == (hResInfo = FindResource(NULL, strFileName, TEXT("WAVE"))))
			{
				if (NULL == (hResInfo = FindResource(NULL, strFileName, TEXT("WAV"))))
					return 0;
			}

			if (NULL == (hResData = LoadResource(NULL, hResInfo)))
				return 0;

			if (0 == (dwSize = SizeofResource(NULL, hResInfo)))
				return 0;

			if (NULL == (pvRes = LockResource(hResData)))
				return 0;

			m_pResourceBuffer = new CHAR[dwSize];
			memcpy(m_pResourceBuffer, pvRes, dwSize);

			MMIOINFO mmioInfo;
			ZeroMemory(&mmioInfo, sizeof(mmioInfo));
			mmioInfo.fccIOProc = FOURCC_MEM;
			mmioInfo.cchBuffer = dwSize;
			mmioInfo.pchBuffer = (CHAR*)m_pResourceBuffer;

			m_hmmio = mmioOpen(NULL, &mmioInfo, MMIO_ALLOCBUF | MMIO_READ);
		}

		if (FAILED(hr = ReadMMIO()))
		{
			mmioClose(m_hmmio, 0);
			return 0;
		}

		if (FAILED(hr = ResetFile()))
			return 0;

		m_dwSize = m_ck.cksize;
	}
	else
	{
		m_hmmio = mmioOpen(strFileName, NULL, MMIO_ALLOCBUF |
			MMIO_READWRITE |
			MMIO_CREATE);
		if (NULL == m_hmmio)
			return 0;

		if (FAILED(hr = WriteMMIO(pwfx)))
		{
			mmioClose(m_hmmio, 0);
			return 0;
		}

		if (FAILED(hr = ResetFile()))
			return 0;
	}

	return hr;
}




HRESULT WaveFile::OpenFromMemory(BYTE* pbData, ULONG ulDataSize,
	WAVEFORMATEX* pwfx, DWORD dwFlags)
{
	m_pwfx = pwfx;
	m_ulDataSize = ulDataSize;
	m_pbData = pbData;
	m_pbDataCur = m_pbData;
	m_bIsReadingFromMemory = TRUE;

	if (dwFlags != WAVEFILE_READ)
		return E_NOTIMPL;

	return S_OK;
}




HRESULT WaveFile::ReadMMIO()
{
	MMCKINFO        ckIn;           
	PCMWAVEFORMAT   pcmWaveFormat;  

	m_pwfx = NULL;

	if ((0 != mmioDescend(m_hmmio, &m_ckRiff, NULL, 0)))
		return 0;

	if ((m_ckRiff.ckid != FOURCC_RIFF) ||
		(m_ckRiff.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
		return 0;

	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (0 != mmioDescend(m_hmmio, &ckIn, &m_ckRiff, MMIO_FINDCHUNK))
		return 0;

	if (ckIn.cksize < (LONG) sizeof(PCMWAVEFORMAT))
		return 0;

	if (mmioRead(m_hmmio, (HPSTR)&pcmWaveFormat,
		sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat))
		return 0;

	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		m_pwfx = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
		if (NULL == m_pwfx)
			return 0;

		memcpy(m_pwfx, &pcmWaveFormat, sizeof(pcmWaveFormat));
		m_pwfx->cbSize = 0;
	}
	else
	{
		WORD cbExtraBytes = 0L;
		if (mmioRead(m_hmmio, (CHAR*)&cbExtraBytes, sizeof(WORD)) != sizeof(WORD))
			return 0;

		m_pwfx = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)+cbExtraBytes];
		if (NULL == m_pwfx)
			return 0;

		memcpy(m_pwfx, &pcmWaveFormat, sizeof(pcmWaveFormat));
		m_pwfx->cbSize = cbExtraBytes;

		if (mmioRead(m_hmmio, (CHAR*)(((BYTE*)&(m_pwfx->cbSize)) + sizeof(WORD)),
			cbExtraBytes) != cbExtraBytes)
		{
			SAFE_DELETE(m_pwfx);
			return 0;
		}
	}

	if (0 != mmioAscend(m_hmmio, &ckIn, 0))
	{
		SAFE_DELETE(m_pwfx);
		return 0;
	}

	return S_OK;
}


DWORD WaveFile::GetSize()
{
	return m_dwSize;
}


HRESULT WaveFile::ResetFile()
{
	if (m_bIsReadingFromMemory)
	{
		m_pbDataCur = m_pbData;
	}
	else
	{
		if (m_hmmio == NULL)
			return CO_E_NOTINITIALIZED;

		if (m_dwFlags == WAVEFILE_READ)
		{
			if (-1 == mmioSeek(m_hmmio, m_ckRiff.dwDataOffset + sizeof(FOURCC),
				SEEK_SET))
				return 0;

			m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
			if (0 != mmioDescend(m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK))
				return 0;
		}
		else
		{
			m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
			m_ck.cksize = 0;

			if (0 != mmioCreateChunk(m_hmmio, &m_ck, 0))
				return 0;

			if (0 != mmioGetInfo(m_hmmio, &m_mmioinfoOut, 0))
				return 0;
		}
	}

	return S_OK;
}


HRESULT WaveFile::Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead)
{
	if (m_bIsReadingFromMemory)
	{
		if (m_pbDataCur == NULL)
			return CO_E_NOTINITIALIZED;
		if (pdwSizeRead != NULL)
			*pdwSizeRead = 0;

		if ((BYTE*)(m_pbDataCur + dwSizeToRead) >
			(BYTE*)(m_pbData + m_ulDataSize))
		{
			dwSizeToRead = m_ulDataSize - (DWORD)(m_pbDataCur - m_pbData);
		}

		CopyMemory(pBuffer, m_pbDataCur, dwSizeToRead);

		if (pdwSizeRead != NULL)
			*pdwSizeRead = dwSizeToRead;

		return S_OK;
	}
	else
	{
		MMIOINFO mmioinfoIn; 

		if (m_hmmio == NULL)
			return CO_E_NOTINITIALIZED;
		if (pBuffer == NULL || pdwSizeRead == NULL)
			return E_INVALIDARG;

		if (pdwSizeRead != NULL)
			*pdwSizeRead = 0;

		if (0 != mmioGetInfo(m_hmmio, &mmioinfoIn, 0))
			return 0;

		UINT cbDataIn = dwSizeToRead;
		if (cbDataIn > m_ck.cksize)
			cbDataIn = m_ck.cksize;

		m_ck.cksize -= cbDataIn;

		for (DWORD cT = 0; cT < cbDataIn; cT++)
		{
			if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
			{
				if (0 != mmioAdvance(m_hmmio, &mmioinfoIn, MMIO_READ))
					return 0;

				if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
					return 0;
			}

			*((BYTE*)pBuffer + cT) = *((BYTE*)mmioinfoIn.pchNext);
			mmioinfoIn.pchNext++;
		}

		if (0 != mmioSetInfo(m_hmmio, &mmioinfoIn, 0))
			return 0;

		if (pdwSizeRead != NULL)
			*pdwSizeRead = cbDataIn;

		return S_OK;
	}
}




HRESULT WaveFile::Close()
{
	if (m_dwFlags == WAVEFILE_READ)
	{
		mmioClose(m_hmmio, 0);
		m_hmmio = NULL;
		SAFE_DELETE_ARRAY(m_pResourceBuffer);
	}
	else
	{
		m_mmioinfoOut.dwFlags |= MMIO_DIRTY;

		if (m_hmmio == NULL)
			return CO_E_NOTINITIALIZED;

		if (0 != mmioSetInfo(m_hmmio, &m_mmioinfoOut, 0))
			return 0;

		if (0 != mmioAscend(m_hmmio, &m_ck, 0))
			return 0;

		if (0 != mmioAscend(m_hmmio, &m_ckRiff, 0))
			return 0;

		mmioSeek(m_hmmio, 0, SEEK_SET);

		if (0 != (INT)mmioDescend(m_hmmio, &m_ckRiff, NULL, 0))
			return 0;

		m_ck.ckid = mmioFOURCC('f', 'a', 'c', 't');

		if (0 == mmioDescend(m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK))
		{
			DWORD dwSamples = 0;
			mmioWrite(m_hmmio, (HPSTR)&dwSamples, sizeof(DWORD));
			mmioAscend(m_hmmio, &m_ck, 0);
		}

		if (0 != mmioAscend(m_hmmio, &m_ckRiff, 0))
			return 0;

		mmioClose(m_hmmio, 0);
		m_hmmio = NULL;
	}

	return S_OK;
}




HRESULT WaveFile::WriteMMIO(WAVEFORMATEX *pwfxDest)
{
	DWORD    dwFactChunk;
	MMCKINFO ckOut1;

	dwFactChunk = (DWORD)-1;

	m_ckRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	m_ckRiff.cksize = 0;

	if (0 != mmioCreateChunk(m_hmmio, &m_ckRiff, MMIO_CREATERIFF))
		return 0;

	m_ck.ckid = mmioFOURCC('f', 'm', 't', ' ');
	m_ck.cksize = sizeof(PCMWAVEFORMAT);

	if (0 != mmioCreateChunk(m_hmmio, &m_ck, 0))
		return 0;

	if (pwfxDest->wFormatTag == WAVE_FORMAT_PCM)
	{
		if (mmioWrite(m_hmmio, (HPSTR)pwfxDest,
			sizeof(PCMWAVEFORMAT)) != sizeof(PCMWAVEFORMAT))
			return 0;
	}
	else
	{
		if ((UINT)mmioWrite(m_hmmio, (HPSTR)pwfxDest,
			sizeof(*pwfxDest) + pwfxDest->cbSize) !=
			(sizeof(*pwfxDest) + pwfxDest->cbSize))
			return 0;
	}

	if (0 != mmioAscend(m_hmmio, &m_ck, 0))
		return 0;

	ckOut1.ckid = mmioFOURCC('f', 'a', 'c', 't');
	ckOut1.cksize = 0;

	if (0 != mmioCreateChunk(m_hmmio, &ckOut1, 0))
		return 0;

	if (mmioWrite(m_hmmio, (HPSTR)&dwFactChunk, sizeof(dwFactChunk)) !=
		sizeof(dwFactChunk))
		return 0;

	if (0 != mmioAscend(m_hmmio, &ckOut1, 0))
		return 0;

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: WaveFile::Write()
// Desc: Writes data to the open wave file
//-----------------------------------------------------------------------------
HRESULT WaveFile::Write(UINT nSizeToWrite, BYTE* pbSrcData, UINT* pnSizeWrote)
{
	UINT cT;

	if (m_bIsReadingFromMemory)
		return E_NOTIMPL;
	if (m_hmmio == NULL)
		return CO_E_NOTINITIALIZED;
	if (pnSizeWrote == NULL || pbSrcData == NULL)
		return E_INVALIDARG;

	*pnSizeWrote = 0;

	for (cT = 0; cT < nSizeToWrite; cT++)
	{
		if (m_mmioinfoOut.pchNext == m_mmioinfoOut.pchEndWrite)
		{
			m_mmioinfoOut.dwFlags |= MMIO_DIRTY;
			if (0 != mmioAdvance(m_hmmio, &m_mmioinfoOut, MMIO_WRITE))
				return 0;//( TEXT("mmioAdvance"), E_FAIL );
		}

		*((BYTE*)m_mmioinfoOut.pchNext) = *((BYTE*)pbSrcData + cT);
		(BYTE*)m_mmioinfoOut.pchNext++;

		(*pnSizeWrote)++;
	}

	return S_OK;
}
