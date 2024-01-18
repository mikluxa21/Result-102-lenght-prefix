#include <memory>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include "helpers.hpp"

#ifndef SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_
#define SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_

template<class MessageType>
class DelimitedMessagesStreamParser
{
public:
typedef std::shared_ptr<const MessageType> PointerToConstValue;
	std::list<PointerToConstValue> parse(const std::string& data)
	{
		for(auto i: data)
			if((int) i > 100)
				throw std::runtime_error("Wrong data"); //I don't understang how to write correctly check
		std::list<PointerToConstValue> result;
		size_t byteConsumed;
		for(auto i: data)
		{
			m_buffer.push_back(i);
			std::shared_ptr<MessageType> resParse =  parseDelimited<MessageType>(static_cast<const void*> (m_buffer.data()), m_buffer.size(), &byteConsumed);
			if(resParse != nullptr)
			{
			auto item = *serializeDelimited<MessageType>(static_cast<const MessageType&> (*(resParse.get())));
			for(int i = 0; i < byteConsumed; i++)
				if(item[i] != m_buffer[m_buffer.size() - byteConsumed + i])
					throw std::runtime_error("Corrupted data");
				result.push_back(resParse);
				m_buffer.erase(m_buffer.end() - byteConsumed, m_buffer.end());
				resParse = nullptr;
				byteConsumed = 0;
			}
			
		}
		return result;
	}
private:
	std::vector<char> m_buffer = {};
};


#endif /* SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_ */
