#include <gtk/gtk.h>
#include <stdlib.h>
#include <gdk/gdkkeysyms.h>
#include <stdio.h>
#include <time.h>
#include <mysql/mysql.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


// #define IP "192.168.43.11"
#define IP "127.0.0.1"

    //Take values   
    GtkWidget   *g_lb_game_score;   //Score in the game
    GtkWidget   *g_lb_end_score;    //Last score    
    GtkBuilder  *builder;       //GTK Builder 
    GtkWidget   *window;        //Main menu window
    GtkWidget   *login;         //Login Window
    GtkWidget   *end_game;      //EndGame Widget    
    GtkWidget   *join_game;     //Joining the game 
    GtkWidget   *not_created;    //Not created window 
    //Game
        //Actual Game Window
        GtkWidget   *game;          
        //Question label
        GtkWidget   *g_lb_question;     
        //Buttons
        GtkButton *g_bt_answer3;
        GtkButton *g_bt_answer1;
        GtkButton *g_bt_answer2;
        GtkButton *g_bt_answer4;
        GtkWidget *g_lb_game_score;   //Score in the game
        GtkWidget *g_lb_game_rounds;   //Rounds in the game

    //Create game
    GtkWidget   *wait_game;
    GtkEntry    *g_creategame_name;
    GtkWidget   *g_creategame_empty;
    
    //LeaderBoard
    GtkWidget *lb_leader_name1;
    GtkWidget *lb_leader_name2;
    GtkWidget *lb_leader_name3;
    GtkWidget *lb_leader_name4;
    GtkWidget *lb_leader_name5;
    GtkWidget *lb_leader_score1;
    GtkWidget *lb_leader_score2;
    GtkWidget *lb_leader_score3;
    GtkWidget *lb_leader_score4;
    GtkWidget *lb_leader_score5;
    
    //Take Account registration values
    GtkEntry *g_new_name;
    GtkEntry *g_new_password;    
    GtkLabel *g_new_id;
    GtkLabel *g_empty_field1;
    GtkLabel *g_empty_field2;
    
    //Account login values
    GtkEntry *g_log_name;
    GtkEntry *g_log_password; 
    GtkLabel *g_log_name_emptyfield;
    GtkLabel *g_log_password_emptyfield;

    //Profile values
    GtkLabel *g_profile_name_emptyfield;
    GtkLabel *g_profile_score_emptyfield;
    GtkLabel *g_profile_id;
    
    //Error messages
    GtkMessageDialog *invalid_entry;
   
    //About dialog
    GtkAboutDialog *about;
    //Css values
    GtkCssProvider  *provider;
    GdkScreen       *screen;
    GdkDisplay      *display;
    
    //Static values
    //User values
    char static globalname[1024];    
    char  mysqlname[1024];
    char  mysqlpass[1024];
    //Game values
    int static rounds = 0;
    int static score = 0;
    int static question_number = 0;
    
    
    //Creating game values
    char static game_name[1024];

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

    // Client side C program to demonstrate Socket programming
    struct sockaddr_in client_address, serv_addr;
    int client_socket = 0, client_valread;

    char buffer[1024];
    int valread;
    //Client commands
    const char *wait_msg = "wait_client";
	const char *start_msg = "start_game";
	const char *end_msg = "end_game";
	const char *close_msg = "close_msg";
	const char *join_msg = "join_game";
	const char *create_msg = "create_game";
	const char *finish_msg = "finish_game";
	const char *send_score = "game_score";
	const char *game_not_created = "game_not_created";

    void join();
    void splitStringToArray(char buf[], char* array[]);
    void connectToSocket();
    
    #define PORT 8888
    
int main(int argc, char *argv[])
{
   // srand(time(0));
    //Mysql initialization
    conn = mysql_init(NULL);
    //Mysql Connection
    if(!(mysql_real_connect(conn,host,user,pass,dbname, port, unix_socket, flag)))
    {
        fprintf(stderr, "Error: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
    }

    connectToSocket();

    //Gtk setup 
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    login = GTK_WIDGET(gtk_builder_get_object(builder, "window_log"));
    gtk_builder_connect_signals(builder, NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);  
    wait_game = GTK_WIDGET(gtk_builder_get_object(builder, "window_create_game"));
    gtk_builder_connect_signals(builder, NULL);  
    join_game = GTK_WIDGET(gtk_builder_get_object(builder, "window_join_game"));
    gtk_builder_connect_signals(builder, NULL); 
    end_game = GTK_WIDGET(gtk_builder_get_object(builder, "window_endgame"));
    gtk_builder_connect_signals(builder, NULL);
    //Building not created game
    not_created = GTK_WIDGET(gtk_builder_get_object(builder, "window_notcreated"));
    gtk_builder_connect_signals(builder, NULL);


    about = GTK_WIDGET(gtk_builder_get_object(builder, "about"));
    gtk_builder_connect_signals(builder, NULL);

    //Building registration entries
    g_new_name = GTK_ENTRY(gtk_builder_get_object(builder, "entry_name1"));
    g_new_password = GTK_ENTRY(gtk_builder_get_object(builder,"entry_pass1"));
    g_new_id = GTK_LABEL(gtk_builder_get_object(builder,"lb_new_id"));
    g_empty_field1 = GTK_LABEL(gtk_builder_get_object(builder, "lb_emptyfield1"));
    g_empty_field2 = GTK_LABEL(gtk_builder_get_object(builder, "lb_emptyfield2"));
    
    //Building create and join entries
    g_creategame_name = GTK_ENTRY(gtk_builder_get_object(builder, "entry_create"));
    g_creategame_empty = GTK_LABEL(gtk_builder_get_object(builder, "lb_create_emptyfield"));    

    //Building login entries
    g_log_name = GTK_ENTRY(gtk_builder_get_object(builder, "entry_name"));
    g_log_password = GTK_ENTRY(gtk_builder_get_object(builder,"entry_pass"));   
    g_log_name_emptyfield = GTK_LABEL(gtk_builder_get_object(builder, "lb_log_emptyfield"));
    g_log_password_emptyfield = GTK_LABEL(gtk_builder_get_object(builder, "lb_log_emptyfield1"));
    
    //Building Profile entries
    g_profile_name_emptyfield = GTK_LABEL(gtk_builder_get_object(builder, "lb_empty_profile_name"));
    g_profile_score_emptyfield = GTK_LABEL(gtk_builder_get_object(builder, "lb_empty_profile_score"));
    g_profile_id = GTK_LABEL(gtk_builder_get_object(builder, "lb_profile_id"));

    //EndGame
    g_lb_end_score = GTK_WIDGET(gtk_builder_get_object(builder, "lb_end_score"));

    //Building Leaderboard entries
    lb_leader_name1 = GTK_LABEL(gtk_builder_get_object(builder, "lb_leader_name1"));
    lb_leader_name2 = GTK_LABEL(gtk_builder_get_object(builder, "lb_leader_name2"));
    lb_leader_name3 = GTK_LABEL(gtk_builder_get_object(builder, "lb_leader_name3"));
    lb_leader_name4 = GTK_LABEL(gtk_builder_get_object(builder, "lb_leader_name4"));
    lb_leader_name5 = GTK_LABEL(gtk_builder_get_object(builder, "lb_leader_name5"));
    lb_leader_score1 = GTK_LABEL(gtk_builder_get_object(builder, "lb_leader_score1"));
    lb_leader_score2 = GTK_LABEL(gtk_builder_get_object(builder, "lb_leader_score2"));
    lb_leader_score3 = GTK_LABEL(gtk_builder_get_object(builder, "lb_leader_score3"));
    lb_leader_score4 = GTK_LABEL(gtk_builder_get_object(builder, "lb_leader_score4"));
    lb_leader_score5 = GTK_LABEL(gtk_builder_get_object(builder, "lb_leader_name1"));

    //Building error dialogs
    invalid_entry = GTK_WIDGET(gtk_builder_get_object(builder, "msg_invalidentry"));

    //stlyesheet connecting part
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider),"style.css",NULL);

    g_object_unref(builder);
    gtk_widget_show(login);                
    gtk_main(); 
    return 0;
}

//Login of player 
G_MODULE_EXPORT void on_btn_login_clicked()
{
    //Set empty field to empty (Maybe illogical, but actually it has logic)))
    gtk_label_set_text(g_log_name_emptyfield, " ");
    gtk_label_set_text(g_log_password_emptyfield, " ");
    
    char *name = gtk_entry_get_text(g_log_name);
    char *password = gtk_entry_get_text(g_log_password);
    
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
        snprintf(globalname, 1024,  name); 
        Login();
        mysql_close(conn);
        
    }   
}
void Login()
        {
            //load game intro window
            g_object_unref(builder);
            leaders(); // Show the leaderboard
            gtk_widget_show(window);       
            gtk_widget_hide(login);
            gtk_main();                    
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
// called when buttons is clicked
void on_btn_create_clicked()
{
    //send create_game msg
    send(client_socket, create_msg,strlen(create_msg), 0);

    while(1)
    {
        valread = read(client_socket, buffer, 1024);

        if(strncmp(buffer, wait_msg,11) == 0){
            //TODO: Open wait window
            gtk_widget_show(wait_game);
            // gtk_main();
            printf("%s\n", "waiting...");
              
        } else if(strncmp(buffer, start_msg,11) == 0){
            //TODO: START GAME
            build_game();
            choose_answer();
            gtk_widget_hide(window);
            gtk_widget_hide(wait_game);
            gtk_main();
            printf("%s\n", "started...");
            break;
        }
    }

    
} 

// void on_btn_creategame_clicked()
    // {
    
    //     char *wait_game_name = gtk_entry_get_text(g_creategame_name);
    //     char statement[1024];
    //     snprintf(statement, 1024,"INSERT INTO games (game_name) VALUES('%s')", wait_game_name);
    //     if (mysql_query(conn, statement))
    //     {            
    //         gtk_label_set_text(g_creategame_empty, "That game already exists!");
                      
    //     }           
    //     else
    //     {
    //         gtk_label_set_text(g_creategame_empty, "Succesfull created" );
    //     }
    //     res = mysql_use_result(conn);
    //     mysql_free_result(res);
    //     snprintf(game_name, 1024, wait_game_name); 

        

    // }
void help_about()
{
    gtk_dialog_run(GTK_DIALOG(about));
    
}

void on_btn_exit_clicked()
{
    gtk_main_quit();
    exit(1);
}

void leaders()
{
    if(mysql_query(conn,"SELECT * FROM users ORDER BY score DESC"))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));            
        }
    MYSQL_ROW row;
    //Store result and add it to the row   
    res = mysql_store_result(conn);  
    int i = 0;
    while(row = mysql_fetch_row(res))
    {
        i++;        
        if(i == 1)
        {
            gtk_label_set_text(GTK_LABEL(lb_leader_name1), row[1]);  
            gtk_label_set_text(GTK_LABEL(lb_leader_score1), row[3]);
        }
        if(i == 2)
        {
            gtk_label_set_text(GTK_LABEL(lb_leader_name2), row[1]);  
            gtk_label_set_text(GTK_LABEL(lb_leader_score2), row[3]);
        }
        if(i == 3)
        {
            gtk_label_set_text(GTK_LABEL(lb_leader_name3), row[1]);  
            gtk_label_set_text(GTK_LABEL(lb_leader_score3), row[3]);
        }
        if(i == 4)
        {
            gtk_label_set_text(GTK_LABEL(lb_leader_name4), row[1]);  
            gtk_label_set_text(GTK_LABEL(lb_leader_score4), row[3]);
        }
        if(i == 5)
        {
            gtk_label_set_text(GTK_LABEL(lb_leader_name5), row[1]);  
            gtk_label_set_text(GTK_LABEL(lb_leader_score5), row[3]);
        }    
    }
    //free the result
    mysql_free_result(res); 
}

void on_btn_leader_refresh_clicked()
{
    leaders();
}

void on_btn_join_clicked()
{   

    // gtk_widget_show(join_game);
    // gtk_main();
    // void on_box_game_name_changed()
    // {
           
    //     if(mysql_query(conn,"SELECT *  FROM games "))
    //     {
    //         fprintf(stderr, "%s\n", mysql_error(conn));
            
    //     }

    //     MYSQL_ROW row;
    //     //Store result and add it to the row   
    //     res = mysql_store_result(conn); 
    //     //free the result
    //     mysql_free_result(res); 
    // }   
    
    join();
    
    // build_game();
    // choose_answer();
    // gtk_widget_hide(window);
    // gtk_main();
}
void choose_answer()
{
    //Write sql code into an variable and send the query to find the password   
    if (mysql_query(conn, "SELECT * FROM `questions` " ))
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
    // 
    int i = 0;
    score = 0;
    while(row = mysql_fetch_row(res))
    {
        //counter is going up everytime when loop is going, so if random number is equals to counter it will show this question
             
        if(i == question_number)
        {
        
            gtk_label_set_text(GTK_LABEL(g_lb_question), row[1]);              
            

            int rand_but = rand() % 4;
            if(rand_but == 1)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but+3]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+4]);
            }
            else if(rand_but == 4)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but]);
                gtk_button_set_label(g_bt_answer1, row[rand_but-2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but-1]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+1]);
            }
            else if (rand_but == 3)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but]);
                gtk_button_set_label(g_bt_answer2, row[rand_but-1]);
            }
            else if (rand_but == 2)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1 ]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+3]);
            }        
        }
        i++; 
             
    }
    question_number++; 

    
    setScoreRounds();
    game_rounds();
    //free the result
    mysql_free_result(res);  
    gtk_widget_hide(window); 
}
void update_score()
{
    char updatescore[1024];
    snprintf(updatescore, 1024,"UPDATE `users` SET `score` = score + %d WHERE users.name = '%s'", score, globalname);
        if (mysql_query(conn, updatescore))
        {            
            mysql_errno(conn);         
        }           
        res = mysql_use_result(conn);
        mysql_free_result(res);
}
void build_game()
{
    //Build the game window
    
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    
    game = GTK_WIDGET(gtk_builder_get_object(builder, "window_game"));        
    gtk_builder_connect_signals(builder, NULL);

    //Get the objects for actual game 
    g_lb_question = GTK_WIDGET(gtk_builder_get_object(builder, "lb_question"));
    g_lb_game_score = GTK_WIDGET(gtk_builder_get_object(builder, "lb_game_score"));
    g_lb_game_rounds = GTK_WIDGET(gtk_builder_get_object(builder, "lb_game_rounds"));
    
    g_bt_answer1 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_answer1"));
    g_bt_answer2 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_answer2"));
    g_bt_answer3 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_answer3"));
    g_bt_answer4 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_answer4"));

    g_object_unref(builder);
    gtk_widget_show(game);
}
void setprofilename()
{
        char statement2[1024];
        snprintf(statement2, 1024,"SELECT id, name, score  FROM users WHERE name = '%s'", globalname);   
        if(mysql_query(conn,statement2))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));            
        }
        MYSQL_ROW row;
        //Store result and add it to the row   
        res = mysql_store_result(conn);  
         
        while(row = mysql_fetch_row(res))
        {
            gtk_label_set_text(GTK_LABEL(g_profile_id), row[0]);
            gtk_label_set_text(GTK_LABEL(g_profile_name_emptyfield), row[1]);  
            gtk_label_set_text(GTK_LABEL(g_profile_score_emptyfield), row[2]);  
        }
        //free the result
        mysql_free_result(res); 
}

G_MODULE_EXPORT void on_btn_profile_clicked()
{        
        setprofilename();      
}

G_MODULE_EXPORT void on_btn_close_invalid_entry_clicked()
{
    
    gtk_widget_hide(invalid_entry);
}

//Executes if first button clicked
void on_bt_answer1_clicked()
{
    //Write sql code into an variable and send the query to find the password   
    if (mysql_query(conn, "SELECT * FROM `questions`  " ))
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
    
    int i=0;

    int ans_choose = 0;
    
    while(row = mysql_fetch_row(res))
    {
           
        
            if(strcmp(gtk_button_get_label(g_bt_answer1), row[2]) == 0) 
            {
                score++;
            }
             
             
        //counter is going up everytime when loop is going, so if random number is equals to counter it will show this question
               
        if(i == question_number)
        {    
            
            int rand_but = rand() % 4;
            if(rand_but == 1)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but+3]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+4]);
            }
            else if(rand_but == 4)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but]);
                gtk_button_set_label(g_bt_answer1, row[rand_but-2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but-1]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+1]);
            }
            else if (rand_but == 3)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but]);
                gtk_button_set_label(g_bt_answer2, row[rand_but-1]);
            }
            else if (rand_but == 2)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1 ]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+3]);
            }
            gtk_label_set_text(GTK_LABEL(g_lb_question), row[1]);         
        }
        i++;     
    }
    question_number++;
    
    setScoreRounds();
    //free the result
    mysql_free_result(res);      
    game_rounds();
   
}
//Executes if second button clicked
void on_bt_answer2_clicked()
{    
    //Write sql code into an variable and send the query to find the password   
    if (mysql_query(conn, "SELECT * FROM `questions`  " ))
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
     
    int i=0;
    int ans_choose = 0;
    
    while(row = mysql_fetch_row(res))
    {
           
        
            if(strcmp(gtk_button_get_label(g_bt_answer2), row[2]) == 0) 
            {
                score++;
            }
             
        
        
        
        //counter is going up everytime when loop is going, so if random number is equals to counter it will show this question
               
        if(i == question_number)
        {        
            int rand_but = rand() % 4;
            if(rand_but == 1)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but+3]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+4]);
            }
            else if(rand_but == 4)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but]);
                gtk_button_set_label(g_bt_answer1, row[rand_but-2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but-1]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+1]);
            }
            else if (rand_but == 3)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but]);
                gtk_button_set_label(g_bt_answer2, row[rand_but-1]);
            }
            else if (rand_but == 2)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1 ]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+3]);
            }
            gtk_label_set_text(GTK_LABEL(g_lb_question), row[1]);         
        }
        i++;     
    }
    question_number++;
    
    setScoreRounds();
    //free the result
    mysql_free_result(res);  
    gtk_widget_hide(window);
    game_rounds();
   
}

//Executes when button 3 clicked
void on_bt_answer3_clicked()
{
    //Write sql code into an variable and send the query to find the password   
    if (mysql_query(conn, "SELECT * FROM `questions`  " ))
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
     
    int i=0;
    int ans_choose = 0;
    
    while(row = mysql_fetch_row(res))
    {
           
        
            if(strcmp(gtk_button_get_label(g_bt_answer3), row[2]) == 0) 
            {
                score++;
            }
             
        
        
        
        //counter is going up everytime when loop is going, so if random number is equals to counter it will show this question
               
        if(i == question_number)
        {        
            int rand_but = rand() % 4;
            if(rand_but == 1)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but+3]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+4]);
            }
            else if(rand_but == 4)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but]);
                gtk_button_set_label(g_bt_answer1, row[rand_but-2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but-1]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+1]);
            }
            else if (rand_but == 3)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but]);
                gtk_button_set_label(g_bt_answer2, row[rand_but-1]);
            }
            else if (rand_but == 2)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1 ]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+3]);
            }
            gtk_label_set_text(GTK_LABEL(g_lb_question), row[1]);         
        }
        i++;     
    }
    question_number++;
    
    setScoreRounds();
    //free the result
    mysql_free_result(res);  
    gtk_widget_hide(window);
    game_rounds();
   
}
//Executes when button4 clicked
void on_bt_answer4_clicked()
{
    //Write sql code into an variable and send the query to find the password   
    if (mysql_query(conn, "SELECT * FROM `questions`  " ))
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
     
    int i = 0;
    int ans_choose = 0;
    
    while(row = mysql_fetch_row(res))
    {
           
        
            if(strcmp(gtk_button_get_label(g_bt_answer4), row[2]) == 0) 
            {
                score++;
            }
             
        
        //counter is going up everytime when loop is going, so if random number is equals to counter it will show this question
               
        if(i == question_number)
        {
        
            int rand_but = rand() % 4;
            if(rand_but == 1)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but+3]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+4]);
            }
            else if(rand_but == 4)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but]);
                gtk_button_set_label(g_bt_answer1, row[rand_but-2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but-1]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+1]);
            }
            else if (rand_but == 3)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but]);
                gtk_button_set_label(g_bt_answer2, row[rand_but-1]);
            }
            else if (rand_but == 2)
            {
                gtk_button_set_label(g_bt_answer3, row[rand_but+1 ]);
                gtk_button_set_label(g_bt_answer1, row[rand_but+2]);
                gtk_button_set_label(g_bt_answer4, row[rand_but]);
                gtk_button_set_label(g_bt_answer2, row[rand_but+3]);
            } 
            gtk_label_set_text(GTK_LABEL(g_lb_question), row[1]);        
        }
        i++;     
    }
    question_number++;
    setScoreRounds();
    //free the result
    game_rounds();
    mysql_free_result(res);  
    gtk_widget_hide(window);     
}

//Counting of game;
void game_rounds()
{ 
    rounds += 1;
    if(rounds >= 22)
    {        
        update_score();        
        rounds = 0;        
        game_end(); 
        score = 0;     
    }
}
void setScoreRounds()
{
    char stringscore[20];    
    snprintf(stringscore, 20, "%d", score);
    gtk_label_set_text(g_lb_game_score, stringscore);
    char stringrounds[20];    
    snprintf(stringrounds, 20, "%d", rounds);
    gtk_label_set_text(g_lb_game_rounds, stringrounds);
}

void game_end()
{
    //End game window    
    char lastscore[20] ;    
    snprintf(lastscore, 20, "%d", score);
    gtk_label_set_text(g_lb_end_score, lastscore);      
    gtk_widget_show(end_game);
    gtk_widget_hide(game); 
    gtk_main();      
}


void on_btn_returnmain_clicked()
{
    Login();
}

void on_window_main_destroy()
{     
      
}

void connectToSocket(){
       
    printf("CREATING CLIENT SOCKET .....\n");
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return ;
    }
    printf("DEFINING SOCKET FAMILY, ADDRESS & PORT .....\n");
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    memset(buffer, 0, sizeof(buffer));

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, IP, &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return;
    }

    printf("CLIENT CONNECTING ON PORT 8080 TO COMMUNICATE WITH SERVER..\n");
    if (connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return;
    }
}

void join(){

    send(client_socket, join_msg, strlen(join_msg), 0);

    while(1)
    {
        
        valread = read( client_socket , buffer, 1024);

        if(strncmp(buffer, wait_msg,11) == 0){
            //TODO: Open wait window
            gtk_widget_show(wait_game); 
            printf("%s\n", "waiting...");
              
        } else if(strncmp(buffer, start_msg,11) == 0){
            //TODO: START GAME
            build_game();
            choose_answer();
            gtk_widget_hide(window);
            gtk_widget_hide(wait_game);
            gtk_main();
            printf("%s\n", "started...");
            break;
        } else if(strncmp(buffer, game_not_created,16) == 0){
            //TODO: Game is not created
            printf("%s\n", "game is not created...");
            break;
        }
        
    }
    
}

void splitStringToArray(char buf[], char* array[]){
    int i = 0;
    char *p = strtok (buf, "/");

    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, "/");
    }
    
}
