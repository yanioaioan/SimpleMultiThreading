#include <iostream>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <vector>

using namespace std;

class  P
{
public:
     P()
     {
       m_a =0;
     }

     int m_a;
};


pthread_mutex_t lock_mutex;

typedef struct s_xyzzy {
    std::vector<P> inMyvector;
    std::vector<P> outMyvector;
} xyzzy;


static int counter;
class  Foo
{
public:
     Foo() {}

     static void * doSmth(/*void *myvector*/ void * plugh)
     {
//         std::vector<P> castedVector = *(static_cast< std::vector<P> * > (myvector));
//         std::cout<<"..doind smth.."<<std::endl;

//         P p;p.m_a=11;

//         pthread_mutex_lock(&lock_mutex);
//             castedVector.push_back(p);
//         pthread_mutex_unlock(&lock_mutex);

//         myvector =((void*)&castedVector.at(0));


                  s_xyzzy *s = (static_cast<  s_xyzzy* > (plugh));
                  std::vector<P> castedVector = s->inMyvector;
                  std::cout<<"..doind smth.."<<std::endl;

                  P *p=new P();
                  p->m_a=counter++;

                  pthread_mutex_lock(&lock_mutex);
                      castedVector.push_back(*p);
                  pthread_mutex_unlock(&lock_mutex);


//                  s->outMyvector = *(( std::vector<P>*)&castedVector.at(0));
                  s->outMyvector = castedVector;


     }
     static void * thread_talk(void * array){}


};


const int NUMBER_OF_THREADS = 3;

void * thread_talk(void * thread_nr)

{

  int a = *(static_cast<int*>(thread_nr));
  sleep(a+1);
  cout << "Thread " <<  a <<" has finished"  << endl;

  pthread_exit(NULL);
//  return 0;
}




int main()
{
//    int temp_arg[NUMBER_OF_THREADS];

//    pthread_t thread[NUMBER_OF_THREADS];

//    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
//    {
//       temp_arg[current_t]   = current_t;

//       int result = pthread_create(&thread[current_t], NULL, (thread_talk), static_cast<void*>(&temp_arg[current_t]))  ;

//       if (result !=0)
//       {
//       cout << "Error creating thread " << current_t << ". Return code:" << result <<  endl;
//       }

//    }

//    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
//    {
//     pthread_join(thread[current_t], NULL);
//    }

//    cout << "All threads completed.\n" ;




    Foo foo;
    std::vector<P> inmyvector;

    for(int i=0;i<10;i++)
    {
       P p;
       inmyvector.push_back(p);
    }

    std::vector<P> outmyvector;

    //int temp_arg[NUMBER_OF_THREADS];

//    std::vector< std::vector<P> > vectorOfVectorsOfP;
//    vectorOfVectorsOfP.resize(3);




    xyzzy *plugh = new xyzzy;

    plugh->inMyvector = inmyvector;
    outmyvector.resize(inmyvector.size());
    plugh->outMyvector = outmyvector;



    pthread_t thread[NUMBER_OF_THREADS];

    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
    {
//       vectorOfVectorsOfP[current_t] = myvector;

       int result = pthread_create(&thread[current_t], NULL, (&Foo::doSmth), static_cast<void*>(/*vectorOfVectorsOfP[current_t]*/plugh));

       if (result !=0)
       {
       cout << "Error creating thread " << current_t << ". Return code:" << result <<  endl;
       }

    }

    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
    {
     pthread_join(thread[current_t], NULL);
    }



//    for(int i=0;i<vectorOfVectorsOfP.size();i++)
    {
        for(int j=0;j<plugh->outMyvector.size();j++)
        {
           std::cout<<plugh->outMyvector[j].m_a<<std::endl;
        }
    }

    delete plugh;

    cout << "All threads completed.\n" ;


    return 0;
}

