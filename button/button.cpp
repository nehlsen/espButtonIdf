/*
  * ESPRESSIF MIT License
  *
  * Copyright (c) 2017 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
  *
  * Permission is hereby granted for use on ESPRESSIF SYSTEMS products only, in which case,
  * it is free of charge, to any person obtaining a copy of this software and associated
  * documentation files (the "Software"), to deal in the Software without restriction, including
  * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
  * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
  * to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all copies or
  * substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  *
  */

#include <button.h>

Button::Button(gpio_num_t gpio_num, button_active_t active_level)
{
    m_btn_handle = iot_button_create(gpio_num, active_level);
}

Button::~Button()
{
    iot_button_delete(m_btn_handle);
    m_btn_handle = NULL;
}

esp_err_t Button::setEventCallback(button_cb_type_t type, button_cb cb, void* arg)
{
    return iot_button_set_evt_cb(m_btn_handle, type, cb, arg);
}

esp_err_t Button::setSerialCallback(button_cb cb, void* arg, TickType_t interval_tick, uint32_t start_after_sec)
{
    return iot_button_set_serial_cb(m_btn_handle, start_after_sec, interval_tick, cb, arg);
}

esp_err_t Button::addOnPressCallback(uint32_t press_sec, button_cb cb, void* arg)
{
    return iot_button_add_on_press_cb(m_btn_handle, press_sec, cb, arg);
}

esp_err_t Button::addOnReleaseCallback(uint32_t press_sec, button_cb cb, void* arg)
{
    return iot_button_add_on_release_cb(m_btn_handle, press_sec, cb, arg);
}

esp_err_t Button::removeCallback(button_cb_type_t type)
{
    return iot_button_rm_cb(m_btn_handle, type);
}
