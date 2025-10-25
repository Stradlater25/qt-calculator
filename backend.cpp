#include <QWidget>
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <qlist.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>


class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
    currentInput = "";
    resetOnNextInput = false;
    setupUI();
    setupConnections();
  }

private slots:
  void onButton1Clicked() { appendToInput("1"); }
  void onButton2Clicked() { appendToInput("2"); }
  void onButton3Clicked() { appendToInput("3"); }
  void onButton4Clicked() { appendToInput("4"); }
  void onButton5Clicked() { appendToInput("5"); }
  void onButton6Clicked() { appendToInput("6"); }
  void onButton7Clicked() { appendToInput("7"); }
  void onButton8Clicked() { appendToInput("8"); }
  void onButton9Clicked() { appendToInput("9"); }
  void onButton0Clicked() { appendToInput("0"); }
  void onCommaButtonClicked() { appendToInput("."); }


  void onClearClicked() {
    currentInput = "";
    textField->clear();
  }


private:
  QString currentInput;
  bool resetOnNextInput;
  void setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    textField = new QLineEdit(this);
    QPushButton *button1 = new QPushButton("1", this); 
    QPushButton *button2 = new QPushButton("2", this);
    QPushButton *button3 = new QPushButton("3", this);
    QPushButton *button4 = new QPushButton("4", this);
    QPushButton *button5 = new QPushButton("5", this);
    QPushButton *button6 = new QPushButton("6", this);
    QPushButton *button7 = new QPushButton("7", this);
    QPushButton *button8 = new QPushButton("8", this);
    QPushButton *button9 = new QPushButton("9", this);
    QPushButton *button0 = new QPushButton("0", this);
    QPushButton *additionButton = new QPushButton("+", this);
    QPushButton *subtractionButton = new QPushButton("-", this);
    QPushButton *multiplicationButton = new QPushButton("*", this);
    QPushButton *divisionButton = new QPushButton("÷", this);
    QPushButton *commaButton = new QPushButton(".", this);
    QPushButton *clearButton = new QPushButton("C", this);


    // customization of textField
    textField->setAlignment(Qt::AlignRight);
    textField->setMinimumHeight(40);
    QFont font = textField->font();
    font.setPointSize(16);
    textField->setFont(font);
    


    // creating layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QGridLayout *buttonLayout = new QGridLayout();

    // setting up minimal size of the buttons
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QList<QPushButton *> buttons = {
        button0,        button1,     button2,        button3,
        button4,        button5,     button6,        button7,
        button8,        button9,     additionButton, subtractionButton,
        multiplicationButton, divisionButton, commaButton, clearButton};
    
    for (QPushButton *button : buttons) {
      button->setSizePolicy(sizePolicy);
      button->setMinimumSize(60, 60);
    }
    
    // adding buttons to hlayout
    mainLayout->addWidget(textField);
    buttonLayout->addWidget(button1,1,1);
    buttonLayout->addWidget(button2,1,2);
    buttonLayout->addWidget(button3,1,3);
    buttonLayout->addWidget(button4,2,1);
    buttonLayout->addWidget(button5,2,2);
    buttonLayout->addWidget(button6,2,3);
    buttonLayout->addWidget(button7,3,1);
    buttonLayout->addWidget(button8,3,2);
    buttonLayout->addWidget(button9,3,3);
    buttonLayout->addWidget(button0,4,2);
    buttonLayout->addWidget(additionButton,1,4);
    buttonLayout->addWidget(subtractionButton,2,4);
    buttonLayout->addWidget(multiplicationButton,3,4);
    buttonLayout->addWidget(divisionButton,4,4);
    buttonLayout->addWidget(commaButton,4,1);
    buttonLayout->addWidget(clearButton,4,3);

    // include to main layout
    mainLayout->addLayout(buttonLayout);

    // save buttons pointers for signals' connection
    this->button1 = button1;
    this->button2 = button2;
    this->button3 = button3;
    this->button4 = button4;
    this->button5 = button5;
    this->button6 = button6;
    this->button7 = button7;
    this->button8 = button8;
    this->button9 = button9;
    this->button0 = button0;
    this->clearButton = clearButton;
    this->commaButton = commaButton;

    setWindowTitle("QT6 Calculator");
    resize(275,325);
  }

  void appendToInput(const QString &text) {
    if (resetOnNextInput) {
      textField->clear();
      currentInput = "";
      resetOnNextInput = false;
    }
    currentInput += text;
    textField->setText(currentInput);
  }
  
  void setupConnections() {
    connect(button1, &QPushButton::clicked, this, &MainWindow::onButton1Clicked);
    connect(button2, &QPushButton::clicked, this, &MainWindow::onButton2Clicked);
    connect(button3, &QPushButton::clicked, this, &MainWindow::onButton3Clicked);
    connect(button4, &QPushButton::clicked, this, &MainWindow::onButton4Clicked);
    connect(button5, &QPushButton::clicked, this, &MainWindow::onButton5Clicked);
    connect(button6, &QPushButton::clicked, this, &MainWindow::onButton6Clicked);
    connect(button7, &QPushButton::clicked, this, &MainWindow::onButton7Clicked);
    connect(button8, &QPushButton::clicked, this, &MainWindow::onButton8Clicked);
    connect(button9, &QPushButton::clicked, this, &MainWindow::onButton9Clicked);
    connect(button0, &QPushButton::clicked, this, &MainWindow::onButton0Clicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(commaButton, &QPushButton::clicked, this, &MainWindow::onCommaButtonClicked);
    }
  
  QPushButton *button1;  
  QPushButton *button2;
  QPushButton *button3;
  QPushButton *button4;
  QPushButton *button5;
  QPushButton *button6;
  QPushButton *button7;
  QPushButton *button8;
  QPushButton *button9;
  QPushButton *button0;
  QPushButton *clearButton;
  QPushButton *commaButton;
  QLineEdit *textField;
  // QLabel  *statusLabel;
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow window;
  window.show();
    
  return app.exec();
}

#include "backend.moc"
