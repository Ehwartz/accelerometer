//
// Created by Ehwartz on 08/05/2024.
//
#include "ui.h"

bool str2int(const std::string &str, int &ret)
{
    try
    {
        size_t pos;
        ret = std::stoi(str, &pos);

        if (pos != str.length())
        {
            return false;
        }
        return true;
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
    catch (const std::out_of_range &e)
    {
        return false;
    }
}

void Ui_MainWindow::start_server()
{
//    delete this->_worker_thread_tcp;
//    this->_worker_thread_tcp=nullptr;
//    this->_worker_thread_tcp=new Worker_Thread_TCP(this, &thread_break, &mode, &req_add, &req_num);
    this->thread_break = false;
    this->start_thread();

    this->progressBar->setValue(0);
    int rand1 = std::rand() % 100;
    this->progressBar->setValue(rand1);
    this->progressBar->setValue(std::rand() % (99 - rand1) + rand1);
    this->progressBar->setValue(100);

}

void Ui_MainWindow::change_mode()
{
//    if (!this->thread_break)
//    {
//        *this->output_op_str = "Thread stop";
//        this->output_op->append(*this->output_op_str);
//    }
//    this->thread_break = true;
    this->mode = this->combo_mode->currentIndex();
    std::string tmp_str = "Mode switched to: ";
    *this->output_op_str = (tmp_str + std::to_string(this->mode)).c_str();
    this->output_op->append(*this->output_op_str);
}

void Ui_MainWindow::change_prot()
{
    this->prot = this->combo_prot->currentIndex();
    std::string tmp_str = "Protocol switched to: ";
    *this->output_op_str = (tmp_str + (!this->prot ? "RTU" : "TCP")).c_str();
    this->output_op->append(*this->output_op_str);
}

void Ui_MainWindow::change_req_data()
{
    if (!this->input_req_addr->text().isEmpty())
    {
        std::wstring req_addr_wstr = this->input_req_addr->text().toStdWString();
        std::string req_addr_str(req_addr_wstr.begin(), req_addr_wstr.end());
        bool is_converted = str2int(req_addr_str, this->req_add);
        if (!is_converted)
        {
            *this->output_op_str = "Invalid request address";
            this->output_op->append(*this->output_op_str);
        }
        else
        {

        }

    }
    if (!this->input_req_num->text().isEmpty())
    {
        std::wstring req_num_wstr = this->input_req_num->text().toStdWString();
        std::string req_num_str(req_num_wstr.begin(), req_num_wstr.end());
        bool is_converted = str2int(req_num_str, this->req_num);
        if (!is_converted)
        {
            *this->output_op_str = "Invalid request num";
            this->output_op->append(*this->output_op_str);
        }
        else
        {

        }
    }
}

void Ui_MainWindow::start_thread()
{
    if (this->_worker_thread_tcp->isRunning() || this->_worker_thread_rtu->isRunning())
    {
        this->update_output_op("Progress running, please stop current thread.");
        return;
    }

    else if (this->prot == 0)
    {
        _worker_thread_rtu->start();
    }
    else if (this->prot == 1)
    {
        _worker_thread_tcp->start();
    }
    else
    {
        this->update_output_op("Invalid mode");
    }
//    if (this->_worker_thread_tcp->isRunning() || this->thread_mode_1->isRunning())
//    {
//        return;
//    }
//    if (this->ctx)
//    {
//        if (!this->thread_break)
//        {
//            this->thread_break = true;
//            if (this->_worker_thread_tcp->isRunning())
//                this->_worker_thread_tcp->quit();
//            if (this->thread_mode_1->isRunning())
//                this->thread_mode_1->quit();
//            this->thread_break = true;
//        }
//        this->thread_break = false;
//
//        if (this->mode == 0)
//        {
//            _worker_thread_tcp->start();
//            *this->output_op_str = "Thread mode 0 start";
//            this->output_op->append(*this->output_op_str);
//        }
//        if (this->mode == 1)
//        {
//            thread_mode_1->start();
//            *this->output_op_str = "Thread mode 1 start";
//            this->output_op->append(*this->output_op_str);
//        }
//    }
//    else
//    {
//        *this->output_op_str = "No connection, start failed.";
//        this->output_op->append(*this->output_op_str);
//    }

}

void Ui_MainWindow::stop_thread()
{
    this->thread_break = true;
//    this->_worker_thread_rtu->exit();
    this->update_output_op("Thread stop");
}

void Ui_MainWindow::update_output_request(int32_t req)
{
    *this->output_request_str = std::to_string(req).c_str();
    this->output_request->setText(*this->output_request_str);
}

void Ui_MainWindow::update_output_xyzt(int32_t ax, int32_t ay, int32_t az, int32_t t)
{
    *this->output_ax_str = std::to_string(ax).c_str();
    this->output_ax->setText(*this->output_ax_str);
    *this->output_ay_str = std::to_string(ay).c_str();
    this->output_ay->setText(*this->output_ay_str);
    *this->output_az_str = std::to_string(az).c_str();
    this->output_az->setText(*this->output_az_str);
    *this->output_t_str = std::to_string(t).c_str();
    this->output_t->setText(*this->output_t_str);
}

void Ui_MainWindow::update_output_op(const std::string &str)
{
    *this->output_op_str = str.c_str();
    this->output_op->append(*this->output_op_str);
}

void Ui_MainWindow::update_led_color(int c)
{
    if (c == 0)
    {
        label_led->setStyleSheet("QLabel { background-color : red; }");
    }
    if (c == 1)
    {
        label_led->setStyleSheet("QLabel { background-color : green; }");
    }
}

void Ui_MainWindow::update_connection_state(bool s)
{
    if (s)
    {
        *this->label_status_str = "Connected";
        this->label_state->setText(*this->label_status_str);
    }
    else
    {
        *this->label_status_str = "Disconnected";
        this->label_state->setText(*this->label_status_str);
    }
}

int32_t extract_long_int(const uint8_t *q)
{
    ////  extract long int data(uint32_t) from q (or q+x with offset x)

    return static_cast<int32_t>((q[0] << 24) | (q[1] << 16) | (q[2] << 8) | q[3]);
}

void extract_xyzt(const uint8_t *q, int32_t &ax, int32_t &ay, int32_t &az, int32_t &T)
{
    ax = static_cast<int32_t>((q[0] << 24) | (q[1] << 16) | (q[2] << 8) | q[3]);
    ay = static_cast<int32_t>((q[4] << 24) | (q[5] << 16) | (q[6] << 8) | q[7]);
    az = static_cast<int32_t>((q[8] << 24) | (q[9] << 16) | (q[10] << 8) | q[11]);
    T = static_cast<int32_t>((q[12] << 24) | (q[13] << 16) | (q[14] << 8) | q[15]);
}

void extract_xyzt_tcp(const uint8_t *q, int32_t &ax, int32_t &ay, int32_t &az, int32_t &T)
{
    extract_xyzt(q + 8, ax, ay, az, T);
}

void extract_xyzt_rtu(const uint8_t *q, int32_t &ax, int32_t &ay, int32_t &az, int32_t &T)
{
    extract_xyzt(q + 3, ax, ay, az, T);
}


void zero_mapping(modbus_mapping_t *mb_mapping, int zero_len)
{
    for (int i = 0; i < zero_len; ++i)
    {
        mb_mapping->tab_registers[i] = 0;
    }
}

void edit_mapping(modbus_mapping_t *mb_mapping, int req_add, int req_num)
{
    //// reply data for request
    mb_mapping->tab_registers[0] = static_cast<int16_t>(req_add);
    mb_mapping->tab_registers[1] = static_cast<int16_t>(req_num);
}


void Worker_Thread_RTU::run()
{


    this->ctx = modbus_new_rtu("COM1", 9600, 'N', 8, 1);
//    modbus_set_debug(this->ctx, TRUE);
    int set_serial_mode = modbus_rtu_set_serial_mode(ctx, MODBUS_RTU_RS485);


    emit
    this->update_output_op("Initialized RTU: RS485");
    int mc = modbus_connect(this->ctx);

    modbus_set_slave(this->ctx, 1);
    emit
    this->update_output_op("Slave number set to 1;");

    this->mb_mapping = modbus_mapping_new(100, 100, 100, 100);

    uint8_t query[MODBUS_RTU_MAX_ADU_LENGTH];
    int32_t ax, ay, az, T;
    while (!*thread_break)
    {

        while (true)
        {
            int rc = modbus_receive(ctx, query);
            zero_mapping(this->mb_mapping, 12);
            if (rc > 0 && *this->p_mode == 0)
            {
                emit this->update_led_color(1);
                emit this->update_connection_state(true);
                //// filter received data of specific length (uint8_t), set 12 while tested in Modbus Poll
                if (rc == 21)
                {
                    if (query[0] == 0xF1 && query[1] == 0x03)
                    {
                        extract_xyzt_rtu(query, ax, ay, az, T);
                        // test data to reply
                        //                        mb_mapping->tab_registers[0] = 0xFAFA;
                        //                        mb_mapping->tab_registers[1] = 0xFAFA;
                        modbus_reply(ctx, query, rc, mb_mapping);
                        //// update ax, ay, az, T in ui main window
                        emit this->update_output_xyzt(ax, ay, az, T);
                    }
                    else
                    {
                        modbus_reply(ctx, query, rc, mb_mapping);
                    }
                }
                else if (rc == 12)
                {
                    //// debug on modbus poll
                    extract_xyzt(query, ax, ay, az, T);
                    // test data to reply
                    mb_mapping->tab_registers[0] = 0xFAFA;
                    mb_mapping->tab_registers[1] = 0xFAFA;
                    modbus_reply(ctx, query, rc, mb_mapping);
                    //// update ax, ay, az, T in ui main window
                    emit this->update_output_xyzt(ax, ay, az, T);
                }
                else
                {
                    //// rc
                    modbus_reply(ctx, query, rc, mb_mapping);
                }

            }
            else if (rc > 0 && rc != 8 && *this->p_mode == 1)
            {
                emit this->update_led_color(1);
                emit this->update_connection_state(true);
                edit_mapping(this->mb_mapping, *this->p_req_add, *this->p_req_num);
                modbus_reply(this->ctx, query, rc, this->mb_mapping);
                //// query + x : begin address of extracted data
//                emit this->update_output_request(extract_long_int(query + 3));
            }
            else if (rc == 8 && *this->p_mode == 1)
            {
                emit this->update_led_color(1);
                emit this->update_connection_state(true);
                edit_mapping(this->mb_mapping, *this->p_req_add, *this->p_req_num);
                modbus_reply(this->ctx, query, rc, this->mb_mapping);
                //// query + x : begin address of extracted data
                emit this->update_output_request(extract_long_int(query + 3));
            }
            else if (rc == -1)
            {
                emit this->update_led_color(0);
                emit this->update_connection_state(false);
                modbus_reply(this->ctx, query, rc, this->mb_mapping);
                if (errno == ETIMEDOUT)
                {
                    emit this->update_led_color(0);
                    emit this->update_connection_state(false);
                    continue;
                }
                else if (errno == ECONNRESET)
                {
                    emit this->update_led_color(0);
                    emit this->update_connection_state(false);
                }
                else
                {
                    emit this->update_led_color(0);
                    emit this->update_connection_state(false);
                }
            }
            if (*thread_break)
            {
                modbus_mapping_free(this->mb_mapping);
                modbus_close(this->ctx);
                modbus_free(this->ctx);
                this->mb_mapping = nullptr;
                this->ctx = nullptr;
                emit this->update_led_color(0);
                emit this->update_connection_state(false);
                emit this->update_output_op("Thread RTU stopped;");
                break;
            }
        }
    }
}


void Worker_Thread_TCP::run()
{

    this->ctx = modbus_new_tcp("127.0.0.1", 485);
//    modbus_set_debug(this->ctx, TRUE);
    emit this->update_output_op("Initialized TCP: 127.0.0.1 -p 485");

    modbus_set_slave(this->ctx, 1);
    emit this->update_output_op("Slave number set to 1;");
    if (this->server_socket == -1)
    {
        server_socket = modbus_tcp_listen(ctx, 1);
    }

    emit this->update_output_op("Start listening;");
    this->mb_mapping = modbus_mapping_new(100, 100, 100, 100);
//    modbus_set_response_timeout(ctx, 5, 0);

    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
    int32_t ax, ay, az, T;
    while (!*thread_break)
    {
        int acp = modbus_tcp_accept(ctx, &server_socket);
        emit this->update_led_color(1);
        emit this->update_connection_state(true);
        emit this->update_output_op("Connected;");
        while (true)
        {
            int rc = -1;
            rc = modbus_receive(ctx, query);
            zero_mapping(this->mb_mapping, 5);
            if (rc > 0 && *this->p_mode == 0)
            {
                emit this->update_led_color(1);
                emit this->update_connection_state(true);
                //// filter received data of specific length (uint8_t), set 12 while tested in Modbus Poll
                if (rc == 24)
                {
                    if (true)
                    {
                        extract_xyzt_tcp(query, ax, ay, az, T);
                        // test data to reply
                        // mb_mapping->tab_registers[0] = 0x0000;
                        // mb_mapping->tab_registers[1] = 0x0000;
                        modbus_reply(ctx, query, rc, mb_mapping);
                        //// update ax, ay, az, T in ui main window
                        emit this->update_output_xyzt(ax, ay, az, T);
                    }
                    else
                    {
                        modbus_reply(ctx, query, rc, mb_mapping);
                    }
                }
                else if (rc == 20)
                {
                    extract_xyzt(query + 3, ax, ay, az, T);
                    //// test data to reply
                    //                        mb_mapping->tab_registers[0] = 0xFAFA;
                    //                        mb_mapping->tab_registers[1] = 0xFAFA;
                    modbus_reply(ctx, query, rc, mb_mapping);
                    //// update ax, ay, az, T in ui main window
                    emit this->update_output_xyzt(ax, ay, az, T);
                }
                else if (rc == 8)
                {
                    edit_mapping(this->mb_mapping, *this->p_req_add, *this->p_req_num);
                    modbus_reply(this->ctx, query, rc, this->mb_mapping);
                    //// query + x : begin address of extracted data
                    emit this->update_output_request(extract_long_int(query + 3));
                }
                else if (rc == 12)
                {
                    //// debug on modbus poll
                    extract_xyzt(query, ax, ay, az, T);
                    // test data to reply
//                    mb_mapping->tab_registers[0] = 0xFAFA;
//                    mb_mapping->tab_registers[1] = 0xFAFA;
                    modbus_reply(ctx, query, rc, mb_mapping);
                    //// update ax, ay, az, T in ui main window
//                    emit this->update_output_xyzt(ax, ay, az, T);
                }
                else
                {
                    //// rc
                    modbus_reply(ctx, query, rc, mb_mapping);
                }

            }
            else if (rc > 0 && rc != 12 && *this->p_mode == 1)
            {
                emit this->update_led_color(1);
                emit this->update_connection_state(true);
                edit_mapping(this->mb_mapping, *this->p_req_add, *this->p_req_num);
                modbus_reply(this->ctx, query, rc, this->mb_mapping);
                //// query + x : begin address of extracted data
//                emit this->update_output_request(extract_long_int(query + 3));
            }
            else if (rc == 12 && *this->p_mode == 1)
            {
                emit this->update_led_color(1);
                emit this->update_connection_state(true);
                edit_mapping(this->mb_mapping, *this->p_req_add, *this->p_req_num);
                modbus_reply(this->ctx, query, rc, this->mb_mapping);
                //// query + x : begin address of extracted data
                emit this->update_output_request(extract_long_int(query + 8));
            }
            else if (rc == -1)
            {
                if (errno == ETIMEDOUT)
                {
                    emit this->update_led_color(0);
                    emit this->update_connection_state(false);
                    continue;
                }
                else if (errno == ECONNRESET)
                {
                    emit this->update_led_color(0);
                    emit this->update_connection_state(false);
                    emit this->update_output_op("Connection reset;");
                    emit this->update_output_op("Waiting for new connection...");
                    break;
                }
                else
                {
                    emit this->update_led_color(0);
                    emit this->update_connection_state(false);
                    emit this->update_output_op("Connection closed or error occurred;");
                    emit this->update_output_op("Waiting for new connection...");
                    break;
                }
            }
            if (*thread_break)
            {
                modbus_mapping_free(this->mb_mapping);
                modbus_close(this->ctx);
                modbus_free(this->ctx);
                this->mb_mapping = nullptr;
                this->ctx = nullptr;
                emit this->update_led_color(0);
                emit this->update_connection_state(false);
                emit this->update_output_op("Thread TCP stopped;");
                break;
            }
        }
    }
}

