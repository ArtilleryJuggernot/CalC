#include "calculator.h"

/*Cette fonction est utilisée pour gérer la sortie et l'arrêt du programme*/
int my_exit(int reason)
{
  switch (reason)
  {
  case ERROR:
    printf("%s%s", ERROR_MSG, USAGE);
    return -1;
    break;
  case USR_EXIT:
    printf("%s", USR_EXIT_MSG);
    return 1;
    break;
  case DIV_ZERO:
    printf("%s", USR_DIV_ZERO);
    return 2;
    break;
  }
  return 0;
}

/*Fonction de sortie de boucle, nettoyant l'utilisation mémoire de notre liste chaînée*/
void                       free_operations(t_operation* op)
{
  for (t_operation* tmp = op; tmp != NULL;)
  {
    t_operation* stmp = tmp;
    tmp = tmp->next;
    free(stmp);
  }
}

/*Fonction principale contenant la boucle principale d'exécution du programme*/
int main(int ac, char **av)
{
  t_operation *op;                                   //Structure contenant les opérations
  int ret_code;

  while ((op = add_elem()) != NULL && (ret_code = read_command(op)) != 1)         //Boucle d'exécution contenant la lecture de l'entrée utilisateur
  {
    if (ret_code == 0)
    {
      if (do_priority_op(op) == NULL)                //Gestion des divisions par zéro lors des opérations prioritaires
        printf("%s", USR_DIV_ZERO);
      else
        {
          do_second_op(op);                          //Opérations secondaires
        printf(" = %lf\n", op->number);              //Affichage du résultat
        }
    }
    free_operations(op);
  }
  return ret_code;
}
