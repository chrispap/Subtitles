#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

public slots:
    void goTransparrent();

private slots:
    void on_btn_goTransp_clicked();

protected:
    void enterEvent ( QMouseEvent * event );
};

#endif // MAINWINDOW_H
