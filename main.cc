//#include "partial_box2d_iterator.h"
#include <iostream>
#include "partial_image2d.h"


void version3();
void version4();
void version6();
void version8();




int main()
{
    /*
    version3();
    version4();
    version6();
	*/
	version8();
	return 0;
}



void version3()
{
	std::cout<<"Version 3 : carte de distance\n";
    image2d<unsigned> input({22,18});
    unsigned ima[] = 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,
    0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,0,0,0,
    0,0,0,0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,
    0,0,0,0,0,0,0,1,0,0,1,1,1,1,0,0,0,0,
    0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,
    0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,
    0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,
    0,0,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,
    0,1,1,1,1,1,1,0,0,1,1,1,0,0,1,1,0,0,
    0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,
    0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,
    0,0,0,1,0,1,0,0,0,1,1,1,0,0,1,0,0,0,
    0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,1,1,0,
    0,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1};
    input.fill_with(ima);
    
    input.compute_dmap(input).affiche();

}

//version 4
void version4()
{
	std::cout<<"Version 4 : parcourt partial box2d\n";
    image2d<unsigned> input({3,3});
    unsigned ima[] = 
    {2,1,1,
	 0,0,1,
	 1,1,1};
    input.fill_with(ima);
    partial_box2d part(input);
    partial_box2d_iterator iter(part);
    for (iter.start();iter.isdone()==false;iter.next())
    {
			iter.get().affichepoint();
	}
    
    
    
    
    partial_box2d_iterator iter2(part);
    for (iter2.start();iter2.isdone()==false;iter2.next())
    {
			iter2.get().affichepoint();
	}
	
	
	std::cout<<"\n";
	
}

// Version 6
void version6()
{
    std::cout<<"Version 6 : carte de distance pour partial image2d\n";
    image2d<unsigned> input({6,5});
    // image squelette
    unsigned ima_skeleton[] = 
    {2,1,1,1,0,
     0,0,0,1,0,
     0,1,1,1,0,
     0,1,0,1,0,
     1,1,0,0,0,
     0,1,1,1,3};
     
     // contenant les valeurs du partial image
     unsigned ima_value[] = 
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    input.fill_with(ima_skeleton);
    partial_box2d part(input);
    
    partial_image2d<unsigned> partima(part);
    partima.fill_with(ima_value);
	
	partima.affiche();
	std::cout<<"\n";
	partima.compute_dmap(partima).affiche();
}

// Version 8
void version8()
{
    std::cout<<"Version 8 : resolution labyrinthe\n";
    image2d<unsigned> input({6,5});
    // image squelette
    unsigned ima_skeleton[] = 
    {2,1,1,1,0,
     0,0,0,1,0,
     0,1,1,1,0,
     0,1,0,1,0,
     1,1,0,0,0,
     0,1,1,1,3};
     
     // n'influence pas le code de résolution du labyrinthe
     unsigned ima_value[] = 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    input.fill_with(ima_skeleton);
    partial_box2d part(input);
    
    partial_image2d<unsigned> partima(part);
    partima.fill_with(ima_value);
    
    std::cout<<"Labyrinthe :";
	partima.get().getIma().affiche();
    std::cout<<"\nChemin du labyrinthe : \n";
	partima.affiche();
	std::cout<<"\nChemin le plus court : \n";
	partima.solve().affiche();
}




