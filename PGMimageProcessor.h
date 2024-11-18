/*
include guides to prevent file from being compiled more
than once
*/

#ifndef _PGM_IP_HEADER
#define _PGM_IP_HEADER
#include "ConnectedComponent.h"
#include <vector>
#include <string>
#include <memory>
using namespace sngsiy006;

class PGMimageProcessor{
    private:
        std::string filename;
        int width , height;
        int min_comp , max_comp , threshold;
        std::vector<std::vector<unsigned char>> TwoD_data;
        std::vector<std::vector<int>>  two_d_vector;
        std::vector<std::unique_ptr<ConnectedComponent>> component_list;
    public:
        /**
         * default constructor for PGMimageProcessor
        */
        PGMimageProcessor();
        /**
         * consturctor to take in the file
        */
        PGMimageProcessor(const std::string& inputFile);
        /**
         * copy constructor
        */
        PGMimageProcessor(const PGMimageProcessor& other);
        /**
         * move constructor
        */
        PGMimageProcessor(PGMimageProcessor && other);
        /**
         * copy assignment
        */
        PGMimageProcessor& operator = (const PGMimageProcessor & other);
        /**
         * move assignment
        */
        PGMimageProcessor& operator = (PGMimageProcessor && other);
        
        /**
         * Methos to readfile
        */
        bool readFile();
        /**
         * set image dimension
        */
        void setDimensions(int  w , int h);
        /**
         * converts fattened array to 2D
        */
        void convertToTwoDimensions(const unsigned char *image_1D_data);
        /**
         * Extracts components
        */
        int extractComponents(unsigned char threshold, int minValidSize);
        /**
         * helper method to extract components
        */
        void extractGreaterOrEqualComponent(unsigned char threshold,std::vector<std::vector<int>>& data_vector);
        /**
         * retrieves the component based on a treshold
        */
        void findComponent(std::vector<std::vector<int>> & data_vector, const unsigned char threshold, const int min_size, int max_size);
        /**
         * helper method findcomponent, using floodfill algorithms
        */
        int floodFill(std::vector<std::vector<int>>& data, int start_x, int start_y, int visited_pixel,
        std::vector<std::pair<int, int>>& coordinates, int counter);
        /**
         * filtering components using comp_size
        */
        int filterComponentsBySize(int minSize, int maxSize);
        /**
         * writes components to outfile
        */
        bool writeComponents(const std::string & outFileName);
        /**
         * gets the component maximum size
        */
        int getMaxSize();
        /**
         * sets the minimum and maximum size of the component
        */
        void setComponentSize(int min,int max);
        /**
         * sets the threshold of the image
        */
        void setTreshold(int t);
        /**
         * gets the component count
        */
        int getComponentCount(void) const;
        /**
         * gets the Largest size
        */
        int getLargestSize(void) const;
        /**
         * gets the smallest size
        */
        int getSmallestSize(void) const;
        /**
         * prints the a single connectComponents using overloade <<
        */
        void printComponentData(const ConnectedComponent & theComponent) const;
        /**
         * helper method for printComponentData to print all Connected data
        */
        void printAllComponentsData()const;
        /**
         * destructor
        */
        ~PGMimageProcessor();
            

};

#endif