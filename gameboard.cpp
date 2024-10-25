#include <QGraphicsEllipseItem>
#include <QDebug>
#include "gameboard.h"
#include <QGraphicsProxyWidget>
#include <QIcon>
#include <QPixmap>


GameBoard::GameBoard(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    darkWoodBrush = QBrush(QColor(108, 51, 24));
    blackPen = QPen(QColor(108, 51, 24));
    noPen = QPen(QColor(255, 255, 255, 0));
    noPen.setWidth(0);
    noBrush = QBrush(QColor(255, 255, 255, 0));
    blackPen.setWidth(3);
    pauseButton = new QPushButton(this);
    QIcon icon("../../media/pause-button.png");
    pauseButton->setIcon(icon);
    pauseButton->setIconSize(QSize(60, 60));
    pauseButton->setObjectName("pauseButton");
    QPixmap pixmap("../../media/Seamless-Wood-Texture-3.jpg");
    QBrush customBrush(pixmap);
    board = scene->addRect(5, 5, 790, 790, blackPen, customBrush);
    cellRadius = 17;
    slotRadius = 5;
    lines[0] = scene->addLine(400, 100, 400, 300);
    lines[1] = scene->addLine(500, 400, 700, 400);
    lines[2] = scene->addLine(400, 500, 400, 700);
    lines[3] = scene->addLine(100, 400, 300, 400);
    lines[0]->setPen(blackPen);
    lines[1]->setPen(blackPen);
    lines[2]->setPen(blackPen);
    lines[3]->setPen(blackPen);
    for (int i = 0; i < 3; i++)
    {
        outlines[i] = scene->addRect(100 + i * 100, 100 + i * 100, 600 - i * 200, 600 - i * 200, blackPen);
        for (int j = 0; j < 3; j++)
        {
            slot[i][j] = scene->addEllipse(100 + i * 100 + ((600 - i * 200) / 2) * j - slotRadius, 100 + i * 100 - slotRadius, 2 * slotRadius, 2 * slotRadius, blackPen, darkWoodBrush);
            cells[i][j] = scene->addEllipse(100 + i * 100 + ((600 - i * 200) / 2) * j - cellRadius, 100 + i * 100 - cellRadius, 2 * cellRadius, 2 * cellRadius, noPen, noBrush);
        };
        slot[i][3] = scene->addEllipse(100 + i * 100 + (600 - i * 200) - slotRadius, 100 + i * 100 + (600 - i * 200) / 2 - slotRadius, 2 * slotRadius, 2 * slotRadius, blackPen, darkWoodBrush);
        cells[i][3] = scene->addEllipse(100 + i * 100 + (600 - i * 200) - cellRadius, 100 + i * 100 + (600 - i * 200) / 2 - cellRadius, 2 * cellRadius, 2 * cellRadius, noPen, noBrush);
        for (int j = 4; j < 7; j++)
        {
            slot[i][j] = scene->addEllipse(100 + i * 100 + ((600 - i * 200) / 2) * (6 - j) - slotRadius, 100 + i * 100 + (600 - i * 200) - slotRadius, 2 * slotRadius, 2 * slotRadius, blackPen, darkWoodBrush);
            cells[i][j] = scene->addEllipse(100 + i * 100 + ((600 - i * 200) / 2) * (6 - j) - cellRadius, 100 + i * 100 + (600 - i * 200) - cellRadius, 2 * cellRadius, 2 * cellRadius, noPen, noBrush);
        };
        slot[i][7] = scene->addEllipse(100 + i * 100 - slotRadius, 100 + i * 100 + (600 - i * 200) / 2 - slotRadius, 2 * slotRadius, 2 * slotRadius, blackPen, darkWoodBrush);
        cells[i][7] = scene->addEllipse(100 + i * 100 - cellRadius, 100 + i * 100 + (600 - i * 200) / 2 - cellRadius, 2 * cellRadius, 2 * cellRadius, noPen, noBrush);
    };
    blackPen.setWidth(1);
    QGraphicsProxyWidget *proxy = scene->addWidget(pauseButton);
    proxy->setPos(1000, 100);
    setRenderHint(QPainter::Antialiasing);
    // setViewportUpdateMode(QGraphicsView::NoViewportUpdate); // Disable automatic viewport updates
    // setTransformationAnchor(QGraphicsView::NoAnchor);
    // setResizeAnchor(QGraphicsView::NoAnchor);
    // Ensure the graphicsView spans the entire window initially
    g = Game();
    me = HumanPlayer();
    ai = AIPlayer();
    m = Move();
    playerColor = WHITE;
    awaitRemove = false;
    awaitSlide = false;
    setMouseTracking(true);
    qDebug() << "gameboard created\n";
    connect(pauseButton, SIGNAL (clicked()), this, SLOT (pauseGame()));
}


GameBoard::~GameBoard() {
    qDebug() << "gameboard destroyed\n";
}


void GameBoard::setGameSettings(GameMode m, int d, int p)
{
    gameMode = m;
    g.setGameMode(m);
    if (m == PvAI)
    {
        qDebug() << "player vs AI";
        ai.setDifficulty(d);
        g.setDifficulty(d);
        switch(p)
        {
            case 1:
                playerColor = WHITE;
                break;
            case 2:
                playerColor = BLACK;
                applyAIMove();
                break;
            case 3:
                int i = rand() % 2;
                switch(i)
                {
                    case 0:
                        playerColor = WHITE;
                        break;
                    case 1:
                        playerColor = BLACK;
                        applyAIMove();
                        break;
                };
                break;
        };
    };
    g.setPlayerColor(playerColor);
    return;
}


void GameBoard::loadGame(QString s)
{
    s.prepend("../../savegames/");
    qDebug() << "game loading";
    g.load(s);
    gameMode = g.getGameMode();
    playerColor = g.getPlayerColor();
    ai.setDifficulty(g.getDifficulty());
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 8; j++)
        {
            if (g.getCurrentState().getCellValue(i, j) == WHITE || g.getCurrentState().isLocked(WHITE, i, j))
            {
                cells[i][j]->setBrush(QBrush(Qt::white));
            }
            else if (g.getCurrentState().getCellValue(i, j) == BLACK || g.getCurrentState().isLocked(BLACK, i, j))
            {
                cells[i][j]->setBrush(QBrush(Qt::black));
            };
        };
    };
    if (gameMode == PvAI &&  playerColor != g.getcurrentTurn())
    {
        applyAIMove();
    };
    return;
}

void GameBoard::saveGame()
{
    g.save();
}

void GameBoard::mousePressEvent(QMouseEvent *event)
{

    if ((gameMode == PvAI && g.getcurrentTurn() != playerColor) || g.getCurrentState().checkWin() != EMPTY) { return; };
    // Call the base class implementation
    QGraphicsView::mousePressEvent(event);

    // Convert the mouse position to scene coordinates
    QPointF scenePos = mapToScene(event->pos());

    // Print mouse coordinates
    // qDebug() << "Mouse Clicked at Scene Coordinates: " << scenePos;

    Cell nextTurn = (g.getcurrentTurn() == WHITE) ? BLACK : WHITE;

    m.setColor(g.getcurrentTurn());
    // g.getCurrentState().display();
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 8; j++)
        {
            if (cells[i][j]->contains(scenePos))
            {
                // qDebug() << "Ellipse (" << i << ", " << j << ") clicked!\n";
                if (g.getMoveCount() < 18)
                {
                    if (awaitRemove)
                    {
                        if (g.getCurrentState().getCellValue(i, j) == nextTurn)
                        {
                            m.set_remove_i(i);
                            m.set_remove_j(j);
                            g.makeMove(m);
                            m.set_remove_i(3);
                            qDebug() << "cell" << i << j << "removed\n";
                            cells[i][j]->setBrush(noBrush);
                            cells[i][j]->setPen(noPen);
                            awaitRemove = false;
                            if (g.getCurrentState().checkWin() != EMPTY)
                            {
                                gameOver();
                                return;
                            };
                            if (gameMode == PvAI) { applyAIMove(); };


                        };
                        return;
                    };

                    if (g.getcurrentTurn() == WHITE && g.getCurrentState().getCellValue(i, j) == EMPTY)
                    {
                        cells[i][j]->setBrush(QBrush(Qt::white));
                        cells[i][j]->setPen(blackPen);
                    }
                    else if (g.getcurrentTurn() == BLACK && g.getCurrentState().getCellValue(i, j) == EMPTY)
                    {
                        cells[i][j]->setBrush(QBrush(Qt::black));
                        cells[i][j]->setPen(blackPen);
                    }
                    else
                    {
                        return;
                    };
                    m.set_dest_i(i);
                    m.set_dest_j(j);
                    if (j % 2 == 0)
                    {
                        if ((g.getCurrentState().getCellValue(i, j + 1) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, j + 1))
                            && (g.getCurrentState().getCellValue(i, (j + 2) % 8) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, (j + 2) % 8)))
                        {
                            qDebug() << "awaiting removal";
                            awaitRemove = true;
                            return;
                        };
                        if ((g.getCurrentState().getCellValue(i, mod(j - 1, 8)) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, mod(j - 1, 8)))
                            && (g.getCurrentState().getCellValue(i, mod(j - 2, 8)) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, mod(j - 2, 8))))
                        {
                            awaitRemove = true;
                            return;
                        };
                    }
                    else
                    {
                        if ((g.getCurrentState().getCellValue(i, j - 1) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, j - 1))
                            && (g.getCurrentState().getCellValue(i, (j + 1) % 8) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, (j + 1) % 8)))
                        {
                            awaitRemove = true;
                            return;
                        };
                        if ((g.getCurrentState().getCellValue((i + 1) % 3, j) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), (i + 1) % 3, j))
                            && (g.getCurrentState().getCellValue((i + 2) % 3, j) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), (i + 2) % 3, j)))
                        {
                            awaitRemove = true;
                            return;
                        };
                    };
                    g.makeMove(m);
                    if (g.getCurrentState().checkWin() != EMPTY)
                    {
                        gameOver();
                        return;
                    };
                    if (gameMode == PvAI) { applyAIMove(); };
                    return;
                };

                if (awaitRemove)
                {
                    if (g.getCurrentState().getCellValue(i, j) == nextTurn)
                    {
                        m.set_remove_i(i);
                        m.set_remove_j(j);
                        g.makeMove(m);
                        m.set_remove_i(3);
                        cells[i][j]->setBrush(noBrush);
                        cells[i][j]->setPen(noPen);
                        awaitRemove = false;
                        awaitSlide = false;
                        qDebug() << "pawn removed\n";
                        if (g.getCurrentState().checkWin() != EMPTY)
                        {
                            qDebug() << "Game Over\n";
                            gameOver();
                            return;
                        };
                        if (gameMode == PvAI) { applyAIMove(); };
                    };
                    return;
                };

                if (awaitSlide)
                {
                    if (cells[i][j]->brush() == QBrush(Qt::red))
                    {
                        if (g.getcurrentTurn() == WHITE)
                        {
                            cells[i][j]->setBrush(QBrush(Qt::white));
                            cells[i][j]->setPen(blackPen);
                        }
                        else if (g.getcurrentTurn() == BLACK)
                        {
                            cells[i][j]->setBrush(QBrush(Qt::black));
                            cells[i][j]->setPen(blackPen);
                        };
                        awaitSlide = false;
                        return;
                    };

                    if (g.getCurrentState().getCellValue(i, j) == EMPTY)
                    {
                        if (g.getCurrentState().getPawnsLeft(g.getcurrentTurn()) > 3)
                        {
                            bool validPosition = false;
                            if (i == m.get_source_i() && j  == (m.get_source_j() + 1) % 8 || j == mod(m.get_source_j() - 1, 8) )
                            {
                                validPosition = true;
                            };
                            if (!validPosition
                                && j % 2 == 1
                                && (j == m.get_source_j())
                                && ((i > m.get_source_i() && (i - m.get_source_i()) % 3 == 1) || (i < m.get_source_i() && (m.get_source_i() - i) % 3 == 1)))
                            {
                                validPosition = true;
                            };
                            if (!validPosition) { return; };
                        };
                        if (g.getcurrentTurn() == WHITE)
                        {
                            cells[i][j]->setBrush(QBrush(Qt::white));
                            cells[i][j]->setPen(blackPen);
                        }
                        else if (g.getcurrentTurn() == BLACK)
                        {
                            cells[i][j]->setBrush(QBrush(Qt::black));
                            cells[i][j]->setPen(blackPen);
                        };
                        m.set_dest_i(i);
                        m.set_dest_j(j);
                        cells[m.get_source_i()][m.get_source_j()]->setBrush(noBrush);
                        cells[m.get_source_i()][m.get_source_j()]->setPen(noPen);

                        if (j % 2 == 0)
                        {
                            if (m.get_source_j() != j + 1
                                && (g.getCurrentState().getCellValue(i, j + 1) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, j + 1))
                                && (g.getCurrentState().getCellValue(i, (j + 2) % 8) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, (j + 2) % 8)))
                            {
                                qDebug() << "awaiting removal 1\n";
                                awaitRemove = true;
                                return;
                            };
                            if (m.get_source_j() != mod(j - 1, 8)
                                && (g.getCurrentState().getCellValue(i, mod(j - 1, 8)) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, mod(j - 1, 8)))
                                && (g.getCurrentState().getCellValue(i, mod(j - 2, 8)) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, mod(j - 2, 8))))
                            {
                                qDebug() << "awaiting removal 2\n";
                                awaitRemove = true;
                                return;
                            };
                        }
                        else
                        {
                            if (m.get_source_j() != j - 1
                                && m.get_source_j() != (j + 1) % 8
                                && (g.getCurrentState().getCellValue(i, j - 1) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, j - 1))
                                && (g.getCurrentState().getCellValue(i, (j + 1) % 8) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, (j + 1) % 8)))
                            {
                                qDebug() << "awaiting removal 3\n";
                                awaitRemove = true;
                                return;
                            };
                            if (m.get_source_i() != (i + 1) % 3
                                && m.get_source_i() != (i + 2) % 3
                                && (g.getCurrentState().getCellValue((i + 1) % 3, j) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), (i + 1) % 3, j))
                                && (g.getCurrentState().getCellValue((i + 2) % 3, j) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), (i + 2) % 3, j)))
                            {
                                qDebug() << "awaiting removal 4\n";
                                awaitRemove = true;
                                return;
                            };
                        };
                        g.makeMove(m);
                        awaitSlide = false;
                        if (g.getCurrentState().checkWin() != EMPTY)
                        {
                            gameOver();
                            return;
                        };
                        if (gameMode == PvAI) { applyAIMove(); };
                        return;
                    };
                    return;
                };

                if (g.getCurrentState().getCellValue(i, j) == g.getcurrentTurn() || g.getCurrentState().isLocked(g.getcurrentTurn(), i, j))
                {
                    awaitSlide = true;
                    m.set_source_i(i);
                    m.set_source_j(j);
                    cells[i][j]->setBrush(QBrush(Qt::red));
                    return;
                };
            };
        };
    };
}


void GameBoard::gameOver()
{
    Cell nextTurn = (g.getcurrentTurn() == WHITE) ? BLACK : WHITE;
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 8; j++)
        {
            if (g.getCurrentState().getCellValue(i, j) == nextTurn || g.getCurrentState().isLocked(nextTurn, i, j))
            {
                cells[i][j]->setBrush(QBrush(Qt::green));
            };
        };
    };
    return;
}


void GameBoard::applyAIMove()
{
    Move m = ai.getNextMove(g);
    if (m.get_source_i() != 3)
    {
        cells[m.get_source_i()][m.get_source_j()]->setBrush(noBrush);
        cells[m.get_source_i()][m.get_source_j()]->setPen(noPen);
    };
    if (m.get_remove_i() != 3)
    {
        cells[m.get_remove_i()][m.get_remove_j()]->setBrush(noBrush);
        cells[m.get_remove_i()][m.get_remove_j()]->setPen(noPen);
    };
    qDebug() << m.get_dest_i() << m.get_dest_j() << "\n";
    if (playerColor == WHITE)
    {
        cells[m.get_dest_i()][m.get_dest_j()]->setBrush(QBrush(Qt::black));
        cells[m.get_dest_i()][m.get_dest_j()]->setPen(blackPen);
    }
    else
    {
        cells[m.get_dest_i()][m.get_dest_j()]->setBrush(QBrush(Qt::white));
        cells[m.get_dest_i()][m.get_dest_j()]->setPen(blackPen);
    }
    g.makeMove(m);
    if (g.getCurrentState().checkWin() != EMPTY)
    {
        gameOver();
        return;
    };
}


void GameBoard::pauseGame()
{
    emit pauseButtonClicked();
}


void GameBoard::reinitialize()
{
    for (short i = 0; i < 3 ; i++)
    {
        for (short j = 0; j < 8; j++)
        {
            cells[i][j]->setBrush(noBrush);
            cells[i][j]->setPen(noPen);
        };
    };
    m = Move();
    g = Game();
    awaitRemove = false;
    awaitSlide = false;
    playerColor = WHITE;
}
