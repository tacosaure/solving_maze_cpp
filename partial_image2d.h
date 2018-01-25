#include <cassert>
#include <vector>
#include <queue>
#include "partial_box2d_iterator.h"

template <typename T>
class partial_image2d
{
public:
    using value_type = T;
    using point_type = point2d;
    using domain_type = partial_box2d;
	
  partial_image2d(const domain_type& dom)
    : dom_(dom),
      data_(dom.getIma().get().npoints()),databinary_(dom.getIma().get().npoints())
  {
  	fill_with();
  }
  partial_image2d()
  {
  }

  template <typename U, unsigned n>
  void fill_with(U (&vals)[n])
  {
    //assert(dom_.npoints() == n);
    for (unsigned i = 0; i < n; ++i)
      databinary_[i] = vals[i];
  }

  void fill_with()
  {
    partial_box2d_iterator iter(dom_);
    int i =0;
      for (iter.start();iter.isdone()==false;iter.next())
    {
			data_[i]=dom_.getIma()(iter.get());
			//test_[i] = iter.get();
			i++;
	}
	nbPoints_=i;
  }
  
  void affiche() const

  {

  	  box2d_iterator iter(dom_.getIma().get());
  	  partial_box2d_iterator partiter(dom_);
  	  unsigned i =1,j=0;
  	  iter.start(); 
	  partiter.start();
  	  for (iter.next(); iter.isdone()==false; iter.next())
      {    	
			  if(dom_.getIma()(iter.get())==0)
		        std::cout<<"  ";
		      else
		      {
		        std::cout<<databinary_[j]<<" ";
		        ++j;
		      }
		      if(i% dom_.getIma().get().getNcols()==0)
		          std::cout<<std::endl;
          i++;
      }
      //std::cout<<std::endl;
  }
  

    T& operator()(const int i)//point_type& p)
    {    //int i= (p.getCoordvert())*((int)dom_.getIma().get().getNcols())+p.getCoordhori();
        return databinary_[i];
    }
    
    T operator()(const int i/*point_type& p*/) const 
	{
        //int i= (p.getCoordvert())*((int)dom_.getIma().get().getNcols())+p.getCoordhori();
        return databinary_[i];
	}

    partial_box2d get() const
    {
        return dom_;       
    }
    
    using bool_t = unsigned;
    partial_image2d<unsigned> compute_dmap(const partial_image2d<bool_t>& input)
    {
        point2d p,n;    
        partial_box2d D = dom_;//input.get();
        const unsigned max=unsigned(-1);
        partial_image2d<unsigned> dmap(D);
        
        box2d_iterator iter(dom_.getIma().get()),iter2(dom_.getIma().get());
		partial_box2d_iterator partiter(dom_);
		iter.start(); 
		partiter.start();
		int i=0;
		for (iter.next(); iter.isdone()==false; iter.next())
		{    	
			  if(dom_.getIma()(iter.get())!=0)
			  {
				dmap(i)=max;
				++i;
			  }
		}
        
        //dmap.affiche();
        neighb2d_iterator neighb(input.get().getIma().get());
        std::queue<int> q;
        // peut etre faire une queue de int
        int ok=0;
        iter.start();
        for(iter.next();iter.isdone()==false;iter.next())
        {
          p=iter.get();
          // condition pour etre dans le squelette
          if(dom_.getIma()(iter.get())!=0)
			{
				neighb.center(iter.get());
				// ok est la position et non un point, joue le role de p dans le squelette
				point2d pt;
				if (input(ok)==1)
          		{
					dmap(ok) = 0;
					
					for(neighb.start();neighb.isdone()==false;neighb.next())
					{
						n=neighb.get();
						//n.affichepoint();
						if(dom_.getIma()(n)!=0)	
						{
							// ici on travaille sur le partial image binaire
							int lala=0; // compteur dans le databinary
							// on récupère la position du point dans le tableau databinary
							// donc on compte combien de valeur differente de 0 on parcourt
							// cela nous donne la position dans le databinary
							
							for(iter2.start();iter2.isdone()==false;iter2.next())
    						 {
    						 	if(dom_.getIma()(iter2.get())!=0)
    						 	{
    						 		lala++;
    						 		if(n == iter2.get())
    						 		{
    						 			break;
    						 		}
    						 	}
    						 }
							
							
							if (input(lala)==0) // input(n) et non de ok
						     {
						         // récupération du point en fonction de la position dans le tableau
						         int cpt=0;
						         //std::cout<<"ok";
						         for(iter2.start();iter2.isdone()==false;iter2.next())
        						 {
        						 	if(dom_.getIma()(iter2.get())!=0)
        						 	{
        						 		if(cpt == ok)
        						 		{
        						 			//std::cout<<"ok";
        						 			pt = iter2.get();
        						 			q.push(ok);
        						 			break;
        						 		}
        						 		cpt++;
        						 	}
        						 }
						          break;
						     }
						}
					}
				}
				++ok;
			} 
        }    
       /* std::cout<<"\nMise a l infini\n";
        dmap.affiche();  
        std::cout<<"\n";*/
        // check la file
        int tete;        
        while (q.empty()==false)
        {
            tete=q.front();
            //std::cout<<tete;
            q.pop();
            //std::cout<<tete;
            int lala=-1; // compteur dans le databinary
			// on récupère la position du point dans le tableau databinary
			// donc on compte combien de valeur differente de 0 on parcourt
			// cela nous donne la position dans le databinary
			iter2.start();
			for(iter2.next();iter2.isdone()==false;iter2.next())
			 {
			 	if(dom_.getIma()(iter2.get())!=0)
			 	{
			 		lala++;
			 		if(lala == tete)
			 		{
			 			p=iter2.get();
			 			//p.affichepoint();
			 			break;
			 		}
			 	}
			 }
            neighb.center(p);
            //p.affichepoint();
            for(neighb.start();neighb.isdone()==false;neighb.next())
            {    
            	n=neighb.get();
            	if(dom_.getIma()(n)!=0)	
				{
				
		        	//n.affichepoint();
		        	int lolo=-1; // compteur dans le databinary
					// récupérer le neigb
					iter2.start();
					for(iter2.next();iter2.isdone()==false;iter2.next())
					 {
					 	if(dom_.getIma()(iter2.get())!=0)
					 	{
					 		//iter2.get().affichepoint();
					 		lolo++;
					 		if(n == iter2.get())
					 		{
					 			break;
					 		}
					 	}
					 }
		        	
		            if(dmap(lolo)==max)
		            {    
		                dmap(lolo)=dmap(lala)+1;
		                q.push(lolo);
		            }
		         }
            }
            
        }
        /*std::cout<<"Resulat\n";
        dmap.affiche();  
        std::cout<<"\n";*/
        
        return dmap;
    }
    
    void test()
    {
      point2d p,n;
      box2d_iterator iter(dom_.getIma().get());
  	  neighb2d_iterator neighb(dom_.getIma().get());         
  	  iter.start(); 
	  neighb.center(iter.get());
  	  for (iter.next(); iter.isdone()==false; iter.next())
      {   
      	if(dom_.getIma()(iter.get())!=0)
		{
			neighb.center(iter.get());
			for(neighb.start();neighb.isdone()==false;neighb.next())
			{
				n=neighb.get();
				if(dom_.getIma()(n)!=0)	
				{
					//n.affichepoint();
					// ici on travaille sur le partial image binaire
				}
			}
		}      		
      }
    }
    
    partial_image2d<unsigned> solve()
    {
    	partial_box2d D = dom_;//input.get();
        partial_image2d<unsigned> dmap(D),distance(D);
        
        
        box2d_iterator iter(D.getIma().get());
		neighb2d_iterator neighb(D.getIma().get());    
		     
		int cmpt=0;
		iter.start(); 
		//neighb.center(iter.get());
		for (iter.next(); iter.isdone()==false; iter.next())
		{   
			if(D.getIma()(iter.get())!=0)
			{
				if(D.getIma()(iter.get())==3)
					dmap(cmpt)=1;
				cmpt++;
			}      		
		}
		point2d before;
		distance = distance.compute_dmap(dmap);
		partial_box2d_iterator partIter(distance.get());
		partIter.start();
		before = partIter.get();
		for (partIter.start(); partIter.isdone()==false; partIter.next())
		{ 
			before = partIter.get();
			if(dmap.get().getIma()(partIter.get())==2)
				break;
			
		}
		for (partIter.start(); partIter.isdone()==false; partIter.next())
		{ 
			
			if(before == partIter.get())
				break;
		}
		dmap(position(partIter.get()))=1;
		//int i;
		bool done=false;
		for (; partIter.isdone()==false; partIter.next())
		{   
			  	//partIter.get().affichepoint();
			  	neighb.center(partIter.get());
			  	//std::cout<<distance(position(partIter.get()))<<"\n";
			  	if (done==true)
			  		dmap.dom_.getIma()(partIter.get())=0;
			  	if(dmap.get().getIma()(partIter.get())==3)
			  	{
			  		done=true;
			  	}
			  	
			  	
			  	for (neighb.start(); neighb.isdone()==false; neighb.next())
				{   
					//neighb.get().affichepoint();
					
					  	if(distance(position(neighb.get()))<distance(position(partIter.get())))
					  	{
					  		dmap(position(neighb.get()))=1;
					  		//neighb.get().affichepoint();
					  		if(dmap.get().getIma()(neighb.get())==3)
				  				break;
					  	}
					  	else
					  	{
					  		//remove(position(neighb.get()));
					  		//dmap.dom_.getIma()(neighb.get())=0;
					  		
					  	}
					
				} 
		}
		partIter.start();
		for (partIter.next(); partIter.isdone()==false; partIter.next())
		{   
			  	if(dmap(position(partIter.get()))==0)
			  	{
			  		//remove(position(partIter.get()));
			  		dmap.dom_.getIma()(partIter.get())=0;
			  		nbPoints_--;
			  		
			  		//partIter.get().affichepoint();
			  	}
			  	
		}
		
		dmap.rau();
		/*distance.affiche();
		std::cout<<"\n";
		dmap.get().getIma().affiche();
		std::cout<<"\n";*/
		
		
		return dmap;
        
    }
    
    int position(point2d point)
    {
    	box2d_iterator iter2(dom_.getIma().get());
    	iter2.start();
    	int lolo=-1;
		for(iter2.next();iter2.isdone()==false;iter2.next())
		 {
		 	if(dom_.getIma()(iter2.get())!=0)
		 	{
		 		//iter2.get().affichepoint();
		 		lolo++;
		 		if(point == iter2.get())
		 		{
		 			break;
		 		}
		 	}
		 }
		 return lolo;
    }
    
    void remove(const int indice)
    {
    	for(int i=indice;i<(int)dom_.getIma().get().npoints();i++)
    	{
    		permuter(i,i+1);
    	}
    }
    
    void permuter(int i, int j)
    {
    	int temp = databinary_[j];
    	databinary_[j]=databinary_[i];
    	databinary_[i] = temp;
    }
    
    void rau()
    {
    //assert(dom_.npoints() == n);
    for (unsigned i = 0; i < nbPoints_; ++i)
      databinary_[i] = 1;
  }
    
	private:
	  partial_box2d dom_;
	  std::vector<T> data_;
	  std::vector<T> databinary_;
	  //std::vector<T> test_;
	  unsigned nbPoints_;
};
