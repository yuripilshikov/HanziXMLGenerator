#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QXmlStreamReader>
#include <QIODevice>
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnWriteToXML, &QAbstractButton::clicked, this, &MainWindow::saveToXML);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveToXML()
{
    QStringList components = ui->txtComponents->text().split(" ");

    QFile file("output.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing";
        return;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true); // human readable
    xml.writeStartDocument();

    xml.writeStartElement("hanzilist");

    xml.writeStartElement("word");
    xml.writeAttribute("title", ui->txtTranslation->text());

    xml.writeTextElement("hanzi", ui->txtHanzi->text());
    xml.writeTextElement("pinying", ui->txtPinying->text());
    xml.writeTextElement("translation", ui->txtTranslation->text());

    xml.writeStartElement("components");

    for(auto& comp : components)
    {
        xml.writeTextElement("component", comp);
    }

    xml.writeEndElement(); // components

    xml.writeEndElement(); // word

    xml.writeEndElement(); //hanzilist

    xml.writeEndDocument();

    if(xml.hasError())
    {
        qDebug() << "Failed!";
    }
    else
    {
        qDebug() << "Asset serialized to output.xml successfully";
    }
    file.close();
}

