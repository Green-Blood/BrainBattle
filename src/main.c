#include <gtk/gtk.h>
#include <stdlib.h>
#include <gdk/gdkkeysyms.h>
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>


    //Take values    
    GtkWidget   *g_lb_question;
    GtkBuilder  *builder; 
    GtkWidget   *window;
    GtkWidget   *login;
    
    //Buttons
    GtkButton *g_bt_answer3;
    GtkButton *g_bt_answer1;
    GtkButton *g_bt_answer2;
    GtkButton *g_bt_answer4;

    //Take Account registration values
    GtkEntry *g_new_name;
    GtkEntry *g_new_password;    
    GtkLabel *g_new_id;
    GtkLabel *g_empty_field1;
    GtkLabel *g_empty_field2;
    

    //Take Account login values
    GtkEntry *g_log_name;
    GtkEntry *g_log_password; 
    GtkLabel *g_log_name_emptyfield;
    GtkLabel *g_log_password_emptyfield;

    //Error messages
    GtkMessageDialog *invalid_entry;
   
    

    //Sql setup
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    //SQL Connect
    static char *host = "localhost" ;
    static char *user = "user";
    static char *pass = "asdfasdf";
    static char *dbname = "ClashOfMinds";

    unsigned int port = 3306;
    static char *unix_socket = NULL;
    unsigned int flag = 0;

    
int main(int argc, char *argv[])
{
    conn = mysql_init(NULL);

    if(!(mysql_real_connect(conn,host,user,pass,dbname, port, unix_socket, flag)))
    {
        fprintf(stderr, "Error: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
    }
    //Gtk setup 
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    login = GTK_WIDGET(gtk_builder_get_object(builder, "window_log"));
    gtk_builder_connect_signals(builder, NULL);

    //Building registration entries
    g_new_name = GTK_ENTRY(gtk_builder_get_object(builder, "entry_name1"));
    g_new_password = GTK_ENTRY(gtk_builder_get_object(builder,"entry_pass1"));
    g_new_id = GTK_LABEL(gtk_builder_get_object(builder,"lb_new_id"));
    g_empty_field1 = GTK_LABEL(gtk_builder_get_object(builder, "lb_emptyfield1"));
    g_empty_field2 = GTK_LABEL(gtk_builder_get_object(builder, "lb_emptyfield2"));
    
    //Building login entries
    g_log_name = GTK_ENTRY(gtk_builder_get_object(builder, "entry_name"));
    g_log_password = GTK_ENTRY(gtk_builder_get_object(builder,"entry_pass"));   
    g_log_name_emptyfield = GTK_LABEL(gtk_builder_get_object(builder, "lb_log_emptyfield"));
    g_log_password_emptyfield = GTK_LABEL(gtk_builder_get_object(builder, "lb_log_emptyfield1"));
   
    //Building error dialogs
    invalid_entry = GTK_WIDGET(gtk_builder_get_object(builder, "msg_invalidentry"));
    
    g_object_unref(builder);

    gtk_widget_show(login);                
    gtk_main();
 
    return 0;
}

// called when buttons is clicked

void on_btn_create_clicked()
{
    
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
    //Build the game window
    GtkWidget       *game;
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    
    game = GTK_WIDGET(gtk_builder_get_object(builder, "window_game"));        
    gtk_builder_connect_signals(builder, NULL);
 
    //Get the objects for actual game 
    g_lb_question = GTK_WIDGET(gtk_builder_get_object(builder, "lb_question"));
    g_bt_answer1 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_answer1"));
    g_bt_answer2 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_answer2"));
    g_bt_answer3 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_answer3"));
    g_bt_answer4 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_answer4"));

    g_object_unref(builder);
    gtk_widget_show(game);
    gtk_widget_hide(window);
    gtk_main();

   

    
    // int num_fields = mysql_num_fields(result)
    // while(row)
    // {
        
    //     for(int i = 0; i < num_fields; i++)
    //     {
            
    //     }
        
    // }
    

    


}



//Login of player 
G_MODULE_EXPORT void on_btn_login_clicked()
{
    //Set empty field to empty (Maybe illogical, but actually it has logic)))
    gtk_label_set_text(g_log_name_emptyfield, " ");
    gtk_label_set_text(g_log_password_emptyfield, " ");
    
    //Gtk setup   
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);    
 
    char *name = gtk_entry_get_text(g_log_name);
    char *password = gtk_entry_get_text(g_log_password);
    char mysqlname[1024];
    char mysqlpass[1024];
    int flag = 0;
    
    //Check if the name field is empty or not
    if (!strcmp("", name)){
        gtk_label_set_text(g_log_name_emptyfield, "This field can't be empty!");
        
        flag = 1;
    }
    //Check if the password field is empty or not
    if (!strcmp("", password)){
        gtk_label_set_text(g_log_password_emptyfield, "This field can't be empty!");
        flag = 1;
    }
    //Write sql code into an variable and send the query to find the names
    snprintf(mysqlname, 1024,"SELECT name FROM users WHERE name = '%s'",  name);     
    if (mysql_query(conn, mysqlname))
    {
            fprintf(stderr, "%s\n", mysql_error(conn));            
            gtk_label_set_text(g_log_name_emptyfield, "Name is incorrect!");
            flag = 1;            
    }   
    //Store result and add it to the row   
    res = mysql_store_result(conn);  
    row = mysql_fetch_row(res);
    //Check if the result is correct or not
    if (row == NULL )
    {                    
            gtk_label_set_text(g_log_name_emptyfield, "Name is incorrect!");
            flag = 1;      
    }
    //free the result
    mysql_free_result(res);

    //Write sql code into an variable and send the query to find the password
    snprintf(mysqlpass, 1024,"SELECT password FROM users WHERE password = '%s'",  password);     
    if (mysql_query(conn, mysqlpass))
    {
            fprintf(stderr, "%s\n", mysql_error(conn));            
            gtk_label_set_text(g_log_password_emptyfield, "Password is incorrect!");
            flag = 1;            
    }   
    //Store result and add it to the row   
    res = mysql_store_result(conn);  
    row = mysql_fetch_row(res);
    //Check if the result is correct or not
    if (row == NULL )
    {                    
            gtk_label_set_text(g_log_password_emptyfield, "Password is incorrect!");
            flag = 1;      
    }
    //free the result
    mysql_free_result(res);

    if (flag == 0)
    {    
        //load game intro window
        g_object_unref(builder);

        gtk_widget_show(window);       
        gtk_widget_hide(login);
        gtk_main();        
        mysql_close(conn);
    }
    
}
//Registration of new player
G_MODULE_EXPORT void on_btn_register_clicked()
{
    gtk_label_set_text(g_new_id, " ");
    gtk_label_set_text(g_empty_field1, " ");
    gtk_label_set_text(g_empty_field2, " ");
        
    char *name = gtk_entry_get_text(g_new_name);
    char *password = gtk_entry_get_text(g_new_password);    
    char statement[1024];

    int flag = 0;
    if (!strcmp("", name)){
        gtk_label_set_text(g_empty_field1, "This field can't be empty!");
        // gtk_dialog_run(invalid_entry);
        flag = 1;
    }
    if (!strcmp("", password)){
        gtk_label_set_text(g_empty_field2, "This field can't be empty!");
        flag = 1;
    }  

    if (flag == 0)
    {
        //sending insert query
        snprintf(statement, 1024,"INSERT INTO users (name, password) VALUES('%s','%s')", name, password);
        if (mysql_query(conn, statement))
        {            
            gtk_label_set_text(g_new_id, "That name already exists!");
            flag == 1;            
        }           
        else
        {
            gtk_label_set_text(g_new_id, "Succesfull Registration" );
        }
        res = mysql_use_result(conn);
        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void on_btn_close_invalid_entry_clicked()
{
    
    gtk_widget_hide(invalid_entry);
}



void on_bt_answer1_clicked()
{
    gtk_label_set_text(GTK_LABEL(g_lb_question), "Q1");
}
void on_bt_answer2_clicked()
{
     //Write sql code into an variable and send the query to find the password   
    if (mysql_query(conn, "SELECT * FROM `questions` LEFT JOIN  `answer` on questions.id = parent_question  " ))
    {
            fprintf(stderr, "%s\n", mysql_error(conn));                       
    }   
    //Store result and add it to the row   
    res = mysql_store_result(conn);  
    
    //Check if the result is correct or not
    if (res == NULL )
    {                    
            gtk_widget_show(invalid_entry);
                 
    }
    //Create Mysql row
    MYSQL_ROW row;
    //create random number and counter      
    int rand_num = rand() % mysql_num_rows(res);
    int i=0;
    while(row = mysql_fetch_row(res))
    {
        //counter is going up everytime when loop is going, so if random number is equals to counter in will show this question
        i++;       
        if(i == rand_num)
        {
            gtk_label_set_text(GTK_LABEL(g_lb_question), row[1]);              
            gtk_button_set_label(g_bt_answer3, row[3]);
            gtk_button_set_label(g_bt_answer1, row[3]);
            gtk_button_set_label(g_bt_answer4, row[3]);
            gtk_button_set_label(g_bt_answer2, row[3]);


        }   
    }
    //free the result
    mysql_free_result(res);  
    
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

