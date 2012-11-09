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
    drawGesture();
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
void MainWindow::nextGesture(){
    if(!curGest.nextSibling().isNull()){
        curGest = curGest.nextSibling();
        if(curGest.isElement()){
            QDomElement n=curGest.toElement();
        }
    }else{
        QMessageBox::critical(this,"Error","no gesture");
        return;
    }
    drawGesture();
}
void MainWindow::prevGesture(){
    if(!curGest.previousSibling().isNull()){
        curGest = curGest.previousSibling();
        if(curGest.isElement()){
            QDomElement n=curGest.toElement();
        }
    }else{
        QMessageBox::critical(this,"Error","no gesture");
        return;
    }
    drawGesture();
}
void MainWindow::drawGesture(){
    QPen pen(Qt::blue);
    QBrush brush(Qt::transparent);
    QPainterPath path;
    if(!curGest.isElement())return;
    QString strPath=curGest.toElement().attribute("path","");
    QStringList strList = strPath.split(":", QString::SkipEmptyParts);
    QList<QPointF> points;
    int maxW=0,maxH=0;
    if(strList.size()>0){
        foreach(QString s,strList){
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
        float dx=maxW/userGestureView.width(),dy=maxH/userGestureView.height();
        QPointF p=points.at(0);
        p.setX(p.x()*dx);
        p.setY(p.y()*dy);
        path.moveTo(p);
        foreach(QPointF p,points){
            path.lineTo(p);
            p.setX(p.x()*dx);
            p.setY(p.y()*dy);
        }
    }else{
        QMessageBox::critical(this,"noGest","noGesture");
    }
    userGestureView.clear();
    userGestureView.addPath(path,pen,brush);
}
MainWindow::~MainWindow()
{
    delete ui;
}
