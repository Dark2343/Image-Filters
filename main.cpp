#include <iostream>
#include "../src/bmplib.h"
#include "../src/bmplib.cpp"
unsigned char img[SIZE][SIZE][RGB];
unsigned char img2[SIZE][SIZE][RGB];
using namespace std;


void loadImage ()
{
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Please enter file name of the image to process: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, img);
}

void saveImage () 
{
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, img);
    cout << "File has been created !" << endl;
}

void BWImage (){

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++)
            {

                img[i][j][k] = img[i][j][k/3];
            }
        }
    }
}

void flipImage()
{
    
    string option;

    cout << "Do you want to flip the image\n1- Vertically\n2- Horizontally\n";
    cin >> option;

    if(option == "1"){

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    img2[i][j][k] = img[i][255 - j][k];
                }                
            }
        }
        
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    img[i][j][k] = img2[i][j][k];
                }
            }
        }
    }

    else if (option == "2"){

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    img2[i][j][k] = img[255 - i][j][k];
                }
            }
        }
        
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    img[i][j][k] = img2[i][j][k];
                }
            }
        }
    }
}

void detectEdges()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                if (img[i][j][k] > (img[i + 1][j + 1][k] + 15) || img[i][j][k] > (img[i][j + 1][k] + 15) || img[i][j][k] > (img[i + 1][j][k] + 15) && img[i][j][k] != 255 ){

                    img[i][j][k] = 0;
                }
                else{

                    img[i][j][k] = 255;
                }   
            }
        }
    }
}

void mirrorImage()
{
    string option;
    cout << "Choose which side to mirror\n1-Right side\n2-Left side\n3-Upper side\n4-Bottom side\n";
    cin >> option;

    if (option == "1")
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    img[i][j][k] = img[i][255 - j][k];
                }
            }
        }
    }

    if (option == "2")
    {
        for (int i = 255; i > 0; i--)
        {
            for (int j = 255; j > 0; j--)
            {
                for (int k = 0; k < RGB; k++)
                {
                    img[i][j][k] = img[i][255 - j][k];
                }
            }
        }
    }
    if (option == "3")
    {
        for (int i = 255; i > 0; i--)
        {
            for (int j = 255; j > 0; j--)
            {
                for (int k = 0; k < RGB; k++)
                {
                    img[i][j][k] = img[255 - i][j][k];
                }
            }
        }
    }
    if (option == "4")
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    img[i][j][k] = img[255 - i][j][k];
                }
            }      
        }
    }
}

int main()
{
    char choice;
    loadImage ();
    
    while (true)
    {
    cout << "\nPlease select a filter to apply or 0 to exit:\n" << endl;
    cout << "1- Black & White Filter\n" << endl;
    cout << "2- Flip Image\n" << endl;
    cout << "3- Detect Image Edges\n" << endl;
    cout << "a- Mirror 1/2 Image\n" << endl;
    cout << "s- Save the image to a file\n" << endl;
    cout << "0- Exit\n" << ">> ";
    cin >> choice;

    switch (choice){
      case '1':    
        BWImage();                                        // Black and White Filter
      cout << "Filter applied successfully!" << endl;
        break;
      case '2':
        flipImage();                                     // Flip Filter
        cout << "Filter applied successfully!" << endl;
        break;
      case '3':
        detectEdges();                                   // Detect Image Edges Filter
        cout << "Filter applied successfully!" << endl;
        break;
      case 'a':
        mirrorImage();                                   // Mirror Filter
        cout << "Filter applied successfully!" << endl;
        break;
      case 's':
        saveImage();
        break;
      case '0':
        cout << "Program Ended.";
        return 0;
      default:
        break;
    }
  }
}
