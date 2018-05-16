#include "libr/automat.h"

using namespace std;

int main()
{

Automat uat("autohoho.in","mehehe.in");
//Automat uat("micut_a.in","micut_m.in");
//uat.afis();

Automat AF;

AF.AFD(uat);
AF.afis();

return 0;
}
