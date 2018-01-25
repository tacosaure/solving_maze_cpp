#include "partial_box2d.h"
class partial_box2d_iterator
{	public:
	partial_box2d_iterator (){}
	partial_box2d_iterator (partial_box2d part) :part_{part}{}
	partial_box2d_iterator (partial_box2d part, point2d p) :part_{part}, p_{p}{}
	void start()
		{

			p_.setCoordhori(0);
			p_.setCoordvert(0);
			pos_=0;
			ppp_=pos_;
			
		}
		void next()
		{
			p_.setCoordhori(pos_%part_.getIma().get().getNcols());
			p_.setCoordvert(pos_/part_.getIma().get().getNcols());
			pos_++;
			ppp_=pos_;
			while(!part_.has(p_))
			{
			if (pos_==(part_.getIma().get().npoints()+1))
			{
					p_.setCoordhori(ppp_%part_.getIma().get().getNcols());
					p_.setCoordvert(ppp_/part_.getIma().get().getNcols());
					break;
			}
			p_.setCoordhori(pos_%part_.getIma().get().getNcols());
			p_.setCoordvert(pos_/part_.getIma().get().getNcols());
			pos_++;	
			}
			
		}
		bool isdone()
		{

			return  pos_==(part_.getIma().get().npoints()+1);
		}
		point2d get()
		{
			return p_;
		}
		

	partial_box2d part_;
	point2d p_;
	unsigned pos_;
	unsigned ppp_;
};
