#include <stdio.h>
#include <stdlib.h>

int input (int j)
{
    int bol;

    while (1)
    {
        printf("caracteristica %d: ", j);
        scanf("%d", &bol);    

        if (bol == 0 || bol == 1)
            return bol;

        printf("Entrada invalida\n\n");
        printf("Digite 1 caso a esp. possuir a caracteristica;\n");
        printf("Digite 0 caso a esp. nao possuir a caracteristica;\n\n");
    }
}

void input_matrix (int n, int m, int matrix[][m])
{
    int i, j;
    
    printf("Digite 1 caso a esp. possuir a caracteristica;\n");
    printf("Digite 0 caso a esp. nao possuir a caracteristica;\n");
        
    for (i = 0; i < n; i++)
    {
        printf("esp %d:\n", i + 1);

        for (j = 0; j < m; j++)
        {
            matrix[i][j] = input(j + 1);
        }
    }
}

void print_matrix(int n, int m, int matrix[][m])
{
    int i, j;

    printf("\n\n");
    for (i = 0; i < n; i++)
    {
        printf("esp %d: ", i + 1);

        for (j = 0; j < m; j++)
        {
            if (j + 1 != m)
            {
                printf("%d ", matrix[i][j]);
            }
            else
            {
                printf("%d\n", matrix[i][j]);
            }
        }
    }
}

int sum_dis (int m, int *v1, int *v2)
{
    int i, sum = 0;

    for (i = 0; i < m; i++)
        if (v1[i] != v2[i])
            sum += 1;
    
    return sum;
}

void create_matrix_dis (int n, int m, int m_car[][m], int m_dis[][n])
{
    int i, j;
    
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            m_dis[i][j] = sum_dis(m, &m_car[i][0], &m_car[j][0]);
}

int sum_sim (int m, int *v1, int *v2)
{
    int i, sum = 0;

    for (i = 0; i < m; i++)
        if (v1[i] == v2[i])
            sum += 1;
    
    return sum;
}

void create_matrix_sim (int n, int m, int m_car[][m], int m_sim[][n])
{
    int i, j;
    
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            m_sim[i][j] = sum_sim(m, &m_car[i][0], &m_car[j][0]);
        
}

int main ()
{
    int n_esp, n_car;

    printf("Digite o numero de especies da matriz: ");
    scanf("%d", &n_esp);
    printf("Digite o numero de caracteristicas da matriz: ");
    scanf("%d", &n_car);

    if (n_esp <= 1)
    {
        printf("Digite um numero de especieis tem que maior que 1\n");
        exit(1);
    }
    
    if (n_car <= 1)
    {
        printf("Digite um numero de caracteristicas tem que maior que 1\n");
        exit(1);
    }
    
    int matrix_car[n_esp][n_car];

    input_matrix(n_esp, n_car, matrix_car);

    print_matrix(n_esp, n_car, matrix_car);

    int matrix_dis[n_esp][n_esp];

    printf("\n***Matriz distancia****\n");
    create_matrix_dis(n_esp, n_car, matrix_car, matrix_dis);
    
    print_matrix(n_esp, n_esp, matrix_dis);

    int matrix_sim[n_esp][n_esp];

    printf("\n***Matriz similaridade****\n");
    create_matrix_sim(n_esp, n_car, matrix_car, matrix_sim);
    
    print_matrix(n_esp, n_esp, matrix_sim);

}