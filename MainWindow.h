#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "Calculator.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

protected:
  void keyPressEvent(QKeyEvent *event) override;

private slots:
  void onDigitClicked();
  void onOperationClicked();
  void onEqualClicked();
  void onClearClicked();
  void onDeleteClicked();
  void onSignClicked();

private:
  void setupUI();
  void updateDisplay();

  Calculator m_calculator;
  QLineEdit *m_display;
};
#endif
