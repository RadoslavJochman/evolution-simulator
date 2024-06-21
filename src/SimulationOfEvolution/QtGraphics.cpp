#include "QtGraphics.h"

GridWidget::GridWidget(Config&& config, QWidget* parent)
    : 
    QWidget(parent),
    config_(std::move(config)),
    myEnv_(&config_),
    timer_(this)
{
    setFixedSize(800, 800);
    generateCircles();
    connect(&timer_, &QTimer::timeout, this, &GridWidget::updateFrame);
}


GridWidget::GridWidget()
    :
    QWidget(nullptr),
    config_(),
    myEnv_(&config_),
    frameCount_(0)
{
}

void GridWidget::startAnimation() {
    frameCount_ = 0;
    circles_.clear();
    timer_.start(1000 / 10);
}

void GridWidget::updateFrame() 
{
    if (frameCount_ >= config_.numSteps_) {
        timer_.stop();
        return;
    }
    generateCircles();
    myEnv_.step();
    frameCount_++;
    update(); // Request a paint event
}


void GridWidget::paintEvent(QPaintEvent* event) 
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(Qt::red);
    for (const QRect& rect : circles_) 
    {
        painter.drawEllipse(rect);
    }
}

void GridWidget::generateCircles() 
{
    circles_.clear();
    int cellWidth = width() / (config_.envSize_+2);
    int cellHeight = height() / (config_.envSize_+2);
    for (auto&& creature : myEnv_.getCreatures()) 
    {
        const std::pair<std::size_t, std::size_t>& pos = creature.getPosition();
        int x = (pos.first+1) * cellWidth;
        int y = (pos.second+1) * cellHeight;
        circles_.append(QRect(x, y, cellWidth, cellHeight));
    }
    update();
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
    envTypeBox_.addItems({ "Square in the middle", });

    activeSensorNeuronsEdit_.addItems({ "Age", "Rnd", "BDy", "BD", "Lx", "Ly", "Osc" });
    activeSensorNeuronsEdit_.setSelectionMode(QAbstractItemView::MultiSelection);
    activeActionNeuronsEdit_.addItems({ "MFR", "Mrn", "MRL", "Mx", "My", "Kill" });
    activeActionNeuronsEdit_.setSelectionMode(QAbstractItemView::MultiSelection);

    formLayout_.addRow("Environment size:", &envSizeEdit_);
    formLayout_.addRow("Environment type:", &envTypeBox_);
    formLayout_.addRow("Number of creatures:", &numCreaturesEdit_);
    formLayout_.addRow("Max number of internal neurons:", &maxInternalNeuronsEdit_);
    formLayout_.addRow("Active sensor neurons:", &activeSensorNeuronsEdit_);
    formLayout_.addRow("Active action neurons:", &activeActionNeuronsEdit_);
    formLayout_.addRow("Number of genes:", &numGenesEdit_);
    formLayout_.addRow("Number of generations:", &numGenerationsEdit_);
    formLayout_.addRow("Number of steps per generation:", &numStepsEdit_);
   
    connect(&okButton_, &QPushButton::clicked, this, &DialogWindow::handleOkButtonClicked);
    formLayout_.addRow(&okButton_);

    layout_.addLayout(&formLayout_);
    setLayout(&layout_);
    setWindowTitle("Enter Grid Size");
}

void DialogWindow::handleOkButtonClicked() 
{
    bool sizeOk, numCreaturesOk, maxInternalNeuronsOk, numGenesOk, numGenerationsOk, numStepsOk;
    std::size_t envSize = envSizeEdit_.text().toInt(&sizeOk);
    std::string envType = envTypeBox_.currentText().toStdString();
    std::size_t numCreatures = numCreaturesEdit_.text().toInt(&numCreaturesOk);
    std::size_t maxInternalNeurons = maxInternalNeuronsEdit_.text().toInt(&maxInternalNeuronsOk);
    std::size_t numGenes = numGenesEdit_.text().toInt(&numGenesOk);
    std::vector<SensorNeuronTypes> activeSensorNeurons;
    for (QListWidgetItem* item : activeSensorNeuronsEdit_.selectedItems()) {
        activeSensorNeurons.push_back(getSensorNeuron(item->text().toStdString()));
    }
    std::vector<ActionNeuronTypes> activeActionNeurons;
    for (QListWidgetItem* item : activeActionNeuronsEdit_.selectedItems()) {
        activeActionNeurons.push_back(getActionNeuron(item->text().toStdString()));
    }
    std::size_t numGenerations = numGenerationsEdit_.text().toInt(&numGenerationsOk);
    std::size_t numSteps = numStepsEdit_.text().toInt(&numStepsOk);
    if (sizeOk && numCreaturesOk && maxInternalNeuronsOk && numGenesOk && numGenerationsOk && numStepsOk)
    {
        Config config(envSize, envType, numCreatures, maxInternalNeurons, std::move(activeSensorNeurons), std::move(activeActionNeurons), numGenes, numGenerations, numSteps);
        emit dialogSelected(config);
        accept();
    }
}

MainWindow::MainWindow(QWidget* parent)
    : 
    QMainWindow(parent),
    configSimAction_("Configure simulation", this),
    gridWidget_(nullptr)
{
    connect(&configSimAction_, &QAction::triggered, this, &MainWindow::openDialog);
    menuBar()->addAction(&configSimAction_);
    setWindowTitle("Simulation of evolution");
}

void MainWindow::openDialog()
{
    DialogWindow dialog(this);
    connect(&dialog, &DialogWindow::dialogSelected, this, &MainWindow::createSimulation);
    dialog.exec();
}

void MainWindow::createSimulation(Config config)
{
    gridWidget_ = std::make_unique<GridWidget>(std::move(config), this);
    setCentralWidget(gridWidget_.get());
    gridWidget_->startAnimation();
}
