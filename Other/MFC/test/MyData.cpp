#include "stdafx.h"
#include "MyData.h"

IMPLEMENT_SERIAL(MyData, CObject, VERSIONABLE_SCHEMA | 1)

MyData::MyData()
{
	number = 0;
	cost = 0;
	type = '\0';
}

MyData::~MyData()
{
}

CString MyData::ToString()
{
		CString str;
	//sprintf_s(str, "%-10d %-30s %-30s", number, cost, type);
	str.Format(_T("%-10d\t%-10d\t%-30s"), number, cost, type);
	return str;
}

void MyData::Serialize(CArchive &arch)
{
	if (arch.IsStoring())
		arch << number << cost << type;
	else
		arch >> number >> cost >> type;
}

const MyData& MyData::operator = (const MyData &dat)
{
	number = dat.number;
	cost = dat.cost;
	type = dat.type;
	return *this;
}