/*
include guides to prevent file from being compiled more
than once
*/

#ifndef _CON_COM_HEADER
#define _CON_COM_HEADER
#include <vector>
#include <iostream>

namespace sngsiy006{

    class ConnectedComponent{
        private:
            int comp_no_of_pixels;
            int comp_unique_identifier;
            std::vector<std::pair<int,int>> comp_pixels;
        public:
            /**
             * constructor
            */
            ConnectedComponent();
            /**
             * consturctor to take in parameters
            */
            ConnectedComponent(int compNumberOfPixels, int compIdentifier);
            /**
             * move constructor
            */
            ConnectedComponent(ConnectedComponent&& other);
            /**
             * copy constructor
            */
            ConnectedComponent(const ConnectedComponent& other);
            /**
             * copy assignment
            */
            ConnectedComponent& operator=(const ConnectedComponent& other);
            /**
             * move assignment
            */
            ConnectedComponent& operator=(ConnectedComponent&& other);
            /**
             * sets the components number od pixels
            */
            void setComponentNumberOfPixels(const int noOfCompPixels);
            /**
             * get component number of pixels
            */
            int getComponentNumberOfPixels() const;
            /**
             * set the unique identifier for the component
            */
            void setUniqueIdentifier(const int compIdentifier);
            /**
             * get the unique identifier
            */
            int getUniqueIdentifier() const;
            /**
             * gets the components number of pixels
            */
            std::vector<std::pair<int,int>> getComponentPixels() const;
            /**
             * set the components number of pixels
            */
            void setComponentPixels(std::vector<std::pair<int,int>> componentPixels );
            /**
             * friend function for overloading <<operator
            */
            friend std::ostream& operator<<(std::ostream& print , const ConnectedComponent& object){
                print<<"Component_id is: "<<object.getUniqueIdentifier()<<" number of pixels: "<<object.getComponentNumberOfPixels()<<std::endl;
                return print;
            }
            /**
             * destructor
            */
            ~ConnectedComponent();


    };
}

#endif