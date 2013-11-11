
#include "StdAfx.h"

CIniFile::CIniFile(char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));
}

/**************************
 * Read
 */
int CIniFile::ReadInteger(char* szSection, char* szKey, int iDefaultValue)
{
	int iResult = GetPrivateProfileInt(szSection,  szKey, iDefaultValue, m_szFileName);
	return iResult;
}

float CIniFile::ReadFloat(char* szSection, char* szKey, float fltDefaultValue)
{
	char szResult[255];
	char szDefault[255];
	float fltResult;
	sprintf(szDefault, "%f", fltDefaultValue);
	GetPrivateProfileString(szSection,  szKey, szDefault, szResult, 255, m_szFileName);
	fltResult = (float)atof(szResult);
	return fltResult;
}

bool CIniFile::ReadBoolean(char* szSection, char* szKey, bool bolDefaultValue)
{
	char szResult[255];
	char szDefault[255];
	bool bolResult;
	sprintf(szDefault, "%s", bolDefaultValue? "True" : "False");
	GetPrivateProfileString(szSection, szKey, szDefault, szResult, 255, m_szFileName);
	bolResult = (strcmp(szResult, "True") == 0 || strcmp(szResult, "true") == 0) ? true : false;
	return bolResult;
}

char* CIniFile::ReadString(char* szSection, char* szKey, const char* szDefaultValue)
{
	char* szResult = new char[255];
	memset(szResult, 0x00, 255);
	GetPrivateProfileString(szSection,  szKey, szDefaultValue, szResult, 255, m_szFileName);
	return szResult;
}

/**************************
 * Write
 */
void CIniFile::WriteInteger(char* szSection, char* szKey, int iValue)
{
	char szValue[255];
	sprintf(szValue, "%d", iValue);
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}

void CIniFile::WriteFloat(char* szSection, char* szKey, float fltValue)
{
	char szValue[255];
	sprintf(szValue, "%f", fltValue);
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}

void CIniFile::WriteBoolean(char* szSection, char* szKey, bool bolValue)
{
	char szValue[255];
	sprintf(szValue, "%s", bolValue ? "True" : "False");
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}

void CIniFile::WriteString(char* szSection, char* szKey, char* szValue)
{
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}
