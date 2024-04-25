#include <iostream>
#include <string>
using namespace std;

class Car
{
protected:
    string m_DriveMode;

private:
    int m_Maxseating;
    int m_price;
    void m_UpdatePrice(int bace = 50000)
    {
        m_price = m_Maxseating * bace;
    }

public:
    string m_brand;
    string m_modle;
    int m_year;

    Car(string x, string y, int z, int s)
    {
        m_brand = x;
        m_modle = y;
        m_year = z;
        m_Maxseating = s;
        m_UpdatePrice();
        m_DriveMode = "No-wheel";
    }
    int Get_m_Maxseating()
    {
        return m_Maxseating;
    }
    int Get_Price()
    {
        return m_price;
    }
    string get_DriveMode()
    {
        return m_DriveMode;
    }
};

class BMW_Car : public Car
{
private:
public:
    BMW_Car(string y, int z, int s) : Car("BMW", y, z, s)
    {
        cout << "Constructing BMW_Car\n";
        m_DriveMode = "Rear-wheel";
    }
    string get_DriveMode()
    {
        return m_DriveMode;
    }
};

class AUDI_Car : public Car
{
private:
public:
    AUDI_Car(string y, int z, int s) : Car("AUDI", y, z, s)
    {
        cout << "Constructing AUDI_Car\n";
        m_DriveMode = "Front-wheel";
    }
    string get_DriveMode()
    {
        return m_DriveMode;
    }
};

class BENZ_Car : public Car
{
private:
public:
    BENZ_Car(string y, int z, int s) : Car("BENZ", y, z, s)
    {
        cout << "Constructing BENZ_Car\n";
        m_DriveMode = "Front-wheel";
    }
    string get_DriveMode()
    {
        return m_DriveMode;
    }
};

int main()
{
    // Car car_0("CGU", "CSIE", 2023, 4);
    // cout << car_0.m_brand;
    // cout << " : Drive Mode = " << car_0.get_DriveMode() << "\n";

    BMW_Car car_1("X5", 2023, 6);
    cout << car_1.m_brand;
    cout << " : Drive Mode = " << car_1.get_DriveMode() << "\n";

    AUDI_Car car_2("A1", 2023, 5);
    cout << car_2.m_brand;
    cout << " : Drive Mode = " << car_2.get_DriveMode() << "\n";

    BENZ_Car car_3("C300", 2024, 2);
    cout << car_3.m_brand;
    cout << " : Drive Mode = " << car_3.get_DriveMode() << "\n";
    return 0;
}
