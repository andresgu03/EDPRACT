/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>
#include <image.h>

#include <cassert>
void Image::Invert() {
    for (int i=0; i<this->size(); i++)
        this->set_pixel(i,255-this->get_pixel(i));
}

void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2) {

    assert(in1 < in2 && out1 < out2);
    assert(0 <= in1 && in1 <= 255);
    assert(0 <= in2 && in2 <= 255);
    assert(0 <= out1 && out1 <= 255);
    assert(0 <= out2 && out2 <= 255);

    // Pendiente del ajuste
    double k = ((double)out2 - out1) / (in2 - in1);

    for(int i=0; i<this->size(); i++){

        double old_pixel = this->get_pixel(i);

        if(old_pixel >= in1 && old_pixel <= in2) {
            byte new_pixel = round(out1 + k * (old_pixel - in1));
            this->set_pixel(i, new_pixel);
        }
    }

}

Image Image::Crop(int nrow, int ncol, int height, int width) const {
    Image exit_img(height, width, 0) ;
    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ; j++) {
            exit_img.set_pixel( i, j, this->get_pixel(nrow+i,ncol+j));
        }
    }
    return exit_img ;
}

Image Image::Zoom2X() const {
    Image zoomed_img(2*this->get_rows() - 1 , 2*this->get_cols() - 1 , 0 ) ;
    for ( int i = 0 ; i < zoomed_img.get_rows() ; i++){
        if(i%2==0) {
            for (int j = 0; j < zoomed_img.get_cols(); j++) {
                if (j % 2 == 0) {
                    zoomed_img.set_pixel(i, j, this->get_pixel(i / 2, j / 2));
                }
                else {
                    zoomed_img.set_pixel(i, j, (this->Mean(i/2,(j-1)/2,1,2)));//(this->get_pixel(i/2 , (j-1)/ 2))+(this->get_pixel(i/ 2, (j+1)/ 2))/2));
                }
            }
        }
        else{
            for (int j = 0; j < zoomed_img.get_cols(); j++) {
                if (j % 2 == 0) {
                    zoomed_img.set_pixel(i, j, (this->Mean((i-1)/2,j/2,2,1)));//((this->get_pixel((i-1)/2 , j/ 2))+(this->get_pixel((i+1)/ 2, j/ 2))/2));
                }
                else {
                    zoomed_img.set_pixel(i, j, (this->Mean((i-1)/2,(j-1)/2,2,2)));//((this->get_pixel((i-1)/2 , (j-1)/ 2))+(this->get_pixel((i+1)/ 2, (j+1)/ 2))+(this->get_pixel((i-1)/2 , (j+1)/ 2))+(this->get_pixel((i+1)/ 2, (j-1)/ 2))/4));
                }
            }
        }
    }
    return zoomed_img ;
}

Image Image::Subsample(int factor) const {
    assert(factor > 0) ;
    Image icon(this->get_rows()/factor, this->get_cols()/factor , 0);
    for(int i = 0 ; i < icon.get_rows(); i++){
        for(int j = 0 ; j < icon.get_cols() ; j++){
            icon.set_pixel(i,j, this->Mean(i*factor,j*factor,factor,factor)) ;
        }
    }
    return icon ;
}

double Image::Mean(int i, int j, int height, int width) const {
    double sum = 0 ;
    for (int a = 0 ; a < height ; a++){
        for (int b = 0 ; b < width ; b++){
            sum+=this->get_pixel(i+a,j+b) ;
        }
    }
    double mean = round(sum/(double)(height*width)) ;
    return mean ;
}

void Image::ShuffleRows() {}