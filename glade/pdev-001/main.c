/* simple parport stepper card tester
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

#include <gtk/gtk.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

static void *thread_update_gui(void *thr_arg);
static void *thread_motor_control(void *thr_arg);

static int thread_update_gui_sleeping, thread_motor_sleeping;

void turn_connect_button_to_off();
void disconnect_from_lpt_port();
void disable_all_drivers();


int main(int argc, char *argv[]) {
	GtkBuilder      *builder; 
	GtkWidget       *window;
	pthread_t thread_ui;
	pthread_t thread_motor;
	thread_update_gui_sleeping = TRUE;
	thread_motor_sleeping = TRUE;
	int retval;
	

	retval = pthread_create(&thread_ui, NULL, thread_update_gui, NULL);
	if(retval != 0) {
		printf("can't start update gui thread...\n");
		exit(-1);
	} else {
		printf("update gui thread started, sleeping.\n");
	}

	retval = pthread_create(&thread_motor, NULL, thread_motor_control, NULL);
	if(retval != 0) {
		printf("can't start motor control thread...\n");
		exit(-1);
	} else {
		printf("motor control thread started, sleeping.\n");
	}
	
	
	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "stepper_tester.glade", NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	gtk_builder_connect_signals(builder, NULL);

	g_object_unref(builder);

	gtk_widget_show(window);
	gtk_main();

	return 0;
}

static void *thread_motor_control(void *thr_arg) {
	while(thread_motor_sleeping == TRUE);
	printf("motor control thread awake.\n");
	for(;;) {
		
	}
	return NULL;	
}

static void *thread_update_gui(void *thr_arg) {
	while(thread_update_gui_sleeping == TRUE);
	printf("update gui thread awake.\n");
	
	for(;;) {
		usleep(200000);	// wait 200ms		
	}
	return NULL;	
 }



void handler_btn_connect_state_set() {
	thread_update_gui_sleeping = FALSE;
	thread_motor_sleeping = FALSE;
	printf("button connect state set\n");	
}



void handler_pps_changed(GtkRange *range, gpointer user_data) {
// 	GtkWidget *label = user_data;
	
	guint pps = gtk_range_get_value(range);
	
	
	printf("pps changed to %d\n", pps);
}

void handler_parport_addr_changed(GtkComboBox *widget, gpointer user_data) {
	GtkComboBox *combo_box = widget;
	unsigned long addrul;
	unsigned int addr;
	
// 	if(gtk_combo_box_get_active(combo_box) != 0)

	gchar *parport_addr_str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box));
	addrul = strtoul(parport_addr_str, NULL, 16);
	addr = (unsigned int) addrul;
	g_free(parport_addr_str);	

	disconnect_from_lpt_port();

	printf("parport address changed to 0x%03x\n", addr);

}

void turn_connect_button_to_off() {
	
}

void disconnect_from_lpt_port() {
	// this function should be called when port is changed or anything else bad happens.
	// first it should disable the driver card, then close the parport connection
	
	disable_all_drivers();
	
	turn_connect_button_to_off();
	
	printf("disconnected from lpt port.\n");
	
	
}

void disable_all_drivers() {
	printf("disabling all motor drivers.\n");
	
	return;
	
}

// called when window is closed
void handler_mainwin_destroy() {
	disconnect_from_lpt_port();
	printf("\nquit\n");
	gtk_main_quit();
}

void handler_btn_enable_state_set() {
	printf("button enable state set\n");	
}

void handler_btn_spindle_state_set() {
	printf("button spindle state set\n");	
}


void handler_mX_step_left() {
	printf("motor X step left\n");
}
void handler_mX_step_right() {
	printf("motor X step right\n");
}

void handler_mY_step_left() {
	printf("motor Y step left\n");
}
void handler_mY_step_right() {
	printf("motor Y step right\n");
}

void handler_mZ_step_left() {
	printf("motor Z step left\n");
}
void handler_mZ_step_right() {
	printf("motor Z step right\n");
}

void handler_mC_step_left() {
	printf("motor C step left\n");
}
void handler_mC_step_right() {
	printf("motor C step right\n");
}

void handler_mD_step_left() {
	printf("motor D step left\n");
}
void handler_mD_step_right() {
	printf("motor D step right\n");
}




void handler_mX_rotate_right() {
	printf("motor X rotate right\n");
}
void handler_mX_rotate_left() {
	printf("motor X rotate left\n");
}
void handler_mX_stop() {
	printf("motor X rotate stop\n");
}

void handler_mY_rotate_right() {
	printf("motor Y rotate right\n");
}
void handler_mY_rotate_left() {
	printf("motor Y rotate left\n");
}
void handler_mY_stop() {
	printf("motor Y rotate stop\n");
}


void handler_mZ_rotate_right() {
	printf("motor Z rotate right\n");
}
void handler_mZ_rotate_left() {
	printf("motor Z rotate left\n");
}
void handler_mZ_stop() {
	printf("motor Z rotate stop\n");
}


void handler_mC_rotate_right() {
	printf("motor C rotate right\n");
}
void handler_mC_rotate_left() {
	printf("motor C rotate left\n");
}
void handler_mC_stop() {
	printf("motor C rotate stop\n");
}


void handler_mD_rotate_right() {
	printf("motor D rotate right\n");
}
void handler_mD_rotate_left() {
	printf("motor D rotate left\n");
}
void handler_mD_stop() {
	printf("motor D rotate stop\n");
}

