#include "stdafx.h"
#include "SnowflakeLinkedList.h"


/**
 * \brief constructor
 */
CSnowflakeLinkedList::CSnowflakeLinkedList()
{
}


/**
 * \brief destructor
 */
CSnowflakeLinkedList::~CSnowflakeLinkedList()
{
}


/**
 * \brief remove the end of the list, and return it
 * \returns shared ptr to what was the end of the list
 */
std::shared_ptr<CSnowflake> CSnowflakeLinkedList::pop()
{
	auto snowflake = GetHead();
	if (snowflake != nullptr)
	{
		//check if we are already at last node (singly linked list is size 1)
		if (snowflake->Next() == nullptr)
		{
			mStartSnowflake = nullptr;
			return snowflake;
		}
		else
		{
			//Get to one before the end
			while (snowflake->Next()->Next() != nullptr)
			{
				snowflake = snowflake->Next();
			}
			auto last = snowflake->Next();
			snowflake->SetNext(nullptr);
			return last;
		}
	}
	else
	{
		return nullptr;
	}
}


/**
 * \brief Add a snowflake to this singly linked list
 * \param snowflake we are adding
 */
void CSnowflakeLinkedList::Add(std::shared_ptr<CSnowflake> snowflake)
{
	snowflake->SetNext(mStartSnowflake);
	snowflake->Randomize();
	mStartSnowflake = snowflake;
}


