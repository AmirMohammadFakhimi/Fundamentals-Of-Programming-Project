//
//  main.c
//  new client
//
//  Created by Amir Mohammad on 11/18/1399 AP.
//

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080
#define SA struct sockaddr
#define MAX 10000

#define messageLimit 100000

char requestToSend[MAX];
char originalReq[MAX] = {'\0'};
char token[50];

void copyReqs( void );
void sendRequestToServer( char *request, char *result );
void sendTheRequest( int server_socket );

void registerMenu( void );

void signUp( void );
void signUpMenu( char resultOfSignUp[], char username[], char password[] );

void usernameFunction( char username[], int specifier );
int validateUsername( char usernameTest[] );
void passwordFunction( char password[] );
int validatePassword( char passwordTest[] );

int checkSignUp( char resultOfSignUp[] );
void logInMenuBySignUp( char username[], char password[] );
void checkLogInBySignUp( char resultOfLogIn[] );

void logIn( void );
void logInMenu( char resultOfLogIn[], char username[], char password[] );
int checkLogIn( char resultOfLogIn[] );

void validatingByYesNo( char shouldBeValidated[] );//    change the place

void mainMenu( void );

void timeLine( void );

void sendTweet( void );
int validateTweet( char tweetTest[] );
int checkSendTweet( char resultOfSendTweet[] );

void deleteTweet( void );
int validateID( char id[] );
int checkDeleteATweet( char resultOfLikeAtweet[] );

void refreshTweet( void );
void refreshTweetMenu( char resultOfRefreshTweet[] );
int checkRefreshTweet( char resultOfRefreshTweet[] );
int findShowDetails( char resultOfRefreshTweet[] );
void findNumberOfCommentsOfEachUser( int numberOfCommentsOfEachUser[], int numberOfUsers );
void findDetailsOfCommentsOfEachUser( int numberOfCommentsOfEachUser[], int numberOfUsers );
void showDetails( char id[][20], char author[][21], char **content, int numberOfCommentsOfEachUser[], char likes[][6], int numberOfUsers );

void moreOptions( void );

void likeATweet( void );
int checkLikeATweet( char resultOfLikeAtweet[] );

void commentATweet( void );
int validateComment( char commentTest[] );
int checkCommentATweet( char resultOfCommentAtweet[] );

void seeCommentsOfATweet( void );

void search( void );
int checkSearch( char resultOfSearch[] );
void errorOfSearch( void );
void findShowDetailsInSearch( char resultOfSearch[] );
void findShowDetailsOfCommentsInSearch( char usernameInSearch[], char bio[], char numberOfFollowers[], char numberOfFollowings[], char followStatus[] );
void findNumberOfCommentsOfEachTweet( int numberOfCommentsOfEachTweet[], int numberOfTweets );
void showDetailsInSearch( char usernameInSearch[], char bio[], char numberOfFollowers[], char numberOfFollowings[], char followStatus[], char contentInSearch[][1001], char likesInSearch[][6], int numberOfTweets, int numberOfCommentsOfEachTweet[] );
void changeFollowStatus( void );
void followUnfollow( int specifier );

void tweetProfile ( void );
void findShowDetailsInTweetProfile( char resultOfTweetProfile[] );
void findShowDetailsOfCommentsInTweetProfile( char usernameInTweetProfile[], char bio[], char numberOfFollowers[], char numberOfFollowings[], char followStatusInTweetProfile[] );
void findNumberOfCommentsOfEachTweetForTweetProfile( int numberOfCommentsOfEachTweet[], int numberOfTweets );
void showDetailsInTweetProfile( char usernameInTweetProfile[], char bio[], char numberOfFollowers[], char numberOfFollowings[], char contentInSearch[][1001], char likesInSearch[][6], int numberOfTweets, int numberOfCommentsOfEachTweet[], char idInTweetProfile[][20] );

void personalArea( void );
void setBiography( void );
int validateBio( char biographyTest[] );
int checkSetBio( char resultOfSetBio[] );
void changePassword( void );
int checkChangePassword( char resultOfChangePassword[] );

void logOut( void );
int checkLogOut( char resultOfLogOut[] );

int main( void ) {
    // insert code here...
    
    printf("\n\n");
    printf("\t         tttt                                                      iiii\n");
    printf("\t      ttt:::t                                                     i::::i\n");
    printf("\t      t:::::t                                                      iiii\n");
    printf("\t      t:::::t\n");
    printf("\tttttttt:::::ttttttt    wwwwwww           wwwww           wwwwwww iiiiiii      cccccccccccccccc     cccccccccccccccc     eeeeeeeeeeee     rrrrr   rrrrrrrrr\n");
    printf("\tt:::::::::::::::::t     w:::::w         w:::::w         w:::::w  i:::::i    cc:::::::::::::::c   cc:::::::::::::::c   ee::::::::::::ee   r::::rrr:::::::::r\n");
    printf("\tt:::::::::::::::::t      w:::::w       w:::::::w       w:::::w    i::::i   c:::::::::::::::::c  c:::::::::::::::::c  e::::::eeeee:::::ee r:::::::::::::::::r\n");
    printf("\ttttttt:::::::tttttt       w:::::w     w:::::::::w     w:::::w     i::::i  c:::::::cccccc:::::c c:::::::cccccc:::::c e::::::e     e:::::e rr::::::rrrrr::::::r\n");
    printf("\t      t:::::t              w:::::w   w:::::w:::::w   w:::::w      i::::i  c::::::c     ccccccc c::::::c     ccccccc e:::::::eeeee::::::e  r:::::r     r:::::r\n");
    printf("\t      t:::::t               w:::::w w:::::w w:::::w w:::::w       i::::i  c:::::c              c:::::c              e:::::::::::::::::e   r:::::r     rrrrrrr\n");
    printf("\t      t:::::t                w:::::w:::::w   w:::::w:::::w        i::::i  c:::::c              c:::::c              e::::::eeeeeeeeeee    r:::::r\n");
    printf("\t      t:::::t    tttttt       w:::::::::w     w:::::::::w         i::::i  c::::::c     ccccccc c::::::c     ccccccc e:::::::e             r:::::r\n");
    printf("\t      t::::::tttt:::::t        w:::::::w       w:::::::w         i::::::i c:::::::cccccc:::::c c:::::::cccccc:::::c e::::::::e            r:::::r\n");
    printf("\t      tt::::::::::::::t         w:::::w         w:::::w          i::::::i  c:::::::::::::::::c  c:::::::::::::::::c  e::::::::eeeeeeee    r:::::r\n");
    printf("\t        tt:::::::::::tt          w:::w           w:::w           i::::::i   cc:::::::::::::::c   cc:::::::::::::::c   ee:::::::::::::e    r:::::r\n");
    printf("\t          ttttttttttt             www             www            iiiiiiii     cccccccccccccccc     cccccccccccccccc     eeeeeeeeeeeeee    rrrrrrr\n");
    printf("\n\n\n");

    registerMenu();
    mainMenu();
    
    return 0;
}

void copyReqs( void ) {
    for (int i = 0; i < MAX; i++) {
        requestToSend[i] = '\0';
    }
    for (int i = 0; i < MAX; i++) {
        if (originalReq[i] == '\0') {
            requestToSend[i] = '\n';
            requestToSend[i + 1] = '\0';
            break;
        } else {
            requestToSend[i] = originalReq[i];
        }
    }
}

void sendRequestToServer( char *request, char *result ) {
    strcpy( originalReq, request );
    
    int server_socket;
    struct sockaddr_in servaddr;
    
//    Create and verify socket
    server_socket = socket( AF_INET, SOCK_STREAM, 0 );
    
//    Assign IP and port
    bzero( &servaddr, sizeof(servaddr) );
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons( PORT );
    
//    Connect the client socket to server socket
    connect( server_socket, (SA*)&servaddr, sizeof(servaddr) );
    
//    Function for chat
    sendTheRequest( server_socket );
    
    strcpy( result, requestToSend );
    
//    TODO: for second phase
//    Close the socket
    shutdown( server_socket, SHUT_RDWR );
}

void sendTheRequest( int server_socket ) {
    copyReqs();
    char buffer[10000];
    int n;
    while ( 1 ) {
        bzero( buffer, sizeof(buffer) );
        n = 0;
        send( server_socket, requestToSend, sizeof(requestToSend), 0 );
        bzero( requestToSend, sizeof(requestToSend) );
        
        char *ptr = requestToSend;
        size_t len = sizeof(requestToSend);
        int nread;
        while ( (nread = recv( server_socket, ptr, len, 0 )) != 0 ) {
            if ( nread < 0 ) {
                printf("\nSudden Server Disconnection");
                break;
            } else {
                return;
            }
        }
    }
}

void registerMenu( void ) {
    printf("Register menu:\n(Please enter desired number)\n");
    printf("1. Sign up\n");
    printf("2. Log in\n");
    
    while ( 1 ) {
        char numberOfRegisterMenu[10];
        scanf(" %[^\n]%*c", numberOfRegisterMenu );
        
        if ( strcmp( numberOfRegisterMenu, "1" ) == 0 ) {
            printf("➤ 𝕊𝕚𝕘𝕟 𝕌𝕡\n");
            signUp();
            break;
        } else if ( strcmp( numberOfRegisterMenu, "2" ) == 0 ) {
            printf("➤ 𝕃𝕠𝕘 𝕀𝕟\n");
            logIn();
            break;
        } else {
            printf("Your entered text is invalid\nPlease try again:\n");
        }
    }
    
}

void signUp( void ) {
    char username[21] = { 0 };
    char password[21] = { 0 };
    char resultOfSignUp[500];
    signUpMenu( resultOfSignUp, username, password );
    int check;
    check = checkSignUp( resultOfSignUp );
    
    
    if ( check == 1 ) {
//        {"type":"Successful","message":""}
        printf("You signed up successfully 🙂\n");
        logInMenuBySignUp( username, password );
    } else if ( check == 0 ) {
//        {"type":"Error","message":"This username is already taken."}
        printf("Unfortunately this username is already taken 🙁\n");
        printf("Do you want to sign up again?\n(if you want please enter Yes else, enter No)\n");
        char resultOfSignUpAgain[10];
        scanf("%[^\n]%*c", resultOfSignUpAgain );
        validatingByYesNo( resultOfSignUpAgain );
        if ( strcmp(resultOfSignUpAgain, "YES") == 0 || strcmp(resultOfSignUpAgain, "Yes") == 0 || strcmp(resultOfSignUpAgain, "yes") == 0 ) {
            signUp();
        } else  if ( strcmp(resultOfSignUpAgain, "NO") == 0 || strcmp(resultOfSignUpAgain, "No") == 0 || strcmp(resultOfSignUpAgain, "no") == 0 ) {
            exit(0);
        }
        
        
    } else if ( check == -1 ) {
        printf("Unknown error 😐\nPlease try again\n");
        signUp();
    }
    
}

void signUpMenu( char resultOfSignUp[], char username[], char password[] ) {
    char messageOfSignUp[60];
    
    char sure[10] = "22";
    while ( strcmp(sure, "YES") != 0 && strcmp(sure, "Yes") != 0 && strcmp(sure, "yes") != 0 ) {
        
        usernameFunction( username, 0 );
        passwordFunction( password );
        
        printf("Are you sure about entered information?\n(if you are sure please enter Yes else, enter No)\n");
        scanf("%[^\n]%*c", sure );
        validatingByYesNo( sure );
    }
    
    sprintf( messageOfSignUp, "signup %s, %s", username, password );
    sendRequestToServer( messageOfSignUp, resultOfSignUp );
}

void usernameFunction( char username[], int specifier ) {
    while ( 1 ) {
        if ( specifier == 0 ) {
//            this function was called by signUpMenu function
            printf("Username (maximum 20 characters):\n(Please don't use enter, space and double quotation)\n");
        } else if ( specifier == 1 ) {
//            this function was called by search function
            printf("Please enter your desired username (maximum 20 characters):\n(Please don't use enter, space and double quotation)\n");
        }
        
        int specifier = 0;
        char usernameTest[22] = { 0 };
        for ( int i = 0; i < 21; ++i ) {
            scanf("%c", &usernameTest[i] );
            if ( usernameTest[i] == '\n' ) {
                usernameTest[i] = '\0';
                ++specifier;
                break;
            }
        }
        if ( specifier == 0 ) {
            scanf("%*[^\n]%*c");
        }
        
        int checkUsername;
        checkUsername = validateUsername( usernameTest );
        if ( checkUsername == -6 ) {
            printf("You violate all of username rules 😱\nPlease try again\n");
        } else if ( checkUsername == -5 ) {
            printf("You used '\"' and space 😱\nPlease try again\n");
        } else if ( checkUsername == -4 ) {
            printf("You used '\"' and more than 20 characters 😱\nPlease try again\n");
        } else if ( checkUsername == -3 ) {
            printf("You used space and more than 20 characters 😱\nPlease try again\n");
        } else if ( checkUsername == -2 ) {
            printf("You used '\"' 😱\nPlease try again\n");
        } else if ( checkUsername == -1 ) {
            printf("You used space 😱\nPlease try again\n");
        } else if ( checkUsername == 0 ) {
            printf("Your entered username is more than 20 characters 😱\nPlease try again\n");
        } else if ( checkUsername == 1 ) {
            strcpy( username, usernameTest );
            break;
        }
    }
}

int validateUsername( char usernameTest[] ) {
    if ( strchr( usernameTest, '"' ) != NULL && strchr( usernameTest, ' ' ) != NULL && strlen( usernameTest ) > 20 ) {
        return -6;
    }
    else if ( strchr( usernameTest, '"' ) != NULL && strchr( usernameTest, ' ' ) != NULL ) {
        return -5;
    } else if ( strchr( usernameTest, '"' ) != NULL && strlen( usernameTest ) > 20 ) {
        return -4;
    } else if ( strchr( usernameTest, ' ' ) != NULL && strlen( usernameTest ) > 20 ) {
        return -3;
    }
    else if ( strchr( usernameTest, '"' ) != NULL ) {
        return -2;
    } else if ( strchr( usernameTest, ' ' ) != NULL ) {
        return -1;
    } else if ( strlen( usernameTest ) > 20 ) {
        return 0;
    } else {
        return 1;
    }
}

void passwordFunction( char password[] ) {
    while ( 1 ) {
        printf("Password (maximum 20 character):\n(Please don't use enter and space)\n");
        
        int specifier = 0;
        char passwordTest[22] = { 0 };
        for ( int i = 0; i < 21; ++i ) {
            scanf("%c", &passwordTest[i] );
            if ( passwordTest[i] == '\n' ) {
                passwordTest[i] = '\0';
                ++specifier;
                break;
            }
        }
        if ( specifier == 0 ) {
            scanf("%*[^\n]%*c");
        }
        
        int checkPassword;
        checkPassword = validatePassword( passwordTest );
        if ( checkPassword == -2 ) {
            printf("You violate all of password rules 😱\nPlease try again\n");
        }  else if ( checkPassword == -1 ) {
            printf("You used space 😱\nPlease try again\n");
        }  else if ( checkPassword == 0 ) {
            printf("Your entered password is more than 20 characters 😱\nPlease try again\n");
        }  else if ( checkPassword == 1 ) {
            strcpy( password, passwordTest );
            break;
        }
    }
}

int validatePassword( char passwordTest[] ) {
    if ( strchr( passwordTest, ' ' ) != NULL && strlen( passwordTest ) > 20 ) {
        return -2;
    }
    else if ( strchr( passwordTest, ' ' ) != NULL ) {
        return -1;
    } else if ( strlen( passwordTest ) > 20 ) {
        return 0;
    }
    else {
        return 1;
    }
}

int checkSignUp( char resultOfSignUp[] ) {
    char type[11];
    char message[32];
    
    sscanf( resultOfSignUp, "%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]", type, message );
    if( strcmp( type, "Successful") == 0 ) {
//        {"type":"Successful","message":""}
        return 1;
    } else if ( strcmp( message, "This username is already taken." ) == 0 ){
//        {"type":"Error","message":"This username is already taken."}
        return 0;
    } else {
        printf("%s\n", resultOfSignUp );
        return -1;
    }
}

void logInMenuBySignUp( char username[], char password[] ) {
    char resultOfLogInBySignUp[500];
    char messageOfLogInBySignUp[50];
    
    sprintf( messageOfLogInBySignUp, "login %s, %s", username, password );
    sendRequestToServer( messageOfLogInBySignUp, resultOfLogInBySignUp );
    
    checkLogInBySignUp( resultOfLogInBySignUp );
}

void checkLogInBySignUp( char resultOfLogInBySignUp[] ) {
    char type[11];
    char message[50];
    
    sscanf( resultOfLogInBySignUp, "%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]", type, message );
    strcpy( token, message );
}

void logIn( void ) {
    char username[21];
    char password[21];
    char resultOfLogIn[500];
    logInMenu( resultOfLogIn, username, password );
    int check;
    check = checkLogIn( resultOfLogIn );
    
    
    if ( check == 1 ) {
//    {"type":"Token","message":"<token>"}
        printf("You logged in successfully 🙂\n");
    } else if ( check == 0 ) {
//    {"type":"Error","message":"Incorrect password."}
        printf("It seems your password is incorrect 🙁\nPlease try again:\n");
        logIn();
    } else if ( check == -1 ) {
//    {"type":"Error","message":"This username is not valid."}
        printf("It seems your entered username is not registered 🙁\nPlease try again:\n");
        printf("Do you want to sign up\n(if you want please enter Yes else, enter No)\n");
        char resultOfLogInAgain[10];
        scanf("%[^\n]%*c", resultOfLogInAgain );
        validatingByYesNo( resultOfLogInAgain );
        if ( strcmp(resultOfLogInAgain, "YES") == 0 || strcmp(resultOfLogInAgain, "Yes") == 0 || strcmp(resultOfLogInAgain, "yes") == 0 ) {
            signUp();
        } else if ( strcmp(resultOfLogInAgain, "NO") == 0 || strcmp(resultOfLogInAgain, "No") == 0 || strcmp(resultOfLogInAgain, "no") == 0 ) {
            printf("So please log in again");
            logIn();
        }
    } else if ( check == -2 ) {
//    {"type":"Error","message":"The user <username> is already logged in."}
        printf("It seems you logged in before 🙁\n");
        printf("Do you want to log in again?\n(if you want please enter Yes else, enter No)\n");
        char resultOfLogInAgain[10];
        scanf("%[^\n]%*c", resultOfLogInAgain );
        validatingByYesNo( resultOfLogInAgain );
        if ( strcmp(resultOfLogInAgain, "YES") == 0 || strcmp(resultOfLogInAgain, "Yes") == 0 || strcmp(resultOfLogInAgain, "yes") == 0 ) {
            logIn();
        } else if ( strcmp(resultOfLogInAgain, "NO") == 0 || strcmp(resultOfLogInAgain, "No") == 0 || strcmp(resultOfLogInAgain, "no") == 0 ) {
            exit(0);
        }
        
        
    } else if ( check == -3 ) {
        printf("Unknown error 😐\nPlease try again\n");
        logIn();
    }
    
}

void logInMenu( char resultOfLogIn[], char username[], char password[] ) {
    char messageOfLogIn[50];
    
    char sure[10] = "22";
    while ( strcmp(sure, "YES") != 0 && strcmp(sure, "Yes") != 0 && strcmp(sure, "yes") != 0 ) {
        while ( 1 ) {
            printf("Username:\n");
            
            int specifier = 0;
            char usernameTest[22] = { 0 };
            for ( int i = 0; i < 21; ++i ) {
                scanf("%c", &usernameTest[i] );
                if ( usernameTest[i] == '\n' ) {
                    usernameTest[i] = '\0';
                    ++specifier;
                    break;
                }
            }
            if ( specifier == 0 ) {
                scanf("%*[^\n]%*c");
            }
            
            int checkUsername;
            checkUsername = validateUsername( usernameTest );
            if ( checkUsername == -6 ) {
                printf("You violate all of username rules 😱\nPlease try again\n");
            } else if ( checkUsername == -5 ) {
                printf("You used '\"' and space 😱\nPlease try again\n");
            } else if ( checkUsername == -4 ) {
                printf("You used '\"' and more than 20 characters 😱\nPlease try again\n");
            } else if ( checkUsername == -3 ) {
                printf("You used space and more than 20 characters 😱\nPlease try again\n");
            } else if ( checkUsername == -2 ) {
                printf("You used '\"' 😱\nPlease try again\n");
            } else if ( checkUsername == -1 ) {
                printf("You used space 😱\nPlease try again\n");
            } else if ( checkUsername == 0 ) {
                printf("Your entered username is more than 20 characters 😱\nPlease try again\n");
            } else if ( checkUsername == 1 ) {
                strcpy( username, usernameTest );
                break;
            }
        }
        
        while ( 1 ) {
            printf("Password:\n");
            
            int specifier = 0;
            char passwordTest[22] = { 0 };
            for ( int i = 0; i < 21; ++i ) {
                scanf("%c", &passwordTest[i] );
                if ( passwordTest[i] == '\n' ) {
                    passwordTest[i] = '\0';
                    ++specifier;
                    break;
                }
            }
            if ( specifier == 0 ) {
                scanf("%*[^\n]%*c");
            }
            
            int checkPassword;
            checkPassword = validatePassword( passwordTest );
            if ( checkPassword == -2 ) {
                printf("You violate all of username rules 😱\nPlease try again\n");
            }  else if ( checkPassword == -1 ) {
                printf("You used space 😱\nPlease try again\n");
            }  else if ( checkPassword == 0 ) {
                printf("Your entered password is more than 20 characters 😱\nPlease try again\n");
            }  else if ( checkPassword == 1 ) {
                strcpy( password, passwordTest );
                break;
            }
        }
        
        printf("Are you sure about entered information?\n(if you are sure please enter Yes else, enter No)\n");
        scanf("%[^\n]%*c", sure );
        validatingByYesNo( sure );
    }
    
    sprintf( messageOfLogIn, "login %s, %s", username, password );
    sendRequestToServer( messageOfLogIn, resultOfLogIn );
}

int checkLogIn( char resultOfLogIn[] ) {
    char type[11];
    char message[50];
    
    sscanf( resultOfLogIn, "%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]", type, message );
    strcpy( token, message );
    if( strcmp( type, "Token") == 0 ) {
//    {"type":"Token","message":"<token>"}
        return 1;
    } else if ( strncmp(message, "Incorrect", 9) == 0 ) {
//    {"type":"Error","message":"Incorrect password."}
        return 0;
    } else if ( strncmp(message, "This", 4) == 0 ) {
//    {"type":"Error","message":"This username is not valid."}
        return -1;
    } else if ( strncmp(message, "The user ", 9) == 0 ){
//    {"type":"Error","message":"The user <username> is already logged in."}
        return -2;
    } else {
        printf("%s\n", resultOfLogIn );
        return -3;
    }
}

void validatingByYesNo( char shouldBeValidated[] ) {
    while ( strcmp(shouldBeValidated, "Yes") != 0 && strcmp(shouldBeValidated, "yes") != 0 && strcmp(shouldBeValidated, "YES") != 0 && strcmp(shouldBeValidated, "No") != 0 && strcmp(shouldBeValidated, "no") != 0 && strcmp(shouldBeValidated, "NO") != 0 ) {
        printf("Your entered text is invalid\nPlease try again:\n");
        scanf(" %[^\n]%*c", shouldBeValidated );
    }
}

void mainMenu( void ) {
    printf("Main menu:\n(Please enter desired number)\n");
    printf("1. TimeLine\n");
    printf("2. Search\n");
    printf("3. Tweet Profile\n");
    printf("4. Personal area\n");
    printf("5. Log out\n");
    
    while ( 1 ) {
        char numberOfMainMenu[10];
        scanf(" %[^\n]%*c", numberOfMainMenu );
        
        if ( strcmp( numberOfMainMenu, "1" ) == 0 ) {
            timeLine();
            break;
        } else if ( strcmp( numberOfMainMenu, "2" ) == 0 ) {
            printf("◎ 𝑆𝑒𝑎𝑟𝑐ℎ\n");
            search();
            break;
        } else if ( strcmp( numberOfMainMenu, "3" ) == 0 ) {
            printf("◎ 𝑇𝑤𝑒𝑒𝑡 𝑃𝑟𝑜𝑓𝑖𝑙𝑒\n");
            tweetProfile();
            break;
        } else if ( strcmp( numberOfMainMenu, "4" ) == 0 ) {
            personalArea();
            break;
        } else if ( strcmp( numberOfMainMenu, "5" ) == 0 ) {
            printf("◎ 𝐿𝑜𝑔 𝑂𝑢𝑡\n");
            char sure[10] = "22";
            printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");
            scanf("%[^\n]%*c", sure );
            validatingByYesNo( sure );
            if ( strcmp(sure, "YES") != 0 && strcmp(sure, "Yes") != 0 && strcmp(sure, "yes") != 0 ) {
                mainMenu();
            } else {
                logOut();
            }
            break;
        } else {
            printf("Your entered text is invalid\nPlease try again:\n");
        }
    }
}

void timeLine( void ) {
    printf("◎ 𝑇𝑖𝑚𝑒𝐿𝑖𝑛𝑒\n");
    printf("1. send tweet\n");
    printf("2. delete tweet\n");
    printf("3. refresh\n");
    printf("4. back to main menu\n");
    
    while ( 1 ) {
        
        char numberOfTimeLine[10];
        scanf(" %[^\n]%*c", numberOfTimeLine );
        
        if ( strcmp( numberOfTimeLine, "1" ) == 0 ) {
            printf("⏣ 𝚂𝚎𝚗𝚍 𝚃𝚠𝚎𝚎𝚝\n");
            sendTweet();
            timeLine();
        } else if ( strcmp( numberOfTimeLine, "2" ) == 0 ) {
            printf("⏣ 𝙳𝚎𝚕𝚎𝚝𝚎 𝚃𝚠𝚎𝚎𝚝\n");
            deleteTweet();
            timeLine();
        } else if ( strcmp( numberOfTimeLine, "3" ) == 0 ) {
            printf("⏣ 𝚁𝚎𝚏𝚛𝚎𝚜𝚑\n");
            refreshTweet();
            break;
        } else if ( strcmp( numberOfTimeLine, "4" ) == 0 ) {
            printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");
            char sure[10];
            scanf("%[^\n]%*c", sure );
            validatingByYesNo( sure );
            
            if ( strcmp(sure, "YES") == 0 || strcmp(sure, "Yes") == 0 || strcmp(sure, "yes") == 0 ) {
                printf("⏣ 𝙱𝚊𝚌𝚔 𝚃𝚘 𝙼𝚊𝚒𝚗 𝙼𝚎𝚗𝚞\n");
                mainMenu();
            } else if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
                timeLine();
            }
            
        } else {
            printf("Your entered text is invalid\nPlease try again:\n");
        }
    }
}

void sendTweet( void ) {
    char *messageOfSendTweet = (char *)calloc( 1000000, sizeof(char) );
    char resultOfSendTweet[1000];
    
    char sure[10] = "22";
    char tweet[1001] = { 0 };
    char tweetTest[1002] = { 0 };
    while ( strcmp(sure, "YES") != 0 && strcmp(sure, "Yes") != 0 && strcmp(sure, "yes") != 0 ) {
        printf("Please enter your tweet:\n(Unfortunately you are not able to use enter, double quotation and more than 1000 characters in your tweet :(( )\n");
        
        int specifier = 0;
        for ( int i = 0; i < 1001; ++i ) {
            scanf("%c", &tweetTest[i] );
            if ( tweetTest[i] == '\n' ) {
                tweetTest[i] = '\0';
                ++specifier;
                break;
            }
        }
        if ( specifier == 0 ) {
            scanf("%*[^\n]%*c");
        }
        
        int checkTweet;
        checkTweet = validateTweet( tweetTest );
        if ( checkTweet == -2 ) {
            printf("You used '\"' and more than 1000 characters 😱\nPlease try again\n");
            sendTweet();
        } else if ( checkTweet == -1 ) {
            printf("You used '\"' 😱\nPlease try again\n");
            sendTweet();
        } else if ( checkTweet == 0 ) {
            printf("Your entered tweet is more than 1000 characters 😱\nPlease try again\n");
            sendTweet();
        }
        strcpy( tweet, tweetTest );
        
        printf("Do you confirm your tweet?\n(if you confirm please enter Yes else, enter No)\n");
        scanf("%[^\n]%*c", sure );
        validatingByYesNo( sure );
    }
    
    sprintf( messageOfSendTweet, "send tweet %s, %s", token, tweet );
    sendRequestToServer( messageOfSendTweet, resultOfSendTweet );
    free( messageOfSendTweet );
    
    int check;
    check = checkSendTweet( resultOfSendTweet );
    if ( check == 1 ) {
        printf("Your tweet sent successfully 🙂\n");
    } else {
        printf("Unknown error 😐\nPlease try again\n");
        sendTweet();
    }
}

int validateTweet( char tweetTest[] ) {
    if ( strchr( tweetTest, '"' ) != NULL && strlen( tweetTest ) > 1000 ) {
        return -2;
    } else if ( strchr( tweetTest, '"' ) != NULL ) {
        return -1;
    } else if ( strlen( tweetTest ) > 1000 ) {
        return 0;
    } else {
        return 1;
    }
}

int checkSendTweet( char resultOfSendTweet[] ) {
    char type[11];
    char message[40];
    
    sscanf( resultOfSendTweet, "%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]", type, message );
    if( strcmp( type, "Successful") == 0 ) {
//        {"type":"Successful","message":"Tweet is sent successfully."}
        return 1;
    } else {
//                                                         new error
        printf("%s\n", resultOfSendTweet );
        return 0;
    }
}

void deleteTweet( void ) {
    printf("Please enter your desired id which you want to delete:\n");
    
    char idForDeleteATweet[20/*the same length as global id*/];
    while ( 1 ) {
        scanf(" %[^\n]%*c", idForDeleteATweet );
        
        int checkID;
        checkID = validateID( idForDeleteATweet );
        if ( checkID == 1 ) {
            break;
        } else if ( checkID == 0 ) {
            printf("Your entered id is invalid 🙁\nPlease re-enter your desired id:\n");
        }
    }
    
    printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");
    char sure[10];
    scanf("%[^\n]%*c", sure );
    validatingByYesNo( sure );
    if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
        deleteTweet();
    }
    
    char *messageOfDeleteATweet = (char *)calloc( 1000000, sizeof(char) );
    char *resultOfDeleteAtweet = (char *)calloc( 1000000, sizeof(char) );
    sprintf( messageOfDeleteATweet,"delete tweet %s, %s", token, idForDeleteATweet );
    sendRequestToServer( messageOfDeleteATweet, resultOfDeleteAtweet );
    free( messageOfDeleteATweet );
    
    int check;
    check = checkDeleteATweet( resultOfDeleteAtweet );
    free( resultOfDeleteAtweet );
    if ( check == 1 ) {
        printf("Your tweet deleted successfully 🙂\n");
    } else if ( check == 0 ) {
        printf("Your entered id is invalid 🙁\nPlease try again\n");
    } else if ( check == -1 ) {
        printf("Entered id is not for your tweets 😐\nPlease try again\n");
    } else if ( check == -2 ){
        printf("Unknown error 😐\nPlease try again\n");
    }
    
}

int validateID( char id[] ) {
    if ( strspn( id, "0123456789") == strlen( id ) && strlen( id ) != 0 ) {
        return 1;
    } else {
        return 0;
    }
}

int checkDeleteATweet( char resultOfDeleteAtweet[] ) {
    char type[11];
    char message[40];
    sscanf( resultOfDeleteAtweet, "%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]", type, message );
    
    if( strcmp( type, "Successful" ) == 0 ) {
//        {"type":"Successful","message":"Tweet %d successfully deleted."}
        return 1;
    } else if ( strcmp( message, "Tweet with this id is not available." ) == 0 ) {
//        {"type":"Error","message":"Tweet with this id is not available."}
        return 0;
    } else if ( strcmp( message, "Entered id is not for your tweets." ) == 0 ) {
//        {"type":"Error","message":"Entered id is not for your tweets."}
        return -1;
    } else {
//                                                         new error
        printf("%s\n", resultOfDeleteAtweet );
        return -2;
    }
}

void refreshTweet( void ) {
    char *messageOfRefreshTweet = (char *)calloc( 1000000, sizeof(char) );
    char *resultOfRefreshTweet = (char *)calloc( 1000000, sizeof(char) );
    
    sprintf( messageOfRefreshTweet, "refresh %s", token );
    sendRequestToServer( messageOfRefreshTweet, resultOfRefreshTweet );
    free( messageOfRefreshTweet );
    
    int check;
    check = checkRefreshTweet( resultOfRefreshTweet );
    if ( check == 1 ) {
//        {"type":"List","message":[<{"id":<id>,"author":"<username>","content":"<tweet>","comments":{"<username>":"<comment>",...},"likes":<likes>}>,...]}
        refreshTweetMenu( resultOfRefreshTweet );
        free( resultOfRefreshTweet );
    } else {
//                                                               new error
        printf("Unknown error 😐\nPlease try again\n");
        free( resultOfRefreshTweet );
        timeLine();
    }
    
}

int checkRefreshTweet( char resultOfRefreshTweet[] ) {
    char type[11];
    sscanf( resultOfRefreshTweet, "%*[^:]:\"%[^\"]", type );
    
    if( strcmp( type, "List") == 0 ) {
//        {"type":"List","message":[<{"id":<id>,"author":"<username>","content":"<tweet>","comments":{"<username>":"<comment>",...},"likes":<likes>}>,...]}
        return 1;
    } else {
//                                                               new error
        printf("%s\n", resultOfRefreshTweet );
        return 0;
    }
}

int countLikes[100];
void refreshTweetMenu( char resultOfRefreshTweet[] ) {
    for ( int j = 0; j < 100; ++j ) {
        countLikes[j] = 0;
    }
    
    int numberOfUsers;
    numberOfUsers = findShowDetails( resultOfRefreshTweet );
    
    if ( numberOfUsers == 0 ) {
        printf("1. Back to timeline\n");
        
        while ( 1 ) {
            char numberOfRefreshTweetMenu[10];
            scanf(" %[^\n]%*c", numberOfRefreshTweetMenu );
            
            if ( strcmp( numberOfRefreshTweetMenu, "1" ) == 0 ) {
                printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");
                char sure[10];
                scanf("%[^\n]%*c", sure );
                validatingByYesNo( sure );
                
                if ( strcmp(sure, "YES") == 0 || strcmp(sure, "Yes") == 0 || strcmp(sure, "yes") == 0 ) {
                    printf("⟿ 𝘽𝙖𝙘𝙠 𝙏𝙤 𝙏𝙞𝙢𝙚𝙇𝙞𝙣𝙚\n");
                    timeLine();
                } else if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
                    printf("Please re-enter your desired number:\n");
                }
                
            } else {
                printf("Your entered text is invalid\nPlease try again:\n");
            }
        }
        
    } else {
        printf("1. More options\n");
        printf("2. Back to timeline\n");
        
        while ( 1 ) {
            char numberOfRefreshTweetMenu[10];
            scanf(" %[^\n]%*c", numberOfRefreshTweetMenu );
            
            if ( strcmp( numberOfRefreshTweetMenu, "1" ) == 0 ) {
                moreOptions();
                break;
            } else if ( strcmp( numberOfRefreshTweetMenu, "2" ) == 0 ) {
                printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");
                char sure[10];
                scanf("%[^\n]%*c", sure );
                validatingByYesNo( sure );
                
                if ( strcmp(sure, "YES") == 0 || strcmp(sure, "Yes") == 0 || strcmp(sure, "yes") == 0 ) {
                    printf("⟿ 𝘽𝙖𝙘𝙠 𝙏𝙤 𝙏𝙞𝙢𝙚𝙇𝙞𝙣𝙚\n");
                    timeLine();
                } else if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
                    printf("Please re-enter your desired number:\n");
                }
                
            } else {
                printf("Your entered text is invalid\nPlease try again:\n");
            }
        }
        
    }
    
}

//    limit of users to show in refresh is 99 which is shown in string's first dimension (it's compitable with comments string)
char comments[100][50100];
char id[100][20/*limit of legth of each user's id*/];

int numberOfUsers;
int numberOfCommentsOfEachUser[100] = { 0 };
int findShowDetails( char resultOfRefreshTweet[] ) {
    numberOfUsers = 0;
    char type[11];
    
//    limit of users to show in refresh is 99 which is shown in string's first dimension (it's compitable for comments string)
//    char id[1000][20/*limit of legth of each user's id*/];( main place, it changes because of seeCommentsOfATweet function )
    char author[100][21/*the same length as username*/];
    char **content = (char **)calloc( 100, sizeof(char *) );
    for ( int i = 0; i < 100; ++i ) {
        content[i] = (char *)calloc( 1001/*the same length as tweet*/, sizeof(char) );
    }
            
    char likes[100][6/*limit of length of likes*/];
    
    char *resultOfRefreshTweetCopy = (char *)calloc( 1000000, sizeof(char) );
    strcpy( resultOfRefreshTweetCopy, resultOfRefreshTweet );
    sscanf( resultOfRefreshTweetCopy, "%*[^:]:\"%[^\"]%*[^{]", type );
    unsigned long int firstLength = strlen( type ) + 22;
    int mainLength = 0;
    for ( int j = 0; j < firstLength; ++j ) {
        resultOfRefreshTweetCopy[mainLength + j] = '0';
    }
    mainLength += firstLength;
    
//    int numberOfUsers = 0;( main place is here, it changes because of seeCommentsOfATweet function )
    char specifier;
    char sscanfUse[10] = { 0 };
    sprintf( sscanfUse, "%%*%lus%%c", firstLength );
    sscanf( resultOfRefreshTweetCopy, sscanfUse, &specifier );
    
    for ( int i = 0; specifier != ']' && i < 100; ++i ) {
        sscanf( resultOfRefreshTweetCopy, "%*[^:]:%[^,]%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]%*[^{]%[^}]%*[^:]:%[^}]}%c", id[i], author[i], content[i], comments[i], likes[i], &specifier );
        unsigned long int secondLength = strlen( id[i] ) + strlen( author[i] ) + strlen( content[i] ) + strlen( comments[i] ) + strlen( likes[i] ) + 54;
        
        for ( int j = 0; j < secondLength; ++j ) {
            resultOfRefreshTweetCopy[mainLength + j] = '0';
        }
        mainLength += secondLength;
        numberOfUsers = i + 1;
    }
    free( resultOfRefreshTweetCopy );
    
    for ( int j = 0; j < numberOfUsers; ++j ) {
        strcat( comments[j], "}" );
    }
    
    
    if ( numberOfUsers == 0 ) {
        printf("There's not any new tweet to show 😕\n\n");
        return numberOfUsers;
    } else {
//        int numberOfCommentsOfEachUser[1000] = { 0 };( main place, it changes because of seeCommentsOfATweet function )
        
        findNumberOfCommentsOfEachUser( numberOfCommentsOfEachUser, numberOfUsers );
        findDetailsOfCommentsOfEachUser( numberOfCommentsOfEachUser, numberOfUsers );
        showDetails( id, author, content, numberOfCommentsOfEachUser, likes, numberOfUsers );
        
        return numberOfUsers;
    }
    
    
}

char commentsCopy[100][50100];
void findNumberOfCommentsOfEachUser( int numberOfCommentsOfEachUser[], int numberOfUsers ) {
    for (int j = 0; j < numberOfUsers; ++j ) {
        strcpy( commentsCopy[j], comments[j] );
    }
    
    char specifier;
    for ( int j = 0; j < numberOfUsers; ++j ) {
        sscanf( commentsCopy[j], "{%c", &specifier );
        
        while ( specifier != '}' ) {
            sscanf( commentsCopy[j], "%*[^,|}]%c", &specifier );
            *strpbrk( commentsCopy[j], ",}") = '0';
            ++numberOfCommentsOfEachUser[j];
        }
        
    }
}

char nameofCommentsOfEachUser[100/*limit of users to show in refresh is 99*/][100/*limit of comments' number is 99*/][21/*the same length as username*/] = { 0 };
char commentsOfEachUser[100/*limit of users to show in refresh is 99*/][100/*limit of comments' number is 99*/][501/*limit of comments' length is 500 (the same length as comment in commentATweet function*/] = { 0 };
void findDetailsOfCommentsOfEachUser( int numberOfCommentsOfEachUser[], int numberOfUsers ) {
    for (int j = 0; j < numberOfUsers; ++j ) {
        strcpy( commentsCopy[j], comments[j] );
    }
    
    for ( int j = 0; j < numberOfUsers; ++j ) {
        if ( numberOfCommentsOfEachUser[j] != 0 ) {
            
            
            int i;
            int mainLength = 0;
            for ( i = 0; i < numberOfCommentsOfEachUser[j]; ++i ) {
                sscanf( commentsCopy[j], "%*[^\"]\"%[^\"]\" %*[^\"]\"%[^\"]\"", nameofCommentsOfEachUser[j][i], commentsOfEachUser[j][i] );
                
                unsigned long int length = strlen( nameofCommentsOfEachUser[j][i] ) + strlen( commentsOfEachUser[j][i] ) + 6;
                for ( int k = 0; k < length; ++k ) {
                    commentsCopy[j][mainLength + k] = '0';
                }
                mainLength += length;
            }
            
            
        }
    }
}

void showDetails( char id[][20], char author[][21], char **content, int numberOfCommentsOfEachUser[], char likes[][6], int numberOfUsers ) {
    for (int j = 0; j < numberOfUsers; ++j ) {
        printf("⥛ 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞: %s\n", author[j] );
        printf("⥛ 𝐈𝐃: %s\n", id[j] );
        printf("⇰ 𝐓𝐰𝐞𝐞𝐭: %s\n", content[j] );
        printf("𝐋𝐢𝐤𝐞𝐬: %s  𝐂𝐨𝐦𝐦𝐞𝐧𝐭𝐬: %d\n\n\n", likes[j], numberOfCommentsOfEachUser[j] );
    }
    
    for ( int i = 0; i < 100; ++i ) {
        free( content[i] );
    }
    free( content );
}

void moreOptions( void ) {
    printf("⟿ 𝙈𝙤𝙧𝙚 𝙊𝙥𝙩𝙞𝙤𝙣𝙨\n");
    printf("1. Like a tweet\n");
    printf("2. Comment a tweet\n");
    printf("3. See comments of a tweet\n");
    printf("4. Back to refresh\n");
    
    while ( 1 ) {
        char numberOfMoreOptions[10];
        scanf(" %[^\n]%*c", numberOfMoreOptions );
        
        if ( strcmp( numberOfMoreOptions, "1" ) == 0 ) {
            printf("⟿ 𝙇𝙞𝙠𝙚 𝘼 𝙏𝙬𝙚𝙚𝙩\n");
            likeATweet();
            moreOptions();
        } else if ( strcmp( numberOfMoreOptions, "2" ) == 0 ) {
            printf("⟿ 𝘾𝙤𝙢𝙢𝙚𝙣𝙩 𝘼 𝙏𝙬𝙚𝙚𝙩\n");
            commentATweet();
            moreOptions();
        } else if ( strcmp( numberOfMoreOptions, "3" ) == 0 ) {
            printf("⟿ 𝙎𝙚𝙚 𝘾𝙤𝙢𝙢𝙚𝙣𝙩𝙨 𝙊𝙛 𝘼 𝙏𝙬𝙚𝙚𝙩\n");
            seeCommentsOfATweet();
            printf("Please press enter to continue...\n");
            scanf("%*[^\n]%*c");
            moreOptions();
        } else if ( strcmp( numberOfMoreOptions, "4" ) == 0 ) {
            printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");
            char sure[10];
            scanf("%[^\n]%*c", sure );
            validatingByYesNo( sure );
            
            if ( strcmp(sure, "YES") == 0 || strcmp(sure, "Yes") == 0 || strcmp(sure, "yes") == 0 ) {
                printf("⟿ 𝘽𝙖𝙘𝙠 𝙏𝙤 𝙍𝙚𝙛𝙧𝙚𝙨𝙝\n");
                refreshTweet();
            } else if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
                printf("Please re-enter your desired number:\n");
            }
            
        } else {
            printf("Your entered text is invalid\nPlease try again:\n");
        }
    }
}

void likeATweet( void ) {
    printf("Please enter your desired id which you want to like:\n");
    
    char idForLikeATweet[20/*the same length as global id*/];
    while ( 1 ) {
        scanf(" %[^\n]%*c", idForLikeATweet );
        
        int checkID;
        checkID = validateID( idForLikeATweet );
        if ( checkID == 1 ) {
            break;
        } else if ( checkID == 0 ) {
            printf("Your entered id is invalid 🙁\nPlease re-enter your desired id:\n");
        }
    }
    
    printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");
    char sure[10];
    scanf("%[^\n]%*c", sure );
    validatingByYesNo( sure );
    if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
        likeATweet();
    }
    
    int j;
    for ( j = 0; j < numberOfUsers; ++j ) {
        if ( strcmp( id[j], idForLikeATweet ) == 0 ) {
            ++countLikes[j];
            break;
        }
    }
    
    if ( countLikes[j] > 1 ) {
        printf("You liked this tweet before 🙁\nPlease try again\n");
        moreOptions();
    } else {
        char *messageOfLikeATweet = (char *)calloc( 1000000, sizeof(char) );
        char *resultOfLikeAtweet = (char *)calloc( 1000000, sizeof(char) );
        sprintf( messageOfLikeATweet,"like %s, %s", token, idForLikeATweet );
        sendRequestToServer( messageOfLikeATweet, resultOfLikeAtweet );
        free( messageOfLikeATweet );
        
        int check;
        check = checkLikeATweet( resultOfLikeAtweet );
        free( resultOfLikeAtweet );
        if ( check == 1 ) {
            printf("Your like registered successfully 🙂\n");
        } else if ( check == 0 ) {
            printf("Your entered id is invalid 🙁\n(Maybe author of the tweet has deleted it)\nPlease try again\n");
            moreOptions();
        } else if ( check == -1 ){
            printf("Unknown error 😐\nPlease try again\n");
            moreOptions();
        }
    }
    
}

int checkLikeATweet( char resultOfLikeAtweet[] ) {
    char type[11];
    char message[40];
    sscanf( resultOfLikeAtweet, "%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]", type, message );
    
    if( strcmp( type, "Successful" ) == 0 ) {
//        {"type":"Successful","message":"Tweet <id> successfully liked."}
        return 1;
    } else if ( strcmp( message, "Tweet with this id is not available." ) == 0 ) {
//        {"type":"Error","message":"Tweet with this id is not available."}
        return 0;
    } else {
//                                                         new error
        printf("%s\n", resultOfLikeAtweet );
        return -1;
    }
}

void commentATweet( void ) {
    char idForCommentATweet[20/*the same length as id in findShowDetails function*/];
    while ( 1 ) {
        printf("Please enter your desired id which you want to comment:\n");
        scanf("%[^\n]%*c", idForCommentATweet );
        
        int checkID;
        checkID = validateID( idForCommentATweet );
        if ( checkID == 1 ) {
            break;
        } else if ( checkID == 0 ) {
            printf("Your entered id is invalid\nPlease re-enter your desired id:\n");
        }
    }
    
    char comment[501/*limit of comments' length is 500*/] = { 0 };
    char commentTest[502] = { 0 };
    while ( 1 ) {
        printf("Please enter your comment:\n(Unfortunately you are not able to use enter, double quotation, comma, right curly bracket ( } ) and more than 500 characters in your comment :(( )\n");
        
        int specifier = 0;
        for ( int i = 0; i < 501; ++i ) {
            scanf("%c", &commentTest[i] );
            if ( commentTest[i] == '\n' ) {
                commentTest[i] = '\0';
                ++specifier;
                break;
            }
        }
        if ( specifier == 0 ) {
            scanf("%*[^\n]%*c");
        }
        
        int checkComment;
        checkComment = validateComment( commentTest );
        if ( checkComment == -14 ) {
            printf("You violate all of comment rules 😱\nPlease try again:\n");
        }
        else if ( checkComment == -13 ) {
            printf("You used '\"', ',' and '}' 😱\nPlease try again:\n");
        } else if ( checkComment == -12 ) {
            printf("You used '\"', ',' and more than 500 characters 😱\nPlease try again:\n");
        } else if ( checkComment == -11 ) {
            printf("You used '\"', '}' and more than 500 characters 😱\nPlease try again:\n");
        } else if ( checkComment == -10 ) {
            printf("You used ',', '}' and more than 500 characters 😱\nPlease try again:\n");
        }
        else if ( checkComment == -9 ) {
            printf("You used '\"' and ',' 😱\nPlease try again:\n");
        } else if ( checkComment == -8 ) {
            printf("You used '\"' and '}' 😱\nPlease try again:\n");
        } else if ( checkComment == -7 ) {
            printf("You used '\"' and more than 500 characters 😱\nPlease try again:\n");
        } else if ( checkComment == -6 ) {
            printf("You used ',' and '}' 😱\nPlease try again:\n");
        } else if ( checkComment == -5 ) {
            printf("You used ',' and more than 500 characters 😱\nPlease try again:\n");
        } else if ( checkComment == -4 ) {
            printf("You used '}' and more than 500 characters 😱\nPlease try again:\n");
        }
        else if ( checkComment == -3 ) {
            printf("You used '\"' 😱\nPlease try again:\n");
        } else if ( checkComment == -2 ) {
            printf("You used ',' 😱\nPlease try again:\n");
        } else if ( checkComment == -1 ) {
            printf("You used '}' 😱\nPlease try again:\n");
        } else if ( checkComment == 0 ) {
            printf("Your entered comment is more than 500 characters 😱\nPlease try again:\n");
        }
        else if ( checkComment == 1 ) {
            break;
        }
    }
    strcpy( comment, commentTest );
    
    printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");
    char sure[10];
    scanf("%[^\n]%*c", sure );
    validatingByYesNo( sure );
    if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
        commentATweet();
    }
    
    char *messageOfCommentATweet = (char *)calloc( 1000000, sizeof(char) );
    char *resultOfCommentAtweet = (char *)calloc( 1000000, sizeof(char) );
    sprintf( messageOfCommentATweet,"comment %s, %s, %s", token, idForCommentATweet, comment );
    sendRequestToServer( messageOfCommentATweet, resultOfCommentAtweet );
    free( messageOfCommentATweet );
    
    int check;
    check = checkCommentATweet( resultOfCommentAtweet );
    free( resultOfCommentAtweet );
    if ( check == 1 ) {
        printf("Your comment registers successfully 🙂\n");
    } else if ( check == 0 ) {
        printf("Your entered id is invalid 🙁\n(Maybe author of the tweet has deleted it)\nPlease try again\n");
        commentATweet();
    } else if ( check == -1 ){
        printf("Unknown error 😐\n");
        commentATweet();
    }
}

int validateComment( char commentTest[] ) {
    if ( strchr( commentTest, '"' ) != NULL && strchr( commentTest, ',' ) != NULL && strchr( commentTest, '}' ) != NULL && strlen( commentTest ) > 500 ) {
        return -14;
    }
    else if ( strchr( commentTest, '"' ) != NULL && strchr( commentTest, ',' ) != NULL && strchr( commentTest, '}' ) != NULL ) {
        return -13;
    } else if ( strchr( commentTest, '"' ) != NULL && strchr( commentTest, ',' ) != NULL && strlen( commentTest ) > 500 ) {
        return -12;
    } else if ( strchr( commentTest, '"' ) != NULL && strchr( commentTest, '}' ) != NULL && strlen( commentTest ) > 500 ) {
        return -11;
    } else if ( strchr( commentTest, ',' ) != NULL && strchr( commentTest, '}' ) != NULL && strlen( commentTest ) > 500 ) {
        return -10;
    }
    else if ( strchr( commentTest, '"' ) != NULL && strchr( commentTest, ',' ) != NULL ) {
        return -9;
    } else if ( strchr( commentTest, '"' ) != NULL && strchr( commentTest, '}' ) != NULL ) {
        return -8;
    } else if ( strchr( commentTest, '"' ) != NULL && strlen( commentTest ) > 500 ) {
        return -7;
    } else if ( strchr( commentTest, ',' ) != NULL && strchr( commentTest, '}' ) != NULL ) {
        return -6;
    } else if ( strchr( commentTest, ',' ) != NULL && strlen( commentTest ) > 500 ) {
        return -5;
    } else if ( strchr( commentTest, '}' ) != NULL && strlen( commentTest ) > 500 ) {
        return -4;
    }
    else if ( strchr( commentTest, '"' ) != NULL ) {
        return -3;
    } else if ( strchr( commentTest, ',' ) != NULL ) {
        return -2;
    } else if ( strchr( commentTest, '}' ) != NULL ) {
        return -1;
    } else if ( strlen( commentTest ) > 500 ) {
        return 0;
    }
    else {
        return 1;
    }
}

int checkCommentATweet( char resultOfCommentAtweet[] ) {
    char type[11];
    char message[40];
    sscanf( resultOfCommentAtweet, "%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]", type, message );
    
    if( strcmp( type, "Successful") == 0 ) {
//        {"type":"Successful","message":"Comment is sent successfully."}
        return 1;
    } else if ( strcmp( message, "Tweet with this id is not available." ) == 0 ){
//        {"type":"Error","message":"Tweet with this id is not available."}
        return 0;
    } else {
//                                                         new error
        printf("%s\n", resultOfCommentAtweet );
        return -1;
    }
}

void seeCommentsOfATweet( void ) {
    printf("Please enter your desired id which you want to see its comments:\n");
    
    char idForSeeCommentsOfATweet[20/*the same length as global id*/];
    while ( 1 ) {
        scanf("%[^\n]%*c", idForSeeCommentsOfATweet );
        
        int checkID;
        checkID = validateID( idForSeeCommentsOfATweet );
        if ( checkID == 1 ) {
            break;
        } else if ( checkID == 0 ) {
            printf("Your entered id is invalid\nPlease re-enter your desired id:\n");
        }
    }
    
    printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");
    char sure[10];
    scanf("%[^\n]%*c", sure );
    validatingByYesNo( sure );
    if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
        seeCommentsOfATweet();
    }
    
    int slightlyIndex = -1;
    for ( int j = 0; j < numberOfUsers; ++j ) {
        if ( strcmp( id[j], idForSeeCommentsOfATweet ) == 0 ) {
            slightlyIndex = j;
            break;
        }
    }
    
    if ( slightlyIndex == -1 ) {
        printf("Your entered id is invalid\n");
        seeCommentsOfATweet();
    }else if ( numberOfCommentsOfEachUser[slightlyIndex] == 0 ) {
        printf("There's not any comment to show 😕\n");
    } else {
        for ( int j = 0; j < numberOfCommentsOfEachUser[slightlyIndex]; ++j ) {
            printf("%s: %s\n", nameofCommentsOfEachUser[slightlyIndex][j], commentsOfEachUser[slightlyIndex][j] );
        }
    }
    
}

void search( void ) {
    char clientSearch[21/*the same length as username*/];
    while ( 1 ) {
        usernameFunction( clientSearch, 1 );
        
        printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");
        char sure[10];
        scanf("%[^\n]%*c", sure );
        validatingByYesNo( sure );
        if ( strcmp(sure, "YES") == 0 || strcmp(sure, "Yes") == 0 || strcmp(sure, "yes") == 0 ) {
            break;
        }
    }
    
    char *messageOfSearch = (char *)calloc( 80, sizeof(char) );
    char *resultOfSearch = (char *)calloc( 1000000, sizeof(char) );
    
    sprintf( messageOfSearch, "search %s, %s", token, clientSearch );
    sendRequestToServer( messageOfSearch, resultOfSearch );
    free( messageOfSearch );
    
    int check;
    check = checkSearch( resultOfSearch );
    if ( check == 1 ) {
//        {"type":"Profile","message":{"username":"<username>","bio":"<biography>","numberOfFollowers":<numberOfFollowers>,"numberOfFollowings":<numberOfFollowings>,"followStatus":"<Followed/NotFollowed>","allTweets":[<{"id":<id>,"author":"<username>","content":"<tweet>","comments":{"<username>":"<comment>",...},"likes":<likes>}>,...]}}
        findShowDetailsInSearch( resultOfSearch );
        free( resultOfSearch );
        printf("Please press enter to continue...\n");
        scanf("%*[^\n]%*c");
        changeFollowStatus();
    } else if ( check == 0 ){
//        {"type":"Error","message":"This username is not valid."}
        free( resultOfSearch );
        printf("Your entered username was not found 🙁\n");
        errorOfSearch();
    } else if ( check == -1 ) {
//        {"type":"Error","message":"Searched username is your username."}
        free( resultOfSearch );
        printf("Searched username is your username 😱\n");
        errorOfSearch();
    } else if ( check == -2 ){
        free( resultOfSearch );
        printf("Unknown error 😐\n");
        errorOfSearch();
    }
    
    
}

int checkSearch( char resultOfSearch[] ) {
    char type[11];
    char *message = (char *)calloc( 1000000, sizeof(char) );
    
    sscanf( resultOfSearch, "%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]", type, message );
    if( strcmp( type, "Profile") == 0 ) {
//        {"type":"Profile","message":{"username":"<username>","bio":"<biography>","numberOfFollowers":<numberOfFollowers>,"numberOfFollowings":<numberOfFollowings>,"followStatus":"<Followed/NotFollowed>","allTweets":[<{"id":<id>,"author":"<username>","content":"<tweet>","comments":{"<username>":"<comment>",...},"likes":<likes>}>,...]}}
        free( message );
        return 1;
    } else if ( strcmp( message, "This username is not valid." ) == 0 ) {
//        {"type":"Error","message":"This username is not valid."}
        free( message );
        return 0;
    } else if ( strcmp( message, "Searched username is your username." ) == 0 ) {
//        {"type":"Error","message":"Searched username is your username."}
        free( message );
        return -1;
    } else {
        printf("%s\n", resultOfSearch );
        free( message );
        return -2;
    }
}

void errorOfSearch( void ) {
    printf("1. Search again\n");
    printf("2. Back to main menu\n");
    
    while ( 1 ) {
        char numberOfErrorOfSearch[10];
        scanf(" %[^\n]%*c", numberOfErrorOfSearch );
        
        if ( strcmp( numberOfErrorOfSearch, "1" ) == 0 ) {
            printf("※ 𝙎𝙚𝙖𝙧𝙘𝙝 𝘼𝙜𝙖𝙞𝙣\n");
            search();
        } else if ( strcmp( numberOfErrorOfSearch, "2" ) == 0 ) {
            printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");//                        maybe comment (delete) it
            char sure[10];
            scanf("%[^\n]%*c", sure );
            validatingByYesNo( sure );
            
            if ( strcmp(sure, "YES") == 0 || strcmp(sure, "Yes") == 0 || strcmp(sure, "yes") == 0 ) {
                printf("※ 𝘽𝙖𝙘𝙠 𝙏𝙤 𝙈𝙖𝙞𝙣 𝙈𝙚𝙣𝙪\n");
                mainMenu();
            } else if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
                errorOfSearch();
            }
            
        } else {
            printf("Your entered text is invalid\nPlease try again:\n");
        }
    }
    
}

char usernameInSearch[21/*the same length as username*/];
char followStatus[15];
char allTweets[300000/*101(limit of number of each person's tweet) * 1001(the same length as tweet) + X(unusable characters)*/] = { 0 };
void findShowDetailsInSearch( char resultOfSearch[] ) {
//    char usernameInSearch[21/*the same length as username*/];( main place, it changes because of followUnfollow function )
    char bio[501/*the same length as biography*/] = { 0 };
    char numberOfFollowers[20/*limit of legth of each user's followers*/];
    char numberOfFollowings[20/*limit of legth of each user's followings*/];
//    char followStatus[15];( main place, it changes because of changeFollowStatus function )
//    char allTweets[300000/*101(limit of number of each person's tweet) * 1001(the same length as tweet) + X(unusable characters)*/] = { 0 };( main place, it changes because of findShowDetailsOfCommentsInSearch function )
    
    sscanf( resultOfSearch, "%*[^:]:%*[^:]:%*[^:]:%*[^:]:\"%[^\"]", bio );
    if ( bio[0] == '\0' ) {
        sscanf( resultOfSearch, "%*[^:]:%*[^:]:%*[^:]:\"%[^\"]%*[^:]:\"%[^,]%*[^:]:%[^,]%*[^:]:%[^,]%*[^:]:\"%[^\"]%*[^:]:%[^]]", usernameInSearch, bio, numberOfFollowers, numberOfFollowings, followStatus, allTweets );
        bio[0] = '\0';
    } else {
        sscanf( resultOfSearch, "%*[^:]:%*[^:]:%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]%*[^:]:%[^,]%*[^:]:%[^,]%*[^:]:\"%[^\"]%*[^:]:%[^]]", usernameInSearch, bio, numberOfFollowers, numberOfFollowings, followStatus, allTweets );
    }
    strcat( allTweets, "]" );
    
    findShowDetailsOfCommentsInSearch( usernameInSearch, bio, numberOfFollowers, numberOfFollowings, followStatus );
}

char commentsInSearch[100][50100];
void findShowDetailsOfCommentsInSearch( char usernameInSearch[], char bio[], char numberOfFollowers[], char numberOfFollowings[], char followStatus[] ) {//the same function as findShowDetails function
//    limit of users to show in refresh is 99 which is shown in string's first dimension (it's compitable for comments string)
    char idInSearch[100][20/*limit of legth of each user's id*/];
    char authorInSearch[100][21/*the same length as username*/];
    char contentInSearch[100][1001/*the same length as tweet*/];
    char likesInSearch[100][6/*limit of length of likes*/];
    
    char allTweetsCopy[300000];
    strcpy( allTweetsCopy, allTweets );
    unsigned long int mainLength = 1;
    allTweetsCopy[0] = '0';

    int numberOfTweets = 0;
    char specifier;
    char sscanfUse[10] = { 0 };
    sprintf( sscanfUse, "%%*%lus%%c", mainLength );
    sscanf( allTweetsCopy, sscanfUse, &specifier );
    
    for ( int i = 0; specifier != ']' && i < 100; ++i ) {
        sscanf( allTweetsCopy, "%*[^:]:%[^,]%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]%*[^{]%[^}]%*[^:]:%[^}]}%c", idInSearch[i], authorInSearch[i], contentInSearch[i], commentsInSearch[i], likesInSearch[i], &specifier );
        unsigned long int secondLength = strlen( idInSearch[i] ) + strlen( authorInSearch[i] ) + strlen( contentInSearch[i] ) + strlen( commentsInSearch[i] ) + strlen( likesInSearch[i] ) + 54;
        
        for ( int j = 0; j < secondLength; ++j ) {
            allTweetsCopy[mainLength + j] = '0';
        }
        mainLength += secondLength;
        numberOfTweets = i + 1;
    }
    
    for ( int j = 0; j < numberOfTweets; ++j ) {
        strcat( commentsInSearch[j], "}" );
    }
    
    int numberOfCommentsOfEachTweet[100] = { 0 };
    
    findNumberOfCommentsOfEachTweet( numberOfCommentsOfEachTweet, numberOfTweets );
    showDetailsInSearch( usernameInSearch, bio, numberOfFollowers, numberOfFollowings, followStatus, contentInSearch, likesInSearch, numberOfTweets, numberOfCommentsOfEachTweet );
    
}

char commentsInSearchCopy[100][50100];
void findNumberOfCommentsOfEachTweet( int numberOfCommentsOfEachTweet[], int numberOfTweets ) {//the samae function as findNumberOfCommentsOfEachUser function
    for (int j = 0; j < numberOfTweets; ++j ) {
        strcpy(commentsInSearchCopy[j], commentsInSearch[j]);
    }
    
    char specifier;
    for ( int j = 0; j < numberOfTweets; ++j ) {
        sscanf( commentsInSearchCopy[j], "{%c", &specifier );
        
        while ( specifier != '}' ) {
            sscanf( commentsInSearchCopy[j], "%*[^,|}]%c", &specifier );
            *strpbrk( commentsInSearchCopy[j], ",}") = '0';
            ++numberOfCommentsOfEachTweet[j];
        }
        
    }
}

void showDetailsInSearch( char usernameInSearch[], char bio[], char numberOfFollowers[], char numberOfFollowings[], char followStatus[], char contentInSearch[][1001], char likesInSearch[][6], int numberOfTweets, int numberOfCommentsOfEachTweet[] ) {
    printf("⁍ 𝘜𝘴𝘦𝘳𝘯𝘢𝘮𝘦: %s\n", usernameInSearch );
    if ( bio[0] == '\0' ) {
        printf("⁍ 𝘉𝘪𝘰:\n");
    } else {
        printf("⁍ 𝘉𝘪𝘰: %s\n", bio );
    }
    printf("𝘍𝘰𝘭𝘭𝘰𝘸𝘦𝘳𝘴: %s  𝘍𝘰𝘭𝘭𝘰𝘸𝘪𝘯𝘨𝘴: %s\n", numberOfFollowers, numberOfFollowings );
    printf("⁍ 𝘍𝘰𝘭𝘭𝘰𝘸 𝘚𝘵𝘢𝘵𝘶𝘴: %s\n\n", followStatus );
    printf("⁍ 𝘛𝘸𝘦𝘦𝘵𝘴:\n");
    if ( numberOfTweets != 0 ) {
        for ( int j = 0; j < numberOfTweets; ++j) {
            printf("%s\n", contentInSearch[j] );
            printf("𝘓𝘪𝘬𝘦𝘴: %s  𝘊𝘰𝘮𝘮𝘦𝘯𝘵𝘴: %d\n", likesInSearch[j], numberOfCommentsOfEachTweet[j] );
        }
    } else {
        printf("There's not any tweet to show 😕\n");
    }
    
}

void changeFollowStatus( void ) {
    int specifier = -1;
    if ( strcmp( followStatus, "NotFollowed" ) == 0 ) {
        printf("1. Follow %s\n", usernameInSearch );
        specifier = 0;
    } else if ( strcmp( followStatus, "Followed" ) == 0 ) {
        printf("1. Unfollow %s\n", usernameInSearch );
        specifier = 1;
    }
    printf("2. Search again\n");
    printf("3. Back to main menu\n");
    
    while ( 1 ) {
        char numberOfErrorOfSearch[10];
        scanf(" %[^\n]%*c", numberOfErrorOfSearch );
        
        if ( strcmp( numberOfErrorOfSearch, "1" ) == 0 ) {
            
            printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");//                        maybe comment (delete) it
            char sure[10];
            scanf("%[^\n]%*c", sure );
            validatingByYesNo( sure );
            
            if ( strcmp(sure, "YES") == 0 || strcmp(sure, "Yes") == 0 || strcmp(sure, "yes") == 0 ) {
                followUnfollow( specifier );
                errorOfSearch();
            } else if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
                printf("Please enter desired number again:\n");
            }
            
        } else if ( strcmp( numberOfErrorOfSearch, "2" ) == 0 ) {
            printf("※ 𝙎𝙚𝙖𝙧𝙘𝙝 𝘼𝙜𝙖𝙞𝙣\n");
            search();
        } else if ( strcmp( numberOfErrorOfSearch, "3" ) == 0 ) {
            printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");//                        maybe comment (delete) it
            char sure[10];
            scanf("%[^\n]%*c", sure );
            validatingByYesNo( sure );
            
            if ( strcmp(sure, "YES") == 0 || strcmp(sure, "Yes") == 0 || strcmp(sure, "yes") == 0 ) {
                printf("※ 𝘽𝙖𝙘𝙠 𝙏𝙤 𝙈𝙖𝙞𝙣 𝙈𝙚𝙣𝙪\n");
                mainMenu();
            } else if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
                changeFollowStatus();
            }
            
        } else {
            printf("Your entered text is invalid\nPlease try again:\n");
        }
    }
    
}

void followUnfollow( int specifier ) {
    char *messageOfFollow = (char *)calloc( 1000000, sizeof(char) );
    char *resultOfFollow = (char *)calloc( 1000000, sizeof(char) );
    if ( specifier == 0 ) {
        sprintf( messageOfFollow, "follow %s, %s", token, usernameInSearch );
        sendRequestToServer( messageOfFollow, resultOfFollow );
        free( messageOfFollow );
        free( resultOfFollow );
        printf("You followed %s successfully 🙂\n", usernameInSearch );
    } else if ( specifier == 1 ) {
        sprintf( messageOfFollow, "unfollow %s, %s", token, usernameInSearch );
        sendRequestToServer( messageOfFollow, resultOfFollow );
        free( messageOfFollow );
        free( resultOfFollow );
        printf("You unfollowed %s successfully 🙂\n", usernameInSearch );
    } else if ( specifier == -1 ) {
        printf("Unknown error 😐\n");
    }
}

void tweetProfile ( void ) {
    char *messageOfTweetProfile = (char *)calloc( 1000000, sizeof(char) );
    char *resultOfTweetProfile = (char *)calloc( 1000000, sizeof(char) );

    sprintf( messageOfTweetProfile, "profile %s", token );
    sendRequestToServer( messageOfTweetProfile, resultOfTweetProfile);
    free( messageOfTweetProfile );

    findShowDetailsInTweetProfile( resultOfTweetProfile );
    free( resultOfTweetProfile );
    
    printf("Please press enter to back to main menu\n");
    scanf("%*[^\n]%*c");
    printf("✦ 𝖡𝖺𝖼𝗄 𝖳𝗈 𝖬𝖺𝗂𝗇 𝖬𝖾𝗇𝗎\n");
    mainMenu();
}

char allTweetsInTweetProfile[300000/*101(limit of number of each person's tweet) * 1001(the same length as tweet) + X(unusable characters)*/] = { 0 };
void findShowDetailsInTweetProfile( char resultOfTweetProfile[] ) {//the same function as findShowDetailsInSearch function
    char usernameInTweetProfile[21/*the same length as username*/];
    char bio[501/*the same length as biography*/] = { 0 };
    char numberOfFollowers[20/*limit of legth of each user's followers*/];
    char numberOfFollowings[20/*limit of legth of each user's followings*/];
    char followStatusInTweetProfile[15];
//    char allTweetsInTweetProfile[300000/*101(limit of number of each person's tweet) * 1001(the same length as tweet) + X(unusable characters)*/] = { 0 };( main place, it changes because of findShowDetailsOfCommentsInTweetProfile function )

    sscanf( resultOfTweetProfile, "%*[^:]:%*[^:]:%*[^:]:%*[^:]:\"%[^\"]", bio );
    if ( bio[0] == '\0' ) {
        sscanf( resultOfTweetProfile, "%*[^:]:%*[^:]:%*[^:]:\"%[^\"]%*[^:]:\"%[^,]%*[^:]:%[^,]%*[^:]:%[^,]%*[^:]:\"%[^\"]%*[^:]:%[^]]", usernameInTweetProfile, bio, numberOfFollowers, numberOfFollowings, followStatusInTweetProfile, allTweetsInTweetProfile );
        bio[0] = '\0';
    } else {
        sscanf( resultOfTweetProfile, "%*[^:]:%*[^:]:%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]%*[^:]:%[^,]%*[^:]:%[^,]%*[^:]:\"%[^\"]%*[^:]:%[^]]", usernameInTweetProfile, bio, numberOfFollowers, numberOfFollowings, followStatusInTweetProfile, allTweetsInTweetProfile );
    }
    strcat( allTweetsInTweetProfile, "]" );

    findShowDetailsOfCommentsInTweetProfile( usernameInTweetProfile, bio, numberOfFollowers, numberOfFollowings, followStatusInTweetProfile );
}

char commentsInTweetProfile[100][50100];
void findShowDetailsOfCommentsInTweetProfile( char usernameInTweetProfile[], char bio[], char numberOfFollowers[], char numberOfFollowings[], char followStatusInTweetProfile[] ) {//the same function as findShowDetailsOfCommentsInSearch function
//    limit of users to show in refresh is 99 which is shown in string's first dimension (it's compitable for comments string)
    char idInTweetProfile[100][20/*limit of legth of each user's id*/];
    char authorInTweetProfile[100][21/*the same length as username*/];
    char contentInTweetProfile[100][1001/*the same length as tweet*/];
    char likesInTweetProfile[100][6/*limit of length of likes*/];

    char *allTweetsInTweetProfileCopy = (char *)calloc( 300000, sizeof(char) );
    strcpy( allTweetsInTweetProfileCopy, allTweetsInTweetProfile );
    unsigned long int mainLength = 1;
    allTweetsInTweetProfileCopy[0] = '0';

    int numberOfTweets = 0;
    char specifier;
    char sscanfUse[10] = { 0 };
    sprintf( sscanfUse, "%%*%lus%%c", mainLength );
    sscanf( allTweetsInTweetProfileCopy, sscanfUse, &specifier );

    for ( int i = 0; specifier != ']' && i < 100; ++i ) {
        sscanf( allTweetsInTweetProfileCopy, "%*[^:]:%[^,]%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]%*[^{]%[^}]%*[^:]:%[^}]}%c", idInTweetProfile[i], authorInTweetProfile[i], contentInTweetProfile[i], commentsInTweetProfile[i], likesInTweetProfile[i], &specifier );
        unsigned long int secondLength = strlen( idInTweetProfile[i] ) + strlen( authorInTweetProfile[i] ) + strlen( contentInTweetProfile[i] ) + strlen( commentsInTweetProfile[i] ) + strlen( likesInTweetProfile[i] ) + 54;

        for ( int j = 0; j < secondLength; ++j ) {
            allTweetsInTweetProfileCopy[mainLength + j] = '0';
        }
        mainLength += secondLength;
        numberOfTweets = i + 1;
    }
    free( allTweetsInTweetProfileCopy );

    for ( int j = 0; j < numberOfTweets; ++j ) {
        strcat( commentsInTweetProfile[j], "}" );
    }

    int numberOfCommentsOfEachTweet[100] = { 0 };

    findNumberOfCommentsOfEachTweetForTweetProfile( numberOfCommentsOfEachTweet, numberOfTweets );
    showDetailsInTweetProfile( usernameInTweetProfile, bio, numberOfFollowers, numberOfFollowings, contentInTweetProfile, likesInTweetProfile, numberOfTweets, numberOfCommentsOfEachTweet, idInTweetProfile );

}

char commentsInTweetProfileCopy[100][50100];
void findNumberOfCommentsOfEachTweetForTweetProfile( int numberOfCommentsOfEachTweet[], int numberOfTweets ) {//the samae function as findNumberOfCommentsOfEachUser function
    for (int j = 0; j < numberOfTweets; ++j ) {
        strcpy(commentsInTweetProfileCopy[j], commentsInTweetProfile[j]);
    }

    char specifier;
    for ( int j = 0; j < numberOfTweets; ++j ) {
        sscanf( commentsInTweetProfileCopy[j], "{%c", &specifier );

        while ( specifier != '}' ) {
            sscanf( commentsInTweetProfileCopy[j], "%*[^,|}]%c", &specifier );
            *strpbrk( commentsInTweetProfileCopy[j], ",}") = '0';
            ++numberOfCommentsOfEachTweet[j];
        }

    }
}

void showDetailsInTweetProfile( char usernameInTweetProfile[], char bio[], char numberOfFollowers[], char numberOfFollowings[], char contentInTweetProfile[][1001], char likesInTweetProfile[][6], int numberOfTweets, int numberOfCommentsOfEachTweet[], char idInTweetProfile[][20] ) {//the samae function as showDetailsInSearch function
    printf("✤ 𝘜𝘴𝘦𝘳𝘯𝘢𝘮𝘦: %s\n", usernameInTweetProfile );
    if ( bio[0] == '\0' ) {
        printf("⁍ 𝘉𝘪𝘰:\n");
    } else {
        printf("⁍ 𝘉𝘪𝘰: %s\n", bio );
    }
    printf("𝘍𝘰𝘭𝘭𝘰𝘸𝘦𝘳𝘴: %s  𝘍𝘰𝘭𝘭𝘰𝘸𝘪𝘯𝘨𝘴: %s\n", numberOfFollowers, numberOfFollowings );
    printf("✤ 𝘛𝘸𝘦𝘦𝘵𝘴:\n");
    if ( numberOfTweets != 0 ) {
        for ( int j = 0; j < numberOfTweets; ++j) {
            printf("𝙸𝙳: %s\n", idInTweetProfile[j] );
            printf("%s\n", contentInTweetProfile[j] );
            printf("𝘓𝘪𝘬𝘦𝘴: %s  𝘊𝘰𝘮𝘮𝘦𝘯𝘵𝘴: %d\n", likesInTweetProfile[j], numberOfCommentsOfEachTweet[j] );
        }
    } else {
        printf("There's not any tweet to show 😕\n");
    }

}

void personalArea( void ) {
    printf("◎ 𝑃𝑒𝑟𝑠𝑜𝑛𝑎𝑙 𝐴𝑟𝑒𝑎\n");
    printf("1. set biography\n");
    printf("2. change password\n");
    printf("3. back to main menu\n");
    
    while ( 1 ) {
        
        char numberOfPersonalArea[10];
        scanf(" %[^\n]%*c", numberOfPersonalArea );
        
        if ( strcmp( numberOfPersonalArea, "1" ) == 0 ) {
            printf("⥤ 𝑺𝒆𝒕 𝑩𝒊𝒐𝒈𝒓𝒂𝒑𝒉𝒚\n");
            setBiography();
        } else if ( strcmp( numberOfPersonalArea, "2" ) == 0 ) {
            printf("⥤ 𝑪𝒉𝒂𝒏𝒈𝒆 𝑷𝒂𝒔𝒔𝒘𝒐𝒓𝒅\n");
            changePassword();
        } else if ( strcmp( numberOfPersonalArea, "3" ) == 0 ) {
            printf("Are you sure?\n(if you are sure please enter Yes else, enter No)\n");//                        maybe comment (delete) it
            char sure[10];
            scanf("%[^\n]%*c", sure );
            validatingByYesNo( sure );
            
            if ( strcmp(sure, "YES") == 0 || strcmp(sure, "Yes") == 0 || strcmp(sure, "yes") == 0 ) {
                printf("⥤ 𝑩𝒂𝒄𝒌 𝑻𝒐 𝑴𝒂𝒊𝒏 𝑴𝒆𝒏𝒖\n");
                mainMenu();
            } else if ( strcmp(sure, "NO") == 0 || strcmp(sure, "No") == 0 || strcmp(sure, "no") == 0 ) {
                personalArea();
            }
            
        } else {
            printf("Your entered text is invalid\nPlease try again:\n");
        }
    }
}

void setBiography( void ) {
    char biography[501] = { 0 };
    char biographyTest[502] = { 0 };
    char sure[10] = "22";
    while ( strcmp(sure, "YES") != 0 && strcmp(sure, "Yes") != 0 && strcmp(sure, "yes") != 0 ) {
        printf("Please enter your biography:\n(Unfortunately you are not able to use enter, double quotation and more than 500 characters in your biography :(( )\n");
        
        int specifier = 0;
        for ( int i = 0; i < 501; ++i ) {
            scanf("%c", &biographyTest[i] );
            if ( biographyTest[i] == '\n' ) {
                biographyTest[i] = '\0';
                ++specifier;
                break;
            }
        }
        if ( specifier == 0 ) {
            scanf("%*[^\n]%*c");
        }
        
        int checkBio;
        checkBio = validateBio( biographyTest );
        if ( checkBio == -2 ) {
            printf("You used '\"' and more than 500 characters 😱\nPlease try again\n");
            setBiography();
        } else if ( checkBio == -1 ) {
            printf("You used '\"' 😱\nPlease try again\n");
            setBiography();
        } else if ( checkBio == 0 ) {
            printf("Your entered tweet is more than 500 characters 😱\nPlease try again\n");
            setBiography();
        }
        strcpy( biography, biographyTest );
        
        
        printf("Do you confirm your biography?\nPlease pay 𝐀𝐓𝐓𝐄𝐍𝐓𝐈𝐎𝐍: You only once can set your biography\n(if you confirm please enter Yes else, enter No)\n");
        scanf("%[^\n]%*c", sure );
        validatingByYesNo( sure );
    }
    
    char messageOfSetBio[700];
    char resultOfSetBio[1000];
    
    sprintf( messageOfSetBio, "set bio %s, %s", token, biography );
    sendRequestToServer( messageOfSetBio, resultOfSetBio );
    
    int check;
    check = checkSetBio( resultOfSetBio );
    if ( check == 1 ) {
//        {"type":"Successful","message":"Bio is updated successfully."}
        printf("Your biography set successfully 🙂\n");
        personalArea();
    } else if ( check == 0 ) {
//        {"type":"Error","message":"Bio is already updated."}
        printf("You set your biography before 🙁\n");
        personalArea();
    } else {
        printf("Unknown error 😐\nPlease try again\n");
        setBiography();
    }
    
}

int validateBio( char biographyTest[] ) {
    if ( strchr( biographyTest, '"' ) != NULL && strlen( biographyTest ) > 500 ) {
        return -2;
    }else if ( strchr( biographyTest, '"' ) != NULL ) {
        return -1;
    } else if ( strlen( biographyTest ) > 500 ) {
        return 0;
    } else {
        return 1;
    }
}

int checkSetBio( char resultOfSetBio[] ) {
    char type[11];
    char message[40];
    
    sscanf( resultOfSetBio, "%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]", type, message );
    if( strcmp( type, "Successful") == 0 ) {
//        {"type":"Successful","message":"Bio is updated successfully."}
        return 1;
    } else if ( strcmp( message, "Bio is already updated." ) == 0 ){
//        {"type":"Error","message":"Bio is already updated."}
        return 0;
    } else {
        printf("%s\n", resultOfSetBio );
        return -1;
    }
}

void changePassword( void ) {
    char currentPassword[21] = { 0 };
    char currentPasswordTest[22] = { 0 };
    char newPassword[21] = { 0 };
    char newPasswordTest[22] = { 0 };
    
    char sure[10] = "22";
    while ( strcmp(sure, "YES") != 0 && strcmp(sure, "Yes") != 0 && strcmp(sure, "yes") != 0 ) {
        printf("Please enter your current password (maximum 20 character):\n(Please don't use enter and space)\n");
        while ( 1 ) {
            int specifier = 0;
            for ( int i = 0; i < 21; ++i ) {
                scanf("%c", &currentPasswordTest[i] );
                if ( currentPasswordTest[i] == '\n' ) {
                    currentPasswordTest[i] = '\0';
                    ++specifier;
                    break;
                }
            }
            if ( specifier == 0 ) {
                scanf("%*[^\n]%*c");
            }
            
            int checkPassword;
            checkPassword = validatePassword( currentPasswordTest );
            if ( checkPassword == -2 ) {
                printf("You violate all of password rules 😱\nPlease enter your current password again (maximum 20 character):\n(Please don't use enter and space)\n");
            } else if ( checkPassword == -1 ) {
                printf("You used space 😱\nPlease enter your current password again (maximum 20 character):\n(Please don't use enter and space)\n");
            } else if ( checkPassword == 0 ) {
                printf("Your entered password is more than 20 characters 😱\nPlease enter your current password again (maximum 20 character):\n(Please don't use enter and space)\n");
            } else if ( checkPassword == 1 ) {
                break;
            }
        }
        strcpy( currentPassword, currentPasswordTest );
        
        
        printf("Please enter your new password (maximum 20 character):\n(Please don't use enter and space)\n");
        while ( 1 ) {
            int specifier = 0;
            for ( int i = 0; i < 21; ++i ) {
                scanf("%c", &newPasswordTest[i] );
                if ( newPasswordTest[i] == '\n' ) {
                    newPasswordTest[i] = '\0';
                    ++specifier;
                    break;
                }
            }
            if ( specifier == 0 ) {
                scanf("%*[^\n]%*c");
            }
            
            int checkPassword;
            checkPassword = validatePassword( newPasswordTest );
            if ( checkPassword == -2 ) {
                printf("You violate all of password rules 😱\nPlease enter your current password again (maximum 20 character):\n(Please don't use enter and space)\n");
            } else if ( checkPassword == -1 ) {
                printf("You used space 😱\nPlease enter your current password again (maximum 20 character):\n(Please don't use enter and space)\n");
            } else if ( checkPassword == 0 ) {
                printf("Your entered password is more than 20 characters 😱\nPlease enter your current password again (maximum 20 character):\n(Please don't use enter and space)\n");
            } else if ( checkPassword == 1 ) {
                break;
            }
        }
        strcpy( newPassword, newPasswordTest );
        
        printf("Do you confirm your entered passwords?\n(if you confirm please enter Yes else, enter No)\n");
        scanf("%[^\n]%*c", sure );
        validatingByYesNo( sure );
    }
    
    char messageOfChangePassword[150];
    char resultOfChangePassword[1000];
    sprintf( messageOfChangePassword, "change password %s, %s, %s", token, currentPassword, newPasswordTest );
    sendRequestToServer( messageOfChangePassword, resultOfChangePassword );
    
    int check;
    check = checkChangePassword( resultOfChangePassword );
    if ( check == 1 ) {
//        {"type":"Successful","message":"Password is changed successfully."}
        printf("Your password changed successfully 🙂\n");
        personalArea();
    } else if ( check == 0 ) {
//        {"type":"Error","message":"Entered current password is wrong."}
        printf("Your entered current password is wrong 🙁\n");
        personalArea();
    } else if ( check == -1 ) {
//        {"type":"Error","message":"New password is equal to current password."}
        printf("Your both entered passwords was equal 😱\n");
        personalArea();
    } else if ( check == -2 ) {
//        {"type":"Error","message":"Your entered new password is more than 20 characters."}
        printf("Your entered new password is more than 20 characters 😱\nPlease try again\n");
        changePassword();
    }else if ( check == -3 ) {
        printf("Unknown error 😐\nPlease try again\n");
        changePassword();
    }
    
}

int checkChangePassword( char resultOfChangePassword[] ) {
    char type[11];
    char message[100];

    sscanf( resultOfChangePassword, "%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]", type, message );
    if( strcmp( type, "Successful") == 0 ) {
//        {"type":"Successful","message":"Password is changed successfully."}
        return 1;
    } else if ( strcmp( message, "Entered current password is wrong." ) == 0 ){
//        {"type":"Error","message":"Entered current password is wrong."}
        return 0;
    } else if ( strcmp( message, "New password is equal to current password." ) == 0 ) {
//        {"type":"Error","message":"New password is equal to current password."}
        return -1;
    } else if ( strcmp( message, "Your entered new password is more than 20 characters." ) == 0 ) {
//        {"type":"Error","message":"Your entered new password is more than 20 characters."}
        return -2;
    } else {
        printf("%s\n", resultOfChangePassword );
        return -3;
    }
}

int countLogOut = 0;
void logOut( void ) {
    char messageOfLogOut[100];
    char resultOfLogOut[500];
    
    sprintf( messageOfLogOut, "logout %s", token );
    sendRequestToServer( messageOfLogOut, resultOfLogOut );
    
    int check;
    check = checkLogOut( resultOfLogOut );
    if ( check == 1 ) {
//        {"type":"Successful","message":""}
        printf("You loged out successfully 🙂\nWe hope your surf was good\nIf you find any problem please contact us by fakhimi.amirmohammad@gmail.com\n\n𝕋𝕙𝕚𝕤 ℙ𝕣𝕠𝕘𝕣𝕒𝕞 ℂ𝕠𝕟𝕥𝕚𝕟𝕦𝕖𝕤...\n\n");
        exit(0);
    } else if ( check == 0 ) {
//        new error
        
        
        if ( countLogOut % 10 == 0 && countLogOut != 0 ) {
            printf("We tried to log out this username but it seems there's a problem\nIf you want to we try again, please press enter or if you want to do force quit, enter FRCQUT\nPlease pay 𝐀𝐓𝐓𝐄𝐍𝐓𝐈𝐎𝐍: If you do force quit, you can't use your username anymore\n");
            while ( 1 ) {
                char specifier[10] = { 0 };
                scanf("%[\n]%*c", specifier );
                if ( strcmp( specifier, "" ) == 0 ) {
                    ++countLogOut;
                    logOut();
                } else if ( strcmp( specifier, "FRCQUT" ) == 0 ) {
                    exit(0);
                } else {
                    printf("Your entered text is invalid\nPlease try again:\n");
                }
            }
        } else {
            ++countLogOut;
            logOut();
        }
        
        
    }
}

int checkLogOut( char resultOfLogOut[] ) {
    char type[11];
    char message[40];
    
    sscanf( resultOfLogOut, "%*[^:]:\"%[^\"]%*[^:]:\"%[^\"]", type, message );
    if( strcmp( type, "Successful") == 0 ) {
//        {"type":"Successful","message":""}
        return 1;
    } else {
//        new error
        printf("%s\n", resultOfLogOut );
        return 0;
    }
}
