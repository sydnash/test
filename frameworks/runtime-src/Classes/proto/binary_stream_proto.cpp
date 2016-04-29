#include "binary_stream_proto.h"

namespace cocoslua_ext
{

BinaryStream::BinaryStream()
	: m_addIdx(0)
	, m_readIdx(0)
	, m_len(0)
{
}

BinaryStream::~BinaryStream()
{
	delete[] m_buff;
}

BinaryStream* BinaryStream::create(int size)
{
	auto ret = new BinaryStream;
	ret->init(size);
	ret->autorelease();
	return ret;
}

void BinaryStream::reset()
{
	m_addIdx = 4;
	m_readIdx = 4;
	m_len = 4;
}

void BinaryStream::init(int size)
{
	m_buff = new unsigned char[size];
	m_bufflen = size;
	reset();
}

void BinaryStream::writeInt(int value)
{
	size_t len = sizeof(int);
	checkBuffLen(m_len + len);
	memcpy(m_buff + m_addIdx, &value, len);
	m_addIdx += len;
	m_len += len;
}

int BinaryStream::readInt()
{
	int ret = *((int*)(m_buff + m_readIdx));
	m_readIdx += sizeof(int);
	return ret;
}

void BinaryStream::writeString(const char* buff, int len)
{
	writeInt(len); 
	memcpy(m_buff + m_addIdx, buff, len);
	m_addIdx += len;
	m_len += len;
}

unsigned char* BinaryStream::readString(int *len)
{
	*len = readInt();
	unsigned char* address = m_buff + m_readIdx;
	m_readIdx += *len;
	return address;
}

void BinaryStream::checkBuffLen(int len)
{
	if (m_bufflen < len) {
		int newLen = m_bufflen * 2;
		while (newLen < len) {
			newLen *= 2;
		}
		auto tmp = m_buff;
		m_buff = new unsigned char[newLen];
		memcpy(m_buff, tmp, m_bufflen);
		m_bufflen = newLen;
		delete [] tmp;
	}
}

void BinaryStream::setBuff(const char* buff, int len)
{
	reset();
	checkBuffLen(len);
	memcpy(m_buff, buff, len);
	m_len = len;
}

void BinaryStream::setLengthToBuff() const
{
	memcpy(m_buff, &m_len, sizeof(int));
}

const unsigned char* BinaryStream::getTotalBuff(int *len)
{
	*len = m_len;
	setLengthToBuff();
	return m_buff;
}


} //namespace cocoslua_ext
