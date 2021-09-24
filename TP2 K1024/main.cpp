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

struct Compra
{
 int CompraID;
char FechaHora[14];
float Monto;
int UsuarioID;
int NroArticulo;

};

void CargarArchivoUsuarios(FILE *&Cl)
{
 Cl=fopen("Clientes.bin","rb+");

 if(Cl )
    cout<<"Archivos Clientes cargado exitosamente"<<endl;
}

int main()
{
FILE *U;

CargarArchivoUsuarios(U);




    return 0;
}
