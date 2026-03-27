#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QXmlStreamReader>
#include <QIODevice>
#include <QDebug>
#include <QFile>

#include <QDomDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnWriteToXML, &QAbstractButton::clicked, this, &MainWindow::saveToXML);
    connect(ui->actionNew_XML, &QAction::triggered, this, &MainWindow::newXML);

    connect(ui->btnAddHanzi, &QAbstractButton::clicked, this, &MainWindow::addHanzi);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newXML()
{
    // init xml
    QByteArray xmlData;
    QXmlStreamWriter xmlWriter(&xmlData);

    xmlWriter.setAutoFormatting(true); // human readable
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("root");

    xmlWriter.writeStartElement("glyphs");
    xmlWriter.writeEndElement(); // glyphs

    xmlWriter.writeStartElement("words");
    xmlWriter.writeEndElement(); // words

    xmlWriter.writeStartElement("phrases");
    xmlWriter.writeEndElement(); // words

    xmlWriter.writeEndElement(); // root

    if(xmlWriter.hasError())
    {
        qDebug() << "Failed!";
    }
    else
    {
        qDebug() << "Asset serialized to output.xml successfully";
    }

    xml = QString(xmlData);
    qDebug() << xml;
}

void MainWindow::openXML()
{

}

void MainWindow::saveXML()
{

}

void MainWindow::saveXMLAs()
{

}

void MainWindow::addHanzi()
{
    QDomDocument dom;
    dom.setContent(xml);

    QDomNodeList nodes = dom.elementsByTagName("glyphs");
    QDomNode node = nodes.at(0);
    if(node.isElement())
    {
        // insert
        QDomElement element = node.toElement();
        QDomElement hanzi = dom.createElement("hanzi");
        element.appendChild(hanzi);
    }
    xml = dom.toString();
    qDebug() << xml;
}

void MainWindow::addWord()
{

}

void MainWindow::addPhrase()
{

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

