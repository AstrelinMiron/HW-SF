#include "KMP.h"
#include <iostream>

//������ ����. ���������� ������� � ������������ ������� lps
void computeLPS(std::string pat, int* lps)
{
   //����� ����������� ����������� ��������/��������
    int j = 0;

    lps[0] = 0; // lps[0] is always 0 

    //��������� �������� ��������� ������� � i=1 �� ������� ��������(pat.size())
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

//������ ����. ����� ��������� � ������
int KMPSearch(const std::string& pat, const std::string& txt)
{
    //������ ��� �������� ���������� ���������/��������� ��������
    int* lps = new int[pat.size()];

    computeLPS(pat, lps);

    int patternCounter = 0;
    int i = 0; //������ ��� ������
    int j = 0; //������ ��� ��������
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
        //������������ ����� j ����������
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