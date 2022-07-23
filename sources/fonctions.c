#include "calculator.h"

/*Tableau de pointeurs sur fonctions. Chaque fonction est ainsi
reliée à un charactère, correspondant à l'opération de la fonction*/
double (*operators[])(double, double) = {
    ['*'](mult),
    ['/'](divi),
    ['-'](sub),
    ['+'](add),
    ['%'](mod)};

/*Cette fonction contrôle les opérations simples. En prenant en paramètre
un pointeur sur une t_operation, elle effectue l'opération contenu dans ce pointeur
avec le nombre contenu dans le pointeur suivant. Elle effectue également les 
changements et la suppression de l'élément non-nécessaire une fois l'opération
effectuée.*/
int operate(t_operation *ptr)
{
  t_operation *to_free = ptr->next;

  ptr->number = (*operators[ptr->n_operator])(ptr->number, ptr->next->number);
  ptr->n_operator = ptr->next->n_operator;
  ptr->next = ptr->next->next;
  free(to_free);
  return 0;
}

/*Cette fonction prend en charge les opérations prioritaires telles que la division,
la multiplication et le modulo. Elle se charge également de vérifier qu'une division 
par zéro n'est pas acceptée.*/
t_operation *do_priority_op(t_operation *first)
{
  for (t_operation *tmp = first; tmp != NULL;)
  {
    if ((tmp->n_operator == '*' || tmp->n_operator == '/' || tmp->n_operator == '%') && tmp->next != NULL)
    {
      if (tmp->next->number == 0 && tmp->n_operator != '*')
        return (NULL);
      else
        operate(tmp);
    }
    else
      tmp = tmp->next;
  }
  return first;
}

/*Cette fonction prend en charge les opérations secondaires telles que l'addition et
la soustraction.*/
t_operation *do_second_op(t_operation *first)
{
  for (t_operation *tmp = first; tmp != NULL;)
  {
    if ((tmp->n_operator == '+' || tmp->n_operator == '-') && tmp->next != NULL)
    {
      operate(tmp);
    }
    else
      tmp = tmp->next;
  }
}

/*Fonction d'addition*/
double add(double x, double y)
{
  return x + y;
}

/*Fonction de multiplication*/
double mult(double x, double y)
{
  return x * y;
}

/*Fonction de division*/
double divi(double x, double y)
{
  return x / y;
}

/*Fonction de modulo*/
double mod(double x, double y)
{
  return (int)x % (int)y;
}

/*Fonction de soustraction*/
double sub(double x, double y)
{
  return x - y;
}
