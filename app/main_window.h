#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLineEdit;

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = Q_NULLPTR);
  virtual ~MainWindow();

private slots:
  void on_button_task1Res_clicked();

  void on_le_task2A_textChanged(const QString &arg1);

  void on_le_task2B_textChanged(const QString &arg1);

  void on_le_task3Min_textChanged(const QString &arg1);

  void on_le_task3Max_textChanged(const QString &arg1);

  void on_le_task4Num_textChanged(const QString &arg1);

  void on_sb_task5Num_valueChanged(int arg1);

private:
  void updateTask2Result();

  void updateTask3Result();

  void updateTask4Result();

  void updateTask5Result();

private:
  Ui::MainWindow *m_ui;
};
