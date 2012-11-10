#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

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
    void nextGestureType();
    void prevGestureType();
    void deleteGesture();

private:
    Ui::MainWindow *ui;    
    QDomElement docElem;
    QDomNode curType,curGest;
    QGraphicsScene userGestureView,typeGestureView;
    QString fileName;
    QDomDocument doc;
    void setupFileMenu();
    void setupButtons();
    void setupViews();
    void drawGesture(QGraphicsView *view,QString strPath);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
