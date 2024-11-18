#include "PGMimageProcessor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>
#include <string>
#include <queue>
using namespace sngsiy006; 

//default constructor
PGMimageProcessor::PGMimageProcessor(){
    filename = "";
    min_comp = 0, max_comp =0;
    height = 0 , width = 0;
    threshold = 0;
}

// constructor that takes in an imageinput
PGMimageProcessor::PGMimageProcessor(const std::string& inputFile){
    filename = inputFile;
    width = 0,height =0;
    min_comp = 3, min_comp = width*height;
    threshold = 128;
}

/**
 * copy constructor 
 * used to copy the content of the PGMimageProcessor into another object of it kind
*/
PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor& other):
    filename(other.filename),threshold(other.threshold),
    min_comp(other.min_comp),max_comp(other.max_comp)
    ,width(other.width),height(other.height),two_d_vector(other.two_d_vector){
    this->component_list.clear();
    for(int i=0; i< other.component_list.size(); i++){
        this->component_list[i].get()->setUniqueIdentifier(other.component_list[i].get()->getUniqueIdentifier());
        this->component_list[i].get()->setComponentNumberOfPixels(other.component_list[i].get()->getComponentNumberOfPixels());
        this->component_list[i].get()->setComponentPixels(other.component_list[i].get()->getComponentPixels());
    }
}

/**
 * move constructor 
 * used to move the content of the PGMimageProcessor into another object of it kind
*/
PGMimageProcessor::PGMimageProcessor(PGMimageProcessor && other):
    filename(other.filename),threshold(other.threshold),
    min_comp(other.min_comp),max_comp(other.max_comp)
    ,width(other.width),height(other.height){
    two_d_vector =std::move(other.two_d_vector);
    component_list =std::move(other.component_list);
}

/**
 * copy assignment constructor 
 * used to copy the content of the PGMimageProcessor into another object of it kind
*/
PGMimageProcessor& PGMimageProcessor::operator = (const PGMimageProcessor & other)
{
    if(this != &other){
        this->filename = other.filename;
        this->min_comp = other.min_comp;
        this->max_comp = other.max_comp;
        this->width  = other.width;
        this->height = other.height;
        this->threshold   = other.threshold;
        this->two_d_vector =other.two_d_vector;
        this->component_list.clear();
        for(int i=0; i< other.component_list.size(); i++){
            this->component_list[i].get()->setUniqueIdentifier(other.component_list[i].get()->getUniqueIdentifier());
            this->component_list[i].get()->setComponentNumberOfPixels(other.component_list[i].get()->getComponentNumberOfPixels());
            this->component_list[i].get()->setComponentPixels(other.component_list[i].get()->getComponentPixels());
        }

    }
    return *this;
}

/**
 * move assignment constructor 
 * used to move the content of the PGMimageProcessor into another object of it kind
*/
PGMimageProcessor& PGMimageProcessor::operator = (PGMimageProcessor && other)
{
    if(this != &other){
        this->filename = other.filename;
        this->max_comp = other.max_comp;
        this->min_comp = other.min_comp;
        this->width  = other.width;
        this->height = other.height;
        this->threshold   = other.threshold;
        this->two_d_vector =std::move(other.two_d_vector);
        this->component_list =std::move(other.component_list);
    }
    return *this;
}


/* process the input image to extract all the connected components,
based on the supplied threshold (0...255) and excluding any components
of less than the minValidSize. The final number of components that
is stored in the container (after discarding undersized one)
is returned.
*/
int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize){
    two_d_vector = std::move(std::vector(height, std::vector<int>(width)));
    extractGreaterOrEqualComponent(threshold, two_d_vector);
    findComponent(two_d_vector,threshold,minValidSize,width*height);

    return component_list.size();
}


void  PGMimageProcessor::extractGreaterOrEqualComponent(unsigned char threshold,std::vector<std::vector<int>>& data){
 
   // filtering the sata so that we only have the one that
   // is equal to the threshold or greater
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if( ((int)TwoD_data[i][j]) >= ((int)threshold) ){
                
                data[i][j]=255;
            }
            else{
                data[i][j]=0;
            }
        }
    }
}

 
 /**
  * method to find components that meet intesity threshold and minimum 
  * number of components
  * Uses a helper method floodfill
 */
void PGMimageProcessor::findComponent(std::vector<std::vector<int>> & data_vector, const unsigned char threshold, const int min_size, int max_size) {
    std::vector<std::pair<int, int>> coordinate_component;
    std::vector<std::vector<int>>  data_vector_2 = data_vector;
    int count = 1;
    
    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            int current_pixel = data_vector_2[i][j]; 
            
            if (static_cast<int>(current_pixel) >= static_cast<int>(threshold)) {
                int number_components = floodFill(data_vector_2, j, i, 0, coordinate_component, 0);
                if (number_components >= min_size && number_components <= max_size) {
                    std::unique_ptr<ConnectedComponent>component ( new ConnectedComponent());
                    component->setUniqueIdentifier(count);
                    component->setComponentPixels(coordinate_component);
                    component->setComponentNumberOfPixels(number_components);
                    component_list.push_back(std::move(component));
                    ++count;
                }
                else {
                    for (const auto& coord : coordinate_component) {
                        int x = coord.first;
                        int y = coord.second;
                        data_vector[y][x] = 0;
                    }
                }
                coordinate_component.clear();
            }
        }
    } 
}

/**
 * Helper method to findComponent
 * use flood fill algorithm to find & store co-ordinates of the connected components
 * and count the connected components
*/
int PGMimageProcessor::floodFill(std::vector<std::vector<int>>& data, int start_x, int start_y, int visited_pixel,
                                  std::vector<std::pair<int, int>>& coordinates, int count) {
    std::queue<std::pair<int, int>> q;

    q.push(std::make_pair(start_x, start_y));
    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        if (x >= 0 && x < width && y >= 0 && y < height && data[y][x] != visited_pixel) {
            data[y][x] = visited_pixel;
            coordinates.push_back(std::make_pair(x, y));
            ++count;
            q.push(std::make_pair(x + 1, y));
            q.push(std::make_pair(x - 1, y));
            q.push(std::make_pair(x, y + 1));
            q.push(std::make_pair(x, y - 1));
        } else {
            q.pop();
        }
    }
    return count;
}



/* iterates - with an iterator - through the container of connected
components and filter out (remove) all the components which do not
obey the size criteria pass as arguments. The number remaining
after this operation is returned.
*/
int PGMimageProcessor::filterComponentsBySize(int minSizeThreshold, int maxSizeThreshold) {
    std::vector<std::unique_ptr<ConnectedComponent>> components = std::move(component_list);

    int size = components.size();
  
    for(int i = 0; i < size; i++) {
       if(components[i]->getComponentNumberOfPixels() >= minSizeThreshold && components[i]->getComponentNumberOfPixels()<=maxSizeThreshold) {
           components[i]->setUniqueIdentifier(i + 1);
           components[i]->setComponentPixels(components[i].get()->getComponentPixels());
           components[i]->setComponentNumberOfPixels(components[i].get()->getComponentNumberOfPixels());
           component_list.push_back(std::move(components[i]));
       } else {
           std::vector<std::pair<int,int>> coordinates = components[i]->getComponentPixels();
         
           for(int j = 0; j < coordinates.size(); j++) {
                 int x = coordinates[j].first;
                 int y = coordinates[j].second;
                 two_d_vector[y][x] = 0;
           }
       }
   }

   return component_list.size();
}

int PGMimageProcessor::getMaxSize(){
    return width*height;
}

/* creates a new PGM file which contains all current components
(255=component pixel, 0 otherwise) and writes them to a outFileName as a
valid PGM. the return value indicates success of operation
*/
bool PGMimageProcessor::writeComponents(const std::string & outFileName){
    std::shared_ptr<unsigned char[]> out_image(new unsigned char[width*height]);
    int n = width*height;
    
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            out_image[i*width+j]=two_d_vector[i][j];
        }
    }
   
    std::ofstream out(outFileName+".pgm",std::ios::binary);
    out<<"P5\n";
    out<<width<<" "<<height<<"\n";
    out<<255<<"\n";
    
    out.write( reinterpret_cast<char *>(out_image.get()),(n)*sizeof(unsigned char));
    if(!out){
        std::cout<<"Error in file"<<std::endl;
        return false;
    }
    
    out.close();
    return true;

}
// return number of components
int PGMimageProcessor::getComponentCount(void) const{
    return component_list.size();
}

// return number of pixels in largest component
int PGMimageProcessor::getLargestSize() const {
    if (!component_list.empty()) {
        int largestSize = component_list[0]->getComponentNumberOfPixels();
        
        for (int i = 1; i < component_list.size(); i++) {
            int nextSize = component_list[i]->getComponentNumberOfPixels();
            
            if (largestSize < nextSize)
                largestSize = nextSize;
            else
                largestSize = largestSize;
        }
        return largestSize;
    } else {
        return 0;
    }
}

// return number of pixels in smallest component
int PGMimageProcessor::getSmallestSize(void) const {
    int smallestSize = 0;
    if (!component_list.empty()) {
        smallestSize = component_list[0]->getComponentNumberOfPixels();
        
        for (int i = 1; i < component_list.size(); i++) {
            int nextSize = component_list[i]->getComponentNumberOfPixels();
            if (smallestSize < nextSize)
                smallestSize = smallestSize;
            else
                smallestSize = nextSize;
        }
        return smallestSize;
    } else {
        smallestSize  = 0;
        return smallestSize;
    }
    

}


/* print the data for a component to std::cout
see ConnectedComponent class;
print out to std::cout: component ID, number of pixels
*/
void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const{
    std::cout<<theComponent;
}

void PGMimageProcessor::printAllComponentsData()const{
    for(int i=0; i<component_list.size(); i++){
        printComponentData(*component_list[i]);
    }
}

/**
 * Reads and Processes the inputFile and stores its content
 * Uses two helper methods setDimensions and convertToTwoDimension
 * Functions
*/
bool PGMimageProcessor::readFile() {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        std::cout << "File not found. Please enter the correct filename." << std::endl;
        return false;
    }

    bool validHeader = false;
    bool validSize = false;
    bool validIntensity = false;
    bool comment = false;

    int num_of_rows = 0;
    int num_of_cols = 0;
    int maxIntensity = 0;
    int file_ptr_offset = 0;

    std::string line;
    while (getline(in, line)) {
        if (!validHeader) {
            if (line == "P5") {
                validHeader = true;
                file_ptr_offset+=line.length();
            }
        } else if(!comment){
            if(line[0] == '#'){
                comment = true;
                file_ptr_offset+=line.length();
            }
        }else if (!validSize) {
            if (line[0] != '#') {
                std::istringstream iss(line);
                if (iss >> num_of_cols >> num_of_rows) {
                    validSize = true;
                    file_ptr_offset+=line.length();
                }
            }
        } else if (!validIntensity) {
            if (line != "255") {
                std::cout << "Invalid intensity value." << std::endl;
                return false;
            }
            maxIntensity = 255;
            validIntensity = true;
            file_ptr_offset+=line.length();
        } else {
            break;
        }
    }

    if (!validHeader || !validSize || !validIntensity) {
        std::cout << "Invalid PGM file format." << std::endl;
        return false;
    }

    int number_of_pixels = num_of_cols * num_of_rows;
    std::shared_ptr<unsigned char[]> image_data(new unsigned char[number_of_pixels]);

    in.seekg(file_ptr_offset+3,std::ios::beg); // move ptr relative to the beginning
    int pos_file_ptr = in.tellg();
    in.read(reinterpret_cast<char*>(image_data.get()), (number_of_pixels) * sizeof(unsigned char));

    

    if (!in) {
        std::cout << "Error occurred while reading image data." << std::endl;
        return false;
    }

    setDimensions(num_of_cols, num_of_rows);
    convertToTwoDimensions(image_data.get());

    in.close();
    return true;
}

/**
 * Setter method to se the width and height of the image
*/
void PGMimageProcessor::setDimensions(int w , int h){
    width = w;
    height = h;
}

/**
 * setter method to set the min and max of the component
*/
void PGMimageProcessor::setComponentSize(int min_size, int max_size){
    min_comp = min_size;
    max_comp = max_size;
}

/**
 * setter method to set the treshold of the image 
*/
void PGMimageProcessor::setTreshold(int newthreshold){
    threshold = newthreshold;
}

/**
 * Converts the flattened array of InputFile method to 
 * a 2D array
*/
void PGMimageProcessor::convertToTwoDimensions(const unsigned char* image_1D_data){

    TwoD_data= std::vector<std::vector<unsigned char>>(height, std::vector<unsigned char>(width));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            TwoD_data[i][j] = image_1D_data[i * width + j];
        }
    }
}

// destructor
PGMimageProcessor::~PGMimageProcessor(){};