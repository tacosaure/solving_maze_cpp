#include "point2d.h"
#include "box2d.h"

class box2d_iterator
{
	public:
		box2d_iterator(){}
		box2d_iterator(box2d b, point2d p)
		{
				b_=b;
				p_=p;
		}
		box2d_iterator(box2d b)
		{
				b_=b;
		}
		void start()
		{
			p_.setCoordhori(0);
			p_.setCoordvert(0);
			pos_=0;
		}
		void next()
		{    
			p_.setCoordhori(pos_%b_.getNcols());
			p_.setCoordvert(pos_/b_.getNcols());
			pos_++;
		}
		bool isdone()
		{
			return  pos_==(b_.npoints()+1);
		}
		point2d get()
		{
			return p_;
		}
	
	private:
		box2d b_;
		point2d p_;
		unsigned pos_;
};