
/*Força Bruta O(n³) */

# include  < bits / stdc ++. h >
# define  MAX  1000000

int  main ()
{
    int a [MAX];
    int max_sum, soma;
    int começar, terminar;
    int n;

    while ( scanf ( " % d " , & n)! = EOF)
    {
        max_sum = 0 ;
        begin = end = - 1 ;

        for ( int i = 0 ; i <n; ++ i)
        {
            scanf ( " % d " , & a [i]);
        }

        for ( int primeiro = 0 ; primeiro <n; ++ primeiro)
        {
            for ( int last = first; last <n; ++ last)
            {
                soma = 0 ;
                for ( int k = primeiro; k <= último; ++ k)
                {
                    soma + = a [k];
                }

                if (soma> max_sum)
                {
                    max_sum = soma;
                    begin = first;
                    fim = último;
                }
            }
        }

        printf ( " % d% d% d \n " , max_sum, início, fim);
    }
}