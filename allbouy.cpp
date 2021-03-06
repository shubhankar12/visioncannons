//
//  allbouy.cpp
//  openLOL
//
//  Created by Shubhankar Agarwal on 6/25/16.
//  Copyright © 2016 Shubhankar Agarwal. All rights reserved.
//

#include "allbouy.hpp"
#include "bouydetection.hpp"



vector<Point>   all_bouy( Mat detect , Mat final_image , double yawI , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g , vector<vector<Point> > contours , int color)
{

    Mat threshold_output;
    vector<Vec4i> hierarchy;
    double l_area = 0;  // area of the largest contour
    int l_c_i = 0;   // largest contour index
 //   double ang = 0;

    /// Detect edges using Threshold
    threshold( detect, threshold_output, thresh, 255, THRESH_BINARY );
    cvtColor(threshold_output, threshold_output, CV_BGR2GRAY);
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    if( contours.size() > 0  )  {  /// checking if any countour is detected

        /// Approximate contours to polygons + get bounding rects and circles
        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );
        vector<Point2f>center( contours.size() );
        vector<float>radius( contours.size() );




        for( int i = 0; i < contours.size(); i++ )
        {   approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
            minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );


        }
        
        

        for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
        {
            double a = contourArea( contours_poly[i],false);  //  Find the area of contour
            if( a > l_area){
                l_area=a;
                l_c_i = i;                //Store the index of largest contour
            }

          //  cout<<"contour:" << contours[i]<<endl;
        }

        if( color == 0){

            circle( final_image, center[l_c_i], (int)radius[l_c_i], Scalar( 0 , 0, 255 ), 2, 8, 0 );
            setLabel(final_image, "Target Red", contours[l_c_i]); }
        else if( color == 1){
            circle( final_image, center[l_c_i], (int)radius[l_c_i], Scalar( 0, 255, 0 ), 2, 8, 0 );
            setLabel(final_image, "Target Green", contours[l_c_i]);
        }
        else if( color == 2)
        {
            circle( final_image, center[l_c_i], (int)radius[l_c_i],  Scalar( 0, 255, 255 ), 2, 8, 0 );
            setLabel(final_image, "Target Yellow", contours[l_c_i]);
        }

        return contours[l_c_i];

    }


      //returns empty bouy if nothing detected
   vector<Point> nobouy;

    return  nobouy;
}

void drawcontours(Mat final_image  , vector<vector<Point> > contours , int color_bouy , vector<Point> contour_r , vector<Point> contour_g , vector<Point> contour_y )
    {
       vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );
     //   vector<Point2f>center( contours.size() );
     //   vector<float>radius( contours.size() );

        for( int i = 0; i < contours.size(); i++ )
        { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
         //   minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
        }

        for( int i = 0; i< contours.size(); i++ )
        {
           // Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         //   drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
            rectangle( final_image, boundRect[i].tl(), boundRect[i].br(),  Scalar( 0 , 0, 255 ), 2, 8, 0 );
        //    circle( final_image, center[i], (int)radius[i], color, 2, 8, 0 );
        }
//    if( contour_r.size() > 0  )  {  /// checking if any countour is detected
//
////
////        vector<Point> bouy;
////        bouy.reserve( contour_r.size() + contour_g.size() + contour_y.size() ); // preallocate memory
////        bouy.insert( bouy.end(), contour_r.begin(), contour_r.end() );
////        bouy.insert( bouy.end(), contour_g.begin(), contour_g.end() );
////        bouy.insert( bouy.end(), contour_y.begin(), contour_y.end() );
////
////
////        /// Approximate contours to polygons + get bounding rects and circles
////
////               vector<Rect> boundRect( bouy.size() );
////        vector<vector<Point> > contours_poly( bouy.size() );
//
//
//         vector<Rect> boundRect_r( contour_r.size() );
//         vector<Rect> boundRect_g( contour_g.size() );
//         vector<Rect> boundRect_y( contour_y.size() );
//
//
//
//        for( int i = 0; i < contour_r.size(); i++ )
//        {   //approxPolyDP( Mat(bouy[i]), contours_poly[i], 3, true );
//           boundRect_r[i] = boundingRect( Mat(contour_r[i]) );
//            cout<<"red"<< boundRect_r[i] << endl;
//        }
//        for( int i = 0; i < contour_g.size(); i++ )
//        {   //approxPolyDP( Mat(bouy[i]), contours_poly[i], 3, true );
//            boundRect_g[i] = boundingRect( Mat(contour_g[i]) );
//            cout<<"green"<< boundRect_g[i] << endl;
//        }
//        for( int i = 0; i < contour_r.size(); i++ )
//        {   //approxPolyDP( Mat(bouy[i]), contours_poly[i], 3, true );
//            boundRect_y[i] = boundingRect( Mat(contour_y[i]) );
//            cout<<"yellow"<<boundRect_y[i] << endl;
//        }
//
//
//     //   Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
//
//
//        // red contour coordinates =0
//        // green contour coordinates = 1
//        // yellow contour coordinates = 2
//
////            rectangle( final_image, boundRect_r[0].tl(), boundRect_r[0].br(),  Scalar( 0 , 0, 255 ), 2, 8, 0 );
////            setLabel(final_image, "Target red", contour_r);
////
////            rectangle( final_image, boundRect_g[1].tl(), boundRect_g[1].br(), Scalar( 0, 255, 0 ), 2, 8, 0 );
////            setLabel(final_image, "Target green", contour_g);
////
////            rectangle( final_image, boundRect_y[2].tl(), boundRect_y[2].br(), Scalar( 0, 255, 255 ), 2, 8, 0 );
////            setLabel(final_image, "Target yellow", contour_y);
//
//
       if(!final_image.empty()){
            imshow( "Contours", final_image );
     }
 //   }
}



