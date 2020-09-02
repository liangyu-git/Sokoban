#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFont>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    for(int i = 0; i<100; i++){
        delete mapLabel[i];
        delete endLabel[i];
    }
    for(int i = 0; i<20; i++){
        delete boxLabel[i].object;
    }
    delete characterLabel.object;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right){
        // qDebug() << "right pressed";
        moveRight();
    }
    if(event->key() == Qt::Key_Left){
        // qDebug() << "left pressed";
        moveLeft();
    }
    if(event->key() == Qt::Key_Up){
        // qDebug() << "Up pressed";
        moveUp();
    }
    if(event->key() == Qt::Key_Down){
        // qDebug() << "Down pressed";
        moveDown();
    }
    if(event->key() == Qt::Key_R){
        // qDebug() << "R pressed";
        resetMap();
    }
}

void MainWindow::moveRight()
{
    int boxPos = 0, crystalPos = 0;
    for(int col = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            if(publicObject[col][row] == 3 && publicMap[col][row+1] != 1){
                if(publicObject[col][row+1] == 2 && publicObject[col][row+2] != 2){
                    if(publicMap[col][row+2] != 1){
                        // qDebug() << "character pos" << row << col;
                        characterLabel.object->setGeometry((row+1)*blockSize+blockSize+20,col*blockSize+blockSize,blockSize,blockSize);
                        QPixmap character(":/img/mapImage/Character2.png");
                        characterLabel.object->setPixmap(character);
                        for(boxPos = 0; boxPos<7; boxPos++){
                            if(boxLabel[boxPos].xPos == row+1 && boxLabel[boxPos].yPos == col)
                                break;
                        }
                        // qDebug() << "boxPos" << boxPos;
                        boxLabel[boxPos].object->setGeometry((row+2)*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                        // QPixmap box(":/img/mapImage/Crate_Brown.png");
                        // boxLabel[boxPos].object->setPixmap(box);
                        // qDebug() << "row" << row << "col" << col;
                        publicObject[col][row] = 0;
                        publicObject[col][row+1] = 3;
                        publicObject[col][row+2] = 2;
                        boxLabel[boxPos].xPos = row + 2;
                        boxLabel[boxPos].yPos = col;
                        if(publicEnd[boxLabel[boxPos].yPos][boxLabel[boxPos].xPos] == 1){
                            QPixmap box(":/img/mapImage/CrateDark_Brown.png");
                            boxLabel[boxPos].object->setPixmap(box);
                        }else{
                            QPixmap box(":/img/mapImage/Crate_Brown.png");
                            boxLabel[boxPos].object->setPixmap(box);
                        }
                        if(publiccrystal[col][row+1] == 1){
                            for(crystalPos = 0; crystalPos<3; crystalPos++){
                                if(crystalLabel[crystalPos].xPos == row+1 && crystalLabel[crystalPos].yPos == col)
                                    break;
                            }
                            if(publiccrystal[crystalLabel[crystalPos].yPos][crystalLabel[crystalPos].xPos] == 1){
                                crystalLabel[crystalPos].object->hide();
                                //stepsInGame += 10;
                            }
                        }
                        if(publicportal[col][row+1] == 1){
                            // qDebug() << "see portal";
                            if(stage < 3)
                                QMessageBox::information(this,"WOW","It's a portal! you can directly go to next stage!");
                            stage++;
                            setUpStageMap(stage);
                            return;
                        }
                        if(checkAllBoxOnEnd()){
                            // qDebug() << "complete stage " << stage;
                            stage++;
                            QMessageBox::information(this,"Level complete!","congratulations! please go to next stage");
                            setUpStageMap(stage);
                            return;
                        }
                        stepsInGame++;
                        countStep->setNum(stepsInGame);
                        return;
                    }
                }else if(publicObject[col][row+1] != 2){
                    characterLabel.object->setGeometry((row+1)*blockSize+blockSize+20,col*blockSize+blockSize,blockSize,blockSize);
                    QPixmap character(":/img/mapImage/Character2.png");
                    characterLabel.object->setPixmap(character);
                    publicObject[col][row] = 0;
                    publicObject[col][row+1] = 3;
                    stepsInGame++;
                    countStep->setNum(stepsInGame);
                    if(publiccrystal[col][row+1] == 1){
                        for(crystalPos = 0; crystalPos<3; crystalPos++){
                            if(crystalLabel[crystalPos].xPos == row+1 && crystalLabel[crystalPos].yPos == col)
                                break;
                        }
                        if(publiccrystal[crystalLabel[crystalPos].yPos][crystalLabel[crystalPos].xPos] == 1){
                            crystalLabel[crystalPos].object->hide();
                            //stepsInGame += 10;
                        }
                    }
                    if(publicportal[col][row+1] == 1){
                        // qDebug() << "see portal";
                        if(stage < 3)
                            QMessageBox::information(this,"WOW","It's a portal! you can directly go to next stage!");
                        stage++;
                        setUpStageMap(stage);
                        return;
                    }
                    return;
                }
            }
        }
    }
}

void MainWindow::moveLeft()
{
    //check
    int boxPos = 0, crystalPos = 0;
    for(int col = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            if(publicObject[col][row] == 3 && publicMap[col][row-1] != 1){
                if(publicObject[col][row-1] == 2 && publicObject[col][row-2] != 2){
                    if(publicMap[col][row-2] != 1){
                        // qDebug() << "character pos" << row << col;
                        characterLabel.object->setGeometry((row-1)*blockSize+blockSize+20,col*blockSize+blockSize,blockSize,blockSize);
                        QPixmap character(":/img/mapImage/Character1.png");
                        characterLabel.object->setPixmap(character);
                        for(boxPos = 0; boxPos<7; boxPos++){
                            if(boxLabel[boxPos].xPos == row-1 && boxLabel[boxPos].yPos == col)
                                break;
                        }
                        // qDebug() << "boxPos" << boxPos;
                        boxLabel[boxPos].object->setGeometry((row-2)*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                        // QPixmap box(":/img/mapImage/Crate_Brown.png");
                        // boxLabel[boxPos].object->setPixmap(box);
                        // qDebug() << "row" << row << "col" << col;
                        publicObject[col][row] = 0;
                        publicObject[col][row-1] = 3;
                        publicObject[col][row-2] = 2;
                        boxLabel[boxPos].xPos = row - 2;
                        boxLabel[boxPos].yPos = col;
                        if(publicEnd[boxLabel[boxPos].yPos][boxLabel[boxPos].xPos] == 1){
                            QPixmap box(":/img/mapImage/CrateDark_Brown.png");
                            boxLabel[boxPos].object->setPixmap(box);
                        }else{
                            QPixmap box(":/img/mapImage/Crate_Brown.png");
                            boxLabel[boxPos].object->setPixmap(box);
                        }
                        if(publiccrystal[col][row-1] == 1){
                            for(crystalPos = 0; crystalPos<3; crystalPos++){
                                if(crystalLabel[crystalPos].xPos == row-1 && crystalLabel[crystalPos].yPos == col)
                                    break;
                            }
                            if(publiccrystal[crystalLabel[crystalPos].yPos][crystalLabel[crystalPos].xPos] == 1){
                                crystalLabel[crystalPos].object->hide();
                                //stepsInGame += 10;
                            }
                        }
                        if(publicportal[col][row-1] == 1){
                            if(stage < 3)
                                QMessageBox::information(this,"WOW","It's a portal! you can directly go to next stage!");
                            stage++;
                            setUpStageMap(stage);
                            return;
                        }
                        if(checkAllBoxOnEnd()){
                            // qDebug() << "complete";
                            stage++;
                            QMessageBox::information(this,"Level complete!","congratulations! please go to next stage");
                            setUpStageMap(stage);
                            return;
                        }
                        stepsInGame++;
                        countStep->setNum(stepsInGame);
                        return;
                    }
                }else if(publicObject[col][row-1] != 2){
                    characterLabel.object->setGeometry((row-1)*blockSize+blockSize+20,col*blockSize+blockSize,blockSize,blockSize);
                    QPixmap character(":/img/mapImage/Character1.png");
                    characterLabel.object->setPixmap(character);
                    publicObject[col][row] = 0;
                    publicObject[col][row-1] = 3;
                    stepsInGame++;
                    countStep->setNum(stepsInGame);
                    if(publiccrystal[col][row-1] == 1){
                        for(crystalPos = 0; crystalPos<3; crystalPos++){
                            if(crystalLabel[crystalPos].xPos == row-1 && crystalLabel[crystalPos].yPos == col){
                                // qDebug() << "next is crystal";
                                break;
                            }
                        }
                        if(publiccrystal[crystalLabel[crystalPos].yPos][crystalLabel[crystalPos].xPos] == 1){
                            crystalLabel[crystalPos].object->hide();
                            //stepsInGame += 10;
                        }
                    }
                    if(publicportal[col][row-1] == 1){
                        if(stage < 3)
                            QMessageBox::information(this,"WOW","It's a portal! you can directly go to next stage!");
                        stage++;
                        setUpStageMap(stage);
                        return;
                    }
                    return;
                }
            }
        }
    }
}

void MainWindow::moveUp()
{
    //check
    int boxPos = 0, crystalPos = 0;
    for(int col = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            if(publicObject[col][row] == 3 && publicMap[col-1][row] != 1){
                if(publicObject[col-1][row] == 2 && publicObject[col-2][row] != 2){
                    if(publicMap[col-2][row] != 1){
                        // qDebug() << "character pos" << row << col;
                        characterLabel.object->setGeometry(row*blockSize+blockSize+20,(col-1)*blockSize+blockSize,blockSize,blockSize);
                        QPixmap character(":/img/mapImage/Character7.png");
                        characterLabel.object->setPixmap(character);
                        for(boxPos = 0; boxPos<7; boxPos++){
                            if(boxLabel[boxPos].xPos == row && boxLabel[boxPos].yPos == col-1)
                                break;
                        }
                        // qDebug() << "boxPos" << boxPos;
                        boxLabel[boxPos].object->setGeometry(row*blockSize+blockSize,(col-2)*blockSize+blockSize,blockSize,blockSize);
                        // QPixmap box(":/img/mapImage/Crate_Brown.png");
                        // boxLabel[boxPos].object->setPixmap(box);
                        // qDebug() << "row" << row << "col" << col;
                        publicObject[col][row] = 0;
                        publicObject[col-1][row] = 3;
                        publicObject[col-2][row] = 2;
                        boxLabel[boxPos].xPos = row;
                        boxLabel[boxPos].yPos = col - 2;
                        if(publicEnd[boxLabel[boxPos].yPos][boxLabel[boxPos].xPos] == 1){
                            QPixmap box(":/img/mapImage/CrateDark_Brown.png");
                            boxLabel[boxPos].object->setPixmap(box);
                        }else{
                            QPixmap box(":/img/mapImage/Crate_Brown.png");
                            boxLabel[boxPos].object->setPixmap(box);
                        }
                        if(publiccrystal[col-1][row] == 1){
                            for(crystalPos = 0; crystalPos<3; crystalPos++){
                                if(crystalLabel[crystalPos].xPos == row && crystalLabel[crystalPos].yPos == col-1)
                                    break;
                            }
                            if(publiccrystal[crystalLabel[crystalPos].yPos][crystalLabel[crystalPos].xPos] == 1){
                                crystalLabel[crystalPos].object->hide();
                                //stepsInGame += 10;
                            }
                        }
                        if(publicportal[col-1][row] == 1){
                            if(stage < 3)
                                QMessageBox::information(this,"WOW","It's a portal! you can directly go to next stage!");
                            stage++;
                            setUpStageMap(stage);
                            return;
                        }
                        if(checkAllBoxOnEnd()){
                            // qDebug() << "complete";
                            stage++;
                            QMessageBox::information(this,"Level complete!","congratulations! please go to next stage");
                            setUpStageMap(stage);
                            return;
                        }
                        stepsInGame++;
                        countStep->setNum(stepsInGame);
                        return;
                    }
                }else if(publicObject[col-1][row] != 2){
                    characterLabel.object->setGeometry(row*blockSize+blockSize+20,(col-1)*blockSize+blockSize,blockSize,blockSize);
                    QPixmap character(":/img/mapImage/Character7.png");
                    characterLabel.object->setPixmap(character);
                    publicObject[col][row] = 0;
                    publicObject[col-1][row] = 3;
                    stepsInGame++;
                    countStep->setNum(stepsInGame);
                    if(publiccrystal[col-1][row] == 1){
                        for(crystalPos = 0; crystalPos<3; crystalPos++){
                            if(crystalLabel[crystalPos].xPos == row && crystalLabel[crystalPos].yPos == col-1)
                                break;
                        }
                        if(publiccrystal[crystalLabel[crystalPos].yPos][crystalLabel[crystalPos].xPos] == 1){
                            crystalLabel[crystalPos].object->hide();
                            //stepsInGame += 10;
                        }
                    }
                    if(publicportal[col-1][row] == 1){
                        if(stage < 3)
                            QMessageBox::information(this,"WOW","It's a portal! you can directly go to next stage!");
                        stage++;
                        setUpStageMap(stage);
                        return;
                    }
                    return;
                }
            }
        }
    }
}

void MainWindow::moveDown()
{
    //check
    int boxPos = 0, crystalPos = 0;
    for(int col = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            if(publicObject[col][row] == 3 && publicMap[col+1][row] != 1){
                if(publicObject[col+1][row] == 2 && publicObject[col+2][row] != 2){
                    if(publicMap[col+2][row] != 1){
                        // qDebug() << "character pos" << row << col;
                        characterLabel.object->setGeometry(row*blockSize+blockSize+20,(col+1)*blockSize+blockSize,blockSize,blockSize);
                        QPixmap character(":/img/mapImage/Character4.png");
                        characterLabel.object->setPixmap(character);
                        for(boxPos = 0; boxPos<7; boxPos++){
                            if(boxLabel[boxPos].xPos == row && boxLabel[boxPos].yPos == col+1)
                                break;
                        }
                        // qDebug() << "boxPos" << boxPos;
                        boxLabel[boxPos].object->setGeometry(row*blockSize+blockSize,(col+2)*blockSize+blockSize,blockSize,blockSize);
                        QPixmap box(":/img/mapImage/Crate_Brown.png");
                        boxLabel[boxPos].object->setPixmap(box);
                        // qDebug() << "row" << row << "col" << col;
                        publicObject[col][row] = 0;
                        publicObject[col+1][row] = 3;
                        publicObject[col+2][row] = 2;
                        boxLabel[boxPos].xPos = row;
                        boxLabel[boxPos].yPos = col + 2;
                        if(publiccrystal[col+1][row] == 1){
                            for(crystalPos = 0; crystalPos<3; crystalPos++){
                                if(crystalLabel[crystalPos].xPos == row && crystalLabel[crystalPos].yPos == col+1)
                                    break;
                            }
                            if(publiccrystal[crystalLabel[crystalPos].yPos][crystalLabel[crystalPos].xPos] == 1){
                                crystalLabel[crystalPos].object->hide();
                                //stepsInGame += 10;
                            }
                        }
                        if(publicportal[col+1][row] == 1){
                            if(stage < 3)
                                QMessageBox::information(this,"WOW","It's a portal! you can directly go to next stage!");
                            stage++;
                            setUpStageMap(stage);
                            return;
                        }
                        if(publicEnd[boxLabel[boxPos].yPos][boxLabel[boxPos].xPos] == 1){
                            QPixmap box(":/img/mapImage/CrateDark_Brown.png");
                            boxLabel[boxPos].object->setPixmap(box);
                        }else{
                            QPixmap box(":/img/mapImage/Crate_Brown.png");
                            boxLabel[boxPos].object->setPixmap(box);
                        }
                        if(checkAllBoxOnEnd()){
                            // qDebug() << "complete";
                            stage++;
                            QMessageBox::information(this,"Level complete!","congratulations! please go to next stage");
                            setUpStageMap(stage);
                            return;
                        }
                        stepsInGame++;
                        countStep->setNum(stepsInGame);
                        return;
                    }
                }else if(publicObject[col+1][row] != 2){
                    characterLabel.object->setGeometry(row*blockSize+blockSize+20,(col+1)*blockSize+blockSize,blockSize,blockSize);
                    QPixmap character(":/img/mapImage/Character4.png");
                    characterLabel.object->setPixmap(character);
                    publicObject[col][row] = 0;
                    publicObject[col+1][row] = 3;
                    stepsInGame++;
                    countStep->setNum(stepsInGame);
                    if(publiccrystal[col+1][row] == 1){
                        for(crystalPos = 0; crystalPos<3; crystalPos++){
                            if(crystalLabel[crystalPos].xPos == row && crystalLabel[crystalPos].yPos == col+1)
                                break;
                        }
                        if(publiccrystal[crystalLabel[crystalPos].yPos][crystalLabel[crystalPos].xPos] == 1){
                            crystalLabel[crystalPos].object->hide();
                            //stepsInGame += 10;
                        }
                    }
                    if(publicportal[col+1][row] == 1){
                        if(stage < 3)
                            QMessageBox::information(this,"WOW","It's a portal! you can directly go to next stage!");
                        stage++;
                        setUpStageMap(stage);
                        return;
                    }
                    return;
                }
            }
        }
    }
}

void MainWindow::resetMap()
{
    // qDebug() << "call reset";
    for(int col = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            publicObject[col][row] = publicObjectForReset[col][row];
        }
    }
    for(int col = 0, i = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            if(publicObjectForReset[col][row] == 2){
                boxLabel[i].object->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                boxLabel[i].xPos = row;
                boxLabel[i].yPos = col;
                boxLabel[i].identifier = 2;
                if(publicEnd[boxLabel[i].yPos][boxLabel[i].xPos] == 1){
                    QPixmap box(":/img/mapImage/CrateDark_Brown.png");
                    boxLabel[i].object->setPixmap(box);
                }else{
                    QPixmap box(":/img/mapImage/Crate_Brown.png");
                    boxLabel[i].object->setPixmap(box);
                }
                boxLabel[i].object->show();
                i++;
                // qDebug() << i;
            }else if(publicObjectForReset[col][row] == 3){
                characterLabel.object->setGeometry(row*blockSize+blockSize+20,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap character(":/img/mapImage/Character4.png");
                characterLabel.object->setPixmap(character);
                characterLabel.xPos = row;
                characterLabel.yPos = col;
                characterLabel.identifier = 2;
                characterLabel.object->show();
            }
            for(int i = 0; i<3; i++){
                crystalLabel[i].object->show();
            }
        }
    }
    stepsInGame = 0;
    countStep->setNum(stepsInGame);
}

void MainWindow::setUpStageMap(int s)
{
    if(s == 2){
        // qDebug() << "stage = 2";
        for(int col = 0; col<9; col++){
            for(int row = 0; row<8; row++){
                publicObject[col][row] = level2ObjectForReset[col][row];
                publicMap[col][row] = level2Map[col][row];
                publicEnd[col][row] = level2End[col][row];
                publicObjectForReset[col][row] = level2ObjectForReset[col][row];
                publiccrystal[col][row] = level2crystal[col][row];
                publicportal[col][row] = level2portal[col][row];
            }
        }
        stageEnd = 7;
        stepsInGame = 0;
    }
    if(s == 3){
        // qDebug() << "stage = 3";
        for(int col = 0; col<9; col++){
            for(int row = 0; row<8; row++){
                publicObject[col][row] = level3ObjectForReset[col][row];
                publicMap[col][row] = level3Map[col][row];
                publicEnd[col][row] = level3End[col][row];
                publicObjectForReset[col][row] = level3ObjectForReset[col][row];
                publiccrystal[col][row] = level3crystal[col][row];
                publicportal[col][row] = level3portal[col][row];
            }
        }
        stageEnd = 8;
        stepsInGame = 0;
    }
    if(s == 4){
        QMessageBox::information(this,"yeah","congratulations, complete all stage");
        exit(1);
    }
    setMap();
}

void MainWindow::setMap()
{
    // set up map
    // qDebug() << "set up for next stage";
    for(int col = 0, mapNum = 0, endNum = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            if(publicMap[col][row] == 0){
                mapLabel[mapNum]->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap ground(":/img/mapImage/GroundGravel_Grass.png");
                mapLabel[mapNum]->setPixmap(ground);
                mapLabel[mapNum]->setScaledContents(true);
                mapLabel[mapNum]->show();
                mapNum++;
            }else if(publicMap[col][row] == 1){
                mapLabel[mapNum]->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap wall(":/img/mapImage/Wall_Brown.png");
                mapLabel[mapNum]->setPixmap(wall);
                mapLabel[mapNum]->setScaledContents(true);
                mapLabel[mapNum]->show();
                mapNum++;
            }else{
                mapLabel[mapNum]->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap outside(":/img/mapImage/Ground_Sand.png");
                mapLabel[mapNum]->setPixmap(outside);
                mapLabel[mapNum]->setScaledContents(true);
                mapLabel[mapNum]->show();
                mapNum++;
            }
            if(publicEnd[col][row] == 1){
                endLabel[endNum]->setGeometry(row*blockSize+blockSize+20,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap end(":/img/mapImage/EndPoint_Brown.png");
                endLabel[endNum]->setPixmap(end);
                endLabel[endNum]->show();
                endNum++;
            }
            // qDebug() << "stucked map\nmap row : " << row << "col : " << col;
        }
    }
    // set up object
    for(int col = 0, c_num = 0, i = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            if(publicObject[col][row] == 2){
                boxLabel[i].object->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                boxLabel[i].xPos = row;
                boxLabel[i].yPos = col;
                boxLabel[i].identifier = 2;
                if(publicEnd[boxLabel[i].yPos][boxLabel[i].xPos] == 1){
                    QPixmap box(":/img/mapImage/CrateDark_Brown.png");
                    boxLabel[i].object->setPixmap(box);
                }else{
                    QPixmap box(":/img/mapImage/Crate_Brown.png");
                    boxLabel[i].object->setPixmap(box);
                }
                boxLabel[i].object->show();
                i++;
                // qDebug() << i;
            }else if(publicObject[col][row] == 3){
                characterLabel.object->setGeometry(row*blockSize+blockSize+20,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap character(":/img/mapImage/Character4.png");
                characterLabel.object->setPixmap(character);
                characterLabel.xPos = row;
                characterLabel.yPos = col;
                characterLabel.identifier = 2;
                characterLabel.object->show();
            }
            if(publiccrystal[col][row] == 1){
                crystalLabel[c_num].object->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap crystal(":/img/mapImage/crystal.png");
                crystalLabel[c_num].object->setPixmap(crystal);
                crystalLabel[c_num].object->show();
                crystalLabel[c_num].object->setScaledContents(true);
                crystalLabel[c_num].xPos = row;
                crystalLabel[c_num].yPos = col;
                c_num++;
            }
            if(publicportal[col][row] == 1){
                portalLabel->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap portal(":/img/mapImage/Portal.PNG");
                portalLabel->setPixmap(portal);
                portalLabel->setScaledContents(true);
                portalLabel->show();
            }
            // qDebug() << "stucked map\nmap row : " << row << "col : " << col;
        }
    }
    countStep->setNum(stepsInGame);
}

void MainWindow::setUpFirstMap()
{
    // set up map
    // qDebug() << "set up";
    for(int col = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            publicObject[col][row] = level1Object[col][row];
            publicMap[col][row] = level1Map[col][row];
            publicEnd[col][row] = level1End[col][row];
            publicObjectForReset[col][row] = publicObject[col][row];
            publiccrystal[col][row] = level1crystal[col][row];
            publicportal[col][row] = level1portal[col][row];
        }
    }
    stageEnd = 4;
    for(int i = 0; i<100; i++){
        mapLabel[i] = new QLabel(this);
    }
    for(int i = 0; i<100; i++){
        endLabel[i] = new QLabel(this);
    }
    for(int i = 0; i<100; i++){
        boxLabel[i].object = new QLabel(this);
    }
    for(int i = 0; i<3; i++){
        crystalLabel[i].object = new QLabel(this);
    }
    portalLabel = new QLabel(this);
    for(int col = 0, mapNum = 0, endNum = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            if(publicMap[col][row] == 0){
                mapLabel[mapNum]->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap ground(":/img/mapImage/GroundGravel_Grass.png");
                mapLabel[mapNum]->setPixmap(ground);
                mapLabel[mapNum]->setScaledContents(true);
                mapLabel[mapNum]->show();
                mapNum++;
            }else if(publicMap[col][row] == 1){
                mapLabel[mapNum]->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap wall(":/img/mapImage/Wall_Brown.png");
                mapLabel[mapNum]->setPixmap(wall);
                mapLabel[mapNum]->setScaledContents(true);
                mapLabel[mapNum]->show();
                mapNum++;
            }else{
                mapLabel[mapNum]->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap outside(":/img/mapImage/Ground_Sand.png");
                mapLabel[mapNum]->setPixmap(outside);
                mapLabel[mapNum]->setScaledContents(true);
                mapLabel[mapNum]->show();
                mapNum++;
            }
            if(publicEnd[col][row] == 1){
                endLabel[endNum]->setGeometry(row*blockSize+blockSize+20,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap end(":/img/mapImage/EndPoint_Brown.png");
                endLabel[endNum]->setPixmap(end);
                endLabel[endNum]->show();
                endNum++;
            }
            if(publicportal[col][row] == 1){
                portalLabel->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap portal(":/img/mapImage/Portal.PNG");
                portalLabel->setPixmap(portal);
                portalLabel->setScaledContents(true);
                portalLabel->show();
            }
        }
    }
    // set up object
    for(int col = 0, c_num = 0, i = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            if(publicObjectForReset[col][row] == 2){
                boxLabel[i].object->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                boxLabel[i].xPos = row;
                boxLabel[i].yPos = col;
                boxLabel[i].identifier = 2;
                if(publicEnd[boxLabel[i].yPos][boxLabel[i].xPos] == 1){
                    QPixmap box(":/img/mapImage/CrateDark_Brown.png");
                    boxLabel[i].object->setPixmap(box);
                }else{
                    QPixmap box(":/img/mapImage/Crate_Brown.png");
                    boxLabel[i].object->setPixmap(box);
                }
                boxLabel[i].object->show();
                i++;
                // qDebug() << i;
            }else if(publicObjectForReset[col][row] == 3){
                characterLabel.object = new QLabel(this);
                characterLabel.object->setGeometry(row*blockSize+blockSize+20,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap character(":/img/mapImage/Character4.png");
                characterLabel.object->setPixmap(character);
                characterLabel.xPos = row;
                characterLabel.yPos = col;
                characterLabel.identifier = 2;
                characterLabel.object->show();
            }
            if(publiccrystal[col][row] == 1){
                crystalLabel[c_num].object->setGeometry(row*blockSize+blockSize,col*blockSize+blockSize,blockSize,blockSize);
                QPixmap crystal(":/img/mapImage/crystal.png");
                crystalLabel[c_num].object->setPixmap(crystal);
                crystalLabel[c_num].object->show();
                crystalLabel[c_num].object->setScaledContents(true);
                crystalLabel[c_num].xPos = row;
                crystalLabel[c_num].yPos = col;
                c_num++;
            }
        }
    }
    delete ui->startButton;
    delete ui->mainpage;
    delete ui->level1Button;
    delete ui->level2Button;
    delete ui->level3Button;
    ui->quitButton->setGeometry(660,600,120,50);
    countStep = new QLabel(this);
    countStep->setGeometry(700,390,120,50);
    countStep->setNum(stepsInGame);
    countStep->setStyleSheet("font: 20pt;");
    countStep->show();
    countStepText = new QLabel(this);
    countStepText->setGeometry(660,350,120,50);
    countStepText->setText("Your steps!");
    countStepText->setStyleSheet("font: 17pt;");
    countStepText->show();
    // function button
    functionButton[0] = new QLabel(this);
    functionButton[0]->setGeometry(640,75,150,75);
    QPixmap arrowKey(":/img/mapImage/arrowKey.png");
    functionButton[0]->setPixmap(arrowKey);
    functionButton[0]->setScaledContents(true);
    functionButton[0]->show();
    functionButton[1] = new QLabel(this);
    functionButton[1]->setGeometry(660,150,120,50);
    functionButton[1]->setText("use arrow key to \nmove character");
    functionButton[1]->setStyleSheet("font: 12pt;");
    functionButton[1]->show();

    functionButton[2] = new QLabel(this);
    functionButton[2]->setGeometry(690,220,50,50);
    QPixmap R_icon(":/img/mapImage/R_icon.png");
    functionButton[2]->setPixmap(R_icon);
    functionButton[2]->setScaledContents(true);
    functionButton[2]->show();
    functionButton[3] = new QLabel(this);
    functionButton[3]->setGeometry(660,270,120,50);
    functionButton[3]->setText("press R to reset \nthis level!");
    functionButton[3]->setStyleSheet("font: 12pt;");
    functionButton[3]->show();

    functionButton[4] = new QLabel(this);
    functionButton[4]->setGeometry(640,450,50,50);
    QPixmap crystal_icon(":/img/mapImage/crystal.png");
    functionButton[4]->setPixmap(crystal_icon);
    functionButton[4]->setScaledContents(true);
    functionButton[4]->show();
    functionButton[5] = new QLabel(this);
    functionButton[5]->setGeometry(700,450,120,50);
    functionButton[5]->setText("diamond : \nyou can pick");
    functionButton[5]->setStyleSheet("font: 12pt;");
    functionButton[5]->show();

    functionButton[6] = new QLabel(this);
    functionButton[6]->setGeometry(640,520,50,50);
    QPixmap portal_icon(":/img/mapImage/Portal.PNG");
    functionButton[6]->setPixmap(portal_icon);
    functionButton[6]->setScaledContents(true);
    functionButton[6]->show();
    functionButton[7] = new QLabel(this);
    functionButton[7]->setGeometry(700,520,120,70);
    functionButton[7]->setText("portal : \ndirectly go to \nnext stage");
    functionButton[7]->setStyleSheet("font: 12pt;");
    functionButton[7]->show();
}

bool MainWindow::checkAllBoxOnEnd()
{
    int boxOnEnd = 0;
    for(int col = 0; col<9; col++){
        for(int row = 0; row<8; row++){
            if(publicEnd[col][row] == 1){
                if(publicObject[col][row] == 2){
                    boxOnEnd++;
                }
            }
        }
    }
    if(boxOnEnd<stageEnd) {
        return false;
    }else {
        return true;
    }
}

void MainWindow::on_startButton_clicked()
{
    setUpFirstMap();
    // qDebug()<<"button pressed";
}

int MainWindow::on_quitButton_clicked()
{
    close();
    exit(1);
}

void MainWindow::on_level1Button_clicked()
{
    setUpFirstMap();
}

void MainWindow::on_level2Button_clicked()
{
    setUpFirstMap();
    stage = 2;
    setUpStageMap(2);
}

void MainWindow::on_level3Button_clicked()
{
    setUpFirstMap();
    stage = 3;
    setUpStageMap(3);
}
