/**
 * \file SnowflakeLinkedList.h
 *
 * \author Cameron Miles Merrill
 *
 * \brief Singly linked list for snowflakes
 */

#pragma once
#include <memory>
#include "Snowflake.h"

class CSnowfall;


/**
 * \brief Singly linked list for snowflakes
 */
class CSnowflakeLinkedList
{
public:
	CSnowflakeLinkedList();
	virtual ~CSnowflakeLinkedList();

	/** \brief Setter for the start of this singly linked list
	* \param start new head of list
	*/
	void CSnowflakeLinkedList::SetStart(std::shared_ptr<CSnowflake> start) { mStartSnowflake = start; }
	/** \brief Getter for head of list
	* \returns mStartSnowflake head of list
	*/
	std::shared_ptr<CSnowflake> CSnowflakeLinkedList::GetHead() { return mStartSnowflake; }
	std::shared_ptr<CSnowflake> CSnowflakeLinkedList::pop();
	void CSnowflakeLinkedList::Add(std::shared_ptr<CSnowflake> snowflake);

private:
	/// Shared_ptr to head of the list
	std::shared_ptr<CSnowflake> mStartSnowflake = nullptr;

};

