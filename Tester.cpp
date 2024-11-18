#include "PGMimageProcessor.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#define println(x) std::cout << x << std::endl;
using namespace sngsiy006;
PGMimageProcessor imageprocessor ;

/**
 * print information about method extractComponents
 */
int testExtract(int threshold, int minSize,PGMimageProcessor &imageprocessor){
    int number = imageprocessor.extractComponents(threshold,minSize);
    println("Number components at threshold of "+std::to_string(threshold)+
    " and minimum size of "+std::to_string(minSize)+":  "+std::to_string(number));
    return number;
  

}

/**
 * Test extractComponents with different threshold and minimum size
 * 
 */
 TEST_CASE("Test extractComponents"){
    int chessImageTest[13][3] ={
        {1,2,1},{1,3,1},{50,3,1},{128,400,1},{150,455,1},{180,500,6},
        {180,500,6},{200,50,6},{220,100,6},{250,3,2},{255,3,0},{255,2,0},{255,1,2}
        };
    int testImage[15][3] ={
        {1,2,1},{1,3,1},{50,3,1},{128,400,1},{150,455,1},{180,500,1},
        {190,500,3},{200,50,3},{245,100,3},{247,3,0},{250,3,0},{245,6000,3},{245,7000,2},{245,10000,1},{245,12000,0}
        };
    int test1Image[10][3] ={
        {1,2,1},{1,3,1},{150,10000,1},{200,10000,1},{215,455,3},{220,500,7},
        {245,500,5},{247,50,3},{250,3,0},{220,1000,6}
        };
   
    println("\nTest extractComponents:");
    for(int i=0; i<13; i++){
        imageprocessor = std::move(PGMimageProcessor("chess.pgm"));
        imageprocessor.readFile();
        REQUIRE(testExtract(chessImageTest[i][0],chessImageTest[i][1],imageprocessor)==chessImageTest[i][2]);

    }
    for(int i=0; i<15; i++){
        imageprocessor = std::move(PGMimageProcessor("test.pgm"));
        imageprocessor.readFile();
        REQUIRE(testExtract(testImage[i][0],testImage[i][1],imageprocessor)==testImage[i][2]);

    }
    for(int i=0; i<10; i++){
        imageprocessor = std::move(PGMimageProcessor("test1.pgm"));
        imageprocessor.readFile();
        REQUIRE(testExtract(test1Image[i][0],test1Image[i][1],imageprocessor)==test1Image[i][2]);
        imageprocessor.writeComponents("testOutput");

    }
        
}

/**
 * print information about method filterComponentsBySize
 */
int testFilterBySize(int min, int maxSize,PGMimageProcessor &imageprocessor){
    
    int number = imageprocessor.filterComponentsBySize(min,maxSize);
    println("Number components at minimum size of "+std::to_string(min)+
    " and maxmum size of "+std::to_string(maxSize)+":  "+std::to_string(number));
    return number;
}
/**
 * Test filterComponentsBySize with different threshold and minimum size
 * 
 */
 TEST_CASE("Test filterComponentsBySize"){
    println("\nTest filterComponentsBySize:")

    int testList[15][3] ={
        {3,1,0},{100,300,0},{300,4900,1},{4000,5800,2},{4000,6500,2},
        {4000,6900,3},{4000,7200,4},{4000,7700,5},{4000,8000,5},
        {4000,8500,6},{5000,8500,5},{6000,8500,4},{6700,8500,3},{7800,8500,1},{8100,8500,0}
    };
    int testImage[12][3] ={
        {1,2,0},{100,500,0},{1000,5000,0},{5000,6500,1},{6000,7000,1},
        {6000,7800,2},{6000,10000,2},{6000,11000,2},{6000,11600,3},{6500,11600,2},{7800,11600,1},{11600,20000,0}
        };
    int test1Image[8][3] ={
        {1,2,0},{5000,10000,0},{10000,11100,1},{10000,18000,2},{10000,50000,3},{11100,50000,2},
        {18000,50000,1},{50000,100000,0}
        };
    for(int i=0; i<15; i++){
        imageprocessor = std::move(PGMimageProcessor("chess.pgm"));
        imageprocessor.readFile();
        imageprocessor.extractComponents(180,500);
        REQUIRE(testFilterBySize(testList[i][0],testList[i][1],imageprocessor)==testList[i][2]);
    }
     for(int i=0; i<12; i++){
         
        imageprocessor = std::move(PGMimageProcessor("test.pgm"));
        imageprocessor.readFile();
        imageprocessor.extractComponents(245,500);
        REQUIRE(testFilterBySize(testImage[i][0],testImage[i][1],imageprocessor)==testImage[i][2]);

    }
    for(int i=0; i<8; i++){
        imageprocessor = std::move(PGMimageProcessor("test1.pgm"));
        imageprocessor.readFile();
        imageprocessor.extractComponents(215,500);
        REQUIRE(testFilterBySize(test1Image[i][0],test1Image[i][1],imageprocessor)==test1Image[i][2]);

    }
    
}
/**
 * Display true if success full write file else false
 */
bool writeFile(const std::string& name, PGMimageProcessor & imageprocessor){
   
    
    bool value = imageprocessor.writeComponents(name);
    std::string ans = (value>0? "true":"false");
    println("Filename is successful created ? : "+ans);
    return value;
}
/**
 * test writeComponent
 * all output file are named by range size of components like min_size-max_size.pgm
 */
TEST_CASE("test writeComponent"){
     int extractTestList[15][3] ={
        {3,1,0},{100,300,0},{300,4900,1},{4000,5800,2},{4000,6500,2},
        {4000,6900,3},{4000,7200,4},{4000,7700,5},{4000,8000,5},{4000,8500,6},{5000,8500,5},
        {6000,8500,4},{6700,8500,2},{7800,8500,1},{8100,8500,0}
    };
     int testImage[12][3] ={
        {1,2,0},{100,500,0},{1000,5000,0},{5000,6500,1},{6000,7000,1},
        {6000,7800,2},{6000,10000,2},{6000,11000,2},{6000,11600,3},{6500,11600,2},{7800,11600,1},{11600,20000,0}
        };
    int test1Image[8][3] ={
        {1,2,0},{5000,10000,0},{10000,11100,1},{10000,18000,2},{10000,50000,3},{11100,50000,2},
        {18000,50000,1},{50000,100000,0}
        };
    for(int i=0; i<16; i++){
        imageprocessor = std::move(PGMimageProcessor("chess.pgm"));
        imageprocessor.readFile();
        imageprocessor.extractComponents(180,500);
        imageprocessor.filterComponentsBySize(extractTestList[i][0],extractTestList[i][1]);
        REQUIRE(imageprocessor.writeComponents("chess-"+std::to_string(extractTestList[i][0])+"-"+std::to_string(extractTestList[i][1]))==true);
    }

    for(int i=0; i<12; i++){
         
        imageprocessor = std::move(PGMimageProcessor("test.pgm"));
        imageprocessor.readFile();
        imageprocessor.extractComponents(245,500);
        imageprocessor.filterComponentsBySize(testImage[i][0],testImage[i][1]);
        REQUIRE(imageprocessor.writeComponents("test-"+std::to_string(testImage[i][0])+"-"+std::to_string(testImage[i][1]))==true);


    }
    for(int i=0; i<8; i++){
        imageprocessor = std::move(PGMimageProcessor("test1.pgm"));
        imageprocessor.readFile();
        imageprocessor.extractComponents(215,500);
        imageprocessor.filterComponentsBySize(test1Image[i][0],test1Image[i][1]);
        REQUIRE(imageprocessor.writeComponents("test1-"+std::to_string(test1Image[i][0])+"-"+std::to_string(test1Image[i][1]))==true);
    }
   
   

}
/**
 *helper method for testGetComponentCount
 */
int testGetComponentCount(PGMimageProcessor &imageprocessor){
    int value = imageprocessor.getComponentCount();
    println("Final components count =" +std::to_string(value));
    return value;
}

/**
 * test getComponentCount
 */
TEST_CASE(" test getComponentCount"){
    println("\nTest getComponentCount:");

    int extractTestList[16][3] ={
        {3,1,0},{100,300,0},{300,4900,1},{4000,5800,2},{4000,6500,2},
        {4000,6900,3},{4000,7200,4},{4000,7700,5},{4000,8000,5},{4000,8500,6},{5000,8500,5},
        {6000,8500,4},{6700,8500,3},{7800,8500,1},{8100,8500,0}
    };
 
    for(int i=0; i<16; i++){
        imageprocessor = std::move(PGMimageProcessor("chess.pgm"));
        imageprocessor.readFile();
        imageprocessor.extractComponents(180,500);
        imageprocessor.filterComponentsBySize(extractTestList[i][0],extractTestList[i][1]);
        REQUIRE(testGetComponentCount(imageprocessor)==extractTestList[i][2]);
    }
   
}
int testgetLargestSize(PGMimageProcessor &imageprocessor){
    int value = imageprocessor.getLargestSize();
    println("Large components size = " +std::to_string(value));
    return value;
}
/**
 * test getComponentCount
 */
TEST_CASE(" test getLargestSize"){
    println("\nTest getLargestSize:");
    int extractTestList[16][3] ={
        {3,1,0},{100,300,0},{300,4900,5000},{4000,5800,5800},{4000,6500,6500},
        {4000,6900,6800},{4000,7200,7190},{4000,7700,7690},{4000,8000,7999},{4000,8500,8100},{5000,8500,8100},
        {6000,8500,8100},{6700,8500,8100},{7800,8500,8050},{8100,8500,0}
    };
 
    for(int i=0; i<16; i++){
        imageprocessor = std::move(PGMimageProcessor("chess.pgm"));
        imageprocessor.readFile();
        imageprocessor.extractComponents(180,500);
        imageprocessor.filterComponentsBySize(extractTestList[i][0],extractTestList[i][1]);
        REQUIRE(testgetLargestSize(imageprocessor)<= extractTestList[i][2]);
    }
   
}
/**
 * get small size component 
 */
int testgetSmallestSize(PGMimageProcessor &imageprocessor){
    int value = imageprocessor.getSmallestSize();
    println("Small components size = " +std::to_string(value));
    return value;
}
/**
 * test getSmallestSize
 */
TEST_CASE("Test getSmallestSize"){
    println("\nTest getSmallestSize:");
      
     int extractTestList[16][3] ={
        {3,1,0},{100,300,0},{300,4900,4300},{4000,5800,4300},{4000,6500,4300},
        {4000,6900,4300},{4000,7200,4300},{4000,7700,4300},{4000,8000,4300},{4000,8500,4300},{5000,8500,5730},
        {6000,8500,6500},{6700,8500,7100},{7800,8500,7600},{8100,8500,0}
    };
 
    for(int i=0; i<16; i++){
        imageprocessor = std::move(PGMimageProcessor("chess.pgm"));
        imageprocessor.readFile();
        imageprocessor.extractComponents(180,500);
    
        imageprocessor.filterComponentsBySize(extractTestList[i][0],extractTestList[i][1]);
        REQUIRE(testgetSmallestSize(imageprocessor)>= extractTestList[i][2]);
    }
}
/**
 *test using identifier of 3 but with no data
 */
TEST_CASE("test printComponentData"){
    println("\nTest printComponentData  :");
    ConnectedComponent  connectedComponent;
    connectedComponent.setUniqueIdentifier(3);
    imageprocessor.printComponentData(connectedComponent);
}