#include "calculator.h"

/*Cette fonction sert à lire l'entrée de l'utilisateur et à afficher les messages qui lui
sont destinés*/
int read_command(t_operation *operation)
{
  char buffer[255];
  int cursor = 0;
  char *command;

  printf("%s", USR_INSTRUCTIONS_MSG);
  if ((cursor = read(0, &buffer, BSIZE)) < 0)
    return my_exit(ERROR);
  buffer[cursor - 1] = 0;
  command = strdup(buffer);
  command[cursor - 1] = 0;
  if (check_exit(command) == 1)
    return my_exit(USR_EXIT);
  if (check_help(command) == 1)
  {
    printf("%s", USR_HELP_MSG);
    return USR_HELP;
  }
  return ((operation = parse_operation(command, operation)) == NULL) ? my_exit(ERROR) : 0;
}

/*Cette fonction vérifie que la chaîne de caractères rentrée par l'utilisateur
correspond aux caractères attendus.*/
int is_parsable(char *str)
{
  int check;
  char acceptable[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '+', '-', '/', '*', '%'};
  int j = 0;

  if (str[0] < '0' || str[0] > '9')
    return 0;
  for (int i = 0; i != strlen(str); i++)
  {
    check = 0;
    j = 0;
    while (check != 1 && j != 17)
      check = (str[i] == acceptable[j++]) ? 1 : 0;
    if (check == 0)
      return 0;
  }
  return 1;
}

/*Cette fonction prend en paramètre un pointeur sur t_operation ainsi qu'un
un pointeur sur un endroit de la chaîne de caractères. Elle y récupère un double 
grâce à atof() puis le stock dans la structure t_operation.*/
int parse_nb(t_operation *add, char *str)
{
  int i = 0;

  if (str[i] == '-')
    i++;
  add->number = atof(str);
  while (((str[i] >= '0' && str[i] <= '9') || str[i] == '.') && str[i] != 0)
    i++;
  return i;
}

/* Cette fonction vérifie la présence d'un opérateur seul ou suivi par un - appartenant au prochain nombre*/
int check_operators(char *str, int i, t_operation *op)
{
  if (str[i] == 0)
    return 0;
  else if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '%')
  {
    op->n_operator = str[i];
    if (str[i + 1] == '-' && (str[i + 2] >= '0' && str[i + 2] <= '9'))
      return 0;
    else if (str[i + 1] >= '0' && str[i + 1] <= '9')
      return 0;
    else
      return -1;
  }
  else
    return -1;
}

/*Cette fonction supprime tout les espaces dans la chaîne de caractères.*/
char *trim(char *str)
{
  char *n_str;
  int j = 0;

  if ((n_str = malloc(strlen(str) + 1)) == NULL)
    return NULL;
  n_str[strlen(str)] = 0;
  for (int i = 0; i != strlen(str); i++)
  {
    if (str[i] != ' ')
      n_str[j++] = str[i];
  }
  free(str);
  return n_str;
}

/*Cette fonction est multi-tâche dans le cadre de la compréhension de l'entrée utilisateur*/
t_operation *parse_operation(char *str, t_operation *first)
{
  t_operation *current = first;

  if ((str = trim(str)) == NULL)                                            //Ici on supprimme tout les espaces de la chaîne en vérifiant que la chaîne n'est pas vide
    return NULL;
  if (!is_parsable(str))                                                    //Vérification de l'intégrité de l'expression
    return NULL;
  for (int i = 0; i < strlen(str); i++)                                     //Navigation dans la chaîne de caractères reçu en entrée
  {
    i += parse_nb(current, &(str[i]));                                      //Récupération d'un nombre
    if (check_operators(str, i, current) != 0)                              //Y'a t-il un opérateur ou l'opération est finie ?
      return NULL;
    if (current->n_operator != 0 && (current->next = add_elem()) == NULL)   //Vérifications et construction de la liste chaînée
      return NULL;
    current = current->next;
  }
  free(str);
  return first;                                                             //Retourne la liste chaînée remplie d'élements de l'opération
}

/*Cette fonction alloue en mémoire un nouvel elément de type t_operation et initialise ses valeurs*/
t_operation *add_elem()
{
  t_operation *elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)   //On utilise un malloc ! Ne pas oublier de tout free en fin d'exécution
    return NULL;
  elem->next = NULL;
  elem->number = 0;
  elem->n_operator = 0;
  return elem;
}

/*Cette fonction est utilisée pour vérifier si l'utilisateur désire quitter le programme
en tapant 'exit' ou 'quit'*/
int check_exit(char *comm)
{
  if (comm == NULL || comm == "")
    return 0;
  if (strcmp(comm, "exit") == 0 || strcmp(comm, "quit") == 0)
    return 1;
  return 0;
}

/*Cette fonction est utilisée pour vérifier si l'utilisateur désire afficher l'aide du programme*/
int check_help(char *comm)
{
  if (comm == NULL || comm == "")
    return 0;
  if (strcmp(comm, "help") == 0 || strcmp(comm, "?") == 0)
    return 1;
  return 0;
}