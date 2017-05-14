#include "fifteens.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Fifteens fif(4,4);
    fif.show();

    return a.exec();
}
