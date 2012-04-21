#include "Circle.h"
#include <assert.h>

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
		case csDisappearing:
			{
				curStateTime += dt;
				if (curStateTime >= 0.5)
					state = csDisappeared;
			}
			break;

		case csDisappeared:
			break;

		default:
			assert(0);
	}
}