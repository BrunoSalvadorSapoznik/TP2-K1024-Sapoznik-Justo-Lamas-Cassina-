#include <iostream>
using namespace std;
#include <string.h>
struct Usuario
{
    int IDusuario;
    int FechaCreacion;
    bool Activo;
    float TotalImporteCompras;
    char eMail[26];
};

struct ListaUsuarios
{
    Usuario usuarioact;

    ListaUsuarios *sigUs;
};

struct Compra
{
    int CompraID;
    char FechaHora[14];
    float Monto;
    int UsuarioID;
    int NroArticulo;

};

void CargarArchivoUsuarios()
{
    FILE *Fclientes;
    Fclientes=fopen("Clientes.bin","rb+");

    if(Fclientes )
        cout<<"Archivos Clientes cargado exitosamente"<<endl;
}
int OpcionesMenu()
{
    int opcion;

    //   cout<<"1--Listar Usuario"<<endl;
    //   cout<<"2--Leer ArchivLista UsuariosS"<<endl;
    cout<<"3--Escribir List Usuarios Archvo"<<endl;
    cout<<"4--Agregar nuevo usuario"<<endl;
    cout<<"9-Finalizar jornada"<<endl;
    cout<<"INGRESE OPCION"<<endl    ;
    cin>>opcion;
    return opcion;
}
void Menu(ListaUsuarios *&inicioListaUsuarios)
{
    int opcion=OpcionesMenu();
    while(opcion)
    {
        switch(opcion)
        {
        case 1: //(para verificar que se hayan cargado exitosamente los clientes en proxima ejecucion)
            //  CargarArchivoUsuarios(inicioListaUsuarios);
            opcion=OpcionesMenu();
            break;
        case 2: // verificar que esten listados  correctamente
            //ListarUsuarios();
            opcion=OpcionesMenu();
        case 3 ://prueba escritura  archivo USuarios
            // EscribirListaUsuarios(inicioListaUsuarios);
            opcion=OpcionesMenu();
            break;
        case 4://Agregar Nuevo Usuario.
            //      AgregarnuevoUSuario(inicioListaUsuarios);
            opcion=OpcionesMenu();
            break;
        case 5: //Desactivar usuario existente;
            //DesactivarUsuarioExistente();
            opcion=OpcionesMenu();
            break;
        case 6:// Buscar cliente por ID o por Mail.
            //BuscarClientePorIDoPorMail();
            opcion=OpcionesMenu();
        break;
        case 7://ListarClientesOrdenadosPorImporte
         //ListarClientesOrdenadosPorImporte();
          opcion=OpcionesMenu();
          break;
        case 8://procesar lote compras.
            //ProcesarLoteCompras();
              opcion=OpcionesMenu();
                break;
        case 9: //Mostrar por pantalla las todas las compras de un cliente dado
            // desde el Archivo procesadfo.bin
            //MostrarComprasCliente();
             opcion=OpcionesMenu();
        break;
             case 10: // Mostrar compras realizadas entre dos fechas en un reporte html,.Mostrando también el total de compras.
       //ReporteComprasRealizadasEntreDosFechasHTML();
       break;
             case 11:// Mismo reporte de compras entre dos fechas con total en formato csv,
                //ReporteComprasRealizadasEntreFechasCSV();
                 opcion=OpcionesMenu();
        case 12:
            //FinalizarJornada(opcion);
     break;
        }
    }
}

    int main()
    {
        ListaUsuarios *inicioListaUsuarios;
        CargarArchivoUsuarios();
        Menu(inicioListaUsuarios);





        return 0;
    }
