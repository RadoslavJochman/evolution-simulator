#include "QtGraphics.h"

/**
 * @brief stops the application for given number of milliseconds
 */
void delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

GridWidget::GridWidget(Config&& config, std::size_t fps, QWidget* parent)
    : 
    QWidget(parent),
    config_(std::move(config)),
    myEnv_(&config_),
    timer_(this),
    frameCount_(0),
    genCount_(0),
    fps_(fps)
{
    setFixedSize(1000, 1000);
    generateColors();
    generateCircles();
    connect(&timer_, &QTimer::timeout, this, &GridWidget::updateFrame);
}


GridWidget::GridWidget()
    :
    QWidget(nullptr),
    config_(),
    myEnv_(&config_),
    timer_(this),
    frameCount_(0),
    genCount_(0),
    fps_(0)
{}

void GridWidget::updateFrame() 
{
    if (genCount_ < config_.numGenerations_)
    {
        if (frameCount_ >= config_.numSteps_) 
        {
            myEnv_.killCreatures();
            generateCircles();
            update();
            delay(3000);
            myEnv_.newGeneration();
            circleColors_.clear();
            generateColors();
            frameCount_ = 0;
            genCount_++;
        }
        generateCircles();
        myEnv_.step();
        frameCount_++;
        update();
    }
    else
    {
        timer_.stop();
        return;
    }

}

void GridWidget::paintEvent(QPaintEvent* event) 
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    
    for (std::size_t i = 0; i<circles_.size(); i++)
    {
        painter.setBrush(circleColors_[i]);
        painter.drawEllipse(circles_[i]);
    }
}

void GridWidget::generateCircles() 
{
    circles_.clear();
    std::size_t cellWidth = width() / (config_.envSize_+1);
    std::size_t cellHeight = height() / (config_.envSize_+1);
    std::size_t counter = 0;
    for (auto&& creature : myEnv_.getCreatures()) 
    {
        if (creature.isKilled() && (circleColors_[counter].red()!= 0 || circleColors_[counter].green() != 0 || circleColors_[counter].blue() != 0))
        {
            circleColors_[counter] = QColor(0, 0, 0);
        }

        const std::pair<std::size_t, std::size_t>& pos = creature.getPosition();
        std::size_t x = (pos.first+1) * cellWidth;
        std::size_t y = (pos.second+1) * cellHeight;
        std::string hexColor;
        circles_.append(QRect(x, y, cellWidth, cellHeight));
        counter++;
    }
}

void GridWidget::generateColors()
{
    for (auto&& creature : myEnv_.getCreatures())
    {
        std::array<std::size_t, 3> RGBColor = creature.getColor();
        circleColors_.append(QColor(RGBColor.at(0), RGBColor.at(1), RGBColor.at(2)));
    }
}


DialogWindow::DialogWindow(QWidget* parent)
    : 
    QDialog(parent),
    layout_(),
    formLayout_(),
    envSizeEdit_(),
    envTypeBox_(),
    numCreaturesEdit_(),
    maxInternalNeuronsEdit_(),
    activeSensorNeuronsEdit_(),
    activeActionNeuronsEdit_(),
    numGenesEdit_(),
    numGenerationsEdit_(),
    numStepsEdit_(),
    okButton_("OK")

{
    envTypeBox_.addItems({ "Square Killzone", "West Killzone", "North Killzone", "Dense Killzone" });

    activeSensorNeuronsEdit_.addItems({ "Rnd", "BDy", "BDx", "BD", "Lx", "Ly", "Dens" });
    activeSensorNeuronsEdit_.setSelectionMode(QAbstractItemView::MultiSelection);
    activeActionNeuronsEdit_.addItems({ "MFR", "Mrn", "MRL", "Mx", "My", "Kill" });
    activeActionNeuronsEdit_.setSelectionMode(QAbstractItemView::MultiSelection);

    formLayout_.addRow("Environment size:", &envSizeEdit_);
    formLayout_.addRow("Environment type:", &envTypeBox_);
    formLayout_.addRow("Killzone size:", &killZoneSizeEdit_);
    formLayout_.addRow("Number of creatures:", &numCreaturesEdit_);
    formLayout_.addRow("Number of genes:", &numGenesEdit_);
    formLayout_.addRow("Max number of internal neurons:", &maxInternalNeuronsEdit_);
    formLayout_.addRow("Mutation rate:", &mutRateEdit_);
    formLayout_.addRow("Active sensor neurons:", &activeSensorNeuronsEdit_);
    formLayout_.addRow("Active action neurons:", &activeActionNeuronsEdit_);
    formLayout_.addRow("Number of generations:", &numGenerationsEdit_);
    formLayout_.addRow("Number of steps per generation:", &numStepsEdit_);
    formLayout_.addRow("Number of FPS:", &fpsEdit_);
    connect(&okButton_, &QPushButton::clicked, this, &DialogWindow::handleOkButtonClicked);
    formLayout_.addRow(&okButton_);

    layout_.addLayout(&formLayout_);
    setLayout(&layout_);
    setWindowTitle("Configure new simulation");
}

void DialogWindow::handleOkButtonClicked() 
{
    bool sizeOk, killZoneSizeOk, numCreaturesOk, maxInternalNeuronsOk, numGenesOk, numGenerationsOk, numStepsOk, mutRateOk, fpsOk;
    std::size_t envSize = envSizeEdit_.text().toInt(&sizeOk);
    std::string envType = envTypeBox_.currentText().toStdString();
    std::size_t killZoneSize = killZoneSizeEdit_.text().toInt(&killZoneSizeOk);
    std::size_t numCreatures = numCreaturesEdit_.text().toInt(&numCreaturesOk);
    std::size_t maxInternalNeurons = maxInternalNeuronsEdit_.text().toInt(&maxInternalNeuronsOk);
    std::size_t numGenes = numGenesEdit_.text().toInt(&numGenesOk);
    double mutRate = numGenesEdit_.text().toDouble(&mutRateOk);
    std::vector<SensorNeuronTypes> activeSensorNeurons;
    for (QListWidgetItem* item : activeSensorNeuronsEdit_.selectedItems()) {
        activeSensorNeurons.push_back(getSensorNeuron(item->text().toStdString()));
    }
    if (activeSensorNeuronsEdit_.selectedItems().isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select at least one active sensor neuron.");
        return;
    }
    std::vector<ActionNeuronTypes> activeActionNeurons;
    for (QListWidgetItem* item : activeActionNeuronsEdit_.selectedItems()) {
        activeActionNeurons.push_back(getActionNeuron(item->text().toStdString()));
    }
    if (activeActionNeuronsEdit_.selectedItems().isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select at least one active action neuron.");
        return;
    }
    std::size_t numGenerations = numGenerationsEdit_.text().toInt(&numGenerationsOk);
    std::size_t numSteps = numStepsEdit_.text().toInt(&numStepsOk);
    std::size_t fps = fpsEdit_.text().toInt(&fpsOk);
    if (sizeOk && numCreaturesOk && maxInternalNeuronsOk && numGenesOk && numGenerationsOk && numStepsOk && killZoneSizeOk && mutRateOk && fpsOk)
    {
        Config config(envSize, envType, numCreatures, maxInternalNeurons, std::move(activeSensorNeurons), std::move(activeActionNeurons), 
                      numGenes, numGenerations, numSteps, killZoneSize, mutRate);
        emit dialogSelected(config, fps);
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Selection Error", "Please fill all fields.");
        return;
    }
}

MainWindow::MainWindow(QWidget* parent)
    : 
    QMainWindow(parent),
    configSimAction_("Configure new simulation", this),
    stopSimAction_("Stop", this),
    startSimAction_("Start", this),
    gridWidget_(nullptr)
{
    setFixedSize(1000, 1000);
    connect(&configSimAction_, &QAction::triggered, this, &MainWindow::openDialog);
    connect(&stopSimAction_, &QAction::triggered, this, &MainWindow::stopSimulation);
    connect(&startSimAction_, &QAction::triggered, this, &MainWindow::startSimulation);
    menuBar()->addAction(&configSimAction_);
    menuBar()->addAction(&stopSimAction_);
    menuBar()->addAction(&startSimAction_);
    setWindowTitle("Simulation of evolution");
}

void MainWindow::openDialog()
{
    DialogWindow dialog(this);
    connect(&dialog, &DialogWindow::dialogSelected, this, &MainWindow::createSimulation);
    dialog.exec();
}

void MainWindow::createSimulation(Config config, std::size_t fps)
{
    gridWidget_ = std::make_unique<GridWidget>(std::move(config), fps, this);
    setCentralWidget(gridWidget_.get());
}

void MainWindow::stopSimulation()
{
    if (gridWidget_.get() != nullptr)
    {
        gridWidget_->stopTimer();
    }
    else
    {
        QMessageBox::warning(this, "No simulation configured", "Please configure simulation first.");
    }
}

void MainWindow::startSimulation()
{
    if (gridWidget_.get() != nullptr)
    {
        gridWidget_->startTimer();
    }
    else
    {
        QMessageBox::warning(this, "No simulation configured", "Please configure simulation first.");
    }
    
}
