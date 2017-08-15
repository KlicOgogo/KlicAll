#pragma once
class MyData : public CObject
{
	DECLARE_SERIAL(MyData)
public:
	MyData();
	virtual ~MyData();
	int number;
	int cost;
	CString type;
	CString ToString();
	void Serialize(CArchive &arch);
const MyData& MyData:: operator=(const MyData &dat);
};

