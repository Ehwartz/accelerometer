
#include "ui.h"
#include <QApplication>


#include <Windows.h>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    QMainWindow mainWindow;
    Ui_MainWindow ui;
    ui.setupUi(&mainWindow);
    mainWindow.show();
    return app.exec();

}
