#ifndef __proto_binary_stream_proto_h__
#define __proto_binary_stream_proto_h__

#include "cocos2d.h"

namespace cocoslua_ext
{

class BinaryStream : public cocos2d::Ref
{
public:
	BinaryStream();
	~BinaryStream();

	static BinaryStream* create(int size);
	void reset();

	void writeInt(int value);
	int readInt();
	void writeString(const char* buff, int len);
	unsigned char* readString(int *len);

	void setBuff(const char* buff, int len);
	const unsigned char* getTotalBuff(int *len);
private:
	void init(int size);
	void checkBuffLen(int len);
	void setLengthToBuff() const;
	unsigned char* m_buff;

	int m_addIdx;
	int m_readIdx;
	int m_len;
	int m_bufflen;
};

}
#endif //__proto_binary_stream_proto_h__
