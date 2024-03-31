#include <iostream>
#include <string>
#include <cstring>
#include <exception>

using namespace std;

/*В тази задача, ще трябва да създадете система за състезания. За целта ще трябва да създадете следните класове:
Race
Базов клас, в който трябва да имплементирате дефоултен конструктор, конструктор с параметри, копиращ конструктор, предефиниран оператор =. 

Класът трябва да има следните полета:
raceName (char*)
results (double*)
numberOfResults (size_t)
numberOfTotaRaces (int) - статична променлива за броят на всички създадени състезания
Дефоултният конструктор трябва да зададе празно име и да заделя памет за един резултат. Конструктурът с параметри приема име на състезанието, масив от резултати и неговия размер.

Ограничения:
броят на  results > 0;
results и raceName да НЕ бъдат nullptr;

Класът трябва да има метод getTotalRaces, който връща броят на всички създадени състезания, както и метод printRaceInformation, който да изписва на екрана информацията за състезанието в следния формат:
<totalRaces> <raceName> <avgResult>
Formula1Race
Този клас ще наследява Race и ще съдържа две допълнителни полета:
teams(string*)
numberOfTeams (size_t)

Ограничения:
teams да НЕ бъде nullptr;
броят на екипите> 0

Класът трябва да покрива Rule of 3 (конструктор с параметри, копиращ конструктор и operator=). 
Също така, този клас трябва да предефинира метода printRaceInformation, който да изписва информацията по следния начин:
 <totalRaces> <raceName> <avgResult>
<teams[0]>
…
<teams[numberOfTeams]>
*/




class Race
{
protected:
    char* raceName;
    double* results;
    size_t numberOfResults;
    static int numberOfTotalRaces;
    // TODO add the necessary fields

public:
    Race(): raceName(nullptr), results(nullptr), numberOfResults(0) {
        numberOfTotalRaces++;
    }

    Race(const char *raceName, const double *results, size_t numberOfResults): raceName(nullptr), results(nullptr), numberOfResults(numberOfResults) {
        this->raceName = new char[strlen(raceName) + 1];
        strcpy(this->raceName, raceName);
        this->results = new double[numberOfResults];
        for(size_t i = 0; i < numberOfResults; ++i)
            this->results[i] = results[i];

        numberOfTotalRaces++;
    }
    Race(const Race &other): raceName(nullptr), results(nullptr), numberOfResults(other.numberOfResults) {
        this->raceName = strdup(other.raceName);
        this->results = new double[other.numberOfResults];
        for(size_t i = 0; i < other.numberOfResults; ++i)
            this->results[i] = other.results[i];
        numberOfTotalRaces++;
    }

    ~Race() {
        delete[] raceName;
        delete[] results;
        numberOfTotalRaces--;
    }

    Race &operator=(const Race &other) {
        if(this == &other)
            return *this;

        delete[] raceName;
        delete[] results;
        this->raceName = strdup(other.raceName);
        this->results = new double[other.numberOfResults];
        for(size_t i = 0; i < other.numberOfResults; ++i)
            this->results[i] = other.results[i];

        this->numberOfResults = other.numberOfResults;

        return *this;
    }

    static int getTotalRaces() {
        return numberOfTotalRaces;
    }

    void printRaceInformation() const {
        if(numberOfResults == 0 || results == nullptr || raceName == nullptr)
            return;

        double total = 0;
        for(size_t i = 0; i < numberOfResults; ++i)
            total += results[i];
        
        double avgResult = total / numberOfResults;

        cout << "Nummber of total races :"<< numberOfTotalRaces << " " << raceName <<"Average result: "<< avgResult << endl;
    }
};

int Race::numberOfTotalRaces = 0;

class Formula1Race : public Race
{
private:
    string* teams;
    size_t numberOfTeams;

public:
        Formula1Race(const char *raceName, const double *results, size_t numberOfResults, const string *teams, size_t numberOfTeams): Race(raceName, results, numberOfResults), teams(nullptr), numberOfTeams(numberOfTeams) {
        if(numberOfTeams <= 0 || teams == nullptr)
        {   
            throw invalid_argument("Greshka choveshka");
        }
        this->teams = new string[numberOfTeams];
        for(size_t i = 0; i < numberOfTeams; ++i)
            this->teams[i] = teams[i];
    }
    
    Formula1Race(const Formula1Race &other): Race(other), teams(nullptr), numberOfTeams(other.numberOfTeams) {
        this->teams = new string[other.numberOfTeams];
        for(size_t i = 0; i < other.numberOfTeams; ++i)
            this->teams[i] = other.teams[i];
    }

    ~Formula1Race() {
        delete[] teams;
    }

    Formula1Race &operator=(const Formula1Race &other) {
        if(this == &other)
            return *this;

        Race::operator=(other);

        delete[] teams;

        this->teams = new string[other.numberOfTeams];
        for(size_t i = 0; i < other.numberOfTeams; ++i)
            this->teams[i] = other.teams[i];

        this->numberOfTeams = other.numberOfTeams;

        return *this;
    }

    void printRaceInformation() const {
        Race::printRaceInformation();
        for(size_t i = 0; i < numberOfTeams; ++i)
            cout << teams[i] << endl;
    }
};





int main()
{
    double results[] = {1,2, 3, 4};
    string teams[] = {"Team1(mrecedes)", "Team2(ferari)", "Team3(red bull)"};
    //mnogo dobra pobeda na ferari btw pyrwo i vtoro mqsto
    Formula1Race race("Race 1(Australia grand peix) ", results, 4, teams, 3);
    race.printRaceInformation();

    return 0;
}



