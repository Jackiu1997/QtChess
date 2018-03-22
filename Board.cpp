#include "Board.h"
#include <QPainter>
#include <QMouseEvent>

Board::Board(QWidget *parent) :
    QWidget(parent)
{
	// 固定窗口大小
	this->setMaximumSize(900, 900);
	this->setMinimumSize(900, 900);

	// 初始化棋子
    for(int i = 0; i < 32; i++)
    {
        _s[i].init(i);
    }

    _selectid = -1;
    _bRedTurn = true;
	pointLeftTop.setX(115);
	pointLeftTop.setY(75);
}

void Board::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int d = 84;
    _r = d / 2;

	// 棋盘绘制
    QImage board("://res/board.png");
	painter.drawImage(0, 0, board);

    // 绘制棋子
    for(int i = 0; i < 32; i++)
    {
        drawStone(painter, i);
    }
}

// 绘制棋子模块
void Board::drawStone(QPainter &painter, int id)
{
    if(_s[id]._dead) return;
    QPoint c = center(id);
    QRect paintRect = QRect(c.x() - _r, c.y() - _r, _r * 2, _r * 2);
	QRect imageRect = _s[id].getImageRect();

    QImage stone("://res/stones.png");
	painter.drawImage(paintRect, stone, imageRect);
}

QPoint Board::center(int row, int col)
{
    QPoint ret;
	ret.rx() = pointLeftTop.rx() + 2 * _r * col;
    ret.ry() = pointLeftTop.ry() + 2 * _r * row;
    return ret;
}

QPoint Board::center(int id)
{
    return center(_s[id]._row, _s[id]._col);
}


// 象棋规则模块
bool Board::canMove(int moveid, int row, int col, int killid)
{
    // 判断棋子移动目标选择可行性
    if(killid == -1);// 棋子默认的 ID -1 解决方法
    else if(_s[moveid]._red == _s[killid]._red) {
        _selectid = killid;
        update();

        return false;
    }

    // 对应棋子规则
    switch (_s[moveid]._type) {
    case Stone::JIANG:
        return canMoveJiang(moveid, row, col);
        break;
    case Stone::SHI:
        return canMoveShi(moveid, row, col);
        break;
    case Stone::XIANG:
        return canMoveXiang(moveid, row, col);
        break;
    case Stone::MA:
        return canMoveMa(moveid, row, col);
        break;
    case Stone::CHE:
        return canMoveChe(moveid, row, col);
        break;
    case Stone::PAO:
        return canMovePao(moveid, row, col, killid);
        break;
    case Stone::BING:
        return canMoveBing(moveid, row, col);
        break;
    default:
        return true;
        break;
    }
    return true;
}

bool Board::isStone(int row, int col) {
    for(int i = 0; i < 32; i++) {
       if(_s[i]._row == row && _s[i]._col == col) return true;
    }
    return false;
}

int Board::getStoneCountAtLine(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if(row1 != row2 && col1 != col2) return -1;
    if(row1 == row2 && col1 == col2) return -1;

    if(row1 == row2) {
        int min = col1 < col2 ? col1 : col2;
        int max = col1 > col2 ? col1 : col2;
        for(int col = min+1; col < max; col++) {
            if(isStone(row1, col)) ret++;
        }
    }
    else {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 > row2 ? row1 : row2;
        for(int row = min+1; row < max; row++) {
            if(isStone(row, col1)) ret++;
        }
    }

    return ret;
}

// JIANG
bool Board::canMoveJiang(int moveid, int row, int col)
{
    if(_s[moveid]._red) {
        if(row > 2) return false;
    }
    else {
        if(row < 7) return false;
    }

    if(col < 3) return false;
    if(col > 5) return false;

    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = dr * dr + dc * dc;

    if(d == 1 || d == 10) return true;

    return false;
}

// SHI
bool Board::canMoveShi(int moveid, int row, int col)
{
    if(_s[moveid]._red) {
        if(row > 2) return false;
    }
    else {
        if(row < 7) return false;
    }

    if(col < 3) return false;
    if(col > 5) return false;

    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = dr * dr + dc * dc;

    if(d == 2) return true;
    return false;
}

// XIANG
bool Board::canMoveXiang(int moveid, int row, int col)
{
    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = dr * dr + dc * dc;
    // 防止横竖直接跳
    if(dr == 0 || dc == 0) return false;

    if(d == 8) {
        // 偏相脚检测
        if(dr > 0) {
            if(dc > 0) {
                if(isStone(row + 1, col + 1)) return false;
            }
            else {
                if(isStone(row + 1, col - 1)) return false;
            }
        }
        else {
            if(dc > 0) {
                if(isStone(row - 1, col - 1)) return false;
            }
            else {
                if(isStone(row - 1, col + 1)) return false;
            }
        }
        return true;
    }
    return false;
}

// MA
bool Board::canMoveMa(int moveid, int row, int col)
{
    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = dr * dr + dc * dc;

    if(d == 5) {
        // 偏马脚检测
        if(abs(dr) == 1) {
            if(dc > 0) {
                if(isStone(_s[moveid]._row, _s[moveid]._col - 1)) return false;
            }
            else {
                if(isStone(_s[moveid]._row, _s[moveid]._col + 1)) return false;
            }
        }
        else if(abs(dc) == 1) {
            if(dr > 0) {
                if(isStone(_s[moveid]._row - 1, _s[moveid]._col)) return false;
            }
            else {
                if(isStone(_s[moveid]._row + 1, _s[moveid]._col)) return false;
            }
        }
        return true;
    }

    return false;
}

// CHE
bool Board::canMoveChe(int moveid, int row, int col)
{
    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = dr * dr + dc * dc;
    // 路径检测（路径上不存在棋子）
    if(d == 1) return true;
    else if((dr == 0 || dc == 0) && getStoneCountAtLine(_s[moveid]._row, _s[moveid]._col, row, col) == 0) return true;

    return false;
}

// PAO
bool Board::canMovePao(int moveid, int row, int col, int killid)
{
    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = dr * dr + dc * dc;
    // 路径检测（路径上有两个棋子）
    if(d == 1) return true;
    int ret = getStoneCountAtLine(_s[moveid]._row, _s[moveid]._col, row, col);

    if(killid != -1 && ret == 1) return true;
    else if(killid == -1 && ret == 0) return true;

    return false;
}

// BING
bool Board::canMoveBing(int moveid, int row, int col)
{
    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = dr * dr + dc * dc;

    if(_s[moveid]._red) {
        if(dr > 0) return false;
        // 小兵过河
        else if(_s[moveid]._row > 4) {
            if(d == 1) return true;
        }
        // 未过河
        else if(_s[moveid]._row < 5) {
            if(dc == 0 && d == 1) return true;
        }
    }
    else {
        if(dr < 0) return false;
        // 小兵过河
        else if(_s[moveid]._row < 5) {
            if(d == 1) return true;
        }
        // 未过河
        else if(_s[moveid]._row > 4) {
            if(dc == 0 && d == 1) return true;
        }
    }

    return false;
}

// 获取鼠标点击棋子行列
bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    for(row = 0; row <= 9; row++)
    {
        for(col = 0; col <= 10; col++)
        {
            QPoint c = center(row, col);
            int dx = c.x() - pt.x();
            int dy = c.y() - pt.y();
            int dist = dx*dx + dy*dy;
            if(dist < _r*_r) return true;
        }
    }
    return false;
}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt = ev->pos();
    // 像素值转化为行列值
    int row, col;
    bool bRet = getRowCol(pt, row, col);
    // 点到棋盘外区域
    if(!bRet) return;

    int i;
    bool tag = false;
    // 获取第一次点击的棋子id
    int clickid = -1;

    for(i = 0; i < 32; i++)
    {
        if(_s[i]._row == row && _s[i]._col == col && !_s[i]._dead)
        {
            tag = true;
            break;
        }
    }

    if(tag) clickid = i;

    // 如果一次点击
    if(_selectid == -1)
    {
        if(clickid != -1)
        {
            if(_bRedTurn == _s[clickid]._red)
            {
                _selectid = clickid;
                update();
            }
        }
    }
    // 如果二次点击
    else
    {
        if(canMove(_selectid, row, col, clickid))
        {
            _s[_selectid]._row = row;
            _s[_selectid]._col = col;
            if(clickid != -1)
            {
               _s[clickid]._dead = true;
            }
            _selectid = -1;
            _bRedTurn = !_bRedTurn;
            update();
        }
    }
}
