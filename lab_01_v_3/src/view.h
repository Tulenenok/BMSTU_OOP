#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_load_clicked();

    void on_pushButton_spin_clicked();

    void on_pushButton_move_clicked();

    void on_pushButton_scale_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // VIEW_H
