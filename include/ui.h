/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H
#define UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QThread>
#include "modbus.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <thread>
#include <windows.h>
#include <iomanip>
#include <cerrno>
#include <fcntl.h>

QT_BEGIN_NAMESPACE

class Worker_Thread_TCP : public QThread
{
Q_OBJECT

public:
    modbus_t *ctx=nullptr;
    modbus_mapping_t *mb_mapping;
    int server_socket=-1;
    bool *thread_break;
    int *p_mode;
    int *p_req_add, *p_req_num;

    Worker_Thread_TCP(QObject *parent, bool *thread_break, int *p_mode, int*p_req_add, int*p_req_num) :
            QThread(parent),
            thread_break(thread_break), p_mode(p_mode), p_req_add(p_req_add), p_req_num(p_req_num)
    {};

    void run() override;
//    void get_req(uint8_t *req) const;
signals:
    void update_output_xyzt(int32_t ax, int32_t ay, int32_t az, int32_t t);
    void update_output_request(int32_t req);
    void update_output_op(std::string str);
    void update_led_color(int c);
    void update_connection_state(bool s);

//public slots:

};

class Worker_Thread_RTU : public QThread
{
Q_OBJECT

public:
    modbus_t *ctx=nullptr;
    modbus_mapping_t *mb_mapping;
    bool *thread_break;
    int *p_mode;
    int *p_req_add, *p_req_num;

    Worker_Thread_RTU(QObject *parent, bool *thread_break, int *p_mode, int*p_req_add, int*p_req_num) :
            QThread(parent),
            thread_break(thread_break), p_mode(p_mode), p_req_add(p_req_add), p_req_num(p_req_num)
    {};

    void run() override;
    void get_req(uint8_t *req) const;
signals:
    void update_output_xyzt(int32_t ax, int32_t ay, int32_t az, int32_t t);
    void update_output_request(int32_t req);
    void update_output_op(std::string str);
    void update_led_color(int c);
    void update_connection_state(bool s);

//public slots:

};

class Ui_MainWindow : public QObject
{
Q_OBJECT

public:
    QWidget *centralwidget;
    QTextBrowser *output_op;
    QString *output_op_str = new QString;

    QLineEdit *input_addr;
    QLineEdit *input_port;
    QComboBox *combo_mode;
    QComboBox *combo_prot;

    QTextBrowser *output_request;
    QString *output_request_str = new QString;
    QTextBrowser *output_ax;
    QString *output_ax_str = new QString;
    QTextBrowser *output_ay;
    QString *output_ay_str = new QString;
    QTextBrowser *output_az;
    QString *output_az_str = new QString;
    QTextBrowser *output_t;
    QString *output_t_str = new QString;

    QTextBrowser *output_state;
    QString *output_state_str = new QString;

    QLabel *label_addr;
    QLabel *label_port;

    QPushButton *button_start_server;

    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;

    QLabel *label_device;
    QLabel *label_state;
    QString *label_status_str = new QString;
    QLabel *label_led;

    QPushButton *button_stop;
    QLineEdit *input_req_addr;
    QLineEdit *input_req_num;

    QLabel *label_begin_addr;
    QLabel *label_data_num;
    QLabel *label_mode;
    QLabel *label_prot;
    QLabel *label_request;
    QLabel *label_ax;
    QLabel *label_ay;
    QLabel *label_az;
    QLabel *label_t;
    QLabel *label_outputs;
    QProgressBar *progressBar;

    QMenuBar *menubar;
    QStatusBar *statusbar;

    std::string _modbus_addr = "127.0.0.1";
    int _modbus_port = 485;

    int server_socket=0;
//    modbus_mapping_t *mb_mapping = modbus_mapping_new(500, 50, 50, 50);
    int req_add=0;
    int req_num=1;

    int mode = 0;
    int prot = 0; // TCP:0, RTU:1

    bool thread_break = false;

    Worker_Thread_TCP *_worker_thread_tcp;
    Worker_Thread_RTU *_worker_thread_rtu;;


    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        output_op = new QTextBrowser(centralwidget);
        output_op->setObjectName("output_op");
        output_op->setGeometry(QRect(100, 300, 300, 200));
        input_addr = new QLineEdit(centralwidget);
        input_addr->setObjectName("input_addr");
        input_addr->setGeometry(QRect(500, 320, 120, 20));
        input_port = new QLineEdit(centralwidget);
        input_port->setObjectName("input_port");
        input_port->setGeometry(QRect(650, 320, 60, 20));

        combo_mode = new QComboBox(centralwidget);
        combo_mode->addItem(QString());
        combo_mode->addItem(QString());
        combo_mode->setObjectName("combo_mode");
        combo_mode->setGeometry(QRect(500, 370, 80, 20));

        combo_prot = new QComboBox(centralwidget);
        combo_prot->addItem(QString());
        combo_prot->addItem(QString());
        combo_prot->setObjectName("combo_prot");
        combo_prot->setGeometry(QRect(630, 370, 80, 20));

//        button_send = new QPushButton(centralwidget);
//        button_send->setObjectName("button_send");
//        button_send->setGeometry(QRect(630, 370, 80, 20));
//        button_send->setGeometry(QRect(500, 480, 80, 20));

        output_request = new QTextBrowser(centralwidget);
        output_request->setObjectName("output_request");
        output_request->setGeometry(QRect(100, 40, 300, 20));
        output_request->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        output_ax = new QTextBrowser(centralwidget);
        output_ax->setObjectName("output_ax");
        output_ax->setGeometry(QRect(100, 90, 300, 20));
        output_ax->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        output_ay = new QTextBrowser(centralwidget);
        output_ay->setObjectName("output_ay");
        output_ay->setGeometry(QRect(100, 140, 300, 20));
        output_ay->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        output_az = new QTextBrowser(centralwidget);
        output_az->setObjectName("output_az");
        output_az->setGeometry(QRect(100, 190, 300, 20));
        output_az->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        output_t = new QTextBrowser(centralwidget);
        output_t->setObjectName("output_t");
        output_t->setGeometry(QRect(100, 240, 300, 20));
        output_t->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        label_addr = new QLabel(centralwidget);
        label_addr->setObjectName("label_addr");
        label_addr->setGeometry(QRect(500, 300, 120, 20));
        label_port = new QLabel(centralwidget);
        label_port->setObjectName("label_port");
        label_port->setGeometry(QRect(650, 300, 60, 20));

        button_start_server = new QPushButton(centralwidget);
        button_start_server->setObjectName("button_start_server");
        button_start_server->setGeometry(QRect(500, 480, 80, 20));
//        button_start_server->setGeometry(QRect(630, 370, 80, 20));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 0, 16, 16));

        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(780, 560, 21, 20));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_device = new QLabel(centralwidget);
        label_device->setObjectName("label_device");
        label_device->setGeometry(QRect(500, 90, 80, 20));
        label_device->setFrameShadow(QFrame::Shadow::Sunken);
        label_state = new QLabel(centralwidget);
        label_state->setObjectName("label_state");
        label_state->setGeometry(QRect(640, 90, 90, 20));
        label_state->setFrameShadow(QFrame::Shadow::Sunken);
        label_led = new QLabel(centralwidget);
        label_led->setObjectName("label_led");
        label_led->setGeometry(QRect(600, 90, 20, 20));
        label_led->setFrameShadow(QFrame::Shadow::Raised);
        label_led->setStyleSheet("QLabel { background-color : red; }");


        button_stop = new QPushButton(centralwidget);
        button_stop->setObjectName("button_stop");
        button_stop->setGeometry(QRect(630, 480, 80, 20));

        input_req_addr = new QLineEdit(centralwidget);
        input_req_addr->setObjectName("input_req_addr");
        input_req_addr->setGeometry(QRect(500, 430, 80, 20));
        input_req_num = new QLineEdit(centralwidget);
        input_req_num->setObjectName("input_req_num");
        input_req_num->setGeometry(QRect(630, 430, 80, 20));
        label_begin_addr = new QLabel(centralwidget);
        label_begin_addr->setObjectName("label_begin_addr");
        label_begin_addr->setGeometry(QRect(500, 410, 120, 20));
        label_data_num = new QLabel(centralwidget);
        label_data_num->setObjectName("label_data_num");
        label_data_num->setGeometry(QRect(630, 410, 120, 20));
        label_mode = new QLabel(centralwidget);
        label_mode->setObjectName("label_mode");
        label_mode->setGeometry(QRect(500, 350, 120, 20));

        label_prot = new QLabel(centralwidget);
        label_prot->setObjectName("label_prot");
        label_prot->setGeometry(QRect(630, 350, 120, 20));

        label_request = new QLabel(centralwidget);
        label_request->setObjectName("label_request");
        label_request->setGeometry(QRect(50, 40, 50, 20));
        label_ax = new QLabel(centralwidget);
        label_ax->setObjectName("label_ax");
        label_ax->setGeometry(QRect(80, 90, 20, 20));
        label_ay = new QLabel(centralwidget);
        label_ay->setObjectName("label_ay");
        label_ay->setGeometry(QRect(80, 140, 20, 20));
        label_az = new QLabel(centralwidget);
        label_az->setObjectName("label_az");
        label_az->setGeometry(QRect(80, 190, 20, 20));
        label_t = new QLabel(centralwidget);
        label_t->setObjectName("label_t");
        label_t->setGeometry(QRect(80, 240, 20, 20));

        label_outputs = new QLabel(centralwidget);
        label_outputs->setObjectName("label_outputs");
        label_outputs->setGeometry(QRect(100, 40, 80, 20));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(500, 240, 250, 20));
        progressBar->setValue(0);
        output_state = new QTextBrowser(centralwidget);
        output_state->setObjectName("output_state");
        output_state->setGeometry(QRect(500, 140, 210, 40));

//        thr_t = new Worker_Test(this, &ctx, &thread_break);
        _worker_thread_tcp = new Worker_Thread_TCP(this, &thread_break, &mode, &req_add, &req_num);
        _worker_thread_rtu = new Worker_Thread_RTU(this, &thread_break, &mode, &req_add, &req_num);

//        thread_mode_1 = new Worker_Mode1(this, &ctx, &server_socket, &thread_break, &req_add, &req_num);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);

        connect(this->button_start_server, &QPushButton::clicked, this, &Ui_MainWindow::start_server);
        connect(this->combo_mode, &QComboBox::currentIndexChanged, this, &Ui_MainWindow::change_mode);
        connect(this->combo_prot, &QComboBox::currentIndexChanged, this, &Ui_MainWindow::change_prot);
        connect(this->button_stop, &QPushButton::clicked, this, &Ui_MainWindow::stop_thread);
        connect(this->_worker_thread_tcp, &Worker_Thread_TCP::update_output_xyzt, this, &Ui_MainWindow::update_output_xyzt);
        connect(this->input_req_addr, &QLineEdit::editingFinished, this, &Ui_MainWindow::change_req_data);
        connect(this->input_req_num, &QLineEdit::editingFinished, this, &Ui_MainWindow::change_req_data);
        connect(this->_worker_thread_tcp, &Worker_Thread_TCP::update_output_op, this, &Ui_MainWindow::update_output_op);
        connect(this->_worker_thread_tcp, &Worker_Thread_TCP::update_led_color, this, &Ui_MainWindow::update_led_color);
        connect(this->_worker_thread_tcp, &Worker_Thread_TCP::update_output_request, this, &Ui_MainWindow::update_output_request);
        connect(this->_worker_thread_tcp, &Worker_Thread_TCP::update_connection_state, this, &Ui_MainWindow::update_connection_state);
        connect(this->_worker_thread_rtu, &Worker_Thread_RTU::update_output_op, this, &Ui_MainWindow::update_output_op);
        connect(this->_worker_thread_rtu, &Worker_Thread_RTU::update_led_color, this, &Ui_MainWindow::update_led_color);
        connect(this->_worker_thread_rtu, &Worker_Thread_RTU::update_output_request, this, &Ui_MainWindow::update_output_request);
        connect(this->_worker_thread_rtu, &Worker_Thread_RTU::update_connection_state, this, &Ui_MainWindow::update_connection_state);


    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Accelerometer", nullptr));
        input_addr->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        input_port->setText(QCoreApplication::translate("MainWindow", "485", nullptr));
        combo_mode->setItemText(0, QCoreApplication::translate("MainWindow", "ACTIVE", nullptr));
        combo_mode->setItemText(1, QCoreApplication::translate("MainWindow", "REQUEST", nullptr));

        combo_prot->setItemText(0, QCoreApplication::translate("MainWindow", "RTU", nullptr));
        combo_prot->setItemText(1, QCoreApplication::translate("MainWindow", "TCP", nullptr));

        label_addr->setText(QCoreApplication::translate("MainWindow", "IP address", nullptr));
        label_port->setText(QCoreApplication::translate("MainWindow", "port", nullptr));
        input_req_addr->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        input_req_num->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        button_start_server->setText(QCoreApplication::translate("MainWindow", "Initiate", nullptr));
        label_device->setText(QCoreApplication::translate("MainWindow", "Server state", nullptr));
        label_state->setText(QCoreApplication::translate("MainWindow", "No connection", nullptr));
        label_led->setText(QString());
//        button_send->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        button_stop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        label_begin_addr->setText(QCoreApplication::translate("MainWindow", "Begin address", nullptr));
        label_data_num->setText(QCoreApplication::translate("MainWindow", "Data num", nullptr));
        label_mode->setText(QCoreApplication::translate("MainWindow", "Mode", nullptr));
        label_prot->setText(QCoreApplication::translate("MainWindow", "Protocol", nullptr));
        label_request->setText(QCoreApplication::translate("MainWindow", "request", nullptr));
        label_ax->setText(QCoreApplication::translate("MainWindow", "ax", nullptr));
        label_ay->setText(QCoreApplication::translate("MainWindow", "ay", nullptr));
        label_az->setText(QCoreApplication::translate("MainWindow", "az", nullptr));
        label_t->setText(QCoreApplication::translate("MainWindow", " T", nullptr));
//        label_outputs->setText(QCoreApplication::translate("MainWindow", "OUTPUTS", nullptr));
    } // retranslateUi
public slots:

    void start_server();

    void change_mode();
    void change_prot();

    void change_req_data();


//
    void start_thread();

    void stop_thread();

    void update_output_request(int32_t req);

    void update_output_xyzt(int32_t ax, int32_t ay, int32_t az, int32_t t);
    void update_output_op(const std::string& str);
    void update_led_color(int c);
    void update_connection_state(bool s);

};


namespace Ui
{
    class MainWindow : public Ui_MainWindow
    {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H
