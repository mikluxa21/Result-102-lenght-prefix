#include <vector>
#include <memory>
#include <string>
#include <google/protobuf/message.h>

#ifndef SRC_PROTOBUF_PARSER_HELPERS_H_
#define SRC_PROTOBUF_PARSER_HELPERS_H_

#if GOOGLE_PROTOBUF_VERSION >= 3012004
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSizeLong())
#else
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSize())
#endif
typedef std::vector<char> Data;
typedef std::shared_ptr<const Data> PointerToConstData;
typedef std::shared_ptr<Data> PointerToData;

template <class Message>
PointerToConstData serializeDelimited(const Message& msg)
{
	const size_t messageSize = PROTOBUF_MESSAGE_BYTE_SIZE(msg);
	const size_t headerSize = google::protobuf::io::CodedOutputStream::VarintSize32(messageSize);
	const PointerToData& result = std::make_shared<Data>(headerSize+messageSize);
	google::protobuf::uint8* buffer = reinterpret_cast<google::protobuf::uint8*> (&*result->begin());
	google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(messageSize, buffer);
	msg.SerializeWithCachedSizesToArray(buffer + headerSize);
	return result;
}


template <class Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed = 0)
{
	if(bytesConsumed == nullptr)
		throw std::runtime_error("Don't get bytesConsumed");
	std::vector<char> b((const char*) data, (const char*) data + size);
	Message *resMessage = new Message();
	for(size_t i = 0; i < size; i++)
		for(size_t j = size; j > i + 1; j--)
			if(resMessage->ParseFromString(std::string(b.begin() + (i+1), b.begin() + j)))
			{
				*bytesConsumed = j - i;
				return std::make_shared<Message> (*resMessage);
			}
	delete resMessage;
	return nullptr;
}






#endif /* SRC_PROTOBUF_PARSER_HELPERS_H_ */
