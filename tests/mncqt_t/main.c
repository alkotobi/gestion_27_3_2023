#include <stdio.h>
#include "testing.h"
#include "cqdir_t.h"
#include "cqStandardPaths_t.h"

int main(int argc, char **argv)
{
    //assert(cqdir_test());
    //assert(cqStandardPaths_test());
    QApplication* app= QApplication_new(argc,argv);
    QWidget* wid = QWidget_new_window(0);
    QWidget_show(wid);
    
    
    QVBoxLayout* l= QVBoxLayout_test(wid);
    QBoxLayout_add_widget(l,QLineEdit_test(wid),0,0);
    QBoxLayout_add_widget(l,QPushButton_test(wid),0,0);
    QBoxLayout_add_widget_v1(l,QTableView_test(wid));
    QBoxLayout_add_widget_v1(l,QTableView_test(wid));
    QApplication_exec(app);
    printf("bismi allah\n");
    
    return 0;
}

