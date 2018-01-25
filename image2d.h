#include <cassert>
#include <vector>
#include <iostream>
#include <queue>

#include "point2d.h"
#include "box2d.h"
#include "box2d_iterator.h"
#include "neighb2d_iterator.h"

template <typename T>
class image2d
{
public:
    using value_type = T;
    using point_type = point2d;
    using domain_type = box2d;

  explicit image2d(const box2d& dom)
    : dom_(dom),
      data_(dom.npoints())
  {
  }

  template <typename U, unsigned n>
  void fill_with(U (&vals)[n])
  {
    assert(dom_.npoints() == n);
    for (unsigned i = 0; i < n; ++i)
      data_[i] = vals[i];
  }

  void affiche() const
  {
      for(unsigned i =0;i<dom_.npoints();i++)
      {
          if(data_[i]==1)
            std::cout<<"\033[33m";
          if(i% dom_.getNcols()==0)
              std::cout<<std::endl;
          std::cout<<data_[i]<<" ";
          std::cout<<"\033[0m";
      }
      std::cout<<std::endl;
  }
    T& operator()(const point_type& p)
    {    int i= (p.getCoordvert())*((int)dom_.getNcols())+p.getCoordhori();
        return data_[i];
    }
    T operator()(const point_type& p) const 
	{
        int i= (p.getCoordvert())*((int)dom_.getNcols())+p.getCoordhori();
        return data_[i];
	}

    box2d get() const
    {
        return dom_;       
    }
    
    using bool_t = unsigned;
    image2d<unsigned> compute_dmap(const image2d<bool_t>& input)
    {
        point2d p,n;    
        box2d D = input.get();
        const unsigned max=unsigned(-1);
        image2d<unsigned> dmap(D);
        box2d_iterator iter(input.get());
        for (iter.start(); iter.isdone()==false; iter.next())
        {    
            p=iter.get();
            dmap(p)=max;            
            }
        neighb2d_iterator neighb(input.get());
        std::queue<point2d> q;
        
        for(iter.start();iter.isdone()==false;iter.next())
        {
          p=iter.get();
          if (input(p)==1)
          {
              dmap(p)=0;
              neighb.center(iter.get());
              for(neighb.start();neighb.isdone()==false;neighb.next())
                {
                 n=neighb.get();
                 if (input(n)==0)
                     {
                          q.push(p);
                          break;
                     }
                  
                }
          }
        }    
        while (q.empty()==false)
        {
            p=q.front();
            q.pop();
            neighb.center(p);
            for(neighb.start();neighb.isdone()==false;neighb.next())
            {    n=neighb.get();
                if(dmap(n)==max)
                {    
                    dmap(n)=dmap(p)+1;

                    q.push(n);
                }
            }
        }
        return dmap;
    }
	private:
	  box2d dom_;
	  std::vector<T> data_;
};