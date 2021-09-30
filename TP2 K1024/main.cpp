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

struct ListaCompras
{
    Compra compra;
    ListaCompras *sigCompra;
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
            ListaUsuarios *panterior=NULL;
            ListaUsuarios *p2aux;
            for(loop; loop<numElementos; loop++)
            {

                //   cout<<"loop "<<loop<<endl;
                //mover puntero hacia locación actual


                fseek(archLU,sizeof(ListaUsuarios)*loop,SEEK_SET);

                if(loop==0)
                {
                    cout<<" PRIMER ELEMENTO "<<endl;
                    inicio= new ListaUsuarios();

                    fread(inicio,sizeof(ListaUsuarios),1,archLU);
                    inicio->sigUs=paux;
                    panterior=inicio;

                    //puntero que almacene el anterior para luego vincularlo
                }

                else
                {
                    fread(p2aux,sizeof(ListaUsuarios),1,archLU);
                    while(paux && paux->usuarioact.TotalImporteCompras<p2aux->usuarioact.TotalImporteCompras )
                    {
                        panterior=paux;
                        paux=paux->sigUs;
                    }
                    if(paux!=inicio)
                    {
                        panterior->sigUs= new ListaUsuarios();
                        fread(panterior->sigUs,sizeof(ListaUsuarios),1,archLU);
                        panterior->sigUs->sigUs=paux;

                    }
                    /*
                         panterior->sigUs= new ListaUsuarios();
                         paux=panterior->sigUs;
                         fread(paux,sizeof(ListaUsuarios),1,archLU);
                         paux->sigUs=NULL;
                         panterior=paux;

                         // cout<<"nuevoElemento"<<paux->usuarioact.ID<<endl;
                     }

                    }
                    */

                    fclose(archLU);
                    return ;
                }
    }
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

void EscribirListaArchivoClientes(ListaUsuarios* inicioListaUsuarios)
{
    FILE *archLU;
    archLU=fopen("clientes.bin","wb+");

    ListaUsuarios* usuario=inicioListaUsuarios;

    if(archLU!=NULL)
    {

        while(usuario!=NULL)
        {
            ListaUsuarios *psiguiente;
            psiguiente=usuario->sigUs;
            usuario->sigUs=NULL;
            fwrite(usuario,sizeof(ListaUsuarios),1,archLU);
            usuario->sigUs=psiguiente;
            usuario=usuario->sigUs;
        }
        cout<<"archivo escrito exitosamente"<<endl;


    }
    fclose(archLU);
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
            if(indx->sigUs==NULL)
            cout<<"elemento siguiente nulo"<<endl;
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

void AgregarnuevoUSuario(ListaUsuarios *&inicio)
{
    ListaUsuarios *nuevoUsuario;
    nuevoUsuario= new ListaUsuarios;
    if(inicio)
    {
        cout<<"añadir nuevo elemento"<<endl;
        nuevoUsuario->sigUs=inicio;
        cout<<"Ingrese  ID usuario"<<endl;
        cin>>nuevoUsuario->usuarioact.ID;
        cout<<"email: "<<endl;
        cin>>nuevoUsuario->usuarioact.eMail;
        cout<<"Ingrese Fecha Creación :"<<endl;
        cin>>nuevoUsuario->usuarioact.FechaCreacion;
        nuevoUsuario->usuarioact.activo=true;
        // agregar monto de prueba
        cout<<"monto de prueba"<<endl;
        cin>>nuevoUsuario->usuarioact.TotalImporteCompras;
        inicio=nuevoUsuario;
    }
    else
    {
        //lista vacia
        cout<<"lista vacia"<<endl;
         cout<<"Ingrese  ID usuario"<<endl;
        cin>>nuevoUsuario->usuarioact.ID;
        cout<<"email: "<<endl;
        cin>>nuevoUsuario->usuarioact.eMail;
        cout<<"Ingrese Fecha Creación :"<<endl;
        cin>>nuevoUsuario->usuarioact.FechaCreacion;
        nuevoUsuario->usuarioact.activo=true;
        // agregar monto de prueba
        cout<<"monto de prueba"<<endl;
        cin>>nuevoUsuario->usuarioact.TotalImporteCompras;
        nuevoUsuario->usuarioact.activo=true;
        inicio=nuevoUsuario;
        nuevoUsuario->sigUs=NULL;
    }
}

void DesactivarUsuarioExistente( ListaUsuarios *&inicio)
{
    int idbuscada;
    cout<<"ingrese id del usuario"<<endl;
    ListaUsuarios *paux=inicio;
    cin>>idbuscada;
    if(idbuscada<0)
    {
        cout<<"ID no valida. Vuelva a ingresar : "<<endl;
        cin>>idbuscada;
    }
    else
    {
        while(paux&&paux->usuarioact.ID!=idbuscada)
        {
            paux=paux->sigUs;
        }
        if(paux==NULL)
        {
            cout<<"no se encontró el ID"<<endl;
        }
        paux->usuarioact.activo=false;
        cout<<"usuario "<<paux->usuarioact.ID<<"  fue desactivado"<<endl;
    }

}

void OrdenarListaPorImporte(ListaUsuarios *&inicio)
{

    ListaUsuarios *anterior=NULL;
    ListaUsuarios *paux=NULL;
    paux=inicio;
    ListaUsuarios* psiguiente=NULL;
    ListaUsuarios *p2aux;
    while(paux  )
    {
        if(paux->sigUs!=NULL)
        {
            if((paux->usuarioact.TotalImporteCompras  < paux->sigUs->usuarioact.TotalImporteCompras))
            {

                if(!anterior)
                {
                    p2aux=psiguiente;
                    paux->sigUs=psiguiente->sigUs;

                    psiguiente=paux->sigUs;


                    psiguiente=p2aux;
                    anterior=paux;
                    paux=paux->sigUs;
                }
                else
                {
                    anterior->sigUs=psiguiente;
                    p2aux=psiguiente;
                    paux->sigUs=psiguiente->sigUs;

                    psiguiente=paux->sigUs;


                    psiguiente=p2aux;
                     anterior=paux;
                     paux=paux->sigUs;

                }
            }



        }
        else{
            paux=NULL;
        }
    }

}

    void BorrarListaUs(ListaUsuarios *&inicio)
    {
        ListaUsuarios* paux;



        while(inicio)
        {
            paux=inicio;
            if(paux->sigUs != NULL){
            cout<<"borrando usuario "<<paux->usuarioact.ID<<endl;
               inicio=inicio->sigUs;
            cout<<"paux->sig es : "<<paux->sigUs<<endl;
            delete paux;
            }
            else
            {
                delete inicio;
                inicio=NULL;
            }
        }
        cout<<"lista borrada satisfactoriamente "<<endl;
    }

  void BorrarListaCompras(ListaCompras *indx)
    {
        ListaCompras* paux;
        ListaCompras *pactual;
        paux=indx;

        while(paux!=NULL)
        {
            pactual=paux;
            paux=paux->sigCompra;
            delete pactual;
        }
        cout<<"lista Compras borrada satisfactoriamente "<<endl;
    }

    void BuscarClientePorID(ListaUsuarios* inicio)
    {
     int idbuscada;
        cout<<"ingrese id del usuario"<<endl;
        ListaUsuarios *paux;
        paux=inicio;
        cin>>idbuscada;
        if(idbuscada<0)
        {
            cout<<"id no valida"<<endl;
            cin>>idbuscada;
        }
        else
        {
            while(paux&&paux->usuarioact.ID!=idbuscada)
            {
                paux=paux->sigUs;
            }
            if(paux==NULL)
            {
                cout<<"no se encontró el ID"<<endl;
            }
            else
            {
             cout<<"Usuario ID: "<<paux->usuarioact.ID<<endl;
             cout<<"email: "<<paux->usuarioact.eMail<<endl;
             cout<<"Fecha creacion: "<<paux->usuarioact.FechaCreacion<<endl;
             cout<<"Importe "<<paux->usuarioact.TotalImporteCompras<<endl;
            }
        }
    }
void BuscarClientePorIDoMail(ListaUsuarios *inicio)
{
    int opcion;
    cout<<"Para buscar por ID ingrese 1"<<endl;
    cout<<"para buscar por email, ingrese 2"<<endl;
    cin>>opcion;
    switch(opcion)
    {
    case 1: BuscarClientePorID(inicio);
    break;
    case 2://BuscarClientePorMail(inicio);
  break;
    }
}

/*void CrearListaUsuariosActivos(ListaUsuarios *inicio,ListaUsuarios *& inicioListaUs)
{
    BorrarListaUs(inicioListaUs);

    ListaUsuarios *paux=inicio;
    ListaUsuarios *panterior=inicioListaUs;
     ListaUsuarios *p2aux=inicioListaUs;
     int cont=0; //


  while(paux)
    {
        if(!cont)
        {
            inicioListaUs=new ListaUsuarios();
            panterior=inicioListaUs;
        }
        else
        {
            if(paux->usuarioact.activo==true)
            {
                panterior->sigUs=new ListaUsuarios();
                p2aux->usuarioact=paux->usuarioact;

            }
            else
            {
                paux=paux->sigUs;
            }
        }
    }
    cont++;
}

*/

    int OpcionesMenu()
    {
        int opcion;
        cout<<"INGRESE OPCION"<<endl ;
        cout<<"1--> Cargar usuarios (modo desarrollo)"<<endl;
        cout<<"2--> Listar Usuario (modo dev)"<<endl;
        cout<<"3--Escribir List Usuarios Archivo (modo dev)"<<endl;
        cout<<"4--Agregar nuevo usuario"<<endl;
        cout<<"5--Desactivar usuario Existente"<<endl;
        cout<<"6--Buscar cliente por ID o por mail "<<endl;
        cout<<"7--Listar clientes ordenados por importe (NO DISPONIBLE)"<<endl;
        cout<<"8-Procesar lote de compras (NO DISPONIBLE)"<<endl;
        cout<<"9-Mostrar compras realizadas de un cliente dado(NO DISPONIBLE)"<<endl;
        cout<<"10--Generar reporte HTML de compras realizadas en dos fechas (NO DISPONIBLE)"<<endl;
        cout<<"11-- Generar reporte CSV de compras realizadas en dos fechas (NO DISPONIBLE)" <<endl;
        cout<<"12--- Borrar lista"<<endl;
        cout<<"13-Finalizar jornada"<<endl;

        cin>>opcion;
        return opcion;
    }

    void Menu(ListaUsuarios *&inicioListaUsuarios, ListaCompras *&inicioLC)
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
                break;
            case 3 ://prueba escritura  archivo USuarios
                    EscribirListaArchivoClientes(inicioListaUsuarios);
                opcion=OpcionesMenu();
                break;
            case 4://Agregar Nuevo Usuario.
                     AgregarnuevoUSuario(inicioListaUsuarios);
                opcion=OpcionesMenu();
                break;
            case 5:// Desactivar usuario existente;
                DesactivarUsuarioExistente(inicioListaUsuarios);
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
                break;
            case 12:
                // borrar lista  usuariosfuncion prueba;
              BorrarListaUs(inicioListaUsuarios);
              opcion=OpcionesMenu();
              break;
            case 13:
                //FinalizarJornada(opcion);
                break;



            }
        }
    }

    int main()
    {
        ListaUsuarios *inicioListaUsuarios=NULL;
        ListaUsuarios *inicioListaActivosUsuarios=NULL;
        CargarArchivoUsuarios(inicioListaUsuarios);
        ListaCompras*pauxLC;

        ListaCompras *inicioListaCompras;
//Compra numero 1
        inicioListaCompras= new ListaCompras();
        inicioListaCompras->compra.CompraID=1;
      strcpy(inicioListaCompras->compra.FechaHora,"2021012515:23")  ;
        inicioListaCompras->compra.Monto=240000;
        inicioListaCompras->compra.NroArticulo=43;
        inicioListaCompras->compra.UsuarioID=1;
        inicioListaCompras->sigCompra=new ListaCompras();
        pauxLC=inicioListaCompras->sigCompra;





//compra numero 2
        pauxLC->compra.CompraID=2;
strcpy(pauxLC->compra.FechaHora,"2021022812:20");
            pauxLC->compra.Monto=233000;
        pauxLC->compra.NroArticulo=78;
        pauxLC->compra.UsuarioID=2;
        pauxLC->sigCompra=new ListaCompras();
        pauxLC=pauxLC->sigCompra;

// compra numero 3

        pauxLC->compra.CompraID=3;
     strcpy(  pauxLC->compra.FechaHora,"2021052312:32"),
        pauxLC->compra.Monto=34000;
        pauxLC->compra.NroArticulo=10;
        pauxLC->compra.UsuarioID=3;
        pauxLC->sigCompra=new ListaCompras();
        pauxLC=pauxLC->sigCompra;
// compra numero 4
        pauxLC->compra.CompraID=4;
         strcpy(pauxLC->compra.FechaHora,"2021081718:30");
        pauxLC->compra.Monto=3000;
        pauxLC->compra.NroArticulo=77;
        pauxLC->compra.UsuarioID=4;
        pauxLC->sigCompra=new ListaCompras();
        pauxLC=pauxLC->sigCompra;

//compra numero 5
        pauxLC->compra.CompraID=5;
      strcpy(pauxLC->compra.FechaHora,"2021090213:30");
       pauxLC->compra.Monto=4500;
        pauxLC->compra.NroArticulo=23;
        pauxLC->compra.UsuarioID=5;
        pauxLC->sigCompra=NULL;


 Menu(inicioListaUsuarios,inicioListaCompras);

//BorrarListaUs(inicioListaUsuarios);
       // BorrarListaCompras(inicioListaCompras);
      //  BorrarListaUs(inicioListaActivosUsuarios);
        return 0;
    }
