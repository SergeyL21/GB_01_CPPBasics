#include "main_window.h"
#include "./ui_main_window.h"

#include "hw.h"

// вспомогательный макрос для маркировки аргумента-ссылки в методе класса или функции
#undef OUT
#define OUT

const QString FALSE_STR{"false"};
const QString TRUE_STR{"true"};
const QString ERROR_STR{"INPUT ERROR"};

// ---------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
  , m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  updateTask2Result();
  updateTask3Result();
  updateTask4Result();
  updateTask5Result();
}

// ---------------------------------------------------------------------------
MainWindow::~MainWindow()
{
  delete m_ui;
}

// ---------------------------------------------------------------------------
void MainWindow::on_button_task1Res_clicked()
{
  bool okA, okB;
  const int numA = m_ui->le_task1A->text().toInt(&okA);
  const int numB = m_ui->le_task1B->text().toInt(&okB);
  if (okA && okB)
  {
    const bool task1_res = lib::task1(numA, numB);
    m_ui->le_task1Result->setText(task1_res ? TRUE_STR : FALSE_STR);
  }
  else
  {
    m_ui->le_task1Result->setText(ERROR_STR);
  }
}

// ---------------------------------------------------------------------------
void MainWindow::updateTask2Result()
{
  bool okA, okB;
  const int numA = m_ui->le_task2A->text().toInt(&okA);
  const int numB = m_ui->le_task2B->text().toInt(&okB);
  if (okA && okB)
  {
    const bool task2_res = lib::task2(numA, numB);
    m_ui->lbl_task2Result->setText(task2_res ? TRUE_STR : FALSE_STR);
  }
  else
  {
    m_ui->lbl_task2Result->setText(ERROR_STR);
  }
}

// ---------------------------------------------------------------------------
void MainWindow::updateTask3Result()
{
  bool okMin, okMax;
  const int min = m_ui->le_task3Min->text().toInt(&okMin);
  const int max = m_ui->le_task3Max->text().toInt(&okMax);
  if (okMin && okMax)
  {
    std::string task3_res;
    lib::task3(min, max, OUT task3_res);
    m_ui->tedit_task3Result->setPlainText(QString{task3_res.c_str()});
  }
  else
  {
    m_ui->tedit_task3Result->setPlainText(ERROR_STR);
  }
}

// ---------------------------------------------------------------------------
void MainWindow::updateTask4Result()
{
  bool ok;
  const int num = m_ui->le_task4Num->text().toInt(&ok);
  if (ok)
  {
    // обработка специального случая
    if (1 == num)
    {
      m_ui->lbl_task4Result->setText(QString("SPECIAL CASE"));
    }
    else
    {
      const bool isPrime = lib::task4(num);
      m_ui->lbl_task4Result->setText(
        isPrime ? QString("IS PRIME") : QString("ISN'T PRIME"));
    }
  }
  else
  {
    m_ui->lbl_task4Result->setText(ERROR_STR);
  }
}

// ---------------------------------------------------------------------------
void MainWindow::updateTask5Result()
{
  const bool isLeap = lib::task5(m_ui->sb_task5Num->value());
  m_ui->lbl_task5Result->setText(
        isLeap ? QString("IS LEAP") : QString("ISN'T LEAP"));
}

// ---------------------------------------------------------------------------
void MainWindow::on_le_task2A_textChanged(const QString &arg1)
{
  Q_UNUSED(arg1)
  updateTask2Result();
}

// ---------------------------------------------------------------------------
void MainWindow::on_le_task2B_textChanged(const QString &arg1)
{
  Q_UNUSED(arg1)
  updateTask2Result();
}

// ---------------------------------------------------------------------------
void MainWindow::on_le_task3Min_textChanged(const QString &arg1)
{
  Q_UNUSED(arg1)
  updateTask3Result();
}

// ---------------------------------------------------------------------------
void MainWindow::on_le_task3Max_textChanged(const QString &arg1)
{
  Q_UNUSED(arg1)
  updateTask3Result();
}

// ---------------------------------------------------------------------------
void MainWindow::on_le_task4Num_textChanged(const QString &arg1)
{
  Q_UNUSED(arg1)
  updateTask4Result();
}

// ---------------------------------------------------------------------------
void MainWindow::on_sb_task5Num_valueChanged(int arg1)
{
  Q_UNUSED(arg1)
  updateTask5Result();
}
