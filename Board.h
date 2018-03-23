#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *ev);

    // init game
    void initBoard();

    // draw functions
    void drawStone(QPainter &painter, int _id);

    QPoint center(int row, int col);
    QPoint center(int id);

    /* judge rule */
    bool judgeWinner(QString &s);

    /* move rules */
    bool canMove(int moveid, int row, int col, int killid);
    bool canMoveJiang(int moveid, int row, int col);
    bool canMoveShi(int moveid, int row, int col);
    bool canMoveXiang(int moveid, int row, int col);
    bool canMoveMa(int moveid, int row, int col);
    bool canMoveChe(int moveid, int row, int col);
    bool canMovePao(int moveid, int row, int col, int killid);
    bool canMoveBing(int moveid, int row, int col);

    /* helping functions */
    bool isStone(int row, int col);
    bool getRowCol(QPoint pt, int &row, int &col);
    int getStoneCountAtLine(int, int, int, int);
private:
    /* game data */
    Stone _s[32];
    int _r;
    int _selectid;
    bool _bRedTurn;
    QPoint pointLeftTop;

    /* resource data */
    QImage boardImg, stoneImg;
};

#endif // BOARD_H
