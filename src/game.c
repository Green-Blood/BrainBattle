#include <gtk/gtk.h>
#include <stdlib.h>


 GtkWidget *g_lb_question;


void on_btn_join_clicked()
{
    GtkBuilder      *builder; 
    GtkWidget       *game;
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);

    game = GTK_WIDGET(gtk_builder_get_object(builder, "window_game"));
    gtk_builder_connect_signals(builder, NULL);

    g_lb_question = GTK_WIDGET(gtk_builder_get_object(builder, "lb_question"));
    g_object_unref(builder);
    
    gtk_widget_show(game);
    gtk_main();
    
    

    return 0;
}

// called when button is clicked

void on_btn_ans1_clicked()
{
    gtk_label_set_text(GTK_LABEL(g_lb_hello), "Question1");
}


// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

