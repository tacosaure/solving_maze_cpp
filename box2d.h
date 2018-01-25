class box2d
{
  public:
	box2d(){}
	box2d(unsigned pnrows, unsigned pncols)
	{
		nrows = pnrows;
		ncols = pncols;
	}
	
    unsigned npoints() const { return nrows * ncols; }
	unsigned getNrows() const
	{
		return nrows;
	}
	
	unsigned getNcols() const
	{
		return ncols;
	}
  private:
	unsigned nrows, ncols;
};