#include "PGMimageProcessor.h"
// #include "ConnectedComponent.h"
#include <iostream>
using namespace sngsiy006;

int main(int argc , char *argv[]){

    int min = 3, threshold = 128 ;
    int max;
    std::string inputFile , outputFile;
    bool print_all_bool = false ,
    min_max_bool = false , 
    threshold_bool = false, 
    outputfile_name_bool =false;

    if(argc < 2){
        std::cout<< "provide the correct number of arguments\n";
        return 0;
    };
    // handling connand line inputs
    for(int i = 0 ; i < argc ; i++){

        if(i == 1) inputFile = argv[i];

        if(argv[i][0] == '-'&& argv[i][1] == 's'){
            min = std::stoi(argv[i+1]);
            max = std::stoi(argv[i+2]);
            min_max_bool = true;

        }
        if(argv[i][0] == '-'&& argv[i][1] == 't'){
            threshold = std::stoi(argv[i+1]);
            threshold_bool =true;
        }
        if(argv[i][0] == '-' && argv[i][1] == 'p'){
            print_all_bool = true;
        }
        if(argv[i][0] == '-' && argv[i][1] == 'w'){
            outputFile = argv[i+1];
            outputfile_name_bool=true;
        }

    }


    PGMimageProcessor imageprocessor(inputFile);

    //object call to read the file and process image
    imageprocessor.readFile();

    if(!min_max_bool){
        max = imageprocessor.getMaxSize();
    }

    imageprocessor.setComponentSize(min,max);
    imageprocessor.setTreshold(threshold);

    

    if(print_all_bool){
        imageprocessor.extractComponents(threshold,min);
        imageprocessor.filterComponentsBySize(min,max);

        imageprocessor.printAllComponentsData();
        std::cout <<"total number of components = " << std::to_string(imageprocessor.getComponentCount()) << std::endl;
        std::cout <<"component smallest size = " << std::to_string(imageprocessor.getSmallestSize()) << std::endl;
        std::cout << "component largest size = "<< std::to_string(imageprocessor.getLargestSize()) << std::endl;

    }else{
        imageprocessor.extractComponents(threshold,min);
        imageprocessor.filterComponentsBySize(min,max);
    }

    if(!outputfile_name_bool){
        outputFile = "b";
    }

    imageprocessor.writeComponents(outputFile);
}

