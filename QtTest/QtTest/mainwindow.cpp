#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QDateTime"
#include<QFile>
#include<QString>
#include<QFileDialog>
#include<QFileInfo>
#include<QTextStream>
#include<QMessageBox>
#include<QTextStream>
#include<QTextCharFormat>
#include<QFont>
#include<QFontDialog>
#include<QColorDialog>
#include<QColor>
#include<QPushButton>
#include<QTextCharFormat>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isSaved=false;
    close=false;
    QString curFile = tr("记事本.txt");
    setWindowTitle(curFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::do_file_SaveAS(){
    QString fileName=QFileDialog::getSaveFileName(this,tr("另存为"),curFile);

    if(!fileName.isEmpty()){
          saveFile(fileName);
    }

}

void MainWindow::do_file_Save(){
    if(isSaved){
        saveFile(curFile);
    }
    else{

        do_file_SaveAS();
    }
}
void MainWindow::do_file_SaveOrNot(){
    if(ui->textEdit->document()->isModified()){
        QMessageBox box;
        box.setWindowTitle(tr("警告"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile+tr("是否保存？"));
        box.setStandardButtons(QMessageBox::Yes);
        do_file_Save();
    }

}
bool MainWindow::saveFile(const QString&fileName){
    QFile file(fileName);
            if(!file.open(QFile::WriteOnly|QFile::Text)){

        return false;
    }
    QTextStream out(&file);
    out<<ui->textEdit->toPlainText();
    isSaved=true;
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}


//新建文件
void MainWindow::on_action_triggered()
{
    do_file_SaveOrNot();
    isSaved=false;
    curFile=tr("记事本.txt");
    setWindowTitle(curFile);
    ui->textEdit->clear();
    ui->textEdit->setVisible(true);
}
//打开文件
void MainWindow::on_action_2_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this);
    loadFile(filename);
}
//本地连接
void MainWindow::loadFile(QString filename){
    printf("file name:%s\n",filename.data());

    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream textStream(&file);
        while(!textStream.atEnd())
        {
            ui->textEdit->append(textStream.readLine());
            printf("read line\n");
        }
        printf("end\n");
    }
    }
//保存文件
void MainWindow::on_action_3_triggered()
{
    if(isSaved){
        saveFile(curFile);
    }
    else{

        do_file_SaveAS();
    }
}
//另存为文件
void MainWindow::on_action_4_triggered()
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("另存为"),curFile);

    if(!fileName.isEmpty()){
          saveFile(fileName);
    }

}
//字体颜色
void MainWindow::on_action_16_triggered()
{
    QColor color=QColorDialog::getColor(Qt::red,this);

        if(color.isValid())
        {
            QTextCharFormat fmt;
                fmt.setForeground(color);
                ui->textEdit->mergeCurrentCharFormat(fmt);
        }
}
//关闭文件

void MainWindow::on_action_5_triggered()
{
    if(close){
          QMessageBox::information(this,"提示","文件尚未保存，关闭");
      }else{
    ui->textEdit->close();
    }
}
//撤销
void MainWindow::on_action_6_triggered()
{
   ui->textEdit->undo();
}
//剪切
void MainWindow::on_action_7_triggered()
{
    ui->textEdit->cut();
}
//复制
void MainWindow::on_action_8_triggered()
{
    ui->textEdit->copy();
}
//粘贴
void MainWindow::on_action_9_triggered()
{
    ui->textEdit->paste();
}
//删除
void MainWindow::on_action_10_triggered()
{
    ui->textEdit->redo();
}

//全选
void MainWindow::on_action_13_triggered()
{
    ui->textEdit->selectAll();
}
//显示时间
void MainWindow::on_action_14_triggered()
{
    QDateTime time =QDateTime::currentDateTime();
      QString str= time.toString("yyyy-MM-dd hh:mm:ss dddd");
      ui->textEdit->setText(str);
}


//查找
void MainWindow::close_findhangshu()
{
    ui->gridLayoutWidget->close();
}
void MainWindow::on_action_11_triggered()
{
       QDialog *closefind=new QDialog(this);
       QDialog *findDlg=new QDialog(this);
       find_textLineEdit=new QLineEdit(findDlg);
       QPushButton *find_Bth=new QPushButton(tr("查找下一个"),findDlg);
       QPushButton *close_find=new QPushButton(tr("关闭"),closefind);
       ui->gridLayout->addWidget(find_textLineEdit);
       ui->gridLayout->addWidget(find_Bth);
       ui->gridLayout->addWidget(close_find);
       connect(find_Bth,SIGNAL(clicked()),this,SLOT(show_findText()));
       connect(close_find,SIGNAL(clicked()),this,SLOT(close_findhangshu()));
    }
void MainWindow::show_findText()
{
    QString findText=find_textLineEdit->text();
    if(!ui->textEdit->find(findText,QTextDocument::FindBackward))
    {
        QMessageBox::warning(this,tr("查找"),tr("找不到 %1").arg(findText));

    }
}
//退出
void MainWindow::on_action_12_triggered()
{
     delete ui->textEdit;
}

//关于
void MainWindow::on_action_17_triggered()
{
    ui->textEdit->setText(tr("About Message Box"));
    QMessageBox::about(this,tr("About消息框"),tr("这是一个QT记事本作者：李铖"));
    return;

}
//字体
void MainWindow::on_action_15_triggered()
{
    bool ok;
       QFont currentFont=QFontDialog::getFont(&ok);
       if(ok){
           ui->textEdit->setFont(currentFont);
       }


}
//字体倾斜
void MainWindow::on_action_18_triggered()
{
    QTextCharFormat fmt;
        fmt.setFontItalic(ui->action_18->isChecked());
        ui->textEdit->mergeCurrentCharFormat(fmt);

}
//下划线
void MainWindow::on_action_19_triggered()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->action_19->isChecked());
   ui->textEdit->mergeCurrentCharFormat(fmt);
}

//左对齐
void MainWindow::on_action_20_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);

}
//右对齐
void MainWindow::on_action_21_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

//居中
void MainWindow::on_action_22_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);


}
//两端对齐
void MainWindow::on_action_23_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignJustify);

}

