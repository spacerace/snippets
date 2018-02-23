#include <gtk/gtk.h>
 
void handler_button_ring1_plus();
void handler_button_ring2_plus();
void handler_button_mul_plus();
void handler_button_tolerance_plus();
void handler_button_ring1_minus();
void handler_button_ring2_minus();
void handler_button_mul_minus();
void handler_button_tolerance_minus();
void handler_cb_value_ring1_changed();
void handler_cb_value_ring2_changed();
void handler_cb_value_mul_changed();
void handler_cb_value_tolerance_changed();
void handler_cb_ring1_changed();
void handler_cb_ring2_changed();
void handler_cb_mul_changed();
void handler_cb_tolerance_changed();
 
int main(int argc, char *argv[]) {
	GtkBuilder      *builder; 
	GtkWidget       *window;
 
	gtk_init(&argc, &argv);
 
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "resistor.glade", NULL);
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	gtk_builder_connect_signals(builder, NULL);
 
	g_object_unref(builder);
 
	gtk_widget_show(window);                
	gtk_main();
 
	return 0;
}



void handler_button_ring1_plus() {
	
}
void handler_button_ring2_plus() {
	
}
void handler_button_mul_plus() {
	
}
void handler_button_tolerance_plus() {
	
}
void handler_button_ring1_minus() {
	
}
void handler_button_ring2_minus() {
	
}
void handler_button_mul_minus() {
	
}
void handler_button_tolerance_minus() {
	
}

void handler_window_main_destroy() {
	gtk_main_quit();	
}
