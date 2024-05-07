//
// Created by vardan on 5/7/24.
//
#include "node.h"
#include "headers.h"
#ifndef COMPRESSOR_COMPRESSOR_H
#define COMPRESSOR_COMPRESSOR_H

#endif //COMPRESSOR_COMPRESSOR_H
class compressor
{
private:
    string string_to_be_compressed, encoded_string;
    string file;
    node *root;
    map<char, string> encoding;

    void basename()
    {
        int n = this->file.size();
        int i = n - 1;
        while (i >= 0 && this->file[i] != '.')
            i--;
        if (i < 0)
            return;
        else{
            this->file = this->file.substr(0, i);
        }
    }

    void GENERATE_ENCODING(node *Node, string code = "")
    {
        if (Node == NULL)
            return;
        if (Node->isEnd == 1)
        {
            this->encoding[Node->alp] = code;
            return;
        }
        GENERATE_ENCODING(Node->left, code + "0");
        GENERATE_ENCODING(Node->right, code + "1");
        return;
    }

    // this function will return the root of the compression tree or I may say the decoding tree
    void COMPRESSION_TREE()
    {
        long long n = string_to_be_compressed.size();
        map<char, int> mp;
        for (auto chr : string_to_be_compressed)
        {
            mp[chr]++;
        }
        priority_queue<node *, vector<node *>, Comparator> queue;
        for (auto itr : mp)
        {
            node *temp = new node(itr.first, itr.second);
            queue.push(temp);
        }
        while (queue.size() > 1)
        {
            node *x = queue.top();
            queue.pop();
            node *y = queue.top();
            queue.pop();
            node *sumNode = new node('$', x->val + y->val, 0, x, y);
            queue.push(sumNode);
        }
        // this will return the root node of compression tree
        this->root = queue.top();
    }

    // This is the function where the compression will take place in the program
    void ENCODE_STRING()
    {
        string s = this->string_to_be_compressed;
        string encodedstring = "";
        for (auto it : s)
        {
            encodedstring += this->encoding[it];
        }
        this->encoded_string = encodedstring;
        return;
    }

public:

    void compress(string file_name) {
        string s;
        ifstream file_in(file_name);
        if (file_in.is_open())
        {
            string tmp((istreambuf_iterator<char>(file_in)), istreambuf_iterator<char>());
            s=tmp;
            file_in.close();
        }
        else
        {
            cout << "Unable to open file: " << file_name << endl;
            exit(1);
        }
        this->string_to_be_compressed = s;
        this->file = file_name;
        this->basename();
        this->file += ".zip";
        this->COMPRESSION_TREE();
        cout << "Tree Generated!" << endl;
        this->GENERATE_ENCODING(this->root);
        cout << "Encoding Generated!" << endl;
        this->ENCODE_STRING();
        cout <<"encoded string: "<< this->encoded_string << endl;
        this->checker();
        // save the encoded string
        ofstream out(this->file, ios::binary | ios::out);
        if (!out.is_open()) {
            cout << "Error opening file for writing: " << this->file << endl;
            return;
        }
        int size = int(this->encoding.size());
//        cout<<"size: "<<size<<endl;
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for(auto it: this->encoding){
            out.write(reinterpret_cast<const char*>(&it.first), sizeof(it.first));
            int str_size = it.second.size();
            out.write(reinterpret_cast<const char*>(&str_size), sizeof(str_size));
            const char* data = it.second.c_str();
            out.write(data, str_size);
        }
        int bitIndex = 0;
        int encoded_string_size  = this->encoded_string.size();
        out.write(reinterpret_cast<const char*>(&encoded_string_size), sizeof(encoded_string_size));
        unsigned char byte = 0;
        for (char bit : this->encoded_string) {
            if (bit == '1') {
                byte |= (1 << (bitIndex % 8));
            }
            bitIndex++;
            if (bitIndex % 8 == 0) {
                out.put(byte);
                byte = 0;
            }
        }
        if (bitIndex % 8 != 0) { // Handle the case where the last byte isn't full
            out.put(byte);
        }

        out.close();
    }

    void checker()
    {
        for (auto it : this->encoding)
        {
            cout << it.first << " -> " << it.second << endl;
        }
    }
};
