#ifndef PROTOTIPADOS_H_INCLUDED
#define PROTOTIPADOS_H_INCLUDED

#define PRODUCTOS "productos.dat"
#define USUARIOS "usuarios.dat"
#define VENTAS "ventas.dat"
#define REPORTES "reportes.dat"

#define DIMSTRING 30

typedef struct {
    int dia;
    int mes;
    int anio;
}Fecha;

typedef struct {
    int idProducto;
    char marca[DIMSTRING];
    char modelo[DIMSTRING];
    Fecha altaDeProducto;
    float precioDeProducto;
    char tipoDeProducto[20]; // detalle
    int cantidad; // stock
    int activo;// disponible 1 o 0
}Producto;

typedef struct {
    int dni;
    char nombre[50];
    char telefono[20];
    char direccion[100];
    char rol[20]; // A admin, E empleado, C cliente
    int activo;// disponible 1 o 0
    char password[DIMSTRING];//en caso de ser A o E
}Usuario;

typedef struct {
    Fecha fechaDeVenta;
    int idProducto;
    int dniCliente;
    float precioTotal;
}Venta;

void menu();
void gestionDeProductos();
void gestionDeUsuarios();
void gestionDeVentas();
void reportesYestadisticas();

///Gestion de Productos
int generate_id();
float ajustarPrecio(int , float );
void agregarProductos ();
Producto agregarUNproducto(Producto );
void modificaArticulo();
void modificacionDELarticulo(Producto );
int buscarArticuloPorId (int );
int buscarArticuloPorModelo(char []);
int buscarArticuloPorMarca(char []);
void mostrarProductosSinStock ();
void mostrarUNproducto (Producto );


#endif // PROTOTIPADOS_H_INCLUDED
