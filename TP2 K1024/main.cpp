#include <iostream>
using namespace std;
#include <string.h>
struct Usuario
{
    int ID;
    int FechaCreacion;
    bool activo;
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

void CargarArchivoUsuarios(ListaUsuarios *&inicio)
{
    FILE *archLU;
    archLU=fopen("clientes.bin","rb+");
    if(archLU!=NULL)
    {
        ListaUsuarios *paux=NULL;
        ListaUsuarios *panterior=NULL;
        inicio=NULL;
        fseek(archLU,0,SEEK_END);

        int TamArchivoLista=ftell(archLU);
        int numElementos=TamArchivoLista/sizeof(ListaUsuarios);

        cout<<"la cant de elementos es "<<numElementos<<endl;
        fseek(archLU,0,SEEK_SET);
        if(numElementos>0)
        {

            cout<<"Leyendo datos..."<<endl;
            int loop=0;
            paux=inicio;
            for(loop; loop<numElementos; loop++)
            {

                //   cout<<"loop "<<loop<<endl;
                //mover puntero hacia locación actual
                fseek(archLU,sizeof(ListaUsuarios)*loop,SEEK_SET);

                if(loop==0)
                {
                    cout<<" PRIMER ELEMENT "<<endl;
                    inicio= new ListaUsuarios();

                    fread(inicio,sizeof(ListaUsuarios),1,archLU);

                    inicio->sigUs=NULL;
                    panterior=inicio;

                    //puntero que almacene el anterior para luego vincularlo
                }
                else
                {
                    panterior->sigUs= new ListaUsuarios();
                    paux=panterior->sigUs;
                    fread(paux,sizeof(ListaUsuarios),1,archLU);
                    paux->sigUs=NULL;
                    panterior=paux;
                    // cout<<"nuevoElemento"<<paux->usuarioact.ID<<endl;
                }

            }

            fclose(archLU);
            return ;
        }
        else
        {
            cout<<"Lista vacía ,agregue elementos"<<endl;
            return;
        }
    }
    else
    {
        cout<<"falló apertura del archivo lista usuarios"<<endl;
    }
    //Tamaño de archivo cout<<ftell(archLU)<<endl;
}
void ListarUsuarios (ListaUsuarios *indx)
{

    cout<<"listando usuarios"<<endl;
    if(indx!=NULL)
    {
        while(indx!=NULL)
        {
            cout<<"dir actual: "<<indx<<endl;
                      cout<<" "<<endl;
            cout<<"id de usuario "<<indx->usuarioact.ID<<endl;
                      cout<<" "<<endl;
             cout<<"email de usuario "<<indx->usuarioact.eMail<<endl;
                       cout<<" "<<endl;
             cout<<"estado de actividad :"<<indx->usuarioact.activo<<endl;
                       cout<<" "<<endl;
             cout<<"importe actual: "<<indx->usuarioact.TotalImporteCompras<<endl;
             cout<<" "<<endl;
             cout<<"fecha de creación: "<<indx->usuarioact.FechaCreacion<<endl;
                       cout<<" "<<endl;
            cout<<"sig usuario en dir"<<indx->sigUs<<endl;
                      cout<<" "<<endl;
            indx=indx->sigUs;
            cout<<"ahora indx vale: "<<indx<<endl;
          cout<<" "<<endl;
        }
    }
    else
    {
        cout<<"Lista vacía "<<endl;
    }
}

int OpcionesMenu()
{
    int opcion;
    cout<<"INGRESE OPCION"<<endl    ;
    cout<<"1--> Cargar usuarios (modo desarrollo)"<<endl;
    cout<<"2--Listar Usuario (modo dev)"<<endl;
    cout<<"3--Leer ArchivLista Usuarios (modo dev)"<<endl;
    cout<<"4--Escribir List Usuarios Archvo (modo dev)"<<endl;
    cout<<"5--Agregar nuevo usuario"<<endl;
    cout<<"6--Desactivar usuario Existente--(NO DISPONIBLE)"<<endl;
    cout<<"7--Buscar cliente por ID o por mail (NO DISPONIBLE)"<<endl;
    cout<<"8--Listar clientes ordenados por importe (NO DISPONIBLE)"<<endl;
    cout<<"9-Mostrar compras realizadas de un cliente dado(NO DISPONIBLE"<<endl;
    cout<<"10--Generar reporte HTML de compras realizadas en dos fechas (NO DISPONIBLE)"<<endl;
    cout<<"11-- Generar reporte CSV de compras realizadas en dos fechas (NO DISPONIBLE)" <<endl;
    cout<<"12-Finalizar jornada"<<endl;

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
             CargarArchivoUsuarios(inicioListaUsuarios);
            opcion=OpcionesMenu();
            break;
        case 2: // verificar que esten listados  correctamente
            ListarUsuarios(inicioListaUsuarios);
            opcion=OpcionesMenu();
        case 3 ://prueba escritura  archivo USuarios
       //      EscribirListaUsuarios(inicioListaUsuarios);
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
    ListaUsuarios *inicioListaUsuarios=NULL;
    CargarArchivoUsuarios(inicioListaUsuarios);
    Menu(inicioListaUsuarios);





    return 0;
}
