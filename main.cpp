/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: macbookpro
 *
 * Created on 17 декабря 2017 г., 13:56
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

/*
 * 
 */

int Score(string *m, int len_pat, int num_str){
    int result=0;
    int **profile_matrix;
    profile_matrix=new int* [4];
    for(int i=0;i<4;i++){
        profile_matrix[i]=new int[len_pat];
    }
    for(int i=0;i<num_str;i++){
        for(int j=0;j<len_pat;j++){
            string tmp=m[i];
            switch(tmp[j]){
                case 'A' : profile_matrix[0][j]++; break;
                case 'C' : profile_matrix[1][j]++; break;
                case 'G' : profile_matrix[2][j]++; break;
                case 'T' : profile_matrix[3][j]++; break;
            
            }
        }
    }
    for(int i=0;i<len_pat;i++){
        int max_zn=0;
        for(int j=0;j<4; j++){
            if(max_zn<profile_matrix[j][i]) max_zn=profile_matrix[j][i];
        }
        result+=max_zn;
    }
    return result;
}


string* Motifs(int *bestS, string*DNA, int l, int t)
{
	string* motifs = new string[t];
	for (int i = 0; i < t; i++)
	{
		motifs[i] = new char[l];
	}
	for (int i = 0; i < t; i++)
	{
		motifs[i] = DNA[i].substr(bestS[i], l);
	}
	return motifs;
}

void NextLeaf(int* s, int L, int k)
{
	for (int i = L - 1; i >= 0; i--)
	{
		if (s[i] < k)
		{
			s[i] = s[i] + 1;
			return;
		}
		s[i] = 0;
	}
	return;
}

string* BruteForceMotifSearchAgain(string** DNA, int t, int n, int l)
{
	int count = 0;
        int *bestS = new int[t];
        for (int i = 0; i < t; i++){
            bestS[i] = 0;
        }
        int *s = new int[t];
	for (int i = 0; i < t; i++){
            s[i] = 0;
	}
        int bestScore = 0;
	string* bestM = new string[t];
	int *ss = new int[t];
	for (int i = 0; i < t; i++)
	{
		ss[i] = 0;;
	}
	bestScore = Score(s, DNA, l, t);
	while (true)
	{
		NextLeaf(s, t, n - l);
		if (Score(s, DNA, l, t) >= bestScore)
		{
			bestScore = Score(s, DNA, l, t);
			for (int g = 0; g < t; g++)
			{
				bestS[g] = s[g];
			}
		}
		bool da = true;
		for (int g = 0; g < t; g++)
		{
			if (s[g] != 0)
			{
				da = false;
			}
		}
		if (da == true)
		{
			bestM = Motifs(bestS, DNA, l, t);
			return bestM;
		}
	}
}



int main()
{
    ifstream input_file("Input.txt");
    ofstream output_file("Output.txt");
    string a1,a2;
    string *str;
    string *result;//результат
    string **all_patterns;//все наборы
    int length_pattern;
    int number_str;
    int length_str;
    getline(input_file,a1,' ');
    getline(input_file,a2,' ');
    length_pattern=atoi(a1.c_str());
    number_str=atoi(a2.c_str());
    //cout<<length_pattern<<endl;
    //cout<<number_str<<endl;
    str=new string [number_str];
    result=new string [number_str];
    //считывание строк с ДНК 
    for(int i=0;i<number_str+1;i++){
        string tmp;
        getline(input_file,tmp,'\n');
        if(i>0) str[i-1]=tmp;
    }
    //длина строки
    length_str=str[0].length();
    all_patterns=new string* [number_str];
    for(int i=0;i<number_str;i++){
        all_patterns[i]=new string [length_str-length_pattern+1];
    }
    //заполнение всеми возможными наборами шаблонов 
    for(int i=0;i<number_str;i++){
        string tmp_str=str[i];
        for(int j=0;j<length_str-length_pattern+1;j++){
            for(int k=j;k<j+length_pattern;k++){
                all_patterns[i][j]+=tmp_str[k];
            }
           // cout<<all_patterns[i][j]<<" ";
        }
        //cout<<endl;
    }
    result = BruteForceMotifSearchAgain(all_patterns, number_str, length_str, length_pattern);
    //вывод результата
    for (int i = 0; i < number_str; i++){
	output_file <<result[i] <<" ";
    }
    input_file.close();
    output_file.close();
    return 0;
}
