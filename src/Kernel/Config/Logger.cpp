 
#include "Logger.h"

Logger::Logger()
{
}

Logger::~Logger()
{
}

std::string Logger::dateNow()
{
	auto start = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(start);
	std::string timeNow = std::ctime(&start_time);
	std::string::size_type pos = 0;
	while ((pos = timeNow.find("\n", pos)) != std::string::npos)
	{
		timeNow.erase(pos, 2);
	}
	return timeNow;
	return std::string();
}

bool Logger::__PRINT__(std::string message, std::string caller)
{
	if (message != this->constants->__EMPTY__)
	{
		#ifdef _DEBUG
				this->st.append("[" + this->dateNow() + "] ");
				if (caller != this->constants->__EMPTY__)
				{
					this->st.append("[" + caller+ "] - ");
				}
				this->st.append(message);
				this->st.append("\n");
				std::cout << st.__STR__();
				this->st.clear();
		#endif
	 }
	return false;
}
