#include <vector>
#include <iostream>
class region{
 
	public: 
		region(double ptlo, double ptup, double etalo, double etaup, double sf){
			_ptlo = ptlo;
                  _etalo = etalo;
                  _ptup = ptup;
                  _etaup = etaup;
                  _sf = sf;
           };
		double _ptlo;
          double _etalo;
          double _ptup;
          double _etaup;
          double _sf;
};
 
class sfcon{
	//inherited methods
	// getsf from regions or do printing etc	

};

class dymedsip: public sfcon{
 
 
	public:
		
		std::vector<region*> regions{ new region(1,2,3,4,5), new region(6,7,8,9,10) }; 
		void printregion(){ 
			for(int i=0; i<regions.size(); i++){
				std::cout<<regions[i]->_ptlo<<" "<<regions[i]->_ptup<<std::endl;
                          std::cout<<regions[i]->_etalo<<" "<<regions[i]->_etaup<<std::endl;
                          std::cout<<regions[i]->_sf<<std::endl;
			}
		};	
 }; 
 
int main(){


        dymedsip* t = new dymedsip();
        t->printregion();

}
 
