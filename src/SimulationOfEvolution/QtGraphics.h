#ifndef QT_GRAPHICS
#define QT_GRAPHICS
#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMainWindow>
#include <QMenuBar>
#include <QListWidget>
#include <QComboBox>
#include <memory>
#include "Environment.h"

class GridWidget : public QWidget 
{
    Q_OBJECT
public:
    GridWidget(Config&& config, QWidget* parent = nullptr);
    GridWidget();
    void startAnimation();
protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<QRect> circles_;
    Config config_;
    Environment myEnv_;
    QTimer timer_;
    int frameCount_;
    void generateCircles();
    void updateFrame();
    
};



class DialogWindow : public QDialog {
    Q_OBJECT
public:
    explicit DialogWindow(QWidget* parent = nullptr);

signals:
    void dialogSelected(Config config);

private slots:
    void handleOkButtonClicked();

private:
    QVBoxLayout layout_;
    QFormLayout formLayout_;
    QLineEdit envSizeEdit_;
    QComboBox envTypeBox_;
    QLineEdit numCreaturesEdit_;
    QLineEdit maxInternalNeuronsEdit_;
    QListWidget activeSensorNeuronsEdit_;
    QListWidget activeActionNeuronsEdit_;
    QLineEdit numGenesEdit_;
    QLineEdit numGenerationsEdit_;
    QLineEdit numStepsEdit_;
    QPushButton okButton_;
};

class MainWindow : public QMainWindow 
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void openDialog();
    void createSimulation(Config config);

private:
    std::unique_ptr<GridWidget> gridWidget_;
    QAction configSimAction_;
};

#endif