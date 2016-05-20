#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "chboardmodel.h"
#include "chhumanplayer.h"
#include "chsimplevalidator.h"
#include "chexception.h"

int main(int argc, char *argv[])
{
    try {
        QGuiApplication app(argc, argv);
        ChBoardModel boardModel;
        ChHumanPlayer whitePlayer(CH_WHITE_COLOR);
        ChHumanPlayer blackPlayer(CH_BLACK_COLOR);
        ChSimpleValidator validator;

        whitePlayer.setValidator(&validator);
        blackPlayer.setValidator(&validator);

        boardModel.setPlayers(&whitePlayer, &blackPlayer);
        boardModel.setValidator(&validator);

        QObject::connect(&boardModel, SIGNAL(squareClicked(int, int, const ChSquares &)),
            &whitePlayer, SLOT(onSquareClicked(int, int, const ChSquares &)));

        QObject::connect(&boardModel, SIGNAL(squareClicked(int, int, const ChSquares &)),
            &blackPlayer, SLOT(onSquareClicked(int, int, const ChSquares &)));

        // Valgrind reports about memory leak in FileDialog class at this point.
        // Looks like Qt internals issue.
        QQmlApplicationEngine engine;
        QQmlContext *ctxt = engine.rootContext();
        ctxt->setContextProperty("bModel", &boardModel);

        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

        app.setWindowIcon(QIcon(":/images/king_white.png"));
        return app.exec();
    }
    catch (ChException &e) {
        qDebug("ERROR. %s %d %s", qPrintable(e.file()), e.line(),
            qPrintable(e.description()));
        return -1;
    }
    catch (std::exception &e) {
        qDebug("ERROR. %s", e.what());
        return -2;
    }
    catch (...) {
        qDebug("ERROR");
        return -3;
    }
    return 0;
}

/*! \mainpage QmlChess
 *
 * \section Introduction
 *
 * \b QmlChess is a local multiplayer chess game. It is implemented using Qt + QML.
 * boost and C++11 are not used.
 *
 * \section User Interface
 * Once the application starts the Home screen appears. It contains the following elements:
 * - \b Start button – starts a new game. Leads to the Play screen.
 * - \b Load button – allows user to load saved game. Leads to the Replay screen.
 * - Empty chess board
 *
 * \image html screen1.png
 *
 * Play screen elements:
 * - \b Stop button – stops the game and leads to the Home screen.
 * - \b Save button - saves the game history to a file.
 * - Chess pieces are on the board (in initial position).
 *
 * \image html screen2.png
 *
 * User is able to move the pieces with
 * mouse according to the standard chess rules (click to select the piece, then click on
 * highlighted square to perform the move). Turn by turn rule is followed (white turn -
 * black turn - white - …). Current player is indicated by the rectangle around the King.
 * Castling, check, checkmate, promotion, En passant are not implemented.
 *
 * Replay screen elements:
 * - \b Start button – starts a new game. Leads to the Play screen.
 * - \b Load button - allows user to load saved game. Leads to the Replay screen.
 * - \b "prev" button - undo the move.
 * - \b "next" button - redo the move.
 * - Chess board with pieces.

 * \image html screen3.png
 *
 * Application loads a game history and allows to play it step by step using two buttons:
 * “prev” and “next”.
 *
 * \section Licenses
 *
 * Application uses third-party images:
 * - http://www.fatcow.com/free-icons (License: http://creativecommons.org/licenses/by/4.0/).
 * - https://commons.wikimedia.org/wiki/File:Chess_Pieces_Sprite.svg (License:
 * https://creativecommons.org/licenses/by-sa/3.0/deed.en).
 *
 * \section Terminology
 *
 * \b Selected square is the square clicked by the user to move piece from it.
 *
 * \b Highlighted squares are the possible target squares to move the selected piece.
 *
 * \b Row is used instead of \b rank. Row numbers are changed from 0 to \ref CH_BOARD_SIZE - 1.
 *
 * \b Column is used instead of \b files. Column numbers are changed from 0 to
 * \ref CH_BOARD_SIZE - 1.
 *
 * \section Architecture
 *
 * QML \b ChMainForm.qml pulls data from the model class \ref ChBoardModel.
 *
 * \ref ChBoardModel is configured on startup (in main() function) with players. Player class
 * should implement \ref ChPlayer interface. Application uses \ref ChHumanPlayer class inherited
 * from \ref ChPlayer.
 *
 * Also \ref ChBoardModel is configured with validator. Validator class should implement
 * \ref ChValidator interface. Application uses \ref ChSimpleValidator class. The same validator is
 * used by players (it is useful for Human player but not mandatory in accordance to \ref ChPlayer
 * interface).
 *
 * \ref ChBoardModel is inherited from \b QAbstractListModel. \b ChBoard.qml uses it as a data
 * model.
 *
 * Images below explain how ChBoardModel interacts with two Human players.
 *
 * First image shows the interaction with abstract Player during 2 moves.
 *
 * \image html dfm.png
 *
 * Second image shows additional interactions
 * specific to Human Player. All \ref ChHumanPlayer-specific connections are esteblished in main()
 * function, \ref ChHumanPlayer is not used directly in \ref ChBoardModel.
 *
 * \image html dfm1.png
 *
 * Board state is kept in \ref ChBoardData. \ref ChBoardModel owns that object. Read-only
 * \ref ChBoardData is available to players and to validator. Changes in data may be performed
 * only by \ref ChBoardModel.
 *
 * Board squares may be referred using \ref ChSquare objects. Squares on board are numbered from 0
 * till (\ref CH_BOARD_SIZE * CH_BOARD_SIZE - 1) from left to right from bottom to top.
 *
 * The \ref ChPiece may be located on the square.
 * \ref ChPiece implements pattern \b FlyWeight, references to pieces are provided by
 * \ref ChBoardData.
 *
 * If the user clicks the square with the piece on it to move then the ckicked square is marked
 * as \b selected and possible target squares are marked as \b highlighted. Information about
 * selected and highlighted squares is stored in \ref ChSelection. \ref ChBoardModel owns that
 * object.
 *
 * All moves are represented as \ref ChMoveCommand inherited from \b QUndoCommand, and Replay
 * mode uses \b QUndoStack to navigate between previous and next moves.
 *
 * Saved games are stored in XML format. XML Schema validation is performed before game file
 * parsing. Saving and loading are implemented in \ref ChGameParser class. It is inherited from
 * \ref ChParserBase. \ref ChParserBase implements basic XML manipulations (load XML document,
 * save it, validate using XML Schema).
 *
 * Exceptions may be raised during Save and Load operations. Such exceptions are catched in
 * \ref ChBoardModel. The reason of the problem is reported to the user and the user may continue
 * to work with the application. All other exceptions mean error in application and are
 * catched in the main() function. Base class for exception is \ref ChException.
 *
 */

