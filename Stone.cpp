#include "Stone.h"

void Stone::init(int id)
{
    struct stonePos
    {
        int row, col;
        Stone::TYPE type;
    };
    stonePos pos[16] = {
    {0, 0, Stone::CHE},
    {0, 1, Stone::MA},
    {0, 2, Stone::XIANG},
    {0, 3, Stone::SHI},
    {0, 4, Stone::JIANG},
    {0, 5, Stone::SHI},
    {0, 6, Stone::XIANG},
    {0, 7, Stone::MA},
    {0, 8, Stone::CHE},
    {2, 1, Stone::PAO},
    {2, 7, Stone::PAO},
    {3, 0, Stone::BING},
    {3, 2, Stone::BING},
    {3, 4, Stone::BING},
    {3, 6, Stone::BING},
    {3, 8, Stone::BING},
    };

    _id = id;
    _dead = false;
    _red = id < 16;

    // red stones
    if(id < 16)
    {
        _row = pos[id].row;
        _col = pos[id].col;
        _type = pos[id].type;
    }
    // black stones
    else
    {
        _row = 9 - pos[id - 16].row;
        _col = 8 - pos[id - 16].col;
        _type = pos[id - 16].type;
    }
}

QRect Stone::getImageRect()
{
	int t = 0;
	QRect rect;
	if (this->_red) t = 0;
	else t = 84;
	switch (this->_type)
	{
	case JIANG: rect.setRect(0, t, 84, 84); break;
	case SHI: rect.setRect(84, t, 84, 84); break;
	case XIANG: rect.setRect(168, t, 84, 84); break;
	case MA: rect.setRect(252, t, 84, 84); break;
	case CHE: rect.setRect(336, t, 84, 84); break;
	case PAO: rect.setRect(420, t, 84, 84); break;
	case BING: rect.setRect(504, t, 84, 84); break;
	}
	return rect;
}

