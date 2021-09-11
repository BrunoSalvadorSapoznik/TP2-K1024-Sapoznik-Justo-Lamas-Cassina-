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



int main()
{

    return 0;
}
