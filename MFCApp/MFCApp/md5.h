#ifndef MD5_H
#define MD5_H

#include <string>
#include <fstream>
#include <iostream>
#include "DataStructure.h"

/* Type define */
typedef unsigned char byte;
typedef unsigned int uint32;

using std::string;
using std::ifstream;
using namespace std;

/* MD5 declaration. */
class MD5 {
public:
	MD5();
	MD5(const void* input, size_t length);
	MD5(const string& str);
	MD5(ifstream& in);
	void update(const void* input, size_t length);
	void update(const string& str);
	void update(ifstream& in);
	const byte* digest();
	string toString();
	void reset();
	//
	string bytesToHexString(const byte* input, size_t length);
	void   PrintMD5_Result( const string& str )
	{
		cout << "MD5(\"" << str << "\") = " << toString() << endl;
	}

private:
	void update(const byte* input, size_t length);
	void final();
	void transform(const byte block[64]);
	void encode(const uint32* input, byte* output, size_t length);
	void decode(const byte* input, uint32* output, size_t length);

	/* class uncopyable */
	MD5(const MD5&);
	MD5& operator=(const MD5&);

private:
	uint32 _state[4];	/* state (ABCD) */
	uint32 _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
	byte _buffer[64];	/* input buffer */
	byte _digest[16];	/* message digest */
	bool _finished;		/* calculate finished ? */

	static const byte PADDING[64];	/* padding for calculate */
	static const char HEX[16];
	enum { BUFFER_SIZE = COMLEN };
};

#endif /*MD5_H*/

/*
MD5 md5;                        //����MD5����
CString sql="123456";           //��Ҫ���ܵ��ַ���
md5.update(sql.GetBuffer());    //��Ϊupdate����ֻ����string���ͣ�����ʹ��getbuffer()����ת��CStringΪstring
sql=md5.toString().c_str();     //toString()������ü����ַ�����c_str();��������ת����CString����
���磺md5.reset();              //����ȥ��ԭ�ַ������ݣ��������ܼ���������һ���ַ�����
*/