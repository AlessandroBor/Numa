#include "mainwindow.h"
#include <QObject>
#include "qobject.h"
#include <QFontComboBox>
#include <QAbstractItemView>
#include <QString>
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QIcon fileButtonIcon(":/open.svg");
    QIcon saveButtonIcon(":/save-icon.svg");
    QIcon boldButtonIcon(":/bold-icon.svg");
    QIcon italicButtonIcon(":/italic-icon.svg");
    QIcon highlightButtonIcon(":/highlight-icon.svg");
    QIcon textColorButtonIcon(":/textcolor-icon.svg");
    QIcon underlineButtonIcon(":/underline-icon.svg");
    QIcon colorWheelIcon(":/colorWheelIcon.svg");

    QPushButton *fileOpenButton = ui->fileDropButton;
    QPushButton *fileSaveButton = ui->fileDropButton_2;
    QPushButton *boldButton = ui->boldButton;
    QPushButton *italicButton = ui->italicButton;
    QPushButton *highlightButton = ui->highlightButton;
    QPushButton *textColorButton = ui->textColorButton;
    QPushButton *underlineButton = ui->underlineButton;

    QMenu *saveMenu = new QMenu(fileSaveButton);

    QAction *action1 = saveMenu->addAction("Save (Ctrl + S)");
    QAction *action2 = saveMenu->addAction("Save As");

    fileSaveButton->setFocusPolicy(Qt::NoFocus);

    fileSaveButton->setMenu(saveMenu);

    ui->fontComboBox->setMaxVisibleItems(10);
    ui->fontComboBox->setMinimumHeight(25);
    ui->fontComboBox->view()->setMinimumWidth(200);


    qDebug() << ui->textEdit->contextMenuPolicy();








    int iconSize = 25;
    fileOpenButton->setIcon(fileButtonIcon);
    fileOpenButton->setIconSize(QSize(iconSize,iconSize));
    fileSaveButton->setIcon(saveButtonIcon);
    fileSaveButton->setIconSize(QSize(iconSize,iconSize));
    boldButton->setIcon(boldButtonIcon);
    boldButton->setIconSize(QSize(iconSize,iconSize));
    italicButton->setIcon(italicButtonIcon);
    italicButton->setIconSize(QSize(iconSize,iconSize));
    highlightButton->setIcon(highlightButtonIcon);
    highlightButton->setIconSize(QSize(iconSize,iconSize));
    textColorButton->setIcon(textColorButtonIcon);
    textColorButton->setIconSize(QSize(iconSize,iconSize));
    underlineButton->setIcon(underlineButtonIcon);
    underlineButton->setIconSize(QSize(iconSize,iconSize));
    ui->colorWheelButton->setIcon(colorWheelIcon);
    ui->colorWheelButton->setIconSize(QSize(26,26));
    ui->colorWheelButton->setMaximumSize(26,26);


    QAction* saveAction = new QAction("Save file", this);
    saveAction->setStatusTip("Save the current file.");
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::SaveFile);
    connect(action1, &QAction::triggered, this, &MainWindow::SaveFile);
    connect(action2, &QAction::triggered, this, &MainWindow::saveFileAs);
    ui->fileDropButton_2->addAction(saveAction);
}


    void MainWindow::setText(const QString &text) {
        ui->textEdit->setPlainText(text);
    }


    int MainWindow::SaveFile()
    {
        qDebug() << openedFile;
        if (updateFile != false)
        {
            QFile file(fileName);
            QFileInfo fileId(file.fileName());
            qDebug() << "Working current file selection.";
            if (file.open(QIODevice::WriteOnly))
            {
                QTextStream stream(&file);
                if (fileId.completeSuffix() == "txt") {
                    qDebug() << "Saving as text file...";
                    stream << ui->textEdit->toPlainText();
                    file.close();
                    return 1;
                } else if (fileId.completeSuffix() == "nma") {
                    qDebug() << "Saving as numa file..";
                    stream << ui->textEdit->toHtml();
                    file.close();
                    return 1;
                }
            }

        }
        else{
        qDebug() << "2nd opened";
        fileName = QFileDialog::getSaveFileName (this, tr("Save file"), "/home/username/Documents/untitled", tr("Project Files (*.nma);;Text Files (*.txt);;All Files (*)"));

        if (!fileName.isEmpty())
        {

            QFile file(fileName);
            openedFile = fileName;
            QFileInfo fileId(file.fileName());
            qDebug() << fileId.completeSuffix();

            QString fileExtract = fileId.fileName();
            updateCurrent(fileExtract);
            QString numa = "NUMA--NUMA";
            if (file.open(QIODevice::WriteOnly)) {

                QTextStream stream(&file);
                if (fileId.completeSuffix() == "txt") {
                    qDebug() << "Saving as text file...";
                    stream << ui->textEdit->toPlainText();
                    file.close();
                    return 1;
                } else if (fileId.completeSuffix() == "nma") {
                    qDebug() << numa;
                    stream << ui->textEdit->toHtml();
                    file.close();
                    return 1;
                }
            }
        } else {
            qDebug() << "No file selected or error opening the file dialog.";
        }
        }

        return 0;
    }

    void MainWindow::openTextFile() {
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("All Files (*.txt *.nma);;Project Files (*.nma);;Text files (*.txt)"));
        QFile inputfile(fileName);
        QFileInfo fileId(inputfile.fileName());
        QString fileExtract = fileId.fileName();
        if (inputfile.open(QIODevice::ReadOnly)) {
            ui->textEdit->clear();
            QTextStream tfile(&inputfile);
            QString content = tfile.readAll();
            updateCurrent(fileExtract);

            if (fileId.completeSuffix() == "txt") {
                textDefault();
                ui->textEdit->append(content);
            } else if (fileId.completeSuffix() == "nma") {
                ui->textEdit->append(content);
            }

            inputfile.close();
        }
    }


    void MainWindow::updateCurrent(QString file)
    {
        updateFile = true;
        curFile = file;
        qDebug() << file;
        QString title = QString("Numa - %1").arg(file);
        setWindowTitle(title);
        // ui->topFileLabel->setText(file);
    }


    bool MainWindow::isSaved()
    {
        if (fileName != "null")
        {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly) && fileName != "null")
        {
                QTextStream tfile(&file);
                QString text = tfile.readAll();
                if (ui->textEdit->toHtml() == text)
                {
                    return true;
                }
                else {return false;}
        }
        }
        if (!ui->textEdit->toPlainText().isEmpty())
        {
            return false;
        }
        return true;


    }

    void MainWindow::setBold()
    {
        if (ui->textEdit->fontWeight() == 700)
        {ui->textEdit->setFontWeight(400);}

        else
        {ui->textEdit->setFontWeight(700);}
    }


    void MainWindow::setItalic()
    {
        if (ui->textEdit->fontItalic())
        {ui->textEdit->setFontItalic(false);}

        else
        {ui->textEdit->setFontItalic(true);}
    }


    void MainWindow::setHighlight()
    {
        QTextEdit* editor = ui->textEdit;
        QTextCursor cursor = editor->textCursor();

        qDebug() << ui->textEdit->textBackgroundColor();

        if (ui->textEdit->textBackgroundColor() == highlightColor)
        {
            ui->textEdit->setTextColor(QColor(255,255,255,255));
            ui->textEdit->setTextBackgroundColor(QColor(0,0,0,0));

        }

        else
        {ui->textEdit->setTextBackgroundColor(highlightColor);}

        int position = cursor.position();
        cursor.clearSelection();
        cursor.setPosition(position);
        editor->setTextCursor(cursor);
    }


    void MainWindow::animateButton(QPushButton *button) {
        if (!button) return;  // Safety check

        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(button);
        button->setGraphicsEffect(effect);

        QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
        animation->setDuration(100); // Duration in milliseconds
        animation->setStartValue(1.0);
        animation->setEndValue(0.0);
        animation->setEasingCurve(QEasingCurve::InOutQuad);
        animation->setLoopCount(1);  // Go to zero and back to full opacity
        animation->setDirection(QPropertyAnimation::Forward);

        MainWindow::connect(animation, &QPropertyAnimation::finished, button, [effect, animation]() {
            effect->deleteLater();  // Clean up the effect after the animation
            animation->deleteLater();  // Clean up the animation
        });

        animation->start();
    }

    void MainWindow::selectColor()
    {
        QColor color = QColorDialog::getColor();
        qDebug() << color;
        QString colorStyle = QString("background-color: %1; margin: 4px; border-radius: 5px;").arg(color.name());
        ui->colorWheelButton->setStyleSheet(colorStyle);
        ui->textEdit->setTextColor(color);
        MainWindow::highlightColor = color;
    }

    int MainWindow::saveFileAs()
    {
        fileName = QFileDialog::getSaveFileName (this, tr("Save file"), "/home/username/Documents/untitled", tr("Project Files (*.nma);;Text Files (*.txt);;All Files (*)"));

        if (!fileName.isEmpty())
        {

            QFile file(fileName);
            openedFile = fileName;
            QFileInfo fileId(file.fileName());
            qDebug() << fileId.completeSuffix();
            QString fileExtract = fileId.fileName();
            updateCurrent(fileExtract);
            if (file.open(QIODevice::WriteOnly)) {
                QTextStream stream(&file);
                if (fileId.completeSuffix() == "txt") {
                    qDebug() << "Saving as text file...";
                    stream << ui->textEdit->toPlainText();
                    file.close();
                    return 1;
                } else if (fileId.completeSuffix() == "nma") {
                    stream << ui->textEdit->toHtml();
                    file.close();
                    return 1;
                }
            }
        }
        return 0;
    }


    void MainWindow::textDefault()
    {
        QFont font;
        QColor color = QColor(255,255,255,255);
        font.setFamily("Arial");
        font.setPointSize(16);
        ui->textEdit->setFont(font);
        ui->textEdit->setFontPointSize(16);
        ui->textEdit->setTextColor(QColor(255,255,255,255));
        ui->textEdit->setFontItalic(false);
        ui->textEdit->setFontWeight(400);
        ui->textEdit->setFontUnderline(false);
        ui->textEdit->setFontItalic(false);
        ui->textEdit->setTextBackgroundColor(QColor(0,0,0,0));
        QString colorStyle = QString("background-color: %1; margin: 4px; border-radius: 5px;").arg(color.name());
        ui->colorWheelButton->setStyleSheet(colorStyle);
        ui->textEdit->setTextColor(color);
        ui->fontComboBox->setCurrentFont(font);
        MainWindow::highlightColor = color;
    }



    void MainWindow::closeEvent(QCloseEvent *event) {
        // Check if there are unsaved changes
        if (!isSaved()) {

            QMessageBox::StandardButton resBtn = QMessageBox::question( this, "APP_NAME",
                                                                       tr("Are you sure you want to close?\nYou have unsaved changes that will be lost."),
                                                                       QMessageBox::Cancel | QMessageBox::Save | QMessageBox::Yes,
                                                                       QMessageBox::Yes);
            if (resBtn == QMessageBox::Cancel) {
                event->ignore();
            } else if (resBtn == QMessageBox::Save) {
                SaveFile();
                event->accept();
            }
            else
            {
                event->accept();
            }
        } else {
            event->accept();
        }
    }



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_fileDropButton_2_clicked()
{
    animateButton(ui->fileDropButton_2);
    MainWindow::SaveFile();

}


void MainWindow::on_fileDropButton_clicked()
{
    animateButton(ui->fileDropButton);
    MainWindow::openTextFile();
}

void MainWindow::on_boldButton_clicked()
{
    animateButton(ui->boldButton);
    MainWindow::setBold();
}


void MainWindow::on_italicButton_clicked()
{
    animateButton(ui->italicButton);
    MainWindow::setItalic();
}

void MainWindow::on_highlightButton_clicked()
{
    animateButton(ui->highlightButton);
    MainWindow::setHighlight();

}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if (arg1 > 240){arg1 = 240; ui->spinBox->setValue(arg1);}
    ui->textEdit->setFontPointSize(arg1);
}


void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    qDebug () << f;
    qDebug () << "font change";
    QTextCursor cursor = ui->textEdit->textCursor();

    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }

    QTextCharFormat format;
    format.setFont(f);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}



void MainWindow::on_colorWheelButton_clicked()
{
    MainWindow::selectColor();
}


void MainWindow::on_textColorButton_clicked()
{
    animateButton(ui->textColorButton);
    ui->textEdit->setTextColor(highlightColor);
}


void MainWindow::on_textEdit_customContextMenuRequested(const QPoint &pos)
{
    QTextEdit *editor = qobject_cast<QTextEdit *>(sender());
    if (!editor)
        return;

    QMenu *menu = editor->createStandardContextMenu();
    menu->addSeparator();

    QAction *customAction = new QAction("Remove Formatting", this);
    connect(customAction, &QAction::triggered, this, [this]() {
        qDebug() << "Custom action triggered!";
        textDefault();

    });

    menu->addAction(customAction);

    menu->exec(editor->mapToGlobal(pos));
    delete menu;
}


void MainWindow::on_underlineButton_clicked()
{
    animateButton(ui->underlineButton);
    if (ui->textEdit->fontUnderline() == false)
    {ui->textEdit->setFontUnderline(true);}
    else{ui->textEdit->setFontUnderline(false);}
}

