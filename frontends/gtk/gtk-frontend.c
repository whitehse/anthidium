#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <gtk/gtk.h>

GMainLoop       *loop;
GtkTextView     *text_view;
int             sockfd;

void on_window_destroy (GtkObject *object, gpointer user_data) {
    g_main_loop_quit(loop);
}

gboolean timeout_callback(gpointer data) {
    static int i = 0;
    
    i++;
    g_print("timeout_callback called %d times\n", i);
    if (10 == i)
    {
        g_main_loop_quit(loop);
        return FALSE;
    }

    return TRUE;
}

/*
(gtk-frontend:22921): Gtk-CRITICAL **: IA__gtk_text_buffer_get_end_iter: assertion `GTK_IS_TEXT_BUFFER (buffer)' failed

(gtk-frontend:22921): Gtk-CRITICAL **: IA__gtk_text_buffer_insert: assertion `GTK_IS_TEXT_BUFFER (buffer)' failed

*/

gboolean sock_receive_cb(GIOChannel *source, GIOCondition condition, gpointer data) {
    g_print("sock_receive_cb was called.\n");

    GtkTextBuffer *tbuffer;
    GtkTextIter ei;
    gchar buffer[256];
    int n;

    n = read(sockfd,buffer,255);
    tbuffer = gtk_text_view_get_buffer(text_view);
    gtk_text_buffer_get_end_iter(tbuffer, &ei);
    gtk_text_buffer_insert(tbuffer, &ei, &buffer, -1);
    return TRUE;
}

int main (int argc, char *argv[]) {
    GtkBuilder      *builder; 
    GtkWidget       *window;
    struct sockaddr_in servaddr;
    GIOChannel           *g_client_sock  = NULL;
    guint           id;
    int             ret;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof (struct sockaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port = htons(8080);
    //fcntl(sockfd, F_SETFL, O_NONBLOCK );
    int flag=1;
    ioctl(sockfd, FIONBIO, &flag);
    ret = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if (ret < 0) {
        g_print("Error opening socket: %s\n", strerror(errno));
    } else {
        g_print("sockfd=%d\n", sockfd);
    }

    loop = g_main_loop_new ( NULL , FALSE );

    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "gtk-frontend.xml", NULL);
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
    text_view = GTK_TEXT_VIEW (gtk_builder_get_object (builder, "textview"));
    gtk_builder_connect_signals (builder, NULL);

    g_object_unref (G_OBJECT (builder));
        
    gtk_widget_show (window);                

    g_timeout_add (1000 , timeout_callback , loop);
    g_client_sock = g_io_channel_unix_new(sockfd);
    id = g_io_add_watch(g_client_sock, G_IO_IN, sock_receive_cb, NULL);
    g_io_channel_unref (g_client_sock);
    g_main_loop_run (loop);
    g_main_loop_unref(loop);

    return 0;
}
