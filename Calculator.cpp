#include "Calculator.h"
#include "qobject.h"
#include <QDebug>

Calculator::Calculator() : m_resetOnNextInput(false) {}

void Calculator::appendDigit(const QString &digit) {
  if (m_currentInput == "0" && digit == "0") {
    return;
    }
  if (m_resetOnNextInput) {
    m_currentInput.clear();
    m_resetOnNextInput = false;
  }
  m_currentInput += digit;
#ifdef DEBUG
  qDebug() << "Current input:" << m_currentInput;
#endif
}

void Calculator::setOperation(const QString &op) {
    if (!m_currentInput.isEmpty()) {
      if (!m_currentOperation.isEmpty() && !m_bufferInput.isEmpty()) {
#ifdef DEBUG
        qDebug() << "Operation second time pressed, operation: " << op
                 << "Buffer: " << m_bufferInput;
#endif        
            calculate();  // Вычисляем предыдущую операцию
            // После calculate() результат уже в m_currentInput
        }
        m_bufferInput = m_currentInput;
        m_currentOperation = op;
        m_resetOnNextInput = true;
#ifdef DEBUG
        qDebug() << "Operation set:" << op << "Buffer:" << m_bufferInput;
#endif
    }
}


void Calculator::calculate() {
    if (m_currentOperation.isEmpty() || m_bufferInput.isEmpty()) {
        return;
    }

    double a = m_bufferInput.toDouble();
    double b = m_currentInput.toDouble();

    // Проверка деления на ноль
    if (m_currentOperation == "divide" && b == 0) {
        m_currentInput = "Ошибка: деление на 0";
        m_hasError = true;
        m_bufferInput.clear();
        m_currentOperation.clear();
        m_resetOnNextInput = true;
        return;
    }
    double result = performCalculation(a, b, m_currentOperation);
    
    m_currentInput = QString::number(result);
    m_bufferInput.clear();
    m_currentOperation.clear();
    m_resetOnNextInput = true;
    
#ifdef DEBUG
    qDebug() << "Result:" << result;
#endif
  }

void Calculator::clear() {
    m_currentInput.clear();
    m_bufferInput.clear();
    m_currentOperation.clear();
    m_resetOnNextInput = false;
}

void Calculator::deleteDigit() {
  m_currentInput.chop(1);
}

void Calculator::sign() {
  if (m_currentInput.isEmpty()) {
    return;
  }  
  double value = m_currentInput.toDouble();
  value = -value;
  m_currentInput = QString::number(value);  
  }

bool Calculator::hasError() const {
  return m_hasError;
  }

QString Calculator::getCurrentDisplay() const {
    return m_currentInput;
}

double Calculator::performCalculation(double a, double b, const QString &op) {
    if (op == "plus") return a + b;
    if (op == "minus") return a - b;
    if (op == "multiply") return a * b;
    if (op == "divide") return (b != 0) ? a / b : 0;
    return 0;
}
