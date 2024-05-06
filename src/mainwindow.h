#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qmainwindow.h>
#include <QPushButton>
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <QColor>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QObject>
#include <QGraphicsOpacityEffect>
#include <QColorDialog>
#include <QRegularExpression>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextBlock>
#include <QTextFragment>
#include <QCloseEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setText(const QString &text);
    int SaveFile();
    void openTextFile();
    void updateCurrent(QString file);
    QString curFile = "null";
    QString openedFile;
    void setBold();
    void setItalic();
    void setHighlight();
    bool updateFile = false;
    QString fileName = "null";
    void selectColor();
    QColor highlightColor = QColor(255,255,255,255);
    QString cleanHtml(QString &html);
    void animateButton(QPushButton *button);
    void textDefault();
    bool isSaved();
    void closeEvent(QCloseEvent *event);
    int saveFileAs();

private slots:

    void on_fileDropButton_2_clicked();
    void on_fileDropButton_clicked();
    void on_boldButton_clicked();
    void on_italicButton_clicked();
    void on_highlightButton_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_colorWheelButton_clicked();
    void on_textColorButton_clicked();
    void on_textEdit_customContextMenuRequested(const QPoint &pos);
    void on_underlineButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


