#ifndef INIWRITER_H
#define INIWRITER_H

class CIniFile
{
public:
	CIniFile(char* szFileName);

	void WriteInteger(char* szSection, char* szKey, int iValue);
	void WriteFloat(char* szSection, char* szKey, float fltValue);
	void WriteBoolean(char* szSection, char* szKey, bool bolValue);
	void WriteString(char* szSection, char* szKey, char* szValue);

	int ReadInteger(char* szSection, char* szKey, int iDefaultValue);
	float ReadFloat(char* szSection, char* szKey, float fltDefaultValue);
	bool ReadBoolean(char* szSection, char* szKey, bool bolDefaultValue);
	char* ReadString(char* szSection, char* szKey, const char* szDefaultValue);
private:
	char m_szFileName[255];
};

#endif //INIWRITER_H