#include "image2d.h"
class partial_box2d
{	public:
	partial_box2d(){}
	partial_box2d(image2d<unsigned> ima) : ima_{ima}
	{
			//ima_=ima;
	}
	bool has(const point2d& p) const { return ima_(p)>0; }
	
	image2d<unsigned> getIma() const
	{
			return ima_;
	}
	
	image2d<unsigned>& getIma() 
	{
			return ima_;
	}

	private: 
	image2d<unsigned> ima_;
};
