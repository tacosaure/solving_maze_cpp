#include <cassert>
#include <vector>
#include <iostream>
#include <queue>

class point2d
{
	public:
		point2d() {}
		point2d(int horiz, int verti)
		{
		  Coordhori=horiz;
		  Coordvert=verti;
		}

		void affichepoint()
		{    
			  std::cout<<std::endl;
			  std::cout<<"{";
			  std::cout<<Coordvert<<" ";
			  std::cout<<",";
			  std::cout<<Coordhori<<" ";
			  std::cout<<"}";
			  std::cout<<std::endl;
		}

		point2d& operator=(const point2d& rhs)
		{
			this->Coordhori = rhs.Coordhori;
			this->Coordvert = rhs.Coordvert;
			return *this;
		}
		
		bool operator==(const point2d& rhs)
		{
			return ((this->Coordhori == rhs.Coordhori) && (this->Coordvert == rhs.Coordvert))?true:false;
		}
		
		bool operator!=(const point2d& rhs)
		{
			return ((this->Coordhori != rhs.Coordhori) || (this->Coordvert != rhs.Coordvert))?true:false;
		}
	
		int getCoordhori() const
		{
			return Coordhori;
		}
		
		int getCoordvert() const
		{
			return Coordvert;
		}
		
		void setCoordhori(int pCoordhori)
		{
			Coordhori = pCoordhori;
		}
		
		void setCoordvert(int pCoordvert)
		{
			Coordvert = pCoordvert;
		}
	
	private:
		int Coordhori;
		int Coordvert;
};
