#include "main.h"
#include "MainWindow.h"

IMPLEMENT_APP(MyIDE)

bool MyIDE::OnInit()
{
    MainWindow * mainWin = new MainWindow("HSCode");
    mainWin->Show(true);

    return true;
}