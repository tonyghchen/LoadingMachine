
class INT64 {
	public:
		INT64() ;
		void Mul(unsigned long a,unsigned long b) ;
		void Mul(unsigned long a,unsigned b) ;
		void Div(unsigned long a) ;
		void Div(unsigned a) ;
		unsigned long HiLong() ;
		unsigned long LoLong() ;
	private:
	unsigned long Hi,Lo ;
} ;