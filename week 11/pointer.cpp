#include <iostream>
#include <string>
using namespace std;

class FuncModClass
{
public:
    void FuncMod(int *ptr)
    {
        // cout << "Aiptr = " << *ptr << " Addr " << ptr << endl;
        ptr++;
        // cout << "Biptr = " << *ptr << " Addr " << ptr << endl;
    }
    void FuncMod_pointer(int **ptr)
    {
        (*ptr)++;
    }
    void FuncMod_ref(int *&ptr)
    {
        ptr++;
    }
};

int main()
{
    int arr[4] = {111, 222, 333, 444};
    int *iptr = &arr[1];

    FuncModClass *p = new FuncModClass;
    cout << "iptr = " << *iptr << " Addr " << iptr << endl;

    p->FuncMod(iptr);
    cout << "FuncMod *iptr = " << *iptr << " Addr " << iptr << endl;

    p->FuncMod_pointer(&iptr);
    cout << "FuncMod_pointer *iptr = " << *iptr << " Addr " << iptr << endl;

    p->FuncMod_ref(iptr);
    cout << "FuncMod_ref *iptr = " << *iptr << " Addr " << iptr << endl;
    return 0;
}