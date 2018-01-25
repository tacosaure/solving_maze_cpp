#include "point2d.h"
#include "box2d.h"

class neighb2d_iterator
{
	public:
		neighb2d_iterator(){}
		neighb2d_iterator(box2d b, point2d p)
		{
				b_=b;
				p_=p;
		}
		neighb2d_iterator(box2d b)
		{
				b_=b;
		}
		void center(point2d p)
		{
				p_=p;
		}

		void start()
		{    if(p_.getCoordvert()==0)
			{
				if(p_.getCoordhori()==0)
				{
					it_.setCoordhori(p_.getCoordhori()+1);
					it_.setCoordvert(p_.getCoordvert());
					pos_=2;
				}
				else
				{
					it_.setCoordhori(p_.getCoordhori()-1);
					it_.setCoordvert(p_.getCoordvert());
					pos_=1;
				}
				
			}
			else
			{
			it_.setCoordhori(p_.getCoordhori());
			it_.setCoordvert(p_.getCoordvert()-1);
			pos_=0;
			}
		}
		void next()
		{    
			pos_++;
			switch (pos_)
			{
				case 1:    
						if(p_.getCoordhori()-1<0)
						{

							break;
						}
						else{                
						it_.setCoordhori(p_.getCoordhori()-1);
						it_.setCoordvert(p_.getCoordvert());}
						break;
				case 2:    
						if(p_.getCoordhori()+1>((int)b_.getNcols()-1))
						{
							break;
						}
						else{
						it_.setCoordhori(p_.getCoordhori()+1);
						it_.setCoordvert(p_.getCoordvert());}
						break;
				case 3:    
						if(p_.getCoordvert()+1>((int)b_.getNrows()-1))
						{    
							break;
						}
						else{
						it_.setCoordhori(p_.getCoordhori());
						it_.setCoordvert(p_.getCoordvert()+1);}
						break;
			}
		}
		bool isdone()
		{
			return  pos_==4;
		}
		point2d get()
		{
			return it_;
		}
		
		
	private:
		box2d b_;
		point2d p_;
		point2d it_;
		unsigned pos_;
};