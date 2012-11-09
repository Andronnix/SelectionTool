#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupButtons();
    setupViews();
    setupFileMenu();
}
void MainWindow::setupButtons(){
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(nextGesture()));
    connect(ui->prevButton, SIGNAL(clicked()), this, SLOT(prevGesture()));
    connect(ui->nextType, SIGNAL(clicked()), this, SLOT(nextGestureType()));
    connect(ui->prevType, SIGNAL(clicked()), this, SLOT(prevGestureType()));
}
void MainWindow::setupViews(){
    ui->gestureView->setScene(&userGestureView);
    ui->typeGestureView->setScene(&typeGestureView);
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", "Xml Files (*.xml)");

    QFile *xmlFile = new QFile(fileName);
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this,"Load XML File Problem"
                              ,"Couldn't open file"
                              ,QMessageBox::Ok);
        return;
    }
    QDomDocument doc("mydocument");
    if (!doc.setContent(xmlFile)) {
        xmlFile->close();
        return;
    }
    xmlFile->close();

    // print out the element names of all elements that are direct children
    // of the outermost element.
    docElem = doc.documentElement();
    curType = docElem.firstChild();
    curGest = curType.firstChild();
    drawGesture(&typeGestureView,curType.toElement().attribute("idealPath",""));
    drawGesture(&userGestureView,curGest.toElement().attribute("path",""));
}
void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()),
                        QKeySequence::Open);

    fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()),
                        QKeySequence::Quit);
}
void MainWindow::nextGestureType(){
    if(!curType.nextSibling().isNull()){
        curType = curType.nextSibling();
        curGest = curType.firstChild();
        if(curType.isElement()){
            drawGesture(&typeGestureView,curType.toElement().attribute("idealPath",""));
        }
    }else{
        QMessageBox::critical(this,"Error","no type");
        return;
    }
}
void MainWindow::prevGestureType(){
    if(!curType.previousSibling().isNull()){
        curType = curType.previousSibling();
        curGest = curType.firstChild();
        if(curType.isElement()){
            drawGesture(&typeGestureView,curType.toElement().attribute("idealPath",""));
        }
    }else{
        QMessageBox::critical(this,"Error","no type");
        return;
    }
}
void MainWindow::nextGesture(){
    if(!curGest.nextSibling().isNull()){
        curGest = curGest.nextSibling();
        if(curGest.isElement()){
            QDomElement n=curGest.toElement();
            drawGesture(&userGestureView,n.attribute("path",""));
        }
    }else{
        QMessageBox::critical(this,"Error","no gesture");
        return;
    }
}
void MainWindow::prevGesture(){
    if(!curGest.previousSibling().isNull()){
        curGest = curGest.previousSibling();
        if(curGest.isElement()){
            QDomElement n=curGest.toElement();
            drawGesture(&userGestureView,n.attribute("path",""));
        }
    }else{
        QMessageBox::critical(this,"Error","no gesture");
        return;
    }
}
void MainWindow::drawGesture(QGraphicsScene *scene, QString strPath){
    QPen pen(Qt::blue);
    QBrush brush(Qt::transparent);
    QPainterPath path;
    if(!curGest.isElement())return;
    strPath.remove(" ");
    QStringList strList = strPath.split(":", QString::SkipEmptyParts);
    QList<QPointF> points;
    int maxW=0,maxH=0;
    if(strList.size()>0){
        foreach(QString s,strList){
            if(s.isNull() || s.isEmpty())continue;
            QStringList pos=s.split(",");
            bool ok;
            int x = pos.at(0).toInt(&ok),y=pos.at(1).toInt(&ok);
            if(x>maxW)maxW=x;
            if(y>maxH)maxH=y;
            if(ok){
                QPointF p(x,y);
                points.append(p);
            }
        }
        QPointF p=points.at(0);
        path.moveTo(p);
        for(int i=1;i<points.size();i++){
            QPointF p=points.at(i);
            path.lineTo(p);
        }

    }else{
        QMessageBox::critical(this,"noGest","noGesture");
    }
    scene->clear();
    scene->addPath(path,pen,brush);
    scene->views().first()->fitInView(10,10,scene->views().first()->width()-10,scene->views().first()->height()-10);
}
MainWindow::~MainWindow()
{
    delete ui;
}

