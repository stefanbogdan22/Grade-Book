#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;

template <class Stype>
class Catalog_individual;

template<class Stype>
ostream& operator<<(ostream&, Catalog_individual<Stype>);

class Elev{
protected:

    string nume;
    string prenume;
public:

    Elev(){
        nume = "";
        prenume = "";
    }

    Elev(string nume, string prenume){

        nume = nume;
        prenume = prenume;
    }

    Elev(const Elev& elv){
        nume = elv.nume;
        prenume = elv.prenume;
    }

    Elev operator=(Elev const &elv){

        nume = elv.nume;
        prenume = elv.prenume;
        return *this;
    }

    friend istream& operator>>(istream& in, Elev &e);
    friend ostream& operator<<(ostream& out, const Elev &e);
    friend class Elevi_picati_la_examenul_x;
};

istream& operator>>(istream& in, Elev &e){

    cout<<"Nume: ";
    in>>e.nume;
    cout<<"Prenume: ";
    in>>e.prenume;
    return in;
}

ostream& operator<<(ostream& out, const Elev &e){
    out<<e.nume<<" ";
    out<<e.prenume<<endl;
    return out;
}

class Examen{
protected:

    static int numar_curent;
    int numar_examen;///incrementat automat (id_examen)
    string denumirea_materiei;
    double nota_la_scris;
public:

    int get_numar_examen(){
        return numar_examen;
    }

    void set_numar_examen(int a){
        numar_examen = a;
    }

    Examen(){
        numar_examen = numar_curent++;
        denumirea_materiei = "";
        nota_la_scris = 0;
    }

    Examen(string denumirea_materiei,double nota_la_scris){

        numar_examen = numar_curent++;
        this->denumirea_materiei = denumirea_materiei;
        this->nota_la_scris = nota_la_scris;
    }

    Examen(const Examen &ex){
        numar_examen = ex.numar_examen;
        denumirea_materiei = ex.denumirea_materiei;
        nota_la_scris = ex.nota_la_scris;
    }

    ~Examen(){}

    Examen operator= (Examen const &ex){

        numar_examen = ex.numar_examen;
        denumirea_materiei = ex.denumirea_materiei;
        nota_la_scris = ex.nota_la_scris;
        return *this;
    }

    virtual void afisare(){

        cout<<"Numar examen    : "<<numar_examen<<endl;
        cout<<"Denumire materie: "<<denumirea_materiei<<endl;
        cout<<"Nota la scris   : "<<nota_la_scris<<endl;
    }

    virtual void citire(){

        cout<<"Numar examen    : "; numar_examen = numar_curent++;
        cout<<numar_examen<<endl;
        cout<<"Denumire materie: "; cin>>denumirea_materiei;
        cout<<"Nota la scris   : "; cin>>nota_la_scris;
    }

    friend istream& operator>> (istream& in, Examen &ex);

};

istream& operator>>(istream& in, Examen &ex){
    ex.citire();
    return in;
}

class Examen_Partial : public Examen{

    double nota_la_oral;
public:

    Examen_Partial() : Examen(){

        nota_la_oral = 0;
    }

    Examen_Partial( string denumirea_materiei, double nota_la_scris, double nota_la_oral)
     : Examen(denumirea_materiei, nota_la_scris){

        this->nota_la_oral = nota_la_oral;
     }

     Examen_Partial(const Examen_Partial &ex){

        numar_examen = ex.numar_examen;
        denumirea_materiei = ex.denumirea_materiei;
        nota_la_scris = ex.nota_la_scris;
        nota_la_oral = ex.nota_la_oral;
     }

     ~Examen_Partial(){}

     Examen_Partial operator= (Examen_Partial const &ex){

        numar_examen = ex.numar_examen;
        denumirea_materiei = ex.denumirea_materiei;
        nota_la_scris = ex.nota_la_scris;
        nota_la_oral = ex.nota_la_oral;
        return *this;
    }

     virtual void afisare(){

        Examen::afisare();
        cout<<"Nota la oral    : "<<nota_la_oral<<endl;
     }

     virtual void citire(){
        Examen::citire();
        cout<<"Nota la oral: "; cin>>nota_la_oral;
     }

     friend istream& operator>> (istream& in, Examen_Partial &ex);
};

istream& operator>> (istream& in, Examen_Partial &ex){

    ex.citire();
    return in;
}

int Examen::numar_curent = 0;

class Examen_Final : public Examen{

    double puncte_extra;
public:
    Examen_Final() : Examen(){
        puncte_extra = 0;
    }

    Examen_Final(string denumirea_materiei,double nota_la_scris, double puncte_extra)
    : Examen(denumirea_materiei, nota_la_scris) {

        this->puncte_extra = puncte_extra;
    }

    Examen_Final(const Examen_Final &ex){

        numar_examen = ex.numar_examen;
        denumirea_materiei = ex.denumirea_materiei;
        nota_la_scris = ex.nota_la_scris;
        puncte_extra = ex.puncte_extra;
    }

    ~Examen_Final(){}

    Examen_Final operator= (Examen_Final const &ex){

        numar_examen = ex.numar_examen;
        denumirea_materiei = ex.denumirea_materiei;
        nota_la_scris = ex.nota_la_scris;
        puncte_extra = ex.puncte_extra;
        return *this;
    }

    virtual void afisare(){

        Examen::afisare();
        cout<<"Puncte extra    : "<<puncte_extra<<endl;
    }

    virtual void citire(){

        Examen::citire();
        cout<<"Puncte extra    : "; cin>>puncte_extra;
        cout<<endl;
    }

    friend istream& operator>> (istream& in, Examen_Final &ex);

};

istream& operator>> (istream& in, Examen_Final &ex){

    ex.citire();
    return in;
}

class Quizz : public Examen{
protected:

    int numar_itemi;
public:
    Quizz() : Examen(){
        numar_itemi = 0;
    }

    Quizz(string denumirea_materiei,double nota_la_scris, int numar_itemi)
    : Examen(denumirea_materiei, nota_la_scris) {

        this->numar_itemi = numar_itemi;
    }

    Quizz(const Quizz &ex){

        numar_examen = ex.numar_examen;
        denumirea_materiei = ex.denumirea_materiei;
        nota_la_scris = ex.nota_la_scris;
        numar_itemi = ex.numar_itemi;
    }

    ~Quizz(){}

    Quizz operator= (Quizz const &ex){

        numar_examen = ex.numar_examen;
        denumirea_materiei = ex.denumirea_materiei;
        nota_la_scris = ex.nota_la_scris;
        numar_itemi = ex.numar_itemi;
        return *this;
    }

    virtual void afisare(){

        Examen::afisare();
        cout<<"Numar itemi     : "<<numar_itemi<<endl;
    }

    virtual void citire(){

        Examen::citire();
        cout<<"Numar itemi     : "; cin>>numar_itemi;
        cout<<endl;
    }

    friend istream& operator>> (istream& in, Quizz &ex);
};

istream& operator>> (istream& in, Quizz &ex){
    ex.citire();
    return in;
}

template< class Stype>
class Catalog_individual{
protected:
    static int nr_curent;
    int nr_matricol;///nr matricol elev
    int nr_examene;///nr examene elev
    unordered_map<int,Stype> informatii;

public:

    static const int get_nr_curent(){
        return nr_curent;
    }

    Catalog_individual(){
        nr_matricol = nr_curent++;
        nr_examene = -1;
    }

    Catalog_individual(int nr_examene, unordered_map<int,Stype> inf){
        nr_matricol = nr_curent++;
        informatii(inf.begin(),inf.end());
    }

    /*Catalog_individual(const Catalog_individual &a){

        nr_matricol = a.nr_matricol;
        nr_examene = a.nr_examene;
        informatii(a.informatii.begin(),a.informatii.end());
    }*/
    Catalog_individual operator=(const Catalog_individual<Stype> *a){
        nr_matricol = a.nr_matricol;
        nr_examene = a.nr_examene;
        informatii(a.informatii.begin(),a.informatii.end());
        return *this;
    }

    ~Catalog_individual(){}

    void citire(){
        cout<<"Numar matricol elev: "<<nr_matricol<<endl;
        cout<<"Introduceti numar examene elev: "; cin>>nr_examene;
        int id_examen;
        int x;
        for(int i=0; i<nr_examene;i++){
            Stype bp;
            cout<<"Pentru EXAMEN 1,EXAMEN PARTIAL 2,EXAMEN FINAL 3,QUIZZ 4"<<endl;
            cout<<"Introduceti: ";
            cin>>x;
            switch(x){
                case 1:{
                    Examen d;
                    cin>>d;
                    bp = &d;
                    id_examen = d.get_numar_examen();
                    informatii.insert(pair<int,Stype>(id_examen,bp));
                    cout<<endl;
                    break;
                }
                case 2:{
                    Examen_Partial d;
                    cin>>d;
                    bp = &d;
                    id_examen = d.get_numar_examen();
                    informatii.insert(pair<int,Stype>(id_examen,bp));
                    cout<<endl;
                    break;
                }
                case 3:{
                    Examen_Final d;
                    cin>>d;

                    break;
                }
                case 4:{
                    Quizz d;
                    cin>>d;

                    break;
                }
                default: break;
            }
        }
    }

    friend ostream& operator<< <>(ostream&, Catalog_individual<Stype> );
};

template<class Stype>
ostream& operator<<(ostream& out, Catalog_individual<Stype> a){
    out<<"Numar matricol elev: "<<a.nr_matricol<<endl;
    out<<"Numar examene elev: "<<a.nr_examene<<endl;
    out<<a.nr_examene;
    out<<"Alte informatii: "<<endl;
    typename unordered_map<int,Stype>::iterator i;
        for(i = a.informatii.begin();i!=a.informatii.end();i++)
            out<<i->first<<endl<<i->second<<endl;
    return out;
}

template<class Stype>
int Catalog_individual<Stype>::nr_curent = 0;

int main()
{
    Catalog_individual<Examen*> a;
    a.citire();
    cout<<a;
}
