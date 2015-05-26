/* This file was automatically generated.  Do not edit! */
#ifndef __CMD_LINE_H_
#define __CMD_LINE_H_


typedef enum 
{
    E_SUCCESS = 0,
    E_FAILURE,
    E_QUIT
}STATUS;

typedef struct CMD_TABLE
{
    const char   *cmd_name;
    const char   *sub_cmd_name;
    const char   *cmd_help;
    const char   *sub_cmd_help;
    STATUS        (*fct_call)(int, char **);
    STATUS        (*fct_call2)(int, int, char **);
} CMD_TABLE_STRU;


STATUS ExecuteCommand(int *theShellPtr,char *cmd_line);
void RegisterCommand(const CMD_TABLE_STRU cmd_new_cmd_table[],int cmd_nb_command);
void command_line_input_byte(char c);

#endif
