#include "IteratorTests.hpp"
#include "CUL/ListLinked.hpp"
#include "CUL/ListFactory.hpp"

unsigned manyElementsCount = 1000 * 1000;

using namespace CUL;

TEST_F( IteratorTests, mainTest )
{
	ASSERT_EQ( 1, 1 );
}

TEST_F( IteratorTests, VectorDoubleAdd )
{
	std::unique_ptr<IList<double>> result( ListFactory::createVectorListPtr<double>() );
	result->pushBack( 2.2 );
	GTEST_ASSERT_EQ( 1, result->size() );
}

TEST_F( IteratorTests, VectorIntIterateOneElement )
{
	std::unique_ptr<IList<unsigned>> result( ListFactory::createVectorListPtr<unsigned>() );
	unsigned limit = 1;
	for( unsigned i = 0; i < limit; ++i )
	{
		result->pushBack( i );
	}

	unsigned i = 0;
	IIterator<unsigned>& iterator = result->getRandomIterator();
	GTEST_ASSERT_EQ( true, iterator.hasNext() );
	while( iterator.hasNext() )
	{
		GTEST_ASSERT_EQ( i, iterator.next() );
		++i;
	}
}

TEST_F( IteratorTests, VectorIntIterateTwoElements )
{
	std::unique_ptr<IList<unsigned>> result( ListFactory::createVectorListPtr<unsigned>() );
	unsigned limit = 4;
	for( unsigned i = 0; i < limit; ++i )
	{
		result->pushBack( i );
	}

	unsigned i = 0;
	IIterator<unsigned>& iterator = result->getRandomIterator();
	GTEST_ASSERT_EQ( true, iterator.hasNext() );
	while( iterator.hasNext() )
	{
		GTEST_ASSERT_EQ( i, iterator.next() );
		++i;
	}
}

TEST_F( IteratorTests, VectorIntIterateManyElements )
{
	std::unique_ptr<IList<unsigned>> result( ListFactory::createVectorListPtr<unsigned>() );
	unsigned limit = manyElementsCount;
	for( unsigned i = 0; i < limit; ++i )
	{
		result->pushBack( i );
	}

	unsigned i = 0;
	IIterator<unsigned>& iterator = result->getRandomIterator();
	GTEST_ASSERT_EQ( true, iterator.hasNext() );
	while( iterator.hasNext() )
	{
		GTEST_ASSERT_EQ( i, iterator.next() );
		++i;
	}
}

TEST_F( IteratorTests, LinkedDoubleAdd )
{
	std::unique_ptr<IList<double>> result( ListFactory::createLinkedListPtr<double>() );
	result->pushBack( 2.2 );
	GTEST_ASSERT_EQ( 1, result->size() );
}

TEST_F( IteratorTests, LinkedIntIterateOneElement )
{
	std::unique_ptr<IList<unsigned>> result( ListFactory::createLinkedListPtr<unsigned>() );
	unsigned limit = 1;
	for( unsigned i = 0; i < limit; ++i )
	{
		result->pushBack( i );
	}

	unsigned i = 0;
	IIterator<unsigned>& iterator = result->getRandomIterator();
	GTEST_ASSERT_EQ( true, iterator.hasNext() );
	while( iterator.hasNext() )
	{
		GTEST_ASSERT_EQ( i, iterator.next() );
		++i;
	}
}

TEST_F( IteratorTests, LinkedIntIterateTwoElements )
{
	std::unique_ptr<IList<unsigned>> result( ListFactory::createVectorListPtr<unsigned>() );
	unsigned limit = 4;
	for( unsigned i = 0; i < limit; ++i )
	{
		result->pushBack( i );
	}

	unsigned i = 0;
	IIterator<unsigned>& iterator = result->getRandomIterator();
	GTEST_ASSERT_EQ( true, iterator.hasNext() );
	while( iterator.hasNext() )
	{
		GTEST_ASSERT_EQ( i, iterator.next() );
		++i;
	}
}

TEST_F( IteratorTests, LinkedIntIterateManyElements )
{
	std::unique_ptr<IList<unsigned>> result( ListFactory::createVectorListPtr<unsigned>() );
	unsigned limit = manyElementsCount;
	for( unsigned i = 0; i < limit; ++i )
	{
		result->pushBack( i );
	}

	unsigned i = 0;
	IIterator<unsigned>& iterator = result->getRandomIterator();
	GTEST_ASSERT_EQ( true, iterator.hasNext() );
	while( iterator.hasNext() )
	{
		GTEST_ASSERT_EQ( i, iterator.next() );
		++i;
	}
}