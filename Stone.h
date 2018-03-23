#ifndef STONE_H
#define STONE_H

#include <QString>
#include <qrect.h>


class Stone
{
public:
	enum TYPE { JIANG, CHE, PAO, MA, XIANG, SHI, BING };

	int _row;
	int _col;
	int _id;
	bool _dead;
	bool _red;
	TYPE _type;

    /* init stone data */
	void init(int id);
    /* get stone rect on stones.png */
	QRect getImageRect();
};

#endif // STONE_H
