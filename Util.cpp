#include "stdafx.h"
#include "Tra.h"
#include "Util.h"
#include <fstream>
using namespace std;

/* This helper function is used to read a line from DOS format
 * text file or from Unix text file.
 */
bool CUtil::ReadLineFromFile(CStdioFile &fp, CString &line)
{
	const int LINE_SIZE = 500;
    char buf[LINE_SIZE];
    /*static unsigned int m_hpreFile = 0;
	static ifstream ifs;
	if (m_hpreFile != fp.m_hFile)
	{
		m_hpreFile = fp.m_hFile;
	    ifs.attach(fp.m_pStream->_file);
	}

	if (ifs.eof())
	{
		ifs.close();
		return false;
	}
	
	char c ;
	int i =0;

	ifs.get(c);
	while(!ifs.eof() && c != '\n' && c != '\r')
	{
		buf[i++] = c;
		ifs.get(c);
	}

	buf[i] = '\0';*/

	line = buf;
	return true;
}
