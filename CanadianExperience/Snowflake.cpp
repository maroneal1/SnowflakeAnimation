#include "stdafx.h"
#include "Snowflake.h"
#include "SnowflakeLinkedList.h"
#include <string>

using namespace std;
using namespace Gdiplus;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 20;
/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedY = 35;
///Maximum X value in pixels
const double MaxPositionX = 1200;
///Value to spawn between 0 and this number for the Y of snowflakes on Random. (in pixels)
const double MaxPositionY = -200;
///Minimum speed value in the Y direction for snowflakes
const double YSpeedOffset = 10;
///Offset to make sure we are drawing snowflakes to the left of the screen for wind effect
const double XPositionOffset = 400;
///Offset to make sure we are drawing snowflakes above the screen for  the floating down effect
const double YPositionOffset = 5;


/**
 * \brief constructor, randomize the member variables for speed and position
 */
CSnowflake::CSnowflake()
{
	Randomize();
}


/**
 * \brief brief destructor
 */
CSnowflake::~CSnowflake()
{
}


/**
 * \brief Draw this snowflake
 * \param graphics we are drawing with
 * \param brush use for drawing
 */
void CSnowflake::Draw(Gdiplus::Graphics *graphics, SolidBrush &brush)
{
	int drawX = (int) mPosition.X;
	int drawY = (int) mPosition.Y;
	graphics->FillEllipse(&brush, drawX, drawY, 3,3);
}


/**
 * \brief Update function for snowflakes position
 * \param elapsed time since last update
 */
void CSnowflake::Update(double elapsed)
{
	auto newXPos = mPosition.X + (REAL) elapsed*mVelocityX;
	auto newYPos = mPosition.Y + (REAL) elapsed*mVelocityY;
	SetPosition(Gdiplus::PointF((REAL) newXPos, (REAL) newYPos));
}


/**
 * \brief Check if out of picture
 * \returns true if out of picture
 */
bool CSnowflake::IsBottom()
{
	return mPosition.Y > 600 || mPosition.X > 800;
}


/**
 * \brief Randomize velocity and position of snowflake
 */
void CSnowflake::Randomize()
{
	mVelocityX = ((double) rand() / RAND_MAX) * MaxSpeedX;
	mVelocityY = ((double) rand() / RAND_MAX) * MaxSpeedY + YSpeedOffset;
	mPosition = Gdiplus::PointF((REAL) ((double) rand() / RAND_MAX) * (REAL) MaxPositionX - (REAL) XPositionOffset,
		(REAL) ((double) rand() / RAND_MAX) * (REAL) MaxPositionY - (REAL) YPositionOffset);
}