//
//  main.c
//  project server
//
//  Created by Amir Mohammad on 11/18/1399 AP.
//

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "cJSON.h"
#include "cJSON.c"

#define PORT 8080
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define LISTEN_ERROR -1
#define message_limit 1000000
#define dir_server "/Users/AMF/Desktop/project with delete tweet part/server/"
#define dir_Resources "/Users/AMF/Desktop/project with delete tweet part/server/Resources/"
#define dir_Users "/Users/AMF/Desktop/project with delete tweet part/server/Resources/Users/"
#define dir_Tweets "/Users/AMF/Desktop/project with delete tweet part/server/Resources/Tweets/"

struct user_information {
    char username[21];
    char token[46];
} users_information[1000];

typedef struct sockaddr_in Sockaddr;
typedef int Socket;

int number_of_login_users = 0;
int number_of_sent_tweets = 0;

Socket start_listening( int port );
int run_server( Socket server_socket );

void delete_seenTweets( void );

void handle_requests( char request[], char response[] );
    int starts_with( const char *pre, const char *str );
    
    void signup_function( char request[], char response[] );
    
    void login_function( char request[], char response[] );
    void create_token( char token[], int token_length );
    
    void send_tweet_function( char request[], char response[] );
    int find_online_username( char online_username[], char token[] );
    
    void refresh_function( char request[], char response[] );
    int find_suitable_tweets_from_seenTweets( cJSON *array_pointer, int suitable_tweets[], int suitable_tweets_size, int seen_tweets[], int seen_tweets_size );
    void sort( int array[], int size );
    int change_duplicate_items_to_zero( int array[], int size );
    void delete_zero_items( int array[], int size, int number_of_duplicate_items );
    
    void like_function( char request[], char response[] );
    int count_digits( int number );
    void delete_suitable_tweets( cJSON *array_pointer, int array_size, int tweet_id );
    
    void comment_function( char request[], char response[] );
    
    void search_function( char request[], char response[] );
    
    void follow_function( char request[], char response[] );
    
    void unfollow_function( char request[], char response[] );
    
    void profile_function( char request[], char response[] );
    
    void set_bio_function( char request[], char response[] );
    
    void change_password_function( char request[], char response[] );
    
    void logout_function( char request[], char response[] );
    
    void delete_tweet_function( char request[], char response[] );
    void delete_suitable_index( cJSON *cJSON_array_pointer, int tweet_id );

int main( void ) {
    // insert code here...
    
    printf("\n");
    printf("\t░██╗░░░░░░░██╗███████╗██╗░░░░░░█████╗░░█████╗░███╗░░░███╗███████╗\n");
    printf("\t░██║░░██╗░░██║██╔════╝██║░░░░░██╔══██╗██╔══██╗████╗░████║██╔════╝\n");
    printf("\t░╚██╗████╗██╔╝█████╗░░██║░░░░░██║░░╚═╝██║░░██║██╔████╔██║█████╗░░\n");
    printf("\t░░████╔═████║░██╔══╝░░██║░░░░░██║░░██╗██║░░██║██║╚██╔╝██║██╔══╝░░\n");
    printf("\t░░╚██╔╝░╚██╔╝░███████╗███████╗╚█████╔╝╚█████╔╝██║░╚═╝░██║███████╗\n");
    printf("\t░░░╚═╝░░░╚═╝░░╚══════╝╚══════╝░╚════╝░░╚════╝░╚═╝░░░░░╚═╝╚══════╝\n");
    printf("\n");
    
    Socket server_socket = start_listening( PORT );
    if ( server_socket != INVALID_SOCKET ) {
        run_server( server_socket );
    }
    
    
    return 0;
}

Socket start_listening( int port ) {
    Socket server_socket; // for file descriptor
    // Creating Socket
    server_socket = socket( AF_INET, SOCK_STREAM, 0 );
    if ( server_socket == INVALID_SOCKET ) {
        printf("Socket Failed\n");
        return INVALID_SOCKET;
    }
    // making the port reusable.
    int enable = 1;
    if ( setsockopt( server_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int) ) < 0 )
        printf("setsockopt(SO_REUSEADDR) failed\n");

    Sockaddr server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; //Accept Anything
    server_addr.sin_port = htons(port);
    /*ADDR BINDING*/
    int bind_res = bind( server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr) );
    if ( bind_res == SOCKET_ERROR ) {
        printf("Bind Failed\n");
        return INVALID_SOCKET;
    }
    int listen_resp = listen( server_socket, SOMAXCONN ); // second arg is the number of requests that can stay in the queue.

    if ( listen_resp == LISTEN_ERROR ) {
        printf("Listen Failed\n");
        return INVALID_SOCKET;
    }
    printf("Server started to listen...\n");
    return server_socket;
}

int run_server( Socket server_socket ) {
    int len = sizeof(Sockaddr);
    Socket client_socket;
    Sockaddr client_addr;
    
    srand( (unsigned int)time( 0 ) );
    mkdir( dir_Resources, 0777 );
    mkdir( dir_Users, 0777 );
    mkdir( dir_Tweets, 0777 );
    if ( fopen( dir_Resources, "r" ) == NULL || fopen( dir_Users, "r" ) == NULL || fopen( dir_Tweets, "r" ) == NULL) {
        printf("Server Faces To A Problem In Creating Folders\nPlease Try Again\n");
        exit(0);
    }
    
    FILE *file_pointer;
    if ( ( file_pointer = fopen( dir_Resources"number_of_sent_tweets.txt", "r") ) == NULL ) {
        file_pointer = fopen( dir_Resources"number_of_sent_tweets.txt", "w");
        fprintf( file_pointer, "number of sent tweets: 0\n" );
    } else {
        fscanf( file_pointer, "number of sent tweets: %d\n", &number_of_sent_tweets );
    }
    fclose( file_pointer );
    
    delete_seenTweets();
    
    while ( ( client_socket = accept( server_socket, (struct sockaddr*)&client_addr, &len ) ) != 0 ) {
        int buffer_size = message_limit;
        char buffer[buffer_size];
        memset(buffer, 0, buffer_size);//filling all the buffer with value = 0 (emptying buffer)
        recv(client_socket, buffer, buffer_size - 1, 0);
        
        time_t t;
        t = time( NULL );
        struct tm tm;
        tm = *localtime( &t );
        tm.tm_year += 1900;
        tm.tm_mon += 1;
        
        printf("Info | %d/%02d/%02d %02d:%02d:%02d | Request received: %s", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, buffer );
        char response[message_limit];
        memset( response, 0, sizeof(response) );//filling all the response with value = 0 (emptying response)
        handle_requests( buffer, response );
        send( client_socket, response, strlen( response ), 0 );
        printf("Info | %d/%02d/%02d %02d:%02d:%02d | Response sent: %s\n\n", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, response );
        close( client_socket );
    }
    return 0;
}

void delete_seenTweets( void ) {
    struct dirent *dirnet_pointer;
    DIR *dir_pointer = opendir( dir_Users );
    
    int specifier;
    for ( specifier = 0; ( dirnet_pointer = readdir(dir_pointer) ) != NULL && specifier > 2; ++specifier ) {
        FILE *file_pointer;
        char file_direction[150] = { 0 };
        sprintf( file_direction, dir_Users"%s", dirnet_pointer -> d_name );
        file_pointer = fopen( file_direction, "r" );
        
        char *file_string = calloc( 10000000, sizeof(char) );
        fscanf( file_pointer, "%[^\n]", file_string );
        fclose( file_pointer );
        cJSON *root = cJSON_Parse( file_string );
        free( file_string );
        
        cJSON_DeleteItemFromObject( root, "seenTweets" );
        cJSON_AddArrayToObject( root, "seenTweets" );
    }
    
    closedir( dir_pointer );
}

void handle_requests( char request[], char response[] ) {
    if ( starts_with( "signup ", request ) ) {
        signup_function( request, response );
    } else if ( starts_with( "login ", request ) ) {
        login_function( request, response );
    } else if ( starts_with( "send tweet ", request ) ) {
        send_tweet_function( request, response );
    } else if ( starts_with( "refresh ", request ) ) {
        refresh_function( request, response );
    } else if ( starts_with( "like ", request ) ) {
        like_function( request, response );
    } else if ( starts_with( "comment ", request ) ) {
        comment_function( request, response );
    } else if ( starts_with( "search ", request ) ) {
        search_function( request, response );
    } else if ( starts_with( "follow ", request ) ) {
        follow_function( request, response );
    } else if ( starts_with( "unfollow ", request ) ) {
        unfollow_function( request, response );
    } else if ( starts_with( "profile ", request ) ) {
        profile_function( request, response );
    } else if ( starts_with( "set bio ", request ) ) {
        set_bio_function( request, response );
    } else if ( starts_with( "change password ", request ) ) {
        change_password_function( request, response );
    } else if ( starts_with( "logout ", request ) ) {
        logout_function( request, response );
    } else if ( starts_with( "delete tweet ", request ) ) {
        delete_tweet_function( request, response );
    } else {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}");
    }
}

int starts_with( const char *pre, const char *str ) {
    size_t lenpre = strlen(pre), lenstr = strlen(str);
    return lenstr < lenpre ? 0/*Ambiguous expansion of macro 'false'*/ : memcmp(pre, str, lenpre) == 0;
}//   COMMENT   COMMENT   COMMENT   COMMENT   COMMENT   COMMENT   COMMENT   COMMENT   COMMENT   COMMENT   COMMENT

void signup_function( char request[], char response[] ) {
    char username[22] = { 0 };//because of ',' which will be exist in end of username
    char password[21] = { 0 };
    sscanf( request, "signup %s %s", username, password );
    username[strlen( username ) - 1] = '\0';//because of ',' which exists in end of username
    if ( strlen( username ) + strlen( password ) + 10 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char file_direction[90] = dir_Users;
        strcpy( file_direction, dir_Users );
        strcat( file_direction, username );
        strcat( file_direction, ".user.json");
        
        FILE *file_pointer;
        if ( ( file_pointer = fopen( file_direction, "r" ) ) != NULL ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"This username is already taken.\"}" );
            fclose( file_pointer );
        } else {
            file_pointer = fopen( file_direction, "w" );
            
            cJSON *root = NULL;
            root = cJSON_CreateObject();
            cJSON_AddStringToObject( root, "username", username );
            cJSON_AddStringToObject( root, "password", password );
            cJSON_AddStringToObject( root, "bio", "" );
            cJSON_AddArrayToObject( root, "followers" );
            cJSON_AddArrayToObject( root, "followings" );
            cJSON_AddArrayToObject( root, "personalTweets" );
            cJSON_AddArrayToObject( root, "seenTweets" );
            
            fprintf( file_pointer, "%s", cJSON_PrintUnformatted( root ) );
            fclose( file_pointer );
            cJSON_Delete( root );
            sprintf( response, "{\"type\":\"Successful\",\"message\":\"\"}" );
        }
    }
}

void login_function( char request[], char response[] ) {
    char username[22] = { 0 };//because of ',' which will be exist in end of username
    char password[21] = { 0 };
    sscanf( request, "login %s %s", username, password );
    username[strlen( username ) - 1] = '\0';//because of ',' which exists in end of username
    
    if ( strlen( username ) + strlen( password ) + 9 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char file_direction[150] = { 0 };
        sprintf( file_direction, dir_Users"%s.user.json", username );
        
        FILE *file_pointer;
        if ( ( file_pointer = fopen( file_direction, "r" ) ) == NULL ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"This username is not valid.\"}" );
        } else {
            printf("from user %s\n", username );
            
            char *file_string = calloc( 10000000, sizeof(char) );
            fscanf( file_pointer, "%[^\n]", file_string );
            cJSON *root = NULL;
            root = cJSON_Parse( file_string );
            free( file_string );
            cJSON *cJSON_available_password;
            cJSON_available_password = cJSON_GetObjectItem( root, "password" );
            char string_available_password[21] = { 0 };
            strcpy( string_available_password, cJSON_PrintUnformatted( cJSON_available_password ) );
            string_available_password[strlen( string_available_password ) - 1] = '\0';//because of '"' which exists in the end
            cJSON_Delete( root );
            
            if ( strcmp( string_available_password + 1/*because of '"' which exists in the first*/, password ) != 0 ) {
                sprintf( response, "{\"type\":\"Error\",\"message\":\"Incorrect password.\"}");
            } else {
                int specifier1 = 0;
                for ( int i = 0; i < number_of_login_users; ++i ) {
                    if ( strcmp( users_information[i].username, username ) == 0 ) {
                        ++specifier1;
                        break;
                    }
                }
                if ( specifier1 != 0 ) {
                    sprintf( response, "{\"type\":\"Error\",\"message\":\"The user %s is already logged in.\"}", username );
                } else {
                    strcpy( users_information[number_of_login_users].username, username );
                    
                    char *token = NULL;
                    while ( 1 ) {
                        int specifier2 = 0;
                        int token_length;
                        token_length = rand() % 16 + 31;
                        token = (char *)calloc( token_length, sizeof(char) );
                        create_token( token, token_length );
                        for ( int i = 0; i < number_of_login_users; ++i ) {
                            if ( strcmp( users_information[i].token, token ) == 0 ) {
                                ++specifier2;
                                free( token );
                                break;
                            }
                        }
                        
                        if ( specifier2 == 0 ) {
                            break;
                        }
                    }
                    
                    strcpy( users_information[number_of_login_users].token, token );
                    sprintf( response, "{\"type\":\"Token\",\"message\":\"%s\"}", token );
                    ++number_of_login_users;
                    free( token );
                }
            }
            fclose( file_pointer );
        }
    }
}

void create_token( char token[], int token_length ) {
    for ( int i = 0; i < token_length - 1; ++i ) {
        token[i] = rand() % 92 + 35;
    }
    token[token_length - 1] = '\0';
}

void send_tweet_function( char request[], char response[] ) {
    char token[47] = { 0 };//because of ',' which will be exist in end of token
    char tweet[1001] = { 0 };
    sscanf( request, "send tweet %s %[^\n]", token, tweet );
    token[strlen( token ) - 1] = '\0';//because of ',' which exists in end of token
    
    if ( strlen( token ) + strlen( tweet ) + 14 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier = find_online_username( online_username, token );
        if ( specifier == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}" );
        } else {
            printf("from user %s\n", online_username );
            
            ++number_of_sent_tweets;
            FILE *file_pointer;
            char tweet_file_direction[150] = { 0 };
            sprintf( tweet_file_direction, dir_Tweets"%d.tweet.json", number_of_sent_tweets );
            file_pointer = fopen( tweet_file_direction, "w" );
            
            cJSON *root = NULL;
            root = cJSON_CreateObject();
            cJSON_AddNumberToObject( root, "id", number_of_sent_tweets );
            cJSON_AddStringToObject( root, "author", online_username );
            cJSON_AddStringToObject( root, "content", tweet );
            cJSON_AddObjectToObject( root, "comments" );
            cJSON_AddNumberToObject( root, "likes", 0 );
            
            fprintf( file_pointer, "%s", cJSON_PrintUnformatted( root ) );
            fclose( file_pointer );
            cJSON_Delete( root );
            
            char user_file_direction[100];
            sprintf( user_file_direction, dir_Users"%s.user.json", online_username );
            file_pointer = fopen( user_file_direction, "r" );
            char *file_string = calloc( 10000000, sizeof(char) );
            fscanf( file_pointer, "%[^\n]", file_string );
            root = cJSON_Parse( file_string );
            free( file_string );
            cJSON *array_pointer = cJSON_GetObjectItem( root, "personalTweets" );
            cJSON *number_pointer = cJSON_CreateNumber( number_of_sent_tweets );
            cJSON_AddItemToArray( array_pointer, number_pointer );
            
            fclose( file_pointer );
            
            file_pointer = fopen( user_file_direction, "w" );
            fprintf( file_pointer, "%s", cJSON_PrintUnformatted( root ) );
            fclose( file_pointer );
            cJSON_Delete( root );
            
            char number_of_sent_tweets_file_direction[150] = { 0 };
            sprintf( number_of_sent_tweets_file_direction, dir_Resources"number_of_sent_tweets.txt" );
            file_pointer = fopen( number_of_sent_tweets_file_direction, "w" );
            fprintf( file_pointer, "number of sent tweets: %d\n", number_of_sent_tweets );
            fclose( file_pointer );
            
            sprintf( response, "{\"type\":\"Successful\",\"message\":\"Tweet is sent successfully.\"}" );
        }
    }
}

int find_online_username( char online_username[], char token[] ) {
    int specifier = 0;
    while ( specifier < number_of_login_users ) {
        if ( strcmp( token, users_information[specifier].token ) == 0 ) {
            strcpy( online_username, users_information[specifier].username );
            ++specifier;
            break;
        }
        ++specifier;
    }
    return specifier;
}

void refresh_function( char request[], char response[] ) {
    char token[46] = { 0 };
    sscanf( request, "refresh %s", token );
    
    if ( strlen( token ) + 9 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier = find_online_username( online_username, token );
        if ( specifier == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}" );
        } else {
            printf("from user %s\n", online_username );
            
            FILE *file_pointer;
            char file_direction[150] = { 0 };
            sprintf( file_direction, dir_Users"%s.user.json", online_username );
            file_pointer = fopen( file_direction, "r" );
            char *file_string = calloc( 10000000, sizeof(char) );
            fscanf( file_pointer, "%[^\n]", file_string );
            fclose( file_pointer );
            cJSON *root = cJSON_Parse( file_string );
            free( file_string );
            
            cJSON *array_pointer = cJSON_GetObjectItem( root, "seenTweets" );
            int array_size = cJSON_GetArraySize( array_pointer );
            int seen_tweets[100] = { 0 };
            int seen_tweets_size;
            for ( seen_tweets_size = 0; seen_tweets_size < array_size; ++seen_tweets_size ) {
                cJSON *cJSON_pointer;
                cJSON_pointer = cJSON_GetArrayItem( array_pointer, seen_tweets_size );
                
                char seen_tweet[4];
                strcpy( seen_tweet, cJSON_PrintUnformatted( cJSON_pointer ) );
                sscanf( seen_tweet, "%d", &seen_tweets[seen_tweets_size] );
            }
            
            int followers_should_be_seen_tweets[100];
            int followers_should_be_seen_tweets_size = 0;
            array_pointer = cJSON_GetObjectItem( root, "followers" );
            followers_should_be_seen_tweets_size = find_suitable_tweets_from_seenTweets( array_pointer, followers_should_be_seen_tweets, followers_should_be_seen_tweets_size, seen_tweets, seen_tweets_size );
            
            int followings_should_be_seen_tweets[100] = { 0 };
            int followings_should_be_seen_tweets_size = 0;
            array_pointer = cJSON_GetObjectItem( root, "followings" );
            followings_should_be_seen_tweets_size = find_suitable_tweets_from_seenTweets( array_pointer, followings_should_be_seen_tweets, followings_should_be_seen_tweets_size, seen_tweets, seen_tweets_size );
            
            int should_be_seen_tweets[100] = { 0 };
            int should_be_seen_tweets_size = followers_should_be_seen_tweets_size + followings_should_be_seen_tweets_size;
            for ( int i = 0; i < should_be_seen_tweets_size; ++i ) {
                if ( i < followers_should_be_seen_tweets_size ) {
                    should_be_seen_tweets[i] = followers_should_be_seen_tweets[i];
                } else {
                    should_be_seen_tweets[i] = followings_should_be_seen_tweets[i - followers_should_be_seen_tweets_size];
                }
            }
            
//            add seen tweets to seenTweets key
            array_pointer = cJSON_GetObjectItem( root, "seenTweets" );
            for ( int i = 0; i < should_be_seen_tweets_size; ++i ) {
                cJSON_AddItemToArray( array_pointer, cJSON_CreateNumber( should_be_seen_tweets[i] ) );
            }
            memset( file_direction, 0, sizeof(file_direction) );
            sprintf( file_direction, dir_Users"%s.user.json", online_username );
            file_pointer = fopen( file_direction, "w" );
            fprintf( file_pointer, "%s", cJSON_PrintUnformatted( root ) );
            fclose( file_pointer );
            
            cJSON_Delete( root );
            sort( should_be_seen_tweets, should_be_seen_tweets_size );
            int number_of_duplicate_items = 0;
            number_of_duplicate_items = change_duplicate_items_to_zero( should_be_seen_tweets, should_be_seen_tweets_size );
            sort( should_be_seen_tweets, should_be_seen_tweets_size );
            delete_zero_items( should_be_seen_tweets, should_be_seen_tweets_size, number_of_duplicate_items );
            should_be_seen_tweets_size -= number_of_duplicate_items;
            
            sprintf( response, "{\"type\":\"List\",\"message\":[" );
            for ( int i = 0; i < should_be_seen_tweets_size; ++i ) {
                memset( file_direction, 0, sizeof(file_direction) );
                sprintf( file_direction, dir_Tweets"%d.tweet.json", should_be_seen_tweets[i] );
                file_pointer = fopen( file_direction, "r" );
                file_string = calloc( 10000000, sizeof(char) );
                fscanf( file_pointer, "%[^\n]", file_string );
                fclose( file_pointer );
                if ( i != 0 ) {
                    strcat( response, "," );
                }
                strcat( response, file_string );
                free( file_string );
            }
            strcat( response, "]}");
            
        }
    }
}

int find_suitable_tweets_from_seenTweets( cJSON *array_pointer, int suitable_tweets[], int suitable_tweets_size, int seen_tweets[], int seen_tweets_size ) {
    int array_size = cJSON_GetArraySize( array_pointer );
    for ( int i = 0; i < array_size; ++i ) {
        cJSON *cJSON_pointer;
        cJSON_pointer = cJSON_GetArrayItem( array_pointer, i );
        char username[23];
        strcpy( username, cJSON_PrintUnformatted( cJSON_pointer ) );
        username[strlen( username ) - 1] = '\0';
        
        FILE *file_pointer;
        char file_direction[150] = { 0 };
        sprintf( file_direction, dir_Users"%s.user.json", username + 1 );
        file_pointer = fopen( file_direction, "r" );
        
        char *file_string = calloc( 10000000, sizeof(char) );
        fscanf( file_pointer, "%[^\n]", file_string );
        fclose( file_pointer );
        cJSON *followers_root = cJSON_Parse( file_string );
        free( file_string );
        
        cJSON *followers_array_pointer = cJSON_GetObjectItem( followers_root, "personalTweets" );
        int followers_array_size = cJSON_GetArraySize( followers_array_pointer );
        for ( int j = 0; j < followers_array_size; ++j ) {
            cJSON *followers_cJSON_pointer;
            followers_cJSON_pointer = cJSON_GetArrayItem( followers_array_pointer, j );
            
            char seen_tweet[4];
            strcpy( seen_tweet, cJSON_PrintUnformatted( followers_cJSON_pointer ) );
            int temp_suitable_tweets;
            sscanf( seen_tweet, "%d", &temp_suitable_tweets );
            
            int specifier = 0;
            for ( int k = 0; k < seen_tweets_size; ++k ) {
                if ( temp_suitable_tweets == seen_tweets[k] ) {
                    ++specifier;
                    break;
                }
            }
            if ( specifier == 0 ) {
                suitable_tweets[suitable_tweets_size] = temp_suitable_tweets;
                ++suitable_tweets_size;
            }
            
        }
    }
    return suitable_tweets_size;
}

void sort( int array[], int size ) {
    for ( int i = 0; i < size; ++i ) {
        for ( int j = i + 1; j < size; ++j ) {
            if ( array[i] > array[j] ) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

int change_duplicate_items_to_zero( int array[], int size ) {
    int number_of_duplicate_items = 0;
    for ( int i = 0; i < size - 1; ++i ) {
        if ( array[i + 1] == array[i] ) {
            array[i] = 0;
            ++number_of_duplicate_items;
        }
    }
    return number_of_duplicate_items;
}

void delete_zero_items( int array[], int size, int number_of_duplicate_items ) {
    for ( int i = 0; i < number_of_duplicate_items; ++i ) {
        array[i] = array[i + number_of_duplicate_items];
        array[i + number_of_duplicate_items] = 0;
    }
}

void like_function( char request[], char response[] ) {
    char token[47] = { 0 };//because of ',' which will be exist in end of token
    int tweet_id = 0;
    sscanf( request, "like %s %d", token, &tweet_id );
    token[strlen( token ) - 1] = '\0';//because of ',' which exists in end of token
    
    int number_of_tweet_id_digits = count_digits( tweet_id );
    if ( strlen( token ) + number_of_tweet_id_digits + 8 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier = find_online_username( online_username, token );
        if ( specifier == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}" );
        } else {
            printf("from user %s\n", online_username );
            
            FILE *file_pointer;
            char file_direction[150] = { 0 };
            sprintf( file_direction, dir_Tweets"%d.tweet.json", tweet_id );
            if ( ( file_pointer = fopen( file_direction, "r" ) ) == NULL ) {
                sprintf( response, "{\"type\":\"Error\",\"message\":\"Tweet with this id is not available.\"}" );
            } else {
                char *file_string = calloc( 10000000, sizeof(char) );
                fscanf( file_pointer, "%[^\n]", file_string );
                fclose( file_pointer );
                cJSON *tweet_root = cJSON_Parse( file_string );
                free( file_string );
                
                cJSON *cJSON_pointer;
                cJSON_pointer = cJSON_GetObjectItem( tweet_root, "likes" );
                int number_of_likes;
                sscanf( cJSON_PrintUnformatted( cJSON_pointer ), "%d", &number_of_likes );
                ++number_of_likes;
                cJSON_pointer = cJSON_CreateNumber( number_of_likes );
                cJSON_ReplaceItemInObject( tweet_root, "likes", cJSON_pointer );
                
                file_pointer = fopen( file_direction, "w" );
                fprintf( file_pointer, "%s", cJSON_PrintUnformatted( tweet_root ) );
                fclose( file_pointer );
                
                cJSON_pointer = cJSON_GetObjectItem( tweet_root, "author" );
                char incomplete_file_direction[150] = { 0 };
                strcpy( incomplete_file_direction, cJSON_PrintUnformatted( cJSON_pointer ) );
                incomplete_file_direction[strlen( incomplete_file_direction ) - 1] = '\0';
                memset( file_direction, 0, sizeof(file_direction) );
                sprintf( file_direction, dir_Users"%s.user.json", incomplete_file_direction + 1 );
                cJSON_Delete( tweet_root );
                file_pointer = fopen( file_direction, "r" );
                file_string = calloc( 10000000, sizeof(char) );
                fscanf( file_pointer, "%[^\n]", file_string );
                fclose( file_pointer );
                cJSON *user_root = cJSON_Parse( file_string );
                free( file_string );
                
                cJSON *cJSON_array_pointer = cJSON_GetObjectItem( user_root, "followers" );
                int followers_array_size = 0;
                followers_array_size = cJSON_GetArraySize( cJSON_array_pointer );
                delete_suitable_tweets( cJSON_array_pointer, followers_array_size, tweet_id );
                
                cJSON_array_pointer = cJSON_GetObjectItem( user_root, "followings" );
                int followings_array_size = 0;
                followings_array_size = cJSON_GetArraySize( cJSON_array_pointer );
                delete_suitable_tweets( cJSON_array_pointer, followings_array_size, tweet_id );
                
                cJSON_Delete( user_root );
                sprintf( response, "{\"type\":\"Successful\",\"message\":\"Tweet %d successfully liked.\"}", tweet_id );
            }
        }
    }
}

int count_digits( int number ) {
    int sum = 0;
    while ( number != 0 ) {
        ++sum;
        number /= 10;
    }
    return sum;
}

void delete_suitable_tweets( cJSON *array_pointer, int array_size, int tweet_id ) {
    for ( int i = 0; i < array_size; ++i ) {
        cJSON *cJSON_array_item_pointer = cJSON_GetArrayItem( array_pointer, (double)i );
        
        char file_direction[150] = { 0 }, incomplete_file_direction[150] = { 0 };
        strcpy( incomplete_file_direction, cJSON_PrintUnformatted( cJSON_array_item_pointer ) );
        incomplete_file_direction[strlen( incomplete_file_direction ) - 1] = '\0';
        sprintf( file_direction, dir_Users"%s.user.json", incomplete_file_direction + 1 );
        FILE *file_pointer = fopen( file_direction, "r" );
        char *file_string = calloc( 10000000, sizeof(char) );
        fscanf( file_pointer, "%[^\n]", file_string );
        fclose( file_pointer );
        cJSON *root = cJSON_Parse( file_string );
        free( file_string );
        
        cJSON *cJSON_seenTweets_array_pointer = cJSON_GetObjectItem( root, "seenTweets" );
        int seenTweets_array_size = 0;
        seenTweets_array_size = cJSON_GetArraySize( cJSON_seenTweets_array_pointer );
        for ( int j = 0; j < seenTweets_array_size; ++j ) {
            cJSON *cJSON_seenTweets_array_item_pointer = cJSON_GetArrayItem( cJSON_seenTweets_array_pointer, j );
            int array_item;
            sscanf( cJSON_PrintUnformatted( cJSON_seenTweets_array_item_pointer ), "%d", &array_item );
            
            if ( tweet_id == array_item ) {
                cJSON_DeleteItemFromArray( cJSON_seenTweets_array_pointer, j );
                --seenTweets_array_size;
                --j;
            }
        }
        file_pointer = fopen( file_direction, "w" );
        fprintf( file_pointer, "%s", cJSON_PrintUnformatted( root ) );
        fclose( file_pointer );
        
        cJSON_Delete( root );
    }
}

void comment_function( char request[], char response[] ) {
    char token[47] = { 0 };//because of ',' which will be exist in end of token
    int tweet_id = 0;
    char comment[501] = { 0 };
    sscanf( request, "comment %s %d, %[^\n]", token, &tweet_id, comment );
    token[strlen( token ) - 1] = '\0';//because of ',' which exists in end of token
    
    int number_of_tweet_id_digits = count_digits( tweet_id );
    if ( strlen( token ) + number_of_tweet_id_digits + strlen( comment ) + 13 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier = find_online_username( online_username, token );
        if ( specifier == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}" );
        } else {
            printf("from user %s\n", online_username );
            
            FILE *file_pointer;
            char file_direction[150] = { 0 };
            sprintf( file_direction, dir_Tweets"%d.tweet.json", tweet_id );
            if ( ( file_pointer = fopen( file_direction, "r" ) ) == NULL ) {
                sprintf( response, "{\"type\":\"Error\",\"message\":\"Tweet with this id is not available.\"}" );
            } else {
                char *file_string = calloc( 10000000, sizeof(char) );
                fscanf( file_pointer, "%[^\n]", file_string );
                fclose( file_pointer );
                cJSON *tweet_root = cJSON_Parse( file_string );
                free( file_string );
                
                cJSON *cJSON_pointer_1 = cJSON_GetObjectItem( tweet_root, "comments" );
                cJSON *cJSON_pointer_2 = cJSON_CreateString( comment );
                cJSON_AddItemToObject( cJSON_pointer_1, online_username, cJSON_pointer_2 );
                
                file_pointer = fopen( file_direction, "w" );
                fprintf( file_pointer, "%s", cJSON_PrintUnformatted( tweet_root ) );
                fclose( file_pointer );
                
                cJSON_pointer_1 = cJSON_GetObjectItem( tweet_root, "author" );
                char incomplete_file_direction[150] = { 0 };
                strcpy( incomplete_file_direction, cJSON_PrintUnformatted( cJSON_pointer_1 ) );
                incomplete_file_direction[strlen( incomplete_file_direction ) - 1] = '\0';
                memset( file_direction, 0, sizeof(file_direction) );
                sprintf( file_direction, dir_Users"%s.user.json", incomplete_file_direction + 1 );
                cJSON_Delete( tweet_root );
                file_pointer = fopen( file_direction, "r" );
                file_string = calloc( 10000000, sizeof(char) );
                fscanf( file_pointer, "%[^\n]", file_string );
                fclose( file_pointer );
                cJSON *user_root = cJSON_Parse( file_string );
                free( file_string );
                
                cJSON *cJSON_array_pointer = cJSON_GetObjectItem( user_root, "followers" );
                int followers_array_size = 0;
                followers_array_size = cJSON_GetArraySize( cJSON_array_pointer );
                delete_suitable_tweets( cJSON_array_pointer, followers_array_size, tweet_id );
                
                cJSON_array_pointer = cJSON_GetObjectItem( user_root, "followings" );
                int followings_array_size = 0;
                followings_array_size = cJSON_GetArraySize( cJSON_array_pointer );
                delete_suitable_tweets( cJSON_array_pointer, followings_array_size, tweet_id );
                
                cJSON_Delete( user_root );
                sprintf( response, "{\"type\":\"Successful\",\"message\":\"Comment is sent successfully.\"}" );
            }
        }
    }
}

void search_function( char request[], char response[] ) {
    char token[47] = { 0 };//because of ',' which will be exist in end of token
    char searched_username[21] = { 0 };
    sscanf( request, "search %s %s", token, searched_username );
    token[strlen( token ) - 1] = '\0';//because of ',' which exists in end of token
    
    if ( strlen( token ) + strlen( searched_username ) + 10 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier_1 = find_online_username( online_username, token );
        if ( specifier_1 == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}" );
        } else {
            printf("from user %s\n", online_username );
            
            FILE *file_pointer;
            char file_direction[150] = { 0 };
            sprintf( file_direction, dir_Users"%s.user.json", searched_username );
            if ( ( file_pointer = fopen( file_direction, "r" ) ) == NULL ) {
                sprintf( response, "{\"type\":\"Error\",\"message\":\"This username is not valid.\"}" );
            } else if ( strcmp( online_username, searched_username ) == 0 ) {
                fclose( file_pointer );
                sprintf( response, "{\"type\":\"Error\",\"message\":\"Searched username is your username.\"}" );
            } else {
                char *file_string = calloc( 10000000, sizeof(char) );
                fscanf( file_pointer, "%[^\n]", file_string );
                fclose( file_pointer );
                cJSON *searched_username_root = cJSON_Parse( file_string );
                free( file_string );
                //why?????????????????????????????????????????????????????????????
                cJSON *message_root = cJSON_CreateObject();
                cJSON_AddStringToObject( message_root, "username", cJSON_GetObjectItem( searched_username_root, "username" ) -> valuestring );
//                cJSON_AddItemToObject( message_root, "bio", cJSON_GetObjectItem( searched_username_root, "bio" ) );
                cJSON_AddStringToObject( message_root, "bio", cJSON_GetObjectItem( searched_username_root, "bio" ) -> valuestring );
                cJSON *cJSON_followers_pointer = cJSON_GetObjectItem( searched_username_root, "followers" );
                int number_of_followers = cJSON_GetArraySize( cJSON_followers_pointer );
                cJSON_AddNumberToObject( message_root, "numberOfFollowers", number_of_followers );
                cJSON *cJSON_followings_pointer = cJSON_GetObjectItem( searched_username_root, "followings" );
                cJSON_AddNumberToObject( message_root, "numberOfFollowings", cJSON_GetArraySize( cJSON_followings_pointer ) );
                
                int specifier_2 = 0;
                for ( int i = 0; i < number_of_followers; ++i ) {
                    char array_item[21] = { 0 };
                    strcpy( array_item, cJSON_GetArrayItem( cJSON_followers_pointer, i ) -> valuestring );
                    if ( strcmp( array_item, online_username ) == 0 ) {
                        ++specifier_2;
                        break;
                    }
                }
                if ( specifier_2 == 0 ) {
                    cJSON_AddStringToObject( message_root, "followStatus", "NotFollowed" );
                } else if ( specifier_2 == 1 ) {
                    cJSON_AddStringToObject( message_root, "followStatus", "Followed" );
                }
                
                cJSON_AddArrayToObject( message_root, "allTweets" );
                cJSON *cJSON_array_pointer = cJSON_GetObjectItem( searched_username_root, "personalTweets" );
                char *allTweets = calloc( 1000000, sizeof(char) );
                for ( int i = 0; i < cJSON_GetArraySize( cJSON_array_pointer ); ++i ) {
                    cJSON *cJSON_array_item_pointer = cJSON_GetArrayItem( cJSON_array_pointer, i );
                    sprintf( file_direction, dir_Tweets"%d.tweet.json", cJSON_array_item_pointer -> valueint );
                    file_pointer = fopen( file_direction, "r" );
                    char *file_string = calloc( 10000000, sizeof(char) );
                    fscanf( file_pointer, "%[^\n]", file_string );
                    fclose( file_pointer );
                    strcat( allTweets, file_string );
                    free( file_string );
                    if ( i != cJSON_GetArraySize( cJSON_array_pointer ) - 1 ) {
                        strcat( allTweets, "," );
                    }
                }
                
                char *message = calloc( 1000000, sizeof(char) );
                strcpy( message, cJSON_PrintUnformatted( message_root ) );
                message[strlen( message ) - 2/* ]} */] = '\0';
                strcat( message, allTweets );
                strcat( message, "]}" );
                free( allTweets );
                cJSON_Delete( searched_username_root );
                cJSON_Delete( message_root );//why?????????????????????????????????????????????????????????????
                
                cJSON *responce_root = cJSON_CreateObject();
                cJSON_AddStringToObject( responce_root, "type", "Profile" );
                cJSON_AddStringToObject( responce_root, "message", "" );
                strcpy( response, cJSON_PrintUnformatted( responce_root ) );
                response[strlen( response ) - 3/* ""} */] = '\0';
                strcat( response, message );
                strcat( response, "}" );
                free( message );
                cJSON_Delete( responce_root );
            }
        }
    }
}

void follow_function( char request[], char response[] ) {
    char token[47] = { 0 };//because of ',' which will be exist in end of token
    char username[21] = { 0 };
    sscanf( request, "follow %s %s", token, username );
    token[strlen( token ) - 1] = '\0';//because of ',' which exists in end of token
    
    if ( strlen( token ) + strlen( username ) + 10 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier_1 = find_online_username( online_username, token );
        if ( specifier_1 == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}" );
        } else {
            printf("from user %s\n", online_username );
            
            FILE *file_pointer;
            char file_direction[150] = { 0 };
            sprintf( file_direction, dir_Users"%s.user.json", username );
            if ( ( file_pointer = fopen( file_direction, "r" ) ) == NULL ) {
                sprintf( response, "{\"type\":\"Error\",\"message\":\"This username is not valid.\"}" );
            } else {
                char *file_string = calloc( 10000000, sizeof(char) );
                fscanf( file_pointer, "%[^\n]", file_string );
                fclose( file_pointer );
                cJSON *username_root = cJSON_Parse( file_string );
                free( file_string );
                
                cJSON *cJSON_array_pointer = cJSON_GetObjectItem( username_root, "followers" );
                int specifier_2 = 0;
                for ( int i = 0; i < cJSON_GetArraySize( cJSON_array_pointer ); ++i ) {
                    char follower[21] = { 0 };
                    strcpy( follower, cJSON_GetArrayItem( cJSON_array_pointer, i ) -> valuestring );
                    if ( strcmp( online_username, follower ) == 0 ) {
                        ++specifier_2;
                        break;
                    }
                }
                if ( specifier_2 != 0 ) {
                    sprintf( response, "{\"type\":\"Error\",\"message\":\"User %s is already followed by you.\"}", username );
                } else {
                    cJSON *cJSON_username_followers_array_pointer = cJSON_GetObjectItem( username_root, "followers" );
                    cJSON *cJSON_item_pointer = cJSON_CreateString( online_username );
                    cJSON_AddItemToArray( cJSON_username_followers_array_pointer, cJSON_item_pointer );
                    
                    file_pointer = fopen( file_direction, "w" );
                    fprintf( file_pointer, "%s", cJSON_PrintUnformatted( username_root ) );
                    fclose( file_pointer );
                    cJSON_Delete( username_root );
                    
                    sprintf( file_direction, dir_Users"%s.user.json", online_username );
                    file_pointer = fopen( file_direction, "r" );
                    file_string = calloc( 1000000, sizeof(char) );
                    fscanf( file_pointer, "%[^\n]", file_string );
                    fclose( file_pointer );
                    cJSON *online_username_root = cJSON_Parse( file_string );
                    cJSON *cJSON_online_username_followings_array_pointer = cJSON_GetObjectItem( online_username_root, "followings" );
                    cJSON_item_pointer = cJSON_CreateString( username );
                    cJSON_AddItemToArray( cJSON_online_username_followings_array_pointer, cJSON_item_pointer );
                    free( file_string );
                    
                    file_pointer = fopen( file_direction, "w" );
                    fprintf( file_pointer, "%s", cJSON_PrintUnformatted( online_username_root ) );
                    fclose( file_pointer );
                    cJSON_Delete( online_username_root );
                    
                    sprintf( response, "{\"type\":\"Successful\",\"message\":\"User %s is followed successfully.\"}", username );
                }
            }
        }
    }
}

void unfollow_function( char request[], char response[] ) {
    char token[47] = { 0 };//because of ',' which will be exist in end of token
    char username[21] = { 0 };
    sscanf( request, "unfollow %s %s", token, username );
    token[strlen( token ) - 1] = '\0';//because of ',' which exists in end of token
    
    if ( strlen( token ) + strlen( username ) + 12 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier_1 = find_online_username( online_username, token );
        if ( specifier_1 == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}" );
        } else {
            printf("from user %s\n", online_username );
            
            FILE *file_pointer;
            char file_direction[150] = { 0 };
            sprintf( file_direction, dir_Users"%s.user.json", username );
            if ( ( file_pointer = fopen( file_direction, "r" ) ) == NULL ) {
                sprintf( response, "{\"type\":\"Error\",\"message\":\"This username is not valid.\"}" );
            } else {
                char *file_string = calloc( 10000000, sizeof(char) );
                fscanf( file_pointer, "%[^\n]", file_string );
                fclose( file_pointer );
                cJSON *username_root = cJSON_Parse( file_string );
                free( file_string );
                
                cJSON *cJSON_array_pointer = cJSON_GetObjectItem( username_root, "followers" );
                int specifier_2 = 0;
                int index_of_online_username_in_followers = -1;
                for ( int i = 0; i < cJSON_GetArraySize( cJSON_array_pointer ); ++i ) {
                    char follower[21] = { 0 };
                    strcpy( follower, cJSON_GetArrayItem( cJSON_array_pointer, i ) -> valuestring );
                    if ( strcmp( online_username, follower ) == 0 ) {
                        ++specifier_2;
                        index_of_online_username_in_followers = i;
                        break;
                    }
                }
                if ( specifier_2 == 0 ) {
                    sprintf( response, "{\"type\":\"Error\",\"message\":\"User %s is not followed by you.\"}", username );
                } else {
                    cJSON *cJSON_username_followers_array_pointer = cJSON_GetObjectItem( username_root, "followers" );
                    cJSON_DeleteItemFromArray( cJSON_username_followers_array_pointer, index_of_online_username_in_followers );
                    
                    file_pointer = fopen( file_direction, "w" );
                    fprintf( file_pointer, "%s", cJSON_PrintUnformatted( username_root ) );
                    fclose( file_pointer );
                    cJSON_Delete( username_root );
                    
                    sprintf( file_direction, dir_Users"%s.user.json", online_username );
                    file_pointer = fopen( file_direction, "r" );
                    file_string = calloc( 1000000, sizeof(char) );
                    fscanf( file_pointer, "%[^\n]", file_string );
                    fclose( file_pointer );
                    cJSON *online_username_root = cJSON_Parse( file_string );
                    free( file_string );
                    cJSON *cJSON_online_username_followings_array_pointer = cJSON_GetObjectItem( online_username_root, "followings" );
                    int index_of_username_in_followings = -1;
                    for ( int i = 0; i < cJSON_GetArraySize( cJSON_online_username_followings_array_pointer ); ++i ) {
                        char following[21] = { 0 };
                        strcpy( following, cJSON_GetArrayItem( cJSON_online_username_followings_array_pointer, i ) -> valuestring );
                        if ( strcmp( username, following ) == 0 ) {
                            index_of_username_in_followings = i;
                            break;
                        }
                    }
                    cJSON_DeleteItemFromArray( cJSON_online_username_followings_array_pointer, index_of_username_in_followings );
                    
                    file_pointer = fopen( file_direction, "w" );
                    fprintf( file_pointer, "%s", cJSON_PrintUnformatted( online_username_root ) );
                    fclose( file_pointer );
                    cJSON_Delete( online_username_root );
                    
                    sprintf( response, "{\"type\":\"Successful\",\"message\":\"User %s is unfollowed successfully.\"}", username );
                }
            }
        }
    }
}

void profile_function( char request[], char response[] ) {//the same function as search function
    char token[46] = { 0 };
    sscanf( request, "profile %s", token );
    
    if ( strlen( token ) + 9 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier = find_online_username( online_username, token );
        if ( specifier == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}" );
        } else {
            printf("from user %s\n", online_username );
            
            FILE *file_pointer;
            char file_direction[150] = { 0 };
            sprintf( file_direction, dir_Users"%s.user.json", online_username );
            file_pointer = fopen( file_direction, "r" );
            char *file_string = calloc( 10000000, sizeof(char) );
            fscanf( file_pointer, "%[^\n]", file_string );
            fclose( file_pointer );
            cJSON *online_username_root = cJSON_Parse( file_string );
            free( file_string );
            
            cJSON *message_root = cJSON_CreateObject();
            cJSON_AddStringToObject( message_root, "username", cJSON_GetObjectItem( online_username_root, "username" ) -> valuestring );
            cJSON_AddStringToObject( message_root, "bio", cJSON_GetObjectItem( online_username_root, "bio" ) -> valuestring );
            cJSON *cJSON_followers_pointer = cJSON_GetObjectItem( online_username_root, "followers" );
            cJSON_AddNumberToObject( message_root, "numberOfFollowers", cJSON_GetArraySize( cJSON_followers_pointer ) );
            cJSON *cJSON_followings_pointer = cJSON_GetObjectItem( online_username_root, "followings" );
            cJSON_AddNumberToObject( message_root, "numberOfFollowings", cJSON_GetArraySize( cJSON_followings_pointer ) );
            cJSON_AddStringToObject( message_root, "followStatus", "Yourself" );
            cJSON_AddArrayToObject( message_root, "allTweets" );
            
            cJSON *cJSON_array_pointer = cJSON_GetObjectItem( online_username_root, "personalTweets" );
            char *allTweets = calloc( 1000000, sizeof(char) );
            for ( int i = 0; i < cJSON_GetArraySize( cJSON_array_pointer ); ++i ) {
                cJSON *cJSON_array_item_pointer = cJSON_GetArrayItem( cJSON_array_pointer, i );
                sprintf( file_direction, dir_Tweets"%d.tweet.json", cJSON_array_item_pointer -> valueint );
                file_pointer = fopen( file_direction, "r" );
                char *file_string = calloc( 10000000, sizeof(char) );
                fscanf( file_pointer, "%[^\n]", file_string );
                fclose( file_pointer );
                strcat( allTweets, file_string );
                free( file_string );
                if ( i != cJSON_GetArraySize( cJSON_array_pointer ) - 1 ) {
                    strcat( allTweets, "," );
                }
            }
            
            char *message = calloc( 1000000, sizeof(char) );
            strcpy( message, cJSON_PrintUnformatted( message_root ) );
            message[strlen( message ) - 2/* ]} */] = '\0';
            strcat( message, allTweets );
            strcat( message, "]}" );
            free( allTweets );
            cJSON_Delete( online_username_root );
            cJSON_Delete( message_root );
            
            cJSON *responce_root = cJSON_CreateObject();
            cJSON_AddStringToObject( responce_root, "type", "Profile" );
            cJSON_AddStringToObject( responce_root, "message", "" );
            strcpy( response, cJSON_PrintUnformatted( responce_root ) );
            response[strlen( response ) - 3/* ""} */] = '\0';
            strcat( response, message );
            strcat( response, "}" );
            free( message );
            cJSON_Delete( responce_root );
        }
    }
}

void set_bio_function( char request[], char response[] ) {
    char token[47] = { 0 };//because of ',' which will be exist in end of token
    char bio[501] = { 0 };
    sscanf( request, "set bio %s %[^\n]", token, bio );
    token[strlen( token ) - 1] = '\0';//because of ',' which exists in end of token
    
    if ( strlen( token ) + strlen( bio ) + 11 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier = find_online_username( online_username, token );
        if ( specifier == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}" );
        } else {
            printf("from user %s\n", online_username );
            
            FILE *file_pointer;
            char file_direction[150] = { 0 };
            sprintf( file_direction, dir_Users"%s.user.json", online_username );
            file_pointer = fopen( file_direction, "r" );
            char *file_string = calloc( 10000000, sizeof(char) );
            fscanf( file_pointer, "%[^\n]", file_string );
            fclose( file_pointer );
            cJSON *online_username_root = cJSON_Parse( file_string );
            free( file_string );
            
            if ( strcmp( cJSON_GetObjectItem( online_username_root, "bio" ) -> valuestring, "" ) != 0 ) {
                sprintf( response, "{\"type\":\"Error\",\"message\":\"Bio is already updated.\"}" );
            } else {
                cJSON_ReplaceItemInObject( online_username_root, "bio", cJSON_CreateString( bio ) );
                file_pointer = fopen( file_direction, "w" );
                fprintf( file_pointer, "%s", cJSON_PrintUnformatted( online_username_root ) );
                fclose( file_pointer );
                
                sprintf( response, "{\"type\":\"Successful\",\"message\":\"Bio is updated successfully.\"}" );
            }
            
            cJSON_Delete( online_username_root );
        }
    }
}

void change_password_function( char request[], char response[] ) {
    char token[47] = { 0 };//because of ',' which will be exist in end of token
    char current_password[22] = { 0 };//because of ',' which will be exist in end of current_password
    char new_password[21] = { 0 };
    char new_password_test[22] = { 0 };
    sscanf( request, "change password %s %s %s", token, current_password, new_password_test );
    token[strlen( token ) - 1] = '\0';//because of ',' which exists in end of token
    current_password[strlen( current_password ) - 1] = '\0';//because of ',' which exists in end of current_password
    new_password_test[21] = '\0';
    
    if ( strlen( token ) + strlen( current_password ) + strlen( new_password_test ) + 21 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier = find_online_username( online_username, token );
        if ( specifier == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}");
        } else {
            printf("from user %s\n", online_username );
            
            if ( strlen( new_password_test ) > 20 ) {
                sprintf( response, "{\"type\":\"Error\",\"message\":\"Your entered new password is more than 20 characters.\"}");
            } else {
                strcpy( new_password, new_password_test );
                
                FILE *file_pointer;
                char file_direction[150] = { 0 };
                sprintf( file_direction, dir_Users"%s.user.json", online_username );
                file_pointer = fopen( file_direction, "r" );
                char *file_string = calloc( 10000000, sizeof(char) );
                fscanf( file_pointer, "%[^\n]", file_string );
                fclose( file_pointer );
                cJSON *online_username_root = cJSON_Parse( file_string );
                free( file_string );
                
                if ( strcmp( current_password, cJSON_GetObjectItem( online_username_root, "password" ) -> valuestring ) != 0 ) {
                    sprintf( response, "{\"type\":\"Error\",\"message\":\"Entered current password is wrong.\"}" );
                } else if ( strcmp( new_password, cJSON_GetObjectItem( online_username_root, "password" ) -> valuestring ) == 0 ) {
                    sprintf( response, "{\"type\":\"Error\",\"message\":\"New password is equal to current password.\"}" );
                } else {
                    cJSON_ReplaceItemInObject( online_username_root, "password", cJSON_CreateString( new_password ) );
                    file_pointer = fopen( file_direction, "w" );
                    fprintf( file_pointer, "%s", cJSON_PrintUnformatted( online_username_root ) );
                    fclose( file_pointer );
                    
                    sprintf( response, "{\"type\":\"Successful\",\"message\":\"Password is changed successfully.\"}");
                }
                cJSON_Delete( online_username_root );
            }
        }
    }
}

void logout_function( char request[], char response[] ) {
    char token[46] = { 0 };
    sscanf( request, "logout %s", token );
    
    if ( strlen( token ) + 8 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier = find_online_username( online_username, token );
        if ( specifier == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}" );
        } else {
            printf("from user %s\n", online_username );
            
            --number_of_login_users;
            int online_username_index_in_users_information = specifier - 1;
            memset( users_information[online_username_index_in_users_information].username, 0, sizeof(users_information[online_username_index_in_users_information].username) );
            memset( users_information[online_username_index_in_users_information].token, 0, sizeof(users_information[online_username_index_in_users_information].token) );
            
            for ( int i = online_username_index_in_users_information; i < number_of_login_users; ++i ) {
                strcpy( users_information[i].username, users_information[i + 1].username );
                strcpy( users_information[i].token, users_information[i + 1].token );
            }
            memset( users_information[number_of_login_users].username, 0, sizeof(users_information[number_of_login_users].username) );
            memset( users_information[number_of_login_users].token, 0, sizeof(users_information[number_of_login_users].token) );
            
            sprintf( response, "{\"type\":\"Successful\",\"message\":\"\"}" );
        }
    }
}

void delete_tweet_function( char request[], char response[] ) {
    char token[47] = { 0 };//because of ',' which will be exist in end of token
    int tweet_id = 0;
    sscanf( request, "delete tweet %s %d", token, &tweet_id );
    token[strlen( token ) - 1] = '\0';//because of ',' which exists in end of token
    
    int number_of_tweet_id_digits = count_digits( tweet_id );
    if ( strlen( token ) + number_of_tweet_id_digits + 16 != strlen( request ) ) {
        sprintf( response, "{\"type\":\"Error\",\"message\":\"Bad request format.\"}" );
    } else {
        char online_username[21] = { 0 };
        int specifier = find_online_username( online_username, token );
        if ( specifier == 0 ) {
            sprintf( response, "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}" );
        } else {
            printf("from user %s\n", online_username );
            
            FILE *file_pointer;
            char file_direction[150] = { 0 };
            sprintf( file_direction, dir_Tweets"%d.tweet.json", tweet_id );
            if ( ( file_pointer = fopen( file_direction, "r" ) ) == NULL ) {
                sprintf( response, "{\"type\":\"Error\",\"message\":\"Tweet with this id is not available.\"}" );
            } else {
                fclose( file_pointer );
                
                sprintf( file_direction, dir_Users"%s.user.json", online_username );
                file_pointer = fopen( file_direction, "r" );
                char *file_string = calloc( 10000000, sizeof(char) );
                fscanf( file_pointer, "%[^\n]", file_string );
                fclose( file_pointer );
                cJSON *online_username_root = cJSON_Parse( file_string );
                free( file_string );
                
                int index_of_should_be_deleted_tweet = -1;
                cJSON *cJSON_array_pointer = cJSON_GetObjectItem( online_username_root, "personalTweets" );
                for ( int i = 0; i < cJSON_GetArraySize( cJSON_array_pointer ); ++i ) {
                    if ( tweet_id == cJSON_GetArrayItem( cJSON_array_pointer, i ) -> valueint ) {
                        index_of_should_be_deleted_tweet = i;
                        break;
                    }
                }
                
                if ( index_of_should_be_deleted_tweet == -1 ) {
                    cJSON_Delete( online_username_root );
                    sprintf( response, "{\"type\":\"Error\",\"message\":\"Entered id is not for your tweets.\"}" );
                } else {
                    cJSON_DeleteItemFromArray( cJSON_array_pointer, index_of_should_be_deleted_tweet );
                    file_pointer = fopen( file_direction, "w" );
                    fprintf( file_pointer, "%s", cJSON_PrintUnformatted( online_username_root ) );
                    fclose( file_pointer );
                    
                    sprintf( file_direction, dir_Tweets"%d.tweet.json", tweet_id );
                    remove( file_direction );
                    
//                    --------------------------------------------------
//                    I can delete this part
                    
                    cJSON_array_pointer = cJSON_GetObjectItem( online_username_root, "followers" );
                    for ( int i = 0; i < cJSON_GetArraySize( cJSON_array_pointer ); ++i ) {
                        sprintf( file_direction, dir_Users"%s.user.json", cJSON_GetArrayItem( cJSON_array_pointer, i ) -> valuestring );
                        file_pointer = fopen( file_direction, "r" );
                        file_string = calloc( 10000000, sizeof(char) );
                        fscanf( file_pointer, "%[^\n]", file_string );
                        fclose( file_pointer );
                        cJSON *followers_root = cJSON_Parse( file_string );
                        free( file_string );
                        
                        cJSON *cJSON_seenTweets_array_pointer = cJSON_GetObjectItem( followers_root, "seenTweets" );
                        delete_suitable_index( cJSON_seenTweets_array_pointer, tweet_id );
                        
                        file_pointer = fopen( file_direction, "w" );
                        fprintf( file_pointer, "%s", cJSON_PrintUnformatted( followers_root ) );
                        fclose( file_pointer );
                        
                        cJSON_Delete( followers_root );
                    }
                    
                    cJSON_array_pointer = cJSON_GetObjectItem( online_username_root, "followings" );
                    for ( int i = 0; i < cJSON_GetArraySize( cJSON_array_pointer ); ++i ) {
                        sprintf( file_direction, dir_Users"%s.user.json", cJSON_GetArrayItem( cJSON_array_pointer, i ) -> valuestring );
                        file_pointer = fopen( file_direction, "r" );
                        file_string = calloc( 10000000, sizeof(char) );
                        fscanf( file_pointer, "%[^\n]", file_string );
                        fclose( file_pointer );
                        cJSON *followings_root = cJSON_Parse( file_string );
                        free( file_string );
                        
                        cJSON *cJSON_seenTweets_array_pointer = cJSON_GetObjectItem( followings_root, "seenTweets" );
                        delete_suitable_index( cJSON_seenTweets_array_pointer, tweet_id );
                        
                        file_pointer = fopen( file_direction, "w" );
                        fprintf( file_pointer, "%s", cJSON_PrintUnformatted( followings_root ) );
                        fclose( file_pointer );
                        
                        cJSON_Delete( followings_root );
                    }
                    
                    cJSON_Delete( online_username_root );
                    
//                    --------------------------------------------------
                    
                    sprintf( response, "{\"type\":\"Successful\",\"message\":\"Tweet %d successfully deleted.\"}", tweet_id );
                }
            }
        }
    }
}

void delete_suitable_index( cJSON *cJSON_array_pointer, int tweet_id ) {
    for ( int i = 0; i < cJSON_GetArraySize( cJSON_array_pointer ); ++i ) {
        if ( tweet_id == cJSON_GetArrayItem( cJSON_array_pointer, i ) -> valueint ) {
            cJSON_DeleteItemFromArray( cJSON_array_pointer, i );
            
        }
    }
}
