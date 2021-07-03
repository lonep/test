#include <iostream>
#include <random>
#include <ctime>
#include <map>
#include <vector>
#include <algorithm>


int getRandomNumberInInterval(int intervalBegin, int intervalEnd){
    std::uniform_int_distribution<> interval(intervalBegin,intervalEnd);
    static std::mt19937 mersenne(time(0));
    interval.reset();
    return  interval(mersenne);
}

void synchronize(std::map<int, int> &map1, std::vector<int>& vec1)
{
    for (auto mapIterator = map1.begin(); mapIterator != map1.end(); )
    {
        if (find(vec1.begin(), vec1.end(), mapIterator->second) == vec1.end()) {
            mapIterator = map1.erase(mapIterator);
        }
        else {
            ++mapIterator;
        }
    }
    for (auto vectorIterator = vec1.begin(); vectorIterator != vec1.end(); )
    {
        bool flag = false;
        for (auto& mapIterator : map1)      //Можно было сделать обратный map и пройтись count(c++20), но там
                                            //нету выигрыша, ибо там также просто перебор лежит.
        {
            if (mapIterator.second == *vectorIterator)
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            vectorIterator = vec1.erase(vectorIterator);
        else
            vectorIterator++;
    }

}

template <class Container>
void showContainer(Container &container){
    int i = 0;
    for(auto it:container) {
        std::cout<< i <<'-' << it << ' ';
        i++;
    }
}

template<class First, class Second>
void showContainer(std::map <First, Second> &container){
    for(auto it:container)
        std::cout << it.first << '-' << it.second << ' ';
}

int main() {
    int size = getRandomNumberInInterval(25, 45); //В задании не указано кол-во элементов, поэтому я
                                                                    // взял его случайным в промежутке
    std::vector<int> testVector;
    std::map<int,int> testMap;
     auto mapIterator = testMap.begin();
    for(int i = 0; i < size; i++){
        testVector.push_back(getRandomNumberInInterval(1,9));
        testMap[i] = getRandomNumberInInterval(1,9);
        mapIterator++;
    }

    std::cout << "Vector with random numbers: ";
    showContainer(testVector);
    std::cout << '\n' << "Map with random numbers: ";
    showContainer(testMap);

    int deleteSize = getRandomNumberInInterval(1,15);

    mapIterator = testMap.end();
    std::advance(mapIterator, -deleteSize);
    testMap.erase(mapIterator, testMap.end());

    auto vectorIterator = testVector.end();
    std::advance(vectorIterator, -deleteSize);
    testVector.erase(vectorIterator,testVector.end());


    synchronize(testMap, testVector);
    std::cout <<'\n'<< "-------------------------------------------------------" ;
    std::cout <<'\n'<< "Vector after completing the task: ";
    showContainer(testVector);
    std::cout << '\n' << "Map after completing the task: ";
    showContainer(testMap);
    std::cout <<'\n';
    system("pause");
    return 0;
}
