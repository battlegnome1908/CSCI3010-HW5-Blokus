#include "plotwindow.h"
#include "startupdialog.h"


#include <QApplication>

/** Testing main */
// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     startupDialog dialog;
//     if (dialog.exec() == QDialog::Accepted) {
//         PlotWindow window;
//         window.show();
//         return app.exec();
//     }

//     return 0;
// }


/** Notes:
 *  Design patterns used deliberately:
 *      1. Factory pattern: used in shape factory to create standard shapes for each player in one place
 *      2. Protoype: used to turn bomb-fragmented shapes into their own shpae
 *  Naturally the QApplication is a singleton.
 *
 *  Most legwork is done by PlotWindow, and I again note that I probably don't *need* game.cpp when it's all
 *   wrapped up inside of calls to player and board logic. I'll keep that in mind moving forwards.
 *   I found that keeping track of variables between files wasn't as easy in this program and need to print
 *   off the design sheets as well as update them as I work moving fowards.
 *
 *  Future aspirations: Simplify and combine layers of code when possible. I truly don't like the huge for-loops
 *   I have right now to iterate through QVector items. I imagine using maps would have been wise here but I
 *   got lost in the QSet documentation.
 *   Additionally, removing the QMessageBox and replacing them with a custom UI aimed at communicating with players
 *   without the annoying Windows default BING would be a wonderful quality of life change.
 *
 *  I have three shape-files. One is a factory to generate the shapes. One is the actual blocks and their logic,
 *   the last is the displayed item or a QObject. I spoke with another classmate who is doing Blokus and they
 *   said I could wrap them into one encompassing file but this, at least in my mind, seperates the logic and the
 *   graphics from each other which helped in debugging and clear lines of code.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    startupDialog s;
    if (s.exec() == QDialog::Accepted) {
        PlotWindow w(s.playerNames, s.playerColors, s.playerCount);
        w.show();
        return a.exec();
    }

    return 0;
}
