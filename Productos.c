#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "prototipados.h"

#define ARCHIVO "stock.bin"

static int idProducto = 0;

/// Función para obtener un nuevo ID
int generate_id()
{
    return ++idProducto;
}

float ajustarPrecio(int tipoUsuario, float precioOriginal)
{
    if (tipoUsuario == 1) { // Admin
        return precioOriginal;
    } else if (tipoUsuario == 2) { // Empleado
        return precioOriginal * 1.10;
    } else if (tipoUsuario == 3) { // Cliente
        return precioOriginal * 1.25;
    }
    return precioOriginal; // Caso por defecto, sin cambio
}

void agregarProductos ()
{
    FILE * archi;
    int flag;
    Producto articulo;
    char opt='s';
    archi=fopen(ARCHIVO,"ab");
    if (archi!=NULL)
    {
        do
        {
            articulo = agregarUNproducto(articulo);
            articulo.idProducto = generate_id();
            flag = buscarArticuloEnArchivo(articulo.idProducto);

            if (flag == 1)
            {
                printf("El articulo existe, quiere crear uno nuevo?\n");
                printf("Si->s//No->Otra tecla: ");
                getchar();
                scanf("%c", &opt);
            }
            else
            {
                fwrite(&articulo, sizeof(Producto), 1, archi);
                printf("Desea seguir cargando articulos? \n");
                printf("Si->s//No->Otra tecla: ");
                getchar();
                scanf("%c", &opt);
            }
        }
        while(opt=='s');
    }
    fclose(archi);
}
Producto agregarUNproducto(Producto articulo)
{
    puts("==============================================\n")
    printf("Indique indique marca del producto: \n");
    getchar();
    fgets(articulo.marca, DIMSTRING, stdin);
    articulo.marca[strcspn(articulo.marca, "\n")] = '\0';
    printf("Indique el modelo del producto: \n");
    fgets(articulo.modelo, DIMSTRING, stdin);
    articulo.modelo[strcspn(articulo.modelo, "\n")] = '\0';
    printf("Indique el precio del producto: \n");
    fflush(stdin);
    scanf("%f",&articulo.precioDeProducto);
    printf("Cuantos articulos va a ingresar?: \n");
    fflush(stdin);
    scanf("%d",&articulo.cantidad);
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    articulo.altaDeProducto.dia = tm_info->tm_mday;
    articulo.altaDeProducto.mes = tm_info->tm_mon + 1;
    articulo.altaDeProducto.anio = tm_info->tm_year + 1900;
    puts("========================================")
    articulo.activo=1;
    return articulo;

}
void modificaArticulo()
{
    FILE *archi;
    Producto articulo;
    int opt, id,flag;
    char modelo[DIMSTRING], marca[DIMSTRING],modif='s';
    int encontrado = 0;

    do
    {
        printf("Que articulo desea modificar?\n");
        printf("1) Buscar por ID\n");
        printf("2) Buscar por modelo\n");
        printf("3) Buscar por marca\n");
        getchar();
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            printf("Ingrese el ID del producto: ");
            scanf("%d", &id);
            flag=buscarArticuloPorId(id);
            break;
        case 2:
            printf("Ingrese el modelo del producto: ");
            fgets(modelo, DIMSTRING, stdin);
            modelo[strcspn(modelo, "\n")] = '\0'; /// Elimina salto de línea
            flag=buscarArticuloPorModelo(modelo);
            break;
        case 3:
            printf("Ingrese la marca del producto: ");
            fgets(marca, DIMSTRING, stdin);
            marca[strcspn(marca, "\n")] = '\0'; /// Elimina salto de línea
            flag=buscarArticuloPorMarca(marca);
            break;
        default:
            printf("Opcion no valida.\n");
            continue;
        }

        if (flag)
        {
            printf ("El articulo se encontro correctamente,desea hacer algun cambio?\n")
            printf ("s -> Si    n->Otra tecla");
            scanf("%c"&modif);
            modif =tolower (modif);
            if (modif== s)
            {
                modificacionDELarticulo(articulo);
            }

        }
        else
        {
            printf("Articulo no encontrado.\n");
        }
    }
    while (opt < 1 || opt > 3);
}
void modificacionDELarticulo(Producto articulo)
{
    FILE * archi;
    /// Codigo para modificar el articulo encontrado
    printf("Articulo encontrado: %s %s\n", articulo.marca, articulo.modelo);
    printf("Ingrese el nuevo precio del producto: ");
    scanf("%f", &articulo.precioDeProducto);
    printf("Ingrese la nueva cantidad: ");
    scanf("%d", &articulo.cantidad);

    /// Guardar cambios en el archivo
    archi = fopen(ARCHIVO, "r+b");
    if (archi != NULL)
    {
        fseek(archi,(-1)*sizeof(Producto), SEEK_CUR); /// Mover el puntero de archivo al inicio del artículo
        fwrite(&articulo, sizeof(Producto), 1, archi);
        fclose(archi);
        printf("Articulo modificado correctamente.\n");
    }
    else
    {
        printf("Error al abrir el archivo");
    }
}
int buscarArticuloPorId (int idProduct)
{
    FILE * archi;
    Producto artic;
    int flag=0;
    archi=fopen(ARCHIVO,"rb");
    if (archi==NULL)
    {
        printf("No se encontro el archivo\n");
        printf("Byeee :D");
        return 0;
    }
    while(fread(&artic,sizeof(Producto),1,archi)>0)
    {
        if (artic.idProducto == idProduct)
        {
            flag = 1;
            break;
        }
    }
    fclose(archi);
    return flag;
}
int buscarArticuloPorModelo(char modelo[])
{
    FILE *archi;
    Producto artic;
    int flag=0;
    archi=fopen(ARCHIVO,"rb");
    if (archi==NULL)
    {
        printf("No se encontro el archivo que busca\n");
        return 0;
    }
    while (fread(&artic,sizeof(Producto),1,archi)>0)
    {
        if (strcmpi(modelo,artic.modelo)==0)

            flag=1;
        break;
    }
    fclose(archi);
    return flag;
}
int buscarArticuloPorMarca(char marca[])
{
    FILE *archi;
    Producto artic;
    int flag=0;
    archi=fopen(ARCHIVO,"rb");
    if (archi==NULL)
    {
        printf("No se encontro el archivo que busca\n");
        return 0;
    }
    while (fread(&artic,sizeof(Producto),1,archi)>0)
    {
        if (strcmpi(marca,artic.marca)==0)

            flag=1;
        break;
    }
    fclose(archi);
    return flag;
}
void mostrarProductosSinStock ()
{
    FILE * archi;
    Producto artic;
    archi=fopen(ARCHIVO,"rb");
    if (archi!=NULL)
    {
        while(fread(&artic,sizeof(Producto),1,archi)>0)
        {
            if (artic.cantidad == 0 && artic.activo== 1)
            {
                mostrarUNproducto(artic);
            }

        }
    }
    fclose(archi);
}
void mostrarUNproducto (Producto artic)
{
    puts("=====================================================\n");
    printf("El modelo del producto es: %s\n",artic.modelo);
    printf("La marca del producto es: %s\n",artic.marca);
    printf("El ID es: %d\n",artic.idProducto);
    printf("Y el precio antes de quedarse sin stock era: %d\n",artic.precioDeProducto);
    puts("=====================================================\n");
}
