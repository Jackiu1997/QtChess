#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0);

    Stone _s[32];// 棋子数组
    int _r;// 棋子半径
    int _selectid;
    bool _bRedTurn;
	QPoint pointLeftTop;

    QPoint center(int row, int col);
    QPoint center(int id);

    QImage boardImg, stoneImg;

    bool isStone(int row, int col);
    int getStoneCountAtLine(int, int, int, int);
    // 棋子移动规则
    bool canMove(int moveid, int row, int col, int killid);
    bool canMoveJiang(int moveid, int row, int col);
    bool canMoveShi(int moveid, int row, int col);
    bool canMoveXiang(int moveid, int row, int col);
    bool canMoveMa(int moveid, int row, int col);
    bool canMoveChe(int moveid, int row, int col);
    bool canMovePao(int moveid, int row, int col, int killid);
    bool canMoveBing(int moveid, int row, int col);

    bool getRowCol(QPoint pt, int &row, int &col);
    void drawStone(QPainter &painter, int _id);

    void mouseReleaseEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *event);
private:

};

#endif // BOARD_H
