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
#include <QAnyStringView>
#include <QMessageBox>
#include <memory>
#include <QCoreApplication>
#include "Environment.h"

class GridWidget : public QWidget 
{
    Q_OBJECT
public:
    GridWidget(Config&& config, QWidget* parent = nullptr);
    GridWidget();
    /**
     * @brief Starts the animation
     */
    void startAnimation();
protected:
    /**
     * @brief draws the frame
     */
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<QRect> circles_;
    QVector<QColor> circleColors_;
    Config config_;
    Environment myEnv_;
    QTimer timer_;
    int frameCount_;
    int genCount_;
    /**
     * @brief Generates circles at creature`s current positions
     */
    void generateCircles();
    /**
     * @brief Generates color for every creature depending on its genome
     */
    void generateColors();
    /**
     * @brief Updates frame and checks if we didn`t reach the end of simulation
     */
    void updateFrame();
    
};



class DialogWindow : public QDialog {
    Q_OBJECT
public:
    explicit DialogWindow(QWidget* parent = nullptr);

signals:
    void dialogSelected(Config config);

private slots:
    /**
     * @brief Extracts all the parameters and creates config object
     */
    void handleOkButtonClicked();

private:
    QVBoxLayout layout_;
    QFormLayout formLayout_;
    QLineEdit envSizeEdit_;
    QComboBox envTypeBox_;
    QLineEdit killZoneSizeEdit_;
    QLineEdit numCreaturesEdit_;
    QLineEdit numGenesEdit_;
    QLineEdit maxInternalNeuronsEdit_;
    QLineEdit mutRateEdit_;
    QListWidget activeSensorNeuronsEdit_;
    QListWidget activeActionNeuronsEdit_;
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
    /**
     * @brief Opens input window
     */
    void openDialog();
    /**
     * @brief Creates window where the simulation runs
     */
    void createSimulation(Config config);

private:
    std::unique_ptr<GridWidget> gridWidget_;
    QAction configSimAction_;
};

#endif