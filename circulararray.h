#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray();    //done
    CircularArray(int _capacity); //done
    virtual ~CircularArray();     //done
    void push_front(T data);      //done
    void push_back(T data);       //done
    void insert(T data, int pos); //done
    T pop_front();          //done
    T pop_back();           //done
    bool is_full();         //done
    bool is_empty();        //done
    int size();             //done
    void clear();           //done
    T &operator[](int i){       //done
      return this->array[i];
    };                    
    void sort();              //done
    bool is_sorted();       //done
    void reverse();         //
    string to_string(string sep=" ");//done

private:
    int next(int);    //done
    int prev(int);    //done
    void heapify(T* arr, int size, int i);
    void heap_sort(T* arr, int size);

};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = "";
    int j = this->front; 
    for (int i = 0; i < size(); i++)
    {
        result += std::to_string((*this)[j]) + sep;
        j=next(j);
    }    
    return result;    
}
//*****************************************************************
template <class T>
bool CircularArray<T>::is_empty()
{
    return (front == -1);
}

template <class T>
bool CircularArray<T>::is_full(){
  return next(back)==front;
}
//*****************************************************************
//PUSH BACK
template <class T>
void CircularArray<T>::push_back(T data)
{
    if (is_full())
    {
        cout << "ARRAY LLENO"<<endl<<endl;
        return;
    }
    
    /* Cuando la COLA se encuentra vacía inicialmente,
    se ponen los index de rear y front en 0 porque ahora el array tendrá 1 elemento.*/
    if (is_empty())
    {
        front = 0;
        back = 0;
    }
 
    // Cuando el REAR se encuentra en la última posición
    else if (back == capacity-1)
        back = 0;
 
    // en cualquier otro caso...
    else
        back = back+1;
    
    //Ingresar dato (del parámetro) al array
    array[back] = data;
}
//*****************************************************************
//PUSH FRONT
template <class T>
void CircularArray<T>::push_front(T data)
{
    //Verificar si el array se encontraba lleno en cuyo caso debería aumentarse el tamaño de este (aumentar el capacity con un resize)
    if (is_full())
    {
        cout<<"ARRAY LLENO"<<endl<<endl;
        return;
    }
    
    // Paso realizar si el array estaba inicialmente vacio
    if (is_empty())
    {
        front = 0;
        back = 0;
    }
 
    // En caso de que el front se encuentre en el index=0 del array
    else if (front == 0)
        front = capacity - 1 ; //
 
    else //En caso de que esté en cualquier otro punto del array...
        front = front-1;

    // insertar dato (del parámetro) al array
    array[front] = data ;
}

//*****************************************************************
//DELETEAR DEL FRONT
template <class T>
T CircularArray<T>::pop_front()
{
  T aux=array[front];
  if (is_empty())
  {
    cout<<"ARRAY SIN ELEMENTOS"<<endl<<endl;
    return -1;
  }
 
  if(front==back)
  {
    front=-1;
    back=-1;
  }
  else if(front==capacity-1){
    front=0;
  }
  else
    front=front+1;
  
  return aux;
}

//*****************************************************************
//DELETEAR DEL BACK
template <class T>
T CircularArray<T>::pop_back()
{
    T aux=array[back];
    if (is_empty())
    {
        cout << "ARRAY SIN ELEMENTOS" <<endl<< endl ;
        return -1;
    }
    
    // Cuando el array tiene 1 solo elemento rear_idx==front_idx
    if (front == back)
    {
        front = -1; 
        back = -1;
        //se ponen los f/r_idx en -1 porque el array pasaría a estar vacío indipendiente del valor de los idx puesto que solo había un elemento
    }
    else if (back == 0)
        back = capacity-1;
    else
        back =back-1;
    return aux;
}

//*****************************************************************
//size: retorna la cantidad actual de elementos del array;
template <class T>
int CircularArray<T>::size(){
  int j=this->front;
  if(front==-1 || back==-1)
  {
    return 0;
  }

  if(front==back)
  {
    return 1;
  }
  int size=1;
  while(j!=back)
  {
    size=size+1;
    j=next(j);
  }
  return size;
}
//*****************************************************************
//clear
template <class T>
void CircularArray<T>::clear(){
  front = -1;
  back = -1;
}
//*****************************************************************
template <class T>
void CircularArray<T>::insert(T data, int pos)
{
  if(is_empty())
  {
    front=pos;
    back=pos;
  }
  array[pos]=data;
}

template <class T>
void CircularArray<T>::heapify(T* arr, int size, int i){
    int valor_max = i; // Toma al nodo raiz como valor_max
    int hijo_izq = 2 * i + 1; // left = 2 * i + 1
    int hijo_der = 2 * i + 2; // right = 2 * i + 2
 
    //Verifica si el hijo izq es mayor al valor_max
    if (hijo_izq < size && arr[hijo_izq] > arr[valor_max])
        valor_max = hijo_izq; //Si lo es, valor max toma el indice del hijo
 
    //Lo mismo para el hijo derecho
    if (hijo_der < size && arr[hijo_der] > arr[valor_max])
        valor_max = hijo_der;
 
    //Si es que el valor maximo no terminó siendo el que se ingresó, intercambian lugares en el array
    if (valor_max != i) {
        swap(arr[i], arr[valor_max]);
 
        //Se aplica heapify recursivamente en el arbol, ahora a partir del nuevo subarbol
        heapify(arr, size, valor_max);
    }
}
 
template <class T>
void CircularArray<T>::heap_sort(T* arr, int size)
{
    //Aplica heapify en cada nodo padre del heap
    for (int i = (size - 1) / 2; i >= 0; i--)
        heapify(arr, size, i);
 
    //Se va reduciendo size del heap
    for (int i = size - 1; i > 0; i--) {
        //Intercambia el nodo raíz (mayor valor) con el ultimo
        swap(arr[0], arr[i]);
 
        //aplica heapify al heap reducido, desde su nodo raiz
        heapify(arr, i, 0);
    }
}


template <class T>
void CircularArray<T>::sort()
{
  T *arr = new T[this->size()];
  int j=this->front;
  for(int i=0;i<size();i++){
    arr[i]=array[j];
    j=next(j);
  }
  heap_sort(arr, size());
  j=this->front;

  for(int i=0;i<size();i++){
    array[j]=arr[i];
    j=next(j);
  }

  
}

template <class T>
bool CircularArray<T>::is_sorted()
{
  int j=this->front;
  int counter=1;
  for(int i=1;i<size();i++){
    if(array[j]<=array[next(j)])
    {
      counter=counter+1;
    }
    j=next(j);
  }
  return counter==size();
}

template <class T>
void CircularArray<T>::reverse()
{
  T *arr=new T[this->size()];
  int j=this->front;
  //Revirtiendo y moviendo al auxiliar
  for(int i=(size()-1);i>-1;i--){
    arr[i]=array[j];
    j=next(j);
  }
  //revirtiendo el array
  j=this->front;

  for(int i=0;i<size();i++){
    array[j]=arr[i];
    j=next(j);
  }
}
