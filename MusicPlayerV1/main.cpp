#include "playerlogic.h"
#include <QApplication>

#include "connectsqlite.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConnectSQLite sql;

    PlayerLogic w;
    w.showMainWidget();

    QFile skinFile(":/skins/icons/skins.css");
    if(skinFile.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(skinFile.readAll());
        skinFile.close();
    }

    return a.exec();
}
