//
// Created by vardan on 5/7/24.
//

#ifndef COMPRESSOR_DECOMPRESSOR_H
#define COMPRESSOR_DECOMPRESSOR_H

#endif //COMPRESSOR_DECOMPRESSOR_H
#include "headers.h"

// Bug fix required in decompress
/* Does not read if only 2 words or 1 word present */

class decompressor{
    string string_to_decompress, decompressed_string;
    char* file_name;
    map<char, string> encoding;
    map<string, char> inv_encoding;

    void get_encoding_and_data(){
        ifstream in_file(this->file_name, ios::binary|ios::in);
        int size;
        in_file.read(reinterpret_cast<char*>(&size), sizeof(size));
        while(size--)
        {
            char key;
            in_file.read((&key), sizeof(key));
            int str_size;
            in_file.read(reinterpret_cast<char*>(&str_size), sizeof(str_size));
            char* encod = new char[str_size+1];
            encod[str_size]=0;
            in_file.read(encod, str_size);
            this->encoding[key]=encod;
        }
        char data;
        int string_size;
        in_file.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
//        cout<<string_size<<endl;
        while(in_file.read(&data,sizeof(data))){
            string s = "00000000";
            for(int i=0;i<8;i++){
                if((data>>i)&1)s[i]='1';
            }
            this->string_to_decompress+=s;
        }
        this->string_to_decompress = this->string_to_decompress.substr(0,string_size);
        //cout<<this->string_to_decompress<<endl;
        in_file.close();
        for(auto it: this->encoding){
            this->inv_encoding[it.second]=it.first;
        }
        return;
    }

public:
    decompressor(char* file){
        int size = 0;
        for(int i=0;file[i]!=0;i++){
            size++;
        }
        this->decompressed_string="";
        this->file_name = new char[size+1];
        memset(this->file_name, 0, size+1);
        memcpy(this->file_name, file, size);
        get_encoding_and_data();
    }
    decompressor(string file){
        int size = file.size();
        this->decompressed_string="";
        this->file_name = new char[size+1];
        memset(this->file_name, 0, size+1);
        memcpy(this->file_name, file.c_str(), size);
        get_encoding_and_data();
    }
    void decompress(){
        int n = this->string_to_decompress.size();
        int len=0;

        string tmp;
        for(int i=0;i<n;i++) {
            if (this->inv_encoding.find(tmp) != this->inv_encoding.end()) {
                this->decompressed_string += this->inv_encoding[tmp];
                tmp = "";
            }
            tmp += this->string_to_decompress[i];
        }
        if(tmp.size()!=0){
            this->decompressed_string += this->inv_encoding[tmp];
        }
    }
    string get_data(){
        return this->decompressed_string;
    }
};
