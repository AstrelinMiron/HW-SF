#include "KMP.h"
#include <iostream>

//Первый этап. Префиксная функция и формирование массива lps
void computeLPS(std::string pat, int* lps)
{
   //длина предыдущего длиннейшего префикса/суффикса
    int j = 0;

    lps[0] = 0; // lps[0] is always 0 

    //вычисляем значения элементов массива с i=1 до размера паттерна(pat.size())
    int i = 1;
    while (i < pat.size())
    {
        if (pat[i] == pat[j])
        {
            j++;
            lps[i] = j;
            i++;
        }
        else // (pat[i] != pat[j])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else // if (j == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

//Второй этап. Поиск подстроки в строке
int KMPSearch(const std::string& pat, const std::string& txt)
{
    //массив для хранения длиннейших суффиксов/префиксов паттерна
    int* lps = new int[pat.size()];

    computeLPS(pat, lps);

    int patternCounter = 0;
    int i = 0; //индекс для строки
    int j = 0; //индекс для паттерна
    while (i < txt.size())
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
        if (j == pat.size())
        {
            //std::cout << "Found pattern at index " << i - j << "\n";
            //j = lps[j - 1];
            patternCounter++;            
            j = lps[0];
        }
        //несовпадение после j совпадений
        else if (i < txt.size() && pat[j] != txt[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i = i + 1;
            }
        }
    }
    delete[] lps;
    return patternCounter;
}

bool IsKPeriodic(const std::string& txt, int k)
{
    if (k < 1)
    {
        return false;
    }

    std::string pat = txt.substr(0, k);

    int k_pat = KMPSearch(pat, txt);
    std::string check;
    for (int i = 0; i < k_pat; i++) { check += pat;}

    if (k_pat * k == txt.length() && txt == check)
    {            
        return true;
    }
    return false;
}