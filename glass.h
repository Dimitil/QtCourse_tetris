#ifndef GLASS_H
#define GLASS_H

#include <QWidget>
#include <QVector>
#include "figure.h"

class glass : public QWidget
{
    Q_OBJECT
    const uint W = 20;
    static const QColor emptyCellQColor;
    const uint timeInterval = 100;
    Q_PROPERTY(uint rows READ rows WRITE setRows)
    Q_PROPERTY(uint columns READ columns WRITE setColumns)
    uint m_rows;
    uint m_columns;
    bool gameOn;
    int score;
    QVector<QVector<QColor>>glassArray;
    Figure *cur;
    Figure *next;
    int idTimer;
public:
    explicit glass(QWidget *parent = nullptr);
    ~glass();

    uint rows() const;

    uint columns() const;

    void resetCurAndNext();

    void addScore() {
        score++;
    }

    void dropFigure() {
        int Y = cur->j() / W + 2;
        int X = cur->i() / W;

        int newY = Y;
        for (int i = Y+1; i < glassArray.size(); i++) {
            if (glassArray[i][X] == emptyCellQColor) {
                newY++;
            }
            else {
                break;
            }
        }
        cur->setJ((newY-2)*W);
    }

public slots:
    void setRows(uint rows);

    void setColumns(uint columns);

    void slotGlassInit();

    void clearGlass();

    void slotNewGame();

    QSize windowSize();

    void shiftLeft();

    void shiftRight();

    void acceptFigure(Figure* fig);

    bool checkGlass() {
        bool wasRebuild = false;
        qDebug() << m_rows << m_columns;
        for (uint i = m_rows - 1; i > 2; i--) {
            for( uint j = 0; j < m_columns - 2 ; j++) { //чек строки
                if ( (glassArray[i][j] !=emptyCellQColor) &&
                     (glassArray[i][j] == glassArray[i][j+1]) &&
                     (glassArray[i][j] == glassArray[i][j+2]) )
                {
                    qDebug() << i << j;
                    addScore();
                    for ( uint g = i; g > 0; g--) {
                        glassArray[g][j] = glassArray[g-1][j];
                        glassArray[g][j+1]   = glassArray[g-1][j+1];
                        glassArray[g][j+2] = glassArray[g-1][j+2];
                    }
                    wasRebuild = true;
                }
                if ( (glassArray[i][j] !=emptyCellQColor) &&        // чек столбцов
                      (glassArray[i][j] == glassArray[i+1][j]) &&
                      (glassArray[i][j] == glassArray[i+2][j]) )
                {
                    for ( uint g = j; g > 0; g--) {
//                        glassArray[g][j] = glassArray[g-1][j];
//                        glassArray[g][j+1]   = glassArray[g-1][j+10];
//                        glassArray[g][j+2] = glassArray[g-1][j+2];
                    }
                    wasRebuild = true;
                }
            }
        }


        if (wasRebuild) {
            return checkGlass();
        }
        return false;
    }
signals:
    void signalScore(int);

    void signalGlassInit();

    void signalNewNext(Figure* NewFig);
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void timerEvent(QTimerEvent *event) override;
};

#endif // GLASS_H
