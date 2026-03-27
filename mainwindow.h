#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString xml;

private slots:
    void newXML();
    void openXML();
    void saveXML();
    void saveXMLAs();

    void addHanzi();
    void addWord();
    void addPhrase();

    void saveToXML();
};
#endif // MAINWINDOW_H
