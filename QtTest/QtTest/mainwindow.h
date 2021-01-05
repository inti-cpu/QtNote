#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMainWindow>
#include<qstring.h>
#include<QString>
#include<QLineEdit>
#include<QTextCharFormat>
#include<QAction>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString fileName;
    QString curFile;
    bool isSaved;
    bool close;
    void loadFile(QString fileNames);
private slots:
    void on_action_triggered();
    void do_file_SaveAS();
    void do_file_Save();
    void do_file_SaveOrNot();
    bool saveFile(const QString&fileName);
    void show_findText();
    void close_findhangshu();
    void on_action_3_triggered();
    void on_action_4_triggered();
    void on_action_2_triggered();

    void on_action_16_triggered();

    void on_action_7_triggered();

    void on_action_9_triggered();

    void on_action_8_triggered();

    void on_action_6_triggered();

    void on_action_5_triggered();

    void on_action_13_triggered();

    void on_action_17_triggered();

    void on_action_15_triggered();

    void on_action_10_triggered();

    void on_action_14_triggered();

    void on_action_11_triggered();


    void on_action_22_triggered();

    void on_action_20_triggered();

    void on_action_21_triggered();

    void on_action_23_triggered();

    void on_action_19_triggered();

    void on_action_18_triggered();

    void on_action_12_triggered();

private:
    Ui::MainWindow *ui;
    QLineEdit *find_textLineEdit;
    QAction *centerAction;


};

#endif // MAINWINDOW_H
