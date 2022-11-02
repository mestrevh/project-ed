#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree bt;

typedef struct binary_tree
{
    double item;
    bt *right;
    bt *left;
} bt;

bt *insert (bt *root, double item)
{
    if (root == NULL)
    {
        bt *new_root = (bt *) malloc(sizeof(bt));
        new_root->item = item;
        return new_root;
    }
    
    if (item > root->item)
    {
        root->right = insert(root->right, item);
    }
    else
    {
        root->left = insert(root->left, item);
    }

    return root;
}

void print_binary_tree (bt *root)
{
    if (root != NULL)
    {
        printf("(");
        print_binary_tree(root->left);
        printf(", %.2lf ,", root->item);
        print_binary_tree(root->right);
        printf(")");
    }
    else
    {
        printf("()");
    }
}

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
    {
        for (j = 0; j < n; j++)
        {
            m_dis[i][j] = sum_dis(m, &m_car[i][0], &m_car[j][0]);
        }
    }
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

int count_carac_not_equal (int count_carac_by_esp[], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j =  i + 1; j < n; j++)
        {
            if (count_carac_by_esp[i] == count_carac_by_esp[j])
            {
                return 0;
            }
        }
    }

    return 1;
}

void swap(int *x, int *y)
{
    int aux = *x;
    *x = *y;
    *y = aux;
}

void swap_array (int *a1, int *a2, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        swap(&a1[i], &a2[i]);
    }
}

void bubble_sort (int count_carac[], int n, int matrix_dis[][n])
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (count_carac[i] >= count_carac[j])
            {
                swap(&count_carac[i], &count_carac[j]);
                swap_array(&matrix_dis[i][0], &matrix_dis[j][0], n);
            }
        }
    }
    
}

int index_bigger_number_array (int count_carac_by_esp[], int n)
{
    int i, index = 0;

    for (i = 0; i < n; i++)
    {
        if (count_carac_by_esp[index] < count_carac_by_esp[i])
        {
            index = i;
        }
        
    }
    
    return index;
}

int next_root_tree(int n, int *array, int matrix[][n], int j)
{
    int i, index = 0;

    for (i = 0; i < n; i++)
    {
        if ( (matrix[j][i] <= matrix[j][index]) && (matrix[i][0] != -1) && (i != j))
        {
            index = i;
        }
    }
    
    return index;
}

void insert_bt_ok (int n, int matrix[][n], int j)
{
    int i;

    for (i = 0; i < n; i++)
        matrix[j][i] = -1;
    
}

bt *build_tree_num_carac_not_equal(bt *root, int n, int matrix_carac[][n], int count_carac_by_esp[], int asc)
{
    int i, index = index_bigger_number_array(count_carac_by_esp, n);
    
    for (i = 0; i < n; i++)
    {
        if (i + 1 == n)
        {
            root = insert(root, (double) index + 1);
        }
        else
        {
            double ans = (double) ((index + 1) + (next_root_tree(n, &matrix_carac[index][0], matrix_carac, index) + 1))/2;
            printf("index = %d, next = %d, ans = %.2lf\n", index + 1, next_root_tree(n, &matrix_carac[index][0], matrix_carac, index) + 1, ans);
            root = insert(root, ans);
            root = insert(root, index + 1);
            insert_bt_ok(n, matrix_carac, index);
            index = next_root_tree(n, &matrix_carac[index][0], matrix_carac, index);
        }
    }
    
    return root;
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

    int count_carac_by_esp[n_esp], i, j;

    for (i = 0; i < n_esp; i++)
    {
        int count = 0;

        for (j = 0; j < n_car; j++)
        {
            if (matrix_car[i][j])
            {
                count += 1;
            }
        }

        count_carac_by_esp[i] = count;
    }

    int matrix_dis[n_esp][n_esp];

    printf("\n");

    printf("\n***Matriz distancia****\n");
    create_matrix_dis(n_esp, n_car, matrix_car, matrix_dis);
    
    print_matrix(n_esp, n_esp, matrix_dis);

    /*
    int matrix_sim[n_esp][n_esp];

    printf("\n***Matriz similaridade****\n");
    create_matrix_sim(n_esp, n_car, matrix_car, matrix_sim);
    
    print_matrix(n_esp, n_esp, matrix_sim);
    */
    

    if (count_carac_not_equal(count_carac_by_esp, n_esp))
    {
        //bubble_sort(count_carac_by_esp, n_esp, matrix_dis);

        for (i = 0; i < n_esp; i++)
        {
            printf("%d ", count_carac_by_esp[i]);
        }
        printf("\n");
        

        bt *root = NULL;
        root = build_tree_num_carac_not_equal(root, n_esp, matrix_dis, count_carac_by_esp, 0);
        
        printf("\n");
        print_binary_tree(root);
        printf("\n");
    }
    else
    {
        printf("test\n");
    }

}