//
// KDT.hpp
// CSE 100 Project 1
//
// Last modified by Heitor Schueroff on 01/10/2019
//

#ifndef KDT_HPP
#define KDT_HPP

#include <iostream>
#include <algorithm>
#include <math.h>
#include <limits>
#include <vector>

#include "BST.hpp"

using namespace std;

#define DELTA 0.00005

/**
 * A simple 2D Point struct with (x, y) coordinates.
 */
class Point {
public:
    double x, y;

    /** Default constructor: initializes point at (0, 0) */
    Point() : x(0.0), y(0.0) {}

    /** Constructor that initializes point to given coordinates (x, y) */
    Point(double x, double y) : x(x), y(y) {}

    /** Equals operator */
    bool operator==(const Point &other) const {
        return abs(x - other.x) < DELTA && abs(y - other.y) < DELTA;
    }

    /** Not-equals operator */
    bool operator!=(const Point &other) const {
        return abs(x - other.x) > DELTA || abs(y - other.y) > DELTA;
    }

    /** Less than operator */
    bool operator<(const Point &other) const {
        cerr << "This operator should not be called, you will need "
             << "check the x and y components each time" << endl;
        return false;
    }

    /** Returns the square of the Euclidean distance between points p1 and p2 */
    // TODO: DONE??
    static double squareDistance(const Point &p1, const Point &p2) {
	return (  abs( (pow((p1.x - p2.x) , 2)) - (pow((p1.y - p2.y) , 2)) ) );
	}
};

/** 
 * Overload operator<< to print a Point object to an ostream. 
 */
std::ostream &operator<<(std::ostream &out, const Point &data) {
    out << "(" << data.x << ", " << data.y << ")";
    return out;
}

bool xLessThan(const Point &p1, const Point &p2) { 
    return p1.x < p2.x; 
}

bool yLessThan(const Point &p1, const Point &p2) { 
    return p1.y < p2.y; 
}

/**
 * A 2D Tree with operations to find nearest points in 2D space.
 */
class KDT : public BST<Point> {
public:
    /** 
     * Given a vector of Point references, insert a copy into the KDT.
     *
     * Note. Because of the nature of the KDTree, a simple < operator
     *       will not be sufficient. You will need to check the x and y
     *       coordinates individually.
     * Note. Since KDT inherits from BST, you still have access to the
     *       root, isize, and iheight instance variables and should modify
     *       them accordingly.
     * Note. We have also provided a private helper method for the build
     *       function called buildSubset defined below.
     *
     * Parameters:
     *     points - a vector of points to add into a new KDT
     *
     * Returns:
     *     the number of elements in the built KDT
     */
    // TODO: Done
    virtual unsigned int build(vector<Point> &points) {	
	int s = 0;
	int e = points.size() - 1;
	int d = 0;
	int h = 0;
	root = buildSubset(points, s , e , d , h );
	iheight = iheight + 1;
	//cout << "Root: " << root->data.x <<", "<<root->data.y <<"\n";
	return isize;
    }

    /** 
     * Find the nearest neighbor to a given point.
     *
     * Note. THIS IS DIFFERENT THAN HOW THE PREVIOUS FIND FUNCTION WORKS
     * Note. Since KDT inherits from BST, you still have access to the
     *       root, isize, and iheight member variables.
     * Note. The same dimension ordering you used to build the tree must be used
     *       to search through it.
     * Note. We have added a private helper method for your convenience called
     *       findNNHelper defined below.
     *
     * Paremeters:
     *     p - the query point for which to find its nearest neighbor
     *
     * Returns:
     *     an iterator pointing at the nearest neighbor, or pointing at nullptr
     *     if tree is empty
     */
    // TODO
    virtual iterator findNearestNeighbor(const Point &p) const {
	int d = 0;
	if (root == nullptr)
		return typename BST<Point>::iterator(0);
	//looks for closest neightbor just by  comparing x/y values
	//considers the case user inputs an existing point, where it just returns that point
	else {
		BSTNode<Point>* curr =  root;
		while(curr !=  nullptr) {
			if(d == 0){
				if(p.x == curr->data.x && p.y == curr->data.y)
					return BST<Point>::iterator(curr);
				else if(p.x < curr->data.x){
					if(curr->left == nullptr){
						if(curr->right != nullptr){
							curr = curr->right;
							d = 1;
						}
						else
							break;
					}
					else {
						curr = curr->left;
						d = 1;
					}
				}
				else {
					if(curr->right == nullptr){
						if(curr->left != nullptr){
							curr = curr->left;
							d = 1;
							}
						else
							break;
					}
					else{
						curr = curr->right;
						d = 1;
					}
				}

			}
			else {
				if(p.x == curr->data.x && p.y == curr->data.y)
					return BST<Point>::iterator(curr);
				else if(p.y  < curr->data.y){
					if(curr->left == nullptr){
						if(curr->right != nullptr){
							curr = curr->right;
							d = 0;
							
						}
						else
							break;
					}
					else{
						curr =  curr->left;
						d = 0;
					}
				}
				else {
					if(curr->right == nullptr){
						if (curr->left != nullptr){
							curr = curr->left;
							d = 0;
						}
						else{
							break;  
							}
					}
					else{
						curr = curr->right;
						d = 0;
					}
				}

			}
		}
		//cout <<"here exiting \n";	
		double dis = curr->data.squareDistance(curr->data, p);
		BSTNode<Point>** currp = &curr;
		double * disp = &dis;	
		//function call
		findNNHelper(curr, p, disp, currp , d);
		return BST<Point>::iterator(*currp);
	
	}
    }
 	
	
	

    /** 
     * For the kd-tree, the find method should not be used. Use the function
     * findNearestNeighbor instead.
     */
    virtual iterator find(const Point &p) const override {
        cerr << "The KD Tree find method should not be called" << endl;
        cerr << "Use findNearestNeighbor instead" << endl;
        return 0;
    }

    /** 
     * For the kd-tree, the insert method should not be used. The tree is
     * built all at once. There is no need to add individual points.
     */
    virtual bool insert(const Point &p) override {
        cerr << "The KD Tree insert method should not be called" << endl;
        return false;
    }

private:
    /* 
     * Recursively add a subset of the array to the KD tree.
     *
     * Parameters:member 
     *     items - the list of points that are used to build the kd tree
     *     start - the starting index for this subsection of the tree
     *     end - the non-inclusive ending index for this subtree
     *     dimension - 0 if sorting along the x-axis, and 1 if sorting
     *                 along the y-axis
     * PostConditions: 
     *     the parent node should have its left and right children
     *     set if there are any available points and recursive
     *     calls should be made for the left and right subtree
     *     (again, if there are any remaining points).
     *
     * NOTE: 
     *     We gave you two methods: xLessThan and yLessThan. You may
     *     find them useful for the sort function from #include <algorithm>.
     */
    // TODO: DONE, check for dimention switch
    // NEEDTO: toggle dimension, find a way to stop, check for correct smember ubroot
    BSTNode<Point> *buildSubset(vector<Point> points, 
                                unsigned int start,
                                unsigned int end, 
                                unsigned int dimension,
                                unsigned int height) {

	
	if (height > iheight)
		iheight = height;	
	//NOTE: make sure arithmetic on begin() and end() are working
	if(dimension % 2 == 0) {
		std::sort(points.begin() + start, points.end() - (points.size() - 1 - end) , xLessThan);
	}
	else {
		std::sort(points.begin() + start, points.end() - (points.size() - 1 - end) , yLessThan);
	}
	//middle subscript
	int mid = floor((end - start + 1) / 2 ) + start ;
	//cout<<"mid: "<<mid<<"\n";
	BSTNode<Point>* p = new BSTNode<Point>(points[mid]);
	isize = isize + 1;
	//dimension switch might not work...
	//left
	if (start == mid){
		p->left = nullptr;	
	}
	else {
		p->left = buildSubset(points, start , (mid-1) , dimension+1 , height + 1);
		p->left->parent  =  p;
	}
	//right
	if ( end == mid) {
		p->right = nullptr;
	}
	else {
		p->right = buildSubset(points, (mid + 1) , end , dimension+1 , height + 1);
		p->right->parent = p;
	}
	
	return p;	
}

    /* 
     * Find the node in the subtree that is closest to the given point p
     *  
     * Parameters: 
     *     node - the root of the subtree being searched
     *     queryPoint - the point whose nearest neighbor should be found
     *     smallestSquareDistance - the smallest distance value found in
     *                              the tree so far which can be updated
     *     closestPoint - the node corresponding to the current closest
     *                    node in the tree which can be udpated
     *     dimension - flags whether the node parameter splits remaining
     *                 nodes in its subtree by the x or y dimension
     *                 (has the value of either 0 or 1)
     *
     * PostCondition:
     *     closestPoint points to the nearest neighbor
     */
    // TODO
    void findNNHelper(BSTNode<Point> *node, 
                        const Point &queryPoint,
                        double *smallestSquareDistance,
                        BSTNode<Point> **closestPoint,
                        unsigned int dimension) const {	
	//this boolean will be 0 if previous child visited was left
	//and 1 if previous child was right;
	bool side;
	
	while(node->right != nullptr && node->left !=nullptr){
		if( dimension == 0){
			if(xLessThan(node->data , queryPoint)){
				dimension = 1;
				if(node->right != nullptr){
					findNNHelper(node->right , queryPoint , smallestSquareDistance , closestPoint, dimension);
					side = 1;
					break;
				}
				else{	
					findNNHelper(node->left, queryPoint, smallestSquareDistance, closestPoint, dimension);
					side = 0;
					break;
					}
			}
			else {
				dimension = 1;
				if(node->left != nullptr){
					findNNHelper(node->left , queryPoint , smallestSquareDistance , closestPoint, dimension);
					side = 0;
					break;
				}
				else{
					findNNHelper(node->right, queryPoint, smallestSquareDistance, closestPoint, dimension);
					side = 1;
					break;
				}
			}

		}
		else{
			if(yLessThan(node->data , queryPoint)) {
				dimension = 0;
				if(node->right != nullptr){
					findNNHelper(node->right, queryPoint, smallestSquareDistance, closestPoint, dimension);
					side = 1;
					break;
				}
				else{
					findNNHelper(node->left, queryPoint, smallestSquareDistance, closestPoint, dimension);
					side = 0;
					break;
				}
					
			}
			else{
				dimension = 0;
				if(node->left != nullptr){
					findNNHelper(node->left, queryPoint, smallestSquareDistance, closestPoint, dimension);
					side = 0;
					break;
				}
				else{
					findNNHelper(node->right, queryPoint, smallestSquareDistance, closestPoint, dimension);
					side = 1;
					break;
				}
			}
		}
	//at the end we should always be at a leaf. or its parent.
	}
	double sd1 = node->data.squareDistance(node->data , queryPoint);
	double sdx = sqrt( pow ((node->data.x) - (queryPoint.x) , 2) );
	double sdy = sqrt( pow ((node->data.y) - (queryPoint.y) , 2) );	
	//comparisons
	if(sd1 < *smallestSquareDistance){
		closestPoint = &node;
		return;
	}
	//check if you're at a leaf, if not then check square distance 
	//of either x or y
	else if (node->right != nullptr || node->left != nullptr){
		if (dimension == 1) {
			if(sdy < *smallestSquareDistance ){
				if(side = 0 && node->right != nullptr)
					findNNHelper(node->right, queryPoint, smallestSquareDistance, closestPoint, dimension);
				else if (side = 1 && node->left != nullptr)
					findNNHelper(node->left, queryPoint, smallestSquareDistance, closestPoint, dimension);
				else
					return;
				}
				
			else
				return;
		}
		else{
			if(sdx < *smallestSquareDistance){
				if(side = 0 && node->right != nullptr)
					findNNHelper(node->right, queryPoint, smallestSquareDistance, closestPoint, dimension);
				else if (side = 1 && node->left != nullptr)
					findNNHelper(node->left, queryPoint, smallestSquareDistance, closestPoint, dimension);
				else
					return;
			}
			else return;	
	
		}
	}
	else
		return;
}
};

#endif  // KDT_HPP
