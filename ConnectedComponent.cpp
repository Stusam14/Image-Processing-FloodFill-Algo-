#include "ConnectedComponent.h"
#include <iostream>
using namespace sngsiy006;

// defautlt constructor
ConnectedComponent::ConnectedComponent(){
    comp_no_of_pixels = 0;
    comp_unique_identifier = 0;
    comp_pixels.clear();
}

//constructor to set the compNumberOfPixels and compIndentifier
ConnectedComponent::ConnectedComponent(int compNumberOfPixels, int compIdentifier){
    comp_no_of_pixels = compNumberOfPixels;
    comp_unique_identifier = compIdentifier;  
    comp_pixels.clear();
}


/**
 * copies all contents of an ConnectedComponent into a new object
*/
ConnectedComponent::ConnectedComponent(const ConnectedComponent& other)
{
    comp_pixels.clear();
    comp_no_of_pixels = other.comp_no_of_pixels;
    comp_unique_identifier = other.comp_unique_identifier;

}

/**
 * move constructor
 * moves all content of the connected into a ne object
*/
ConnectedComponent::ConnectedComponent(ConnectedComponent&& other)
{   
    comp_no_of_pixels = other.comp_no_of_pixels;
    comp_unique_identifier = other.comp_unique_identifier;
    comp_pixels = std::move(other.comp_pixels);

    //avoiding dangling ptr
    other.comp_no_of_pixels = 0;
    other.comp_unique_identifier = 0;

}

/**
 * copy assignment
 * copy all content of the connectedComponents into a new object
 * using overloade equals
*/
ConnectedComponent& ConnectedComponent::operator=(const ConnectedComponent& other  ){
    // making sure we not taking in the same object
    if(this!= &other){
        this->comp_no_of_pixels=other.comp_no_of_pixels;
        this->comp_pixels=other.comp_pixels;
        if(this->comp_unique_identifier !=0){
            this->comp_unique_identifier =0;
        }
        if(other.comp_unique_identifier !=0){
            this->comp_unique_identifier = other.comp_unique_identifier;
        }    
    }

    return *this;
}

/**
 * move assignment
 * move all content of the connectedComponents into a new object
 * using overloaded equals
*/
ConnectedComponent& ConnectedComponent::operator=(ConnectedComponent&& other){
    if(this != &other){
        this->comp_no_of_pixels=other.comp_no_of_pixels;
        this->comp_pixels=other.comp_pixels;
        if(this->comp_unique_identifier !=0){
            this->comp_unique_identifier =0;
        }
        if(other.comp_unique_identifier !=0){
            this->comp_unique_identifier = other.comp_unique_identifier;
            other.comp_pixels.clear();
            other.comp_no_of_pixels=0;
            other.comp_unique_identifier=0;
            
        }
    }

    return *this; // returning the current object's reference
}

/**
 * setter method to set the Number Component of pixels
*/
 void ConnectedComponent::setComponentNumberOfPixels(const int noOfCompPixels){

    comp_no_of_pixels = noOfCompPixels;
 }

 /**
  * getter method to get the Number Component of pixels
 */
int ConnectedComponent::getComponentNumberOfPixels() const{

    return comp_no_of_pixels;
}

/**
 * setter method to set the Component Unique ID
*/
void ConnectedComponent::setUniqueIdentifier(const int compIdentifier){
    comp_unique_identifier = compIdentifier;
}

/**
 * getter method to get the Component Unique ID
*/
int ConnectedComponent::getUniqueIdentifier() const{
    return comp_unique_identifier ;
}

/**
 * getter method to get the Component pixel coordinates
*/
std::vector<std::pair<int,int>> ConnectedComponent::getComponentPixels() const{
    return comp_pixels;
}

/**
 * setter method to set the Component pixel coordinates
*/
void ConnectedComponent::setComponentPixels(std::vector<std::pair<int,int>> componentPixels ){
    comp_pixels = componentPixels;
}

/**
 * destructor 
*/
ConnectedComponent::~ConnectedComponent(){}

