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
MD5 md5;                        //定义MD5的类
CString sql="123456";           //需要加密的字符串
md5.update(sql.GetBuffer());    //因为update函数只接收string类型，所以使用getbuffer()函数转换CString为string
sql=md5.toString().c_str();     //toString()函数获得加密字符串，c_str();函数重新转换成CString类型
例如：md5.reset();              //用于去除原字符串内容，这样又能继续加密下一个字符串了
*/