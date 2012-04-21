#include "Circle.h"
#include <assert.h>

const double TCircle::c_blowTime = 0.12;
const double TCircle::c_disappearTime = 0.5;

TCircle::TCircle()
	: state(csFalling)
{
}

void TCircle::Update(double dt)
{
	switch (state)
	{
		case csFalling:
			{
				y += dt * speedY;
				if (y <= radius)
				{
					state = csDisappearing;
					curStateTime = 0;
				}
			}
			break;

		case csBlowing:
			{
				curStateTime += dt;
				if (curStateTime >= c_blowTime)
					state = csDisappeared;
			}
			break;

		case csDisappearing:
			{
				curStateTime += dt;
				if (curStateTime >= c_disappearTime)
					state = csDisappeared;
			}
			break;

		case csDisappeared:
			break;

		default:
			assert(0);
	}
}