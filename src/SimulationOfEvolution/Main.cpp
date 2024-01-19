#include <QApplication>
#include <QPushButton>
#include <matplot/matplot.h>


int main(int argc, char* argv[])

{

	QApplication a(argc, argv);

	QPushButton HelloWorld("Hello World");

	HelloWorld.resize(300, 60);

	HelloWorld.show();

	return a.exec();

}