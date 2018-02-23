#ifndef __STEPPER_TESTER_H__
#define __STEPPER_TESTER_H__


void handler_btn_connect_state_set();
void handler_btn_enable_state_set();
void handler_btn_spindle_state_set();
void handler_mX_step_left();
void handler_mX_step_right();
void handler_mY_step_left();
void handler_mY_step_right();
void handler_mZ_step_left();
void handler_mZ_step_right();
void handler_mC_step_left();
void handler_mC_step_right();
void handler_mD_step_left();
void handler_mD_step_right();
void handler_mX_rotate_right();
void handler_mX_rotate_left();
void handler_mX_stop();
void handler_mY_rotate_right();
void handler_mY_rotate_left();
void handler_mY_stop();
void handler_mZ_rotate_right();
void handler_mZ_rotate_left();
void handler_mZ_stop();
void handler_mC_rotate_right();
void handler_mC_rotate_left();
void handler_mC_stop();
void handler_mD_rotate_right();
void handler_mD_rotate_left();
void handler_mD_stop();
void handler_pps_changed(GtkRange *range, gpointer user_data);
void handler_parport_addr_changed(GtkComboBox *widget, gpointer user_data);
void handler_mainwin_destroy();




#endif // __STEPPER_TESTER_H__
