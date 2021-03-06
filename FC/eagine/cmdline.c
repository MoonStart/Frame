#include "common.h"


#define MAX_ARGC            100
#define COMMAND_TABLE_SIZE  120
#define MAX_CMD_LINE_LENGTH 256

static char buffer[MAX_ARGC];


#ifndef REPEAT
#define REPEAT do{
#endif

#ifndef UNTIL
#define UNTIL(expression) }while( !(expression) );
#endif


typedef struct CMD_REGISTER_TABLE
{
    int             cmd_nb_command;
    CMD_TABLE_STRU *cmd_table;
} CMD_REGISTER_TABLE_STRUCT;

static CMD_REGISTER_TABLE_STRUCT cmd_register_table[COMMAND_TABLE_SIZE];
static int nb_cmd_table = 0;

static void display_help( char *command, char *sub_command );
static void sortAndInsertCmds(int endOfList, const CMD_TABLE_STRU newCmdTable[], int numNewCmds);
static int invoke_cmd(int theShellPtr, int argc, char **argv);
static int process_string( char line_array[], char *argv[], char *tokens );
static int help (int argc, char *argv[]);

static void sortAndInsertCmds(int endOfList, const CMD_TABLE_STRU newCmdTable[], int numNewCmds)
{
    while ((endOfList > 0) &&
            (strcmp(newCmdTable[0].cmd_name,
                    cmd_register_table[endOfList - 1].cmd_table[0].cmd_name) < 0))
    {
        cmd_register_table[endOfList].cmd_table = cmd_register_table[endOfList - 1].cmd_table;
        cmd_register_table[endOfList].cmd_nb_command = cmd_register_table[endOfList - 1].cmd_nb_command;
        endOfList--;
    }
    cmd_register_table[endOfList].cmd_table = (CMD_TABLE_STRU *)newCmdTable;
    cmd_register_table[endOfList].cmd_nb_command = numNewCmds;
}

void  RegisterCommand(const CMD_TABLE_STRU cmd_new_cmd_table[], int cmd_nb_command)
{
    // At first call, array is empty
    if (nb_cmd_table != 0)
    {
        /* For each entry in the register_table */
        int i = 0;
        for (i = 0 ; i < COMMAND_TABLE_SIZE && i < nb_cmd_table ; i++)
        {
            /* If the command names match */
            if(strcmp(cmd_register_table[i].cmd_table[0].cmd_name,
                      cmd_new_cmd_table[0].cmd_name) == 0 )
            {
                // Basically ignore. Do not THROW since we may shutdown
                // and restart multiple times (ex: when testing warm restart etc.)
                printf("Attempt to re-register %s command. \r\n", cmd_new_cmd_table[0].cmd_name );
                return;
            }
        }
    }

    if ((cmd_new_cmd_table[0].cmd_help == NULL) || (strlen(cmd_new_cmd_table[0].cmd_help) == 0))
    {
        printf("WARNING: Registration of '%s' command is missing help string.\r\n", cmd_new_cmd_table[0].cmd_name );
    }
    sortAndInsertCmds(nb_cmd_table, cmd_new_cmd_table, cmd_nb_command);
    nb_cmd_table++;
    return;
}


static int invoke_cmd(int theShellPtr, int argc, char **argv)
{
    STATUS   status = E_FAILURE;
    bool  cmd_found = false;
    bool  sub_cmd_found = false;

    /* For each entry in cmd_register_table */
    int i = 0;
    for (i = 0 ; i < nb_cmd_table && cmd_found == false; i++)
    {
        /* For each command in this table */
        int j = 0;
        for (j = 0 ; j < cmd_register_table[i].cmd_nb_command && cmd_found == false; j++)
        {
            /* If the command names match */
            if( (cmd_register_table[i].cmd_table[j].cmd_name != NULL ) &&
                    (strcmp(cmd_register_table[i].cmd_table[j].cmd_name, argv[0]) == 0 ) )
            {
                cmd_found = true;

                /* If a sub-command exist for this command */
                if ( cmd_register_table[i].cmd_table[j].sub_cmd_name != NULL)
                {
                    /* For the first sub_command */
                    REPEAT

                    /* If the sub-command names match */
                    if( (argc > 1) &&
                            (strcmp(cmd_register_table[i].cmd_table[j].sub_cmd_name, argv[1]) == 0) )
                    {
                        sub_cmd_found = true;

                        //    /* If there is a function for that sub-command */
                        /* Call this function */
                        if((cmd_register_table[i].cmd_table[j].fct_call) == NULL)
                            ( *(cmd_register_table[i].cmd_table[j].fct_call2))(theShellPtr, argc, argv);
                        else
                            ( *(cmd_register_table[i].cmd_table[j].fct_call))(argc, argv);
                    }
                    else
                    {
                        /* ERROR: there is no function related to this sub-command ! */
                        /* DECLARE_ERROR ()*/
                    }

                    j++;

                    /* For other sub_commands of this command */
                    UNTIL( (cmd_register_table[i].cmd_table[j].cmd_name != NULL ) ||
                           (j == cmd_register_table[i].cmd_nb_command ) )

                    /* Sub-command name not found: display help */
                    if (sub_cmd_found == false)
                    {
                        display_help(argv[0], NULL);
                        status = E_FAILURE;
                    }
                }
                /* Command without sub_command */
                else
                {
                    /* If there is a function for that command */
                    /* Call this function */
                    if((cmd_register_table[i].cmd_table[j].fct_call) == NULL)
                        ( *(cmd_register_table[i].cmd_table[j].fct_call2))(theShellPtr, argc, argv);
                    else
                        ( *(cmd_register_table[i].cmd_table[j].fct_call))(argc, argv);
                }
            }
        }
    }

    /* Command name not found: display help */
    if (cmd_found == false)
    {
        printf("Shell: The specified command is not recognized\r\n");
        status = E_FAILURE;
    }

    return status;
}

static int process_string( char line_array[], char *argv[], char *tokens )
{
    char *token = NULL;
    char **lasts;
    char *lastValue = NULL;
    const char *separator = " ";
    char  line_array_clean[MAX_CMD_LINE_LENGTH + 1] = "";
    int   argc = 0;

    /* For all character of the command line */
    int j = 0;
    for (j = 0 ; j < MAX_CMD_LINE_LENGTH && line_array[j] != NULL ; j++ )
    {
        /* Be sure it is a printable character */
        if ( isprint((int)line_array[j]) )
        {
            line_array_clean[j] = line_array[j];
        }
        else
        {
            line_array_clean[j] = ' ';
        }
    }

    /* Break command line in tokens */
    lasts = &lastValue;
#ifdef WIN32 
    token = strtok_s( line_array_clean , separator, lasts );
#else
    token = strtok_r( line_array_clean , separator, lasts );
#endif
    /* While there are tokens in cmd_line */
    while( token != NULL )
    {
        strcpy(tokens, token);
        argv[argc] = tokens;
        tokens += strlen(token) + 1;
        argc++;
        /* Get next token: */
#ifdef WIN32
        token = strtok_s( NULL, separator, lasts );
#else
        token = strtok_r( NULL, separator, lasts );
#endif
    }

    /* Return the number of arguments in the command line */
    return argc;
}


static void display_help( char *command, char *sub_command )
{
    bool cmd_found = false;
    bool sub_cmd_found = false;
    int i = 0;
    int j = 0;

    /* If help on a sub-command is requested */
    if( (command != NULL) && (sub_command != NULL) )
    {
        /* For each entry in the command_register_table */
        for(i = 0; (i < nb_cmd_table) && (cmd_found == false); i++ )
        {
            /* For each command in this table */
            for (j = 0 ; j < cmd_register_table[i].cmd_nb_command && cmd_found == false ; j++)
            {
                /* If the command names match */
                if ( (cmd_register_table[i].cmd_table[j].cmd_name != NULL ) &&
                        (strcmp(cmd_register_table[i].cmd_table[j].cmd_name, command) == 0) )
                {
                    cmd_found = true;

                    /* If a sub-command exist for this command */
                    if ( cmd_register_table[i].cmd_table[j].sub_cmd_name != NULL)
                    {
                        /* For the first sub_command */
                        REPEAT

                        /* If the sub-command names match */
                        if(strcmp(cmd_register_table[i].cmd_table[j].sub_cmd_name,
                                  sub_command) == 0 )
                        {
                            sub_cmd_found = true;

                            /* Print help on this sub-command */
                            printf("\n");
                            printf("%s %s\r\n", cmd_register_table[i].cmd_table[j].sub_cmd_name, cmd_register_table[i].cmd_table[j].sub_cmd_help);
                        }
                        j++;

                        /* For other sub_commands of this command */
                        UNTIL( (cmd_register_table[i].cmd_table[j].cmd_name != NULL ) ||
                               (j == (cmd_register_table[i].cmd_nb_command )) ||
                               (sub_cmd_found == true) )
                    }
                } /* if */
            }
        } /* for */
    } /* if */

    /*  1. If help on a command is requested.
        2. In case where help on the sub-command is requested but the sub-command was
            not found in the previous step */

    if( (( command != NULL) && (sub_cmd_found == false)) ||
            ((cmd_found == true) && (sub_cmd_found == false)) )
    {
        cmd_found = false;
        /* For each entry in the command_register_table */
        for(i = 0; (i < nb_cmd_table) && (cmd_found == false); i++ )
        {
            /* For each command in this table */
            for ( j = 0 ; j < cmd_register_table[i].cmd_nb_command && cmd_found == false; j++)
            {
                /* If the command names match */
                if((cmd_register_table[i].cmd_table[j].cmd_name != NULL ) &&
                        (strcmp(cmd_register_table[i].cmd_table[j].cmd_name, command) == 0))
                {
                    cmd_found = true;

                    /* If there are sub-commands for this command */
                    if ( cmd_register_table[i].cmd_table[j].sub_cmd_name != NULL)
                    {
                        /* Print help on this command */
                        printf("\n    ");
                        printf("%s ", cmd_register_table[i].cmd_table[j].cmd_name);

                        /* For each sub-command */
                        REPEAT

                        /* Print the sub-commands */
                        printf("\n\t");
                        // printf(cmd_register_table[i].cmd_table[j].sub_cmd_name);
                        printf("%s %s", cmd_register_table[i].cmd_table[j].sub_cmd_name, cmd_register_table[i].cmd_table[j].sub_cmd_help);
                        j++;

                        UNTIL( (cmd_register_table[i].cmd_table[j].cmd_name != NULL ) ||
                               (j == cmd_register_table[i].cmd_nb_command ) )
                    }
                    /* Command without sub-commands */
                    else
                    {
                        /* Print help on this command */
                        printf("\t%s", cmd_register_table[i].cmd_table[j].cmd_help);
                    }

                    printf("\n\n");

                } /* if */
            }
        } /* for */
    }

    /* If general help is requested */
    if( cmd_found == false )
    {
        /* For each entry in the command_register_table */
        for(i = 0; (i < nb_cmd_table); i++ )
        {
            /* For each command in this table */
            for (j = 0 ; j < cmd_register_table[i].cmd_nb_command ; j++)
            {
                printf("%s\r\n", cmd_register_table[i].cmd_table[j].cmd_name);
                printf("\t%s\r\n", cmd_register_table[i].cmd_table[j].cmd_help);

                /* If a sub-command exist for this command */
                if ( cmd_register_table[i].cmd_table[j].sub_cmd_name != NULL)
                {
                    /* For each sub-command */
                    REPEAT
                    j++;

                    UNTIL( (cmd_register_table[i].cmd_table[j].cmd_name != NULL ) ||
                           (j == cmd_register_table[i].cmd_nb_command ) )

                    /* Reset j to a valid value */
                    if (j < cmd_register_table[i].cmd_nb_command)
                    {
                        j--;
                    }
                }
            }
        }
    }
}

static int help (int argc, char *argv[])
{
    /* Switch the number of arguments */
    switch( argc )
    {
    case 1:
        /* Display general help */
        display_help( NULL, NULL );
        break;
    case 2:
        /* Display help on the command */
        display_help( argv[1], NULL );
        break;
    case 3:
        /* Display help on the sub-command */
        display_help( argv[1], argv[2] );
        break;
    default:
        /* Display general help */
        display_help( NULL, NULL );
    }

    return E_FAILURE;
}


STATUS ExecuteCommand(int theShellPtr, char *cmd_line)
{
    int       argc = 0;
    char     *argv[MAX_ARGC] = {NULL};
    char      tokens[MAX_CMD_LINE_LENGTH + MAX_ARGC] ;

    /* Initialize our output stream used by printf() */

    /* Set the command line in the right format */
    memset(tokens, 0x00, sizeof(tokens));
    argc = process_string(cmd_line, argv, &tokens[0] );

    /* If no argument were entered (empty line) */
    if (argc == 0)
        return E_FAILURE;

    /* If help is requested */
    if (strcmp(argv[0], "help") == 0 )
    {
        help(argc, argv);
        return E_SUCCESS;
    }

    invoke_cmd(theShellPtr, argc, argv);
    return E_SUCCESS;
}

#define PROMPT "Help>"
void command_line_input_byte(char c)
{
    static int pos = 0;

    if(pos < MAX_ARGC && c != END)
    {
        buffer[pos] = c;
        pos ++;
    }

    if((pos > MAX_ARGC) || (c == '?'))
    {
        ExecuteCommand(0, "help");
        memset(buffer, 0x00, sizeof(buffer));
        pos = 0;
    }

    if(c == END)
    {
        ExecuteCommand(0, buffer);
        memset(buffer, 0x00, sizeof(buffer));
        printf("%s", PROMPT);
        pos = 0;
    }
}


void win32_cmd_process()
{
    while(NULL != fgets(buffer, MAX_ARGC, stdin))
    {
        ExecuteCommand(0, buffer);
        memset(buffer, 0x00, sizeof(buffer));
        printf("%s", PROMPT);
    }
}