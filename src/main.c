#include <gtk/gtk.h>
#include <stdlib.h>
#include <gdk/gdkkeysyms.h>

    GtkWidget *g_lb_hello;
    GtkWidget *g_lb_count;
    





int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    
 
    //get pointers 
    g_lb_hello = GTK_WIDGET(gtk_builder_get_object(builder, "lb_hello"));
    g_lb_count = GTK_WIDGET(gtk_builder_get_object(builder, "lb_count"));
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}

// called when buttons is clicked

void on_btn_create_clicked()
{
    static unsigned int count = 0;
    char str_count[30] = {0};

    gtk_label_set_text(GTK_LABEL(g_lb_hello), "Zdraste");
    count++;
    sprintf(str_count, "%d", count);
    gtk_label_set_text(GTK_LABEL(g_lb_count), str_count);
} 
void help_about(GtkWidget *widget)
{
    gtk_dialog_run(GTK_DIALOG(widget));
    gtk_widget_hide(widget);
}

void on_btn_exit_clicked()
{
    gtk_main_quit();
}

void on_btn_join_clicked()
{
    
    GtkBuilder      *builder; 
    GtkWidget       *game;
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    
    game = GTK_WIDGET(gtk_builder_get_object(builder, "window_game"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(game);
    gtk_main();
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

