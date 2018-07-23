// md5.h: interface for the md5 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MD5_H__34B65701_32CB_4B4F_A422_0C7AD1885F9B__INCLUDED_)
#define AFX_MD5_H__34B65701_32CB_4B4F_A422_0C7AD1885F9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct
{
unsigned int A;
unsigned int B;
unsigned int C;
unsigned int D;
bool Failed;
}
md5_context;

class md5  
{
public:
	md5();
	virtual ~md5();
	static md5_context CalculateMD5(unsigned char* bytes, int size);

};

#endif // !defined(AFX_MD5_H__34B65701_32CB_4B4F_A422_0C7AD1885F9B__INCLUDED_)
