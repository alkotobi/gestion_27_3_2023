//
// Created by merhab on 2023/3/25.
//
#include "frmlogincpp.h"
extern "C"
void frmlogin_setup_wid(Ui_Window_login* ui,QWidget *parent) {
    ui->setupUi(parent);
}

extern "C"
Ui_Window_login* frmlogin_new(){
    Ui_Window_login* a;
    a->btn_close->click.connect()
    return new (std::nothrow) Ui_Window_login();
}