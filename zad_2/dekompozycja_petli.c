#include<stdio.h>
#include<pthread.h>
#include<math.h>

//#include<stdlib.h>
//#include<stdio.h>
//#include <time.h>
//#include<pthread.h>
//#include <unistd.h>
double funkcja ( double x );

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w);

static int l_w_global=5;

static double calka_global=0.0;
static double a_global;
static double b_global;
static double dx_global;
static int N_global;

void* calka_fragment_petli_w(void* arg_wsk);
pthread_mutex_t bloker;
double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w){

  int N = ceil((b-a)/dx);
  double dx_adjust = (b-a)/N;
    l_w_global=l_w;
    N_global = N;
    dx_global = dx_adjust;
    a_global = a;
    b_global = b;
  printf("Obliczona liczba trapezów: N = %d, dx_adjust = %lf\n", N, dx_adjust);
  printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);


  // tworzenie struktur danych do obsługi wielowątkowości
//  pthread_
    pthread_mutex_init(&bloker,NULL);
  // tworzenie wątków
  int tablicaIndeksowWatkow[l_w];
  pthread_t tablicaWatkow[l_w];
//  double diff=
//N_global=(b-a)/l_w;
dx_global=dx;
    for(int i=0;i<l_w;i++)
    {
        tablicaIndeksowWatkow[i]=i;
            pthread_create(&tablicaWatkow[i],NULL,calka_fragment_petli_w,&tablicaIndeksowWatkow[i]);
    }
    for (int i = 0; i < l_w; ++i) {
        pthread_join(tablicaWatkow[i],NULL);
    }

//    for(i=0; i<LICZBA_W; i++ )
//        pthread_create( &watki[i], NULL, suma_w, (void *) &indeksy[i] );

  // oczekiwanie na zakończenie pracy wątków


  return(calka_global);
}

void* calka_fragment_petli_w(void* arg_wsk){

  int my_id= *( (int *) arg_wsk );

  double a, b, dx; // skąd pobrać dane a, b, dx, N, l_w ? 
  int N, l_w;      // wariant 1 - globalne

  // a = a_global; // itd. itp. - wartości globalne nadaje calka_zrownoleglenie_petli

  // dekompozycja cykliczna
//  int my_start = 0;
//  int my_end = 0;
//  int my_stride = 0;
    a = a_global;
    b = b_global;
    dx = dx_global;
    N = N_global;
  // dekompozycja blokowa
//    int my_start = ceil((float)N/l_w_global) * my_id;
//    int my_end = ceil((float)N/l_w_global) * (my_id + 1);
    int my_stride = l_w_global;
    int my_start = 0;
    int my_end = N;
  // something else ? (dekompozycja blokowo-cykliczna)


    int el_na_watek = ceil( (float) dx_global / l_w_global );
    int moj_start = my_id ; // lub moj_start = moj_id
    int moj_koniec = el_na_watek*(my_id+1) ; // lub moj_koniec = N
    printf("\nWątek %d: my_start %d, my_end %d, my_stride %d\n",
           my_id, my_start, my_end, my_stride);
//   int j=ceil( (float)ROZMIAR/LICZBA_W ); // could be double as well
//    for( i = j*moj_id; i < j*(moj_id+1); i++){
        int i;
  double calka = 0.0;
  dx=dx_global;
    for(i=my_id; i<my_end; i+=my_stride){

        double x1 = a + i*dx;
        calka += 0.5*dx*(funkcja(x1)+funkcja(x1+dx));
        printf("i %d, x1 %lf, funkcja(x1) %lf, całka = %.15lf\n",
        	   i, x1, funkcja(x1), calka);

    }
    pthread_mutex_lock(&bloker);
        calka_global+=calka;
    pthread_mutex_unlock(&bloker);


}

