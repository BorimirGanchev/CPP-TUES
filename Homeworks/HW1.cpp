#include <iostream>

using namespace std;

class Vector
{
private:
    int *data;
    size_t size;
    size_t capacity;

    void resize()
    {
        int *newData = new int[this->capacity * 2];
        for (int i = 0; i < this->size; i++)
        {
            newData[i] = this->data[i];
        }
        delete[] this->data;
        this->data = newData;
        this->capacity *= 2;
    }

public:
    Vector()
    {
        this->data = new int[5];
        this->size = 0;
        this->capacity = 5;
    }

    Vector(int *data, size_t size, size_t capacity)
    {

        this->data = data;
        this->size = size;
        this->capacity = capacity;
    }

    ~Vector()
    {
        delete[] this->data;
    }

    Vector &push_back(int value)
    {
        if (this->size == this->capacity)
        {
            this->resize();
        }
        this->data[this->size] = value;
        this->size++;

        return *this;
    }

    Vector &pop_back()
    {
        if (this->size == 0)
        {
            return *this;
        }
        this->size--;
        return *this;
    }

    int at(int index)
    {
        if (index < 0 || index >= this->size)
        {
            return -1; // Indicate failure, as NULL is not appropriate for int
        }
        return data[index];
    }

    size_t getCapacity() const
    {
        return this->capacity;
    }
    size_t getSize() const
    {
        return this->size;
    }

    Vector &insert(int index, int value)
    {
	//Проверка
        if (index < 0 || index > this->size)
        {
            return *this;
        }
	//Тук проверяваме, така че ако случайно няма никакво място в масива, да resize-нем масива, така че после да добавим новия елемент
        if (this->size == this->capacity)
        {
            this->resize();
        }
	//В този цикъл пък првим, така че шитвме някои елементи спрамо позицията на новия елемнт, за да можем да направим място на нови
        for (int i = this->size; i > index; i--) // Shift elements to make space for the new element
        {
            this->data[i] = this->data[i - 1];
        }
        this->data[index] = value;
        this->size++;
        return *this;
    }

    Vector &remove(int index)
    {
	//Проверка за индекса дали е адекватен
        if (index < 0 || index >= this->size) // Check if the index is within bounds
        {
            return *this;
        }
	//Шифтваме елементите, та да премахнем елемента на дадената позиция, която сме подали
        for (int i = index; i < this->size - 1; i++)
        {
            this->data[i] = this->data[i + 1];
        }
        this->size--;
        return *this;
    }
};

int main()
{

    Vector v;

    v.push_back(1).push_back(2).push_back(3).push_back(4).push_back(5);
    v.insert(2, 10);
    cout << "The expected value is 10, the actual value is: " << v.at(2) << endl;
    cout << "The expected capacity is 10, the actual capacity is: " << v.getCapacity() << endl;
    cout << "The expected size is 6, the actual size is: " << v.getSize() << endl;

    v.remove(2);
    cout << "The expected value is 3, the actual value is: " << v.at(2) << endl;
    cout << "The expected capacity is 10, the actual capacity is: " << v.getCapacity() << endl;
    cout << "The expected size is 5, the actual size is: " << v.getSize() << endl;

    return 0;
}
