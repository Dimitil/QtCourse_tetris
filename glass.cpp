#include "glass.h"
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>

glass::glass(QWidget *parent) : QWidget(parent)
{
    gameOn = false;
    score = 0;
    connect(this, &glass::signalGlassInit, this, &glass::slotGlassInit, Qt::QueuedConnection);
    signalGlassInit();

    cur = new Figure;
    cur->setI(0);
    cur->setJ(0);

    next = new Figure;
    next->setI(0);
    next->setJ(0);
}

glass::~glass() {
    delete cur;
    delete next;
}

uint glass::rows() const
{
    return m_rows;
}

uint glass::columns() const
{
    return m_columns;
}

void glass::setRows(uint rows)
{
    m_rows = rows;
}

void glass::setColumns(uint columns)
{
    m_columns = columns;
}

void glass::slotGlassInit()
{
    glassArray.resize(m_rows);
    for (uint i = 0; i < m_rows; ++i) {
        glassArray[i].resize(m_columns);
        glassArray[i].fill(emptyCellQColor);
    }
}

void glass::clearGlass()
{
    slotGlassInit();
}

void glass::slotNewGame() {

    gameOn = true;
    clearGlass();
    cur ->MakeRandomColors();
    cur->setI(m_columns/2 * W);
    cur->setJ(0);
    next->MakeRandomColors();
    setFixedSize(windowSize());
    repaint();
    setFocus();
    idTimer = startTimer(timeInterval);
}

QSize glass::windowSize(){
    return QSize(W*m_columns, W*m_rows);
}

void glass::shiftLeft() {
    int tmp = cur->i();
    tmp -= W;
    if( (cur->i() != 0) && (glassArray[cur->j()/W + 2][tmp/W] == emptyCellQColor)) {
        cur->setI(tmp);
    }
}

void glass::shiftRight() {
    int tmp = cur->i();
    tmp += W;
    if( (cur-> i() != (m_columns-1) * W) && (glassArray[cur->j()/W + 2][tmp/W] == emptyCellQColor)) {
        cur->setI(tmp);
    }
}

const QColor glass::emptyCellQColor = Qt::gray;


void glass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::white);
    for (int i = 0; i < glassArray.size(); i++) {
        for (int j = 0; j < glassArray[i].size(); j++) {
            painter.setBrush(glassArray[i][j]);
            painter.drawRect(j*W, i*W, W, W);
        }
    }
    if (gameOn) {
       cur->paintFigure(painter);
    }
}

void glass::keyPressEvent(QKeyEvent *event)
{
    if(gameOn)
    {
        switch ( event->key()) {
            case Qt::Key_Left:
                shiftLeft();
                break;

            case Qt::Key_Right:
                shiftRight();
                break;

            case Qt::Key_Down:
                //циклически ”переливаем” цвета в фигурке сверху вниз
                cur->rotateColors(Rotate::DOWN);
                break;

            case Qt::Key_Up:
                //циклически ”переливаем” цвета в фигурке снизу вверх
                cur->rotateColors(Rotate::UP);
                break;

            case Qt::Key_Space:
                //«роняем» фигурку
                dropFigure();
                break;

            default:
                QWidget::keyPressEvent(event); //принажатии любых других клавиш вызываем базовую обработку события
        }
    }
    else {
        QWidget::keyPressEvent(event);
    }
    repaint();
}

//    Подсказка:
//    caseQt::Key_Space://«роняем» фигурку
    //ищем «куда ронять»
    //вызываем вспомогательный метод (так как нам нужно будет выполнить те же действия, когда при «падении» вниз фигурке некуда будет падать, то есть она «упрется»), например:
    // void AcceptColors(inti, intj);
    //в котором:
    //Добавляем фигурку в стакан
    //Анализируем и сбрасываем текущее содержимое стакана, вызываем например: voidCheckGlass();
    //Меняем местами next и cur
    //Настраиваем next и cur (у nextобнуляем индексы, а у curустанавливаем). Также генерируем новые цвета в next
    //эмитируем сигнал drawPattern(next); чтобы отрисовать в образце следующую фигурку

void glass::timerEvent(QTimerEvent *event) {
    uint futureJ = cur->j() + W;
    if ( ( (futureJ/W + 2) < m_rows) && (glassArray[futureJ/W+2][cur->i()/W] == emptyCellQColor)) { //если не дно стакана
        cur -> setJ(futureJ);
    }
    else {
        acceptFigure(cur);
        checkGlass();
        resetCurAndNext();
    }
    repaint();
}

void glass::resetCurAndNext() {
    cur = next;
    next -> MakeRandomColors();
    next->setI(m_columns/2 * W);
    next->setJ(0);
    //проанализировать где появляется и может быть это гейм овер

    if (glassArray[cur->rectCount - 1][m_columns/2] != emptyCellQColor) {
        killTimer(idTimer);
        QMessageBox::information(this, "Not bad", "Game over!");
    }
}

void glass::acceptFigure(Figure* fig) {
    uint column = fig -> i() / W;
    uint row = fig -> j() / W;

    for (uint i = 0; i < fig -> rectCount; i++) {
        glassArray[row+i][column] = fig->getColor(i);
    }
}
