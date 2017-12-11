#pragma once

#include "gtest/gtest.h"

class FileTest: public ::testing::Test
{
public:
protected:
	FileTest()
	{
	}

	virtual ~FileTest()
	{
	}

	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}

	std::string dummyFilePath = "../../media/Dummy.txt";

};