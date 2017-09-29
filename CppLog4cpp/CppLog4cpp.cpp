#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>

using namespace std;

int main(int argc, char* argv[])
{
	log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout();
	pLayout->setConversionPattern("%d: %p %c %x: %m%n");

	log4cpp::Appender* fileAppender = new log4cpp::FileAppender("fileAppender","日志.log");
	fileAppender->setLayout(pLayout);

	log4cpp::Category& root = log4cpp::Category::getRoot().getInstance("日志类型");
	root.addAppender(fileAppender);
	root.setPriority(log4cpp::Priority::DEBUG);

	for (int i = 0; i < 10; i++)
	{
		string strError;
		ostringstream oss;
		oss<<i<<" 这是一条Error信息...";
		strError = oss.str();
		root.error(strError);
	}

	for (int i = 0; i < 10; i++)
	{
		string strError;
		ostringstream oss;
		oss<<i<<" 这是一条Info信息...";
		strError = oss.str();
		root.info(strError);
	}

	for (int i = 0; i < 10; i++)
	{
		string strError;
		ostringstream oss;
		oss<<i<<" 这是一条Debug信息...";
		strError = oss.str();
		root.debug(strError);
	}

	log4cpp::Category::shutdown();
	return 0;
}