#ifndef			__CALCULATOR_H__
# define		__CALCULATOR_H__

#include		<stdio.h>
#include		<stdlib.h>
#include		<string.h>
#include		<unistd.h>

#define			BSIZE	522
#define     USR_EXIT                0
#define     ERROR                   1
#define     DIV_ZERO                2
#define     USR_HELP                3
#define     USR_DIV_ZERO            "Be careful ! Division by 0 is not allowed.\n"
#define     USR_EXIT_MSG            "Thank you and see you soon !\n"
#define     ERROR_MSG               "There is an error in your operation, please try again.\n"
#define     USR_INSTRUCTIONS_MSG    "Please enter your operation or type \"?\" or \"help\" :\n"
#define     USAGE                   "Operations must be [0-9][*-/\%+][0-9]...\n"
#define     USR_HELP_MSG            "Usage: Operations must be [0-9][*-/\%+][0-9]...\nTo quit type \"quit\" or \"exit\"\n"

/*Strucure servant à construire une liste chaînée pour enregistrer et résoudre nos opérations*/
typedef struct		          s_operation
{
  double			              number;                       
  struct s_operation	      *next;
  char			                n_operator;           //Opérateur suivant le nombre. Si l'opérateur == '0' cela signifie que le nombre est le dernier membre de l'opération
}			                      t_operation;


/*Prototypes de nos fonctions contenues dans le programme*/
t_operation*	              parse_operation(char*, t_operation*);
t_operation*                add_elem();
t_operation*                do_priority_op(t_operation*);
t_operation*                do_second_op(t_operation*);
int			                    is_done(char*);
int                         read_command(t_operation*);
int			                    is_parsable(char*);
int                         operate(t_operation*);
int                         my_exit(int);
int                         check_help(char*);
int                         check_exit(char*);

double                      mult(double, double);
double                      add(double, double);
double                      divi(double, double);
double                      mod(double, double);
double                      sub(double, double);     

#endif
