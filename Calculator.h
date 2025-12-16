#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>

class Calculator {
public:
  Calculator();

  void appendDigit(const QString &digit);
  void setOperation(const QString &op);
  void calculate();
  void clear();
  void deleteDigit();
  void sign();
  bool hasError() const;
  QString getCurrentDisplay() const;

private:
  double performCalculation(double a, double b, const QString &op);

  QString m_currentInput;
  QString m_bufferInput;
  QString m_currentOperation;
  bool m_resetOnNextInput;
  bool m_hasError;
};

#endif
