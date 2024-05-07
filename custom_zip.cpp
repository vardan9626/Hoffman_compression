#include "headers/compressor.h"
#include "headers/decompressor.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "usage: ./compressor <mode> <files>\nmode = 1(for compression)\nmode = 2(for decompression)\n";
        return 1;
    }
    int mode = atoi(argv[1]);

    if(mode!=1 && mode!=2){
        cout<<"Invalid mode!!!\n";
        return 1;
    }

    if(argc < 3){
        cout<<"please enter some files\n";
        return 1;
    }

    if(mode==1){
        for (int i = 2; i < argc; i++)
        {
                compressor zip;
                string orignal_name = argv[i];
                zip.compress(orignal_name);
        }
    }
    else{
        for (int i = 2; i < argc; i++)
        {
            decompressor dc(argv[i]);
            dc.decompress();
            string data = dc.get_data();
            cout<<data<<"\n------------\n";
        }
    }

    return 0;
}