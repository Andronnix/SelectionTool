#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <qmath.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    

public slots:
    void openFile(const QString &path = QString());
    void nextGesture();
    void prevGesture();

private:
    Ui::MainWindow *ui;    
    QDomElement docElem;
    QDomNode curType,curGest;
    QGraphicsScene userGestureView,typeGestureView;
    void setupFileMenu();
    void setupButtons();
    void setupViews();
    void drawGesture();
};

#endif // MAINWINDOW_H
