//
// Created by merhab on 2023/3/25.
//
#include <stdio.h>
#include "cqStandardPaths.h"
#include "cqapplication.h"
#include "cqwidget.h"
#include "frmlogin.h"
#include "tbluser.h"

int main(int argc, char **argv)
{
    QApplication* app= QApplication_new(argc,argv);
    QWidget* wid = QWidget_new_window(0);
    Ui_Window_login* frm=frmlogin_new();
    frmlogin_setup_wid(frm,wid);
    QWidget_show(wid);
    QApplication_exec(app);
    printf("heello");
    return 0;
}