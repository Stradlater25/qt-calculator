#include "MainWindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QList>
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) { setupUI(); }

void MainWindow::setupUI() {
  QWidget *central = new QWidget(this);
  setCentralWidget(central);

  // Display
  m_display = new QLineEdit(this);
  m_display->setAlignment(Qt::AlignRight);
  m_display->setMinimumHeight(40);
  QFont displayFont = m_display->font();
  displayFont.setPointSize(16);
  m_display->setFocusPolicy(Qt::NoFocus);
  m_display->setFont(displayFont);
  m_display->setReadOnly(true);

  // Layouts
  QVBoxLayout *mainLayout = new QVBoxLayout(central);
  QGridLayout *grid = new QGridLayout();

  // Button data: {text, row, col, rowSpan, colSpan, isOperation}

  struct ButtonData {
    QString text;
    int row, col, rowSpan, colSpan;
    bool isOperation;
  };

  QList<ButtonData> buttons = {
      {"±", 1, 1, 1, 1, true}, {"DEL", 1, 2, 1, 1, true},
      {"C", 1, 3, 1, 1, true},  {"+", 1, 4, 1, 1, true},

      {"1", 2, 1, 1, 1, false}, {"2", 2, 2, 1, 1, false},
      {"3", 2, 3, 1, 1, false}, {"-", 2, 4, 1, 1, true},

      {"4", 3, 1, 1, 1, false}, {"5", 3, 2, 1, 1, false},
      {"6", 3, 3, 1, 1, false}, {"*", 3, 4, 1, 1, true},

      {"7", 4, 1, 1, 1, false}, {"8", 4, 2, 1, 1, false},
      {"9", 4, 3, 1, 1, false}, {"÷", 4, 4, 1, 1, true},

      {".", 5, 1, 1, 1, false}, {"0", 5, 2, 1, 1, false},
      {"=", 5, 3, 1, 2, true}};

  // Create buttons
  QFont btnFont;
  btnFont.setPointSize(16);


  for (const ButtonData &data : buttons) {
    QPushButton *btn = new QPushButton(data.text, this);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setMinimumSize(60, 60);
    btn->setFont(btnFont);

    grid->addWidget(btn, data.row, data.col, data.rowSpan, data.colSpan);

    // Connect signals
    if (data.text == "C") {
      connect(btn, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    } else if (data.text == "=") {
      connect(btn, &QPushButton::clicked, this, &MainWindow::onEqualClicked);
    } else if (data.text == "DEL") {
      connect(btn, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    } else if (data.text == "±") {
      connect(btn, &QPushButton::clicked, this, &MainWindow::onSignClicked);      
    } else if (data.isOperation) {
      connect(btn, &QPushButton::clicked, this, &MainWindow::onOperationClicked);
    } else {
      connect(btn, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    }
  }

  mainLayout->addWidget(m_display);
  mainLayout->addLayout(grid);
  setWindowTitle("QT6 Calculator");
    
  resize(275,325);
}

void MainWindow::onDigitClicked() {
  QPushButton *btn = qobject_cast<QPushButton *>(sender());
  if (btn) {
    m_calculator.appendDigit(btn->text());
    updateDisplay();
  }
};

void MainWindow::onOperationClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn)
     return;

    
    QString op = btn->text();
    QString opCode;
    
    if (op == "+") opCode = "plus";
    else if (op == "-") opCode = "minus";
    else if (op == "*") opCode = "multiply";
    else if (op == "÷") opCode = "divide";
    
    if (!opCode.isEmpty()) {
        m_calculator.setOperation(opCode);
    }
        updateDisplay();
    
}

void MainWindow::onDeleteClicked() {
  m_calculator.deleteDigit();
  updateDisplay();
}


void MainWindow::onEqualClicked() {
  m_calculator.calculate();
  updateDisplay();
}

void MainWindow::onClearClicked() {
    m_calculator.clear();
    updateDisplay();
}

void MainWindow::onSignClicked() {
  m_calculator.sign();
  updateDisplay();  
}

void MainWindow::updateDisplay() {
  m_display->setText(m_calculator.getCurrentDisplay());
  QString text = m_calculator.getCurrentDisplay();
#ifdef DEBUG
  qDebug() << "updateDisplay called, text: " << text;
#endif
  m_display->setText(text);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  QString key = event->text();

  // Обработка цифр
  if (key >= "0" && key <= "9") {
    m_calculator.appendDigit(key);
    updateDisplay();
    return;
  }

  // Обработка операций
  switch (event->key()) {
  case Qt::Key_Plus:
    m_calculator.setOperation("plus");
    updateDisplay();
    break;
  case Qt::Key_Minus:
    m_calculator.setOperation("minus");
    updateDisplay();
    break;
  case Qt::Key_Asterisk:
    m_calculator.setOperation("multiply");
    updateDisplay();
    break;
  case Qt::Key_Slash:
    m_calculator.setOperation("divide");
    updateDisplay();
    break;
  case Qt::Key_Return:
  case Qt::Key_Enter:
  case Qt::Key_Equal:
    m_calculator.calculate();
    updateDisplay();
    break;
  case Qt::Key_Backspace:
    m_calculator.deleteDigit();
    updateDisplay();          
    break;          
  case Qt::Key_C:
    m_calculator.clear();
    updateDisplay();
    break;
  case Qt::Key_Period:
  case Qt::Key_Comma:
    m_calculator.appendDigit(".");
    updateDisplay();
    break;
  default:
    QMainWindow::keyPressEvent(event);
  }  
}
