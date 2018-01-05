#ifndef __CWARE_FILE_H__
#define __CWARE_FILE_H__

#include <Windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <dsound.h>
#include <xstring>

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define WAVEFILE_READ   1

class WaveFile
{
public:
	WAVEFORMATEX* m_pwfx; 
	HMMIO         m_hmmio;     
	MMCKINFO      m_ck;          
	MMCKINFO      m_ckRiff;     
	DWORD         m_dwSize;     
	MMIOINFO      m_mmioinfoOut;
	DWORD         m_dwFlags;
	BOOL          m_bIsReadingFromMemory;
	BYTE*         m_pbData;
	BYTE*         m_pbDataCur;
	ULONG         m_ulDataSize;
	CHAR*         m_pResourceBuffer;

protected:
	HRESULT ReadMMIO();
	HRESULT WriteMMIO(WAVEFORMATEX *pwfxDest);

public:
	WaveFile();
	~WaveFile();

	HRESULT Open(LPTSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags);
	HRESULT OpenFromMemory(BYTE* pbData, ULONG ulDataSize, WAVEFORMATEX* pwfx, DWORD dwFlags);
	HRESULT Close();

	HRESULT Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead);
	HRESULT Write(UINT nSizeToWrite, BYTE* pbData, UINT* pnSizeWrote);

	DWORD   GetSize();
	HRESULT ResetFile();
	WAVEFORMATEX* GetFormat() { return m_pwfx; };
};
#endif
