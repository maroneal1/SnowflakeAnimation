#pragma once
#include <memory>

class CSnowflakeLinkedList;


/**
 * \brief class for a snowflake particle
 */
class CSnowflake
{
public:
	CSnowflake();
	virtual ~CSnowflake();

	// Setters
	/** \brief Setter for Velocity in the Y direciton of this snowflake
	* \param velocityY the velocity we are setting mVelocityY to
	*/
	void CSnowflake::SetVelocityY(double velocityY) { mVelocityY = velocityY; }
	/** \brief Setter for Velocity in the X direction of this snowflake
	* \param velocityX we are setting to
	*/
	void CSnowflake::SetVelocityX(double velocityX) { mVelocityX = velocityX; }
	/** \brief Setter for position for this snowflake
	* \param position we are setting to
	*/
	void CSnowflake::SetPosition(Gdiplus::PointF position) { mPosition = position; }
	/** \brief Setter for Next() in the singly linked list of this snowflake
	* \param next shared_ptr to snowflake we are setting Next() to 
	*/
	void CSnowflake::SetNext(std::shared_ptr<CSnowflake> next) { mNextSnowflake = next; }

	/** \brief Next() gets the next snowflake in the linked list (or nullptr)
	* \returns mNextSnowflake next snowflake in list
	*/
	std::shared_ptr<CSnowflake> Next() { return mNextSnowflake; }
	void CSnowflake::Update(double elapsed);
	void CSnowflake::Draw(Gdiplus::Graphics *graphics, Gdiplus::SolidBrush &brush);
	bool CSnowflake::IsBottom();
	void CSnowflake::Randomize();
private:
	/// The pointer to the next snowflake in the singly linked list.
	std::shared_ptr<CSnowflake> mNextSnowflake = nullptr;

	/// Velocity for this snowflake in the X direction
	double mVelocityX;

	/// Velocity for this snowflake in the Y direction
	double mVelocityY;
	/// The positiob of this snowflake
	Gdiplus::PointF mPosition;
};

