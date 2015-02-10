#include "stdafx.h"
#include "Tra.h"
#include <fstream> 
using namespace std;

#ifndef UTIL_H
#define UTIL_H
class CUtil
{
public:
static bool ReadLineFromFile(CStdioFile &fp, CString &line);

};

#endif