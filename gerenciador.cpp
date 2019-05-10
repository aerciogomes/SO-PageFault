#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>

using namespace std;

struct pages{
    int tempo;
    bool referencia;
    int contador;
    bool r_w;
    bool modificada;
};

struct process{
    vector<pages> paginas;                 //vetor de paginas de cada processo com o tempo de cada pagina
    int tempoMax;                         //tempo maximo de um processo
    vector<int> seqpaginas;               //sequencia de paginas de cada processo

};

// Número de quadros que a memoria terá
int NumQuadro;
vector<process> Processos;

void Entradas_Simulador(){
    int i;
    int j;
    int contTempo;
    int qtdpages, pages_processos;
    cout << "numero de paginas = " << NumQuadro << endl;
    for (i = 0; i < 5; i++){
        Processos.push_back(process());             //cria um novo processo
        contTempo = 30 + (rand()%50);
        Processos[i].tempoMax = contTempo;
        qtdpages = NumQuadro + 2 + (rand()%6);
        cout << "Pagina " <<i<<" com tempo maximo = " << contTempo << "| qtdpages = " << qtdpages << endl;
        Processos[i].paginas.resize(qtdpages);
        for (j = 0; j < qtdpages; j++){
            Processos[i].paginas[j].tempo = 1 + (rand()%5);
            Processos[i].paginas[j].contador = 0;
            Processos[i].paginas[j].referencia = false;
            Processos[i].paginas[j].modificada = false;
            if(rand()%2 == 1){
                Processos[i].paginas[j].r_w = true;
            }else{
                Processos[i].paginas[j].r_w = false;
            }
        }
    }

    for(i = 0; i < 5; i++){
        cout << "\nProcesso[" << i << "] tem: " << endl;
        cout << "Tempo Máximo = " << Processos[i].tempoMax << " \t || Número de páginas = " << Processos[i].paginas.size() << endl;
        for(j = 0; j < Processos[i].paginas.size(); j++){
            cout << "\t Pagina [" << j << "]" << " com tempo  = " << Processos[i].paginas[j].tempo << endl;
        }
    }

    pages_processos = 0;
    j =0;

    // define a sequencia de processos
    for (i=0; i< 5; i++){
        j =0;
        while(j < Processos[i].tempoMax){
            pages_processos = rand()%Processos[i].paginas.size();
            if ((j + Processos[i].paginas[pages_processos].tempo) >= Processos[i].tempoMax){
                break;
            }

            Processos[i].seqpaginas.push_back(pages_processos);
            j = j + Processos[i].paginas[pages_processos].tempo;
        }
        cout << "\nprocesso[" <<i<< "] tem = " << Processos[i].seqpaginas.size()<< endl;
    }

}

bool BuscaMemoria(int *memoria, int pagina){
    for(int i = 0;i<NumQuadro;i++){
        if(pagina == memoria[i]){
            return true;
        }
    }

    return false;
}
void ImprimeSequenciaPaginas(){
    int i,j;

    for(i=0;i<5;i++){
        cout << "Processo [ " << i <<"] :" << endl;
        cout << "[";
        for(j=0;j<Processos[i].seqpaginas.size();j++){
            cout << "\t"<<Processos[i].seqpaginas[j];
        }
        cout << " ]"<< endl<<endl;
    }

}


void ImprimeMemoria(int memoria[]){
    cout << "\nRAM = [";
    for(int i=0;i<NumQuadro;i++){
        cout << "\t" << memoria[i];
    }
    cout << "]" << endl;

}

void IniciaMemoria(int *memoria,int numProcess){
    int i;

    for(i=0;i<NumQuadro;i++){
        memoria[i] = Processos[numProcess].seqpaginas[i];
    }
}

//Fifo - o mais antigo deve sair em kda falta de página
void Gerenciador_FIFO()
{
    int RAM[NumQuadro] = {};
    int contador_tempo = 0;
    int falta_pag = 0;
    int i,j;
    int aux;

    for(i=0;i<5;i++){
        aux = 0;
        cout << "Algoritmo para o processo = " << i << endl<<endl;
        IniciaMemoria(RAM,i);
        for(j = NumQuadro; j < Processos[i].seqpaginas.size(); j++){
            ImprimeMemoria(RAM);
            cout << "Proxima página = " << Processos[i].seqpaginas[j] << endl << endl;
            if(!(BuscaMemoria(RAM,Processos[i].seqpaginas[j]))){   //isso indica que a proxima página não esta na memoria
                //indica falta de pagina
                if(aux == NumQuadro){
                    aux = 0;
                }

                RAM[aux] = Processos[i].seqpaginas[j];
                aux++;
                falta_pag++;

            }
        }
        ImprimeMemoria(RAM);

    }

}

int main()
{

    /*for (i=0;i<5;i++){
        srand(time(NULL));
        cout << "random = " << 20 + (rand()%30) << endl;

    }*/
    srand(time(NULL));
    NumQuadro = 3 + rand()%4;

    Entradas_Simulador();

    ImprimeSequenciaPaginas();

    Gerenciador_FIFO();

    //FIFO - ok
    //NRU -
    //LRU
    //Segunda Chance

}
