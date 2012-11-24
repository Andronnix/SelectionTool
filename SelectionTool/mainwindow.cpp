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
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(deleteGesture()));
    connect(ui->nextType, SIGNAL(clicked()), this, SLOT(nextGestureType()));
    connect(ui->prevType, SIGNAL(clicked()), this, SLOT(prevGestureType()));
}
void MainWindow::setupViews(){
    ui->gestureView->setScene(&userGestureView);
    ui->typeGestureView->setScene(&typeGestureView);
}
void MainWindow::closeEvent(QCloseEvent *event) {
    saveFile();
}
void MainWindow::saveFile(){
    QFile outFile( fileName );
    if( !outFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        QMessageBox::critical(this,"Write XML File Problem"
                              ,"Couldn't save XML file"
                              ,QMessageBox::Ok);
        return;
    }
    QTextStream stream( &outFile );
    stream << doc.toString();

    outFile.close();
}
void MainWindow::openFile(const QString &path)
{    
    if(!fileName.isNull() && !fileName.isEmpty())saveFile();
    QString oldFile=fileName;
    fileName=path;
    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", "Xml Files (*.xml)");

    QFile *xmlFile = new QFile(fileName);
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this,"Load XML File Problem"
                              ,"Couldn't open file"
                              ,QMessageBox::Ok);
        fileName=oldFile;
        return;
    }    
    if (!doc.setContent(xmlFile)) {
        xmlFile->close();
        return;
    }
    xmlFile->close();
    this->setWindowTitle("File: "+fileName);
    docElem = doc.documentElement();
    curType = docElem.firstChild();
    curGest = curType.firstChild();
    changeButtonsState();
    drawGesture(ui->typeGestureView,curType.toElement().attribute("idealPath",""));
    drawGesture(ui->gestureView,curGest.toElement().attribute("path",""));
}
void MainWindow::changeButtonsState(){
    ui->nextType->setEnabled(!curType.nextSibling().isNull() && curType.nextSibling().isElement());
    ui->prevType->setEnabled(!curType.previousSibling().isNull() && curType.previousSibling().isElement());
    ui->gestureNameLabel->setText(curType.toElement().attribute("name"));
    ui->nextButton->setEnabled(!curGest.nextSibling().isNull() && curGest.nextSibling().isElement());
    ui->prevButton->setEnabled(!curGest.previousSibling().isNull() && curGest.previousSibling().isElement());
}

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()),
                        QKeySequence::Open);
    fileMenu->addAction(tr("&Save"), this, SLOT(saveFile()),
                        QKeySequence::Save);
    fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()),
                        QKeySequence::Quit);
}
void MainWindow::nextGestureType(){
    if(!curType.nextSibling().isNull()){
        curType = curType.nextSibling();
        curGest = curType.firstChild();
        changeButtonsState();
        if(curType.isElement()){
            ui->gestureNameLabel->setText(curType.toElement().attribute("name"));
            drawGesture(ui->typeGestureView,curType.toElement().attribute("idealPath",""));
            drawGesture(ui->gestureView,curGest.toElement().attribute("path",""));
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
        changeButtonsState();
        if(curType.isElement()){
            ui->gestureNameLabel->setText(curType.toElement().attribute("name"));
            drawGesture(ui->typeGestureView,curType.toElement().attribute("idealPath",""));
            drawGesture(ui->gestureView,curGest.toElement().attribute("path",""));
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
            drawGesture(ui->gestureView,n.attribute("path",""));
            changeButtonsState();
        }
    }else{
        QMessageBox::critical(this,"Error","No user gestures");
        return;
    }
}
void MainWindow::prevGesture(){
    if(!curGest.previousSibling().isNull()){
        curGest = curGest.previousSibling();
        if(curGest.isElement()){
            QDomElement n=curGest.toElement();
            drawGesture(ui->gestureView,n.attribute("path",""));
            changeButtonsState();
        }
    }else{
        QMessageBox::critical(this,"Error","No user gestures");
        return;
    }
}
void MainWindow::deleteGesture(){
    if(curGest.isNull())return;
    QDomNode toDel=curGest;
    if(!curGest.nextSibling().isNull())
        nextGesture();
    else if(!curGest.previousSibling().isNull())
        prevGesture();
    else{
        drawGesture(ui->gestureView, curType.toElement().attribute("idealPath",""));
    }
    curType.removeChild(toDel);
    changeButtonsState();
}

void MainWindow::drawGesture(QGraphicsView *view, QString strPath){
    QPen pen(Qt::blue);
    QBrush brush(Qt::transparent);
    QPainterPath path;
    strPath.remove(" ");
    QStringList strList = strPath.split(":", QString::SkipEmptyParts);
    QList<QPointF> points;
    int maxX=0,maxY=0;
    int minX=INT_MAX,minY=INT_MAX;
    if(strList.size()>0){
        foreach(QString s,strList){
            if(s.isNull() || s.isEmpty())continue;
            QStringList pos=s.split(",");
            bool ok;
            int x = pos.at(0).toInt(&ok),y=pos.at(1).toInt(&ok);
            if(x>maxX)maxX=x;
            if(y>maxY)maxY=y;
            if(x<minX)minX=x;
            if(y<minY)minY=y;
            if(ok){
                QPointF p(x,y);
                points.append(p);
            }
        }
        QPointF p=points.at(0);
        double sw=maxX-minX; sw/=view->width()-20;
        double sh=maxY-minY; sh/=view->height()-20;
        double scale=( sw> sh)?sw:sh;
        p.setX((p.x()-minX)/scale);
        p.setY((p.y()-minY)/scale);
        path.moveTo(p);
        for(int i=0;i<points.size();i++){
            QPointF p=points.at(i);
            p.setX((p.x()-minX)/scale);
            p.setY((p.y()-minY)/scale);
            path.lineTo(p);
        }
    }else{
        QMessageBox::critical(this,"noGest","noGesture");
    }
    QGraphicsScene *scene=view->scene();
    scene->clear();
    scene->addPath(path,pen,brush);
}
MainWindow::~MainWindow()
{
    delete ui;
}

