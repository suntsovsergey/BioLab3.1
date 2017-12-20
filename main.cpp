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
int Score(int* fnp, string* m, int len_pat, int num_str){
    int score = 0;
    int *profile_matrix;
    profile_matrix=new int [4];
    for (int i = 0; i < len_pat;i++){
        profile_matrix[0]=0;
        profile_matrix[1]=0;
        profile_matrix[2]=0;
        profile_matrix[3]=0;
        for (int j = 0; j < num_str; j++){
            switch(m[j][fnp[j] + i]){
                case 'A' : profile_matrix[0]++; break;
                case 'C' : profile_matrix[1]++; break;
                case 'G' : profile_matrix[2]++; break;
                case 'T' : profile_matrix[3]++; break;
                }
        }
        int maxzn=0;
        for(int k=0;k<4;k++){
            if(maxzn<=profile_matrix[k]){
                maxzn=profile_matrix[k];
            }
        }
        score+=maxzn;
    }
    return score;
}

void NextLeaf(int* fnp, int L, int k){
    for (int i = L - 1; i >= 0; i--) {
	if (fnp[i] < k){
            fnp[i] = fnp[i] + 1;
            return;
	}
	fnp[i] = 0;
    }
    return;
}
//получение искомых мотивов
string* give_motifs(int *bestS, string* str, int len_pat, int num_str){
    string* m = new string[num_str];
    for (int i = 0; i < num_str; i++){
	m[i] = new char[len_pat];
    }
    for (int i = 0; i < num_str; i++){
        m[i] = str[i].substr(bestS[i], len_pat);
    }
    return m;
}
// слайд 26 из 3 презентации
string* BruteForce(string* str, int num_str, int n, int len_pat, int* fnp,  int& best_score){
    int count = 0;
    int *score_pos = new int[num_str];//номера первых элементов паттерна с макс score
    for (int i = 0; i < num_str; i++){
        score_pos[i]=0;
    }
    string* motifs = new string[num_str];
    best_score = Score(fnp, str, len_pat, num_str);
    while (true){
	NextLeaf(fnp, num_str, n - len_pat);
	if (Score(fnp, str, len_pat, num_str) >= best_score){
            best_score = Score(fnp, str, len_pat, num_str);
            for (int i = 0; i < num_str; i++) {
		score_pos[i] = fnp[i];
            }
	}
	bool flag = true;
	for (int i = 0; i < num_str; i++){
            if (fnp[i] != 0){
                flag = false;
            }
        }
	if (flag == true){
            cout<<best_score;
            motifs=give_motifs( score_pos , str, len_pat, num_str);
            return motifs;
	}
    }
}

int main(){
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string a1,a2;
    string *result;//результат
    int length_pattern;//длина паттерна
    int number_str;//кол-во строк
    int length_str;//длина строки
    int best_score=0;//наилучшее score
    getline(input_file, a1, ' ');
    getline(input_file, a2, '\n');
    length_pattern= atoi(a1.c_str());	// размер шаблона
    number_str= atoi(a2.c_str());	// число экземпляров ДНК
    string* str = new string[number_str];
    result=new string [number_str];
    int *first_number_pattern = new int[number_str];// массив с первыми номерами для паттерна
    // считывание строк 
    for (int i = 0; i < number_str; i++){
	getline(input_file, str[i]);
	first_number_pattern[i] = 0;
    } 
    length_str = strlen(str[0].c_str());
    result = BruteForce(str, number_str, length_str, length_pattern, first_number_pattern, best_score);
    for (int i = 0; i < number_str; i++){
	output_file << result[i]<<" ";
    }
    output_file.close();
    input_file.close();
    return 0;
}

