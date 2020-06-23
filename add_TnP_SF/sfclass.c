#include <vector>
#include <iostream>
class region{
 
	public: 
		region(double ptlo, double ptup, double etalo, double etaup, double sf, double err){
			_ptlo = ptlo;
                  _etalo = etalo;
                  _ptup = ptup;
                  _etaup = etaup;
                  _sf = sf;
			_err = err;
           }
		double _ptlo;
          double _etalo;
          double _ptup;
          double _etaup;
          double _sf;
		double _err;
};
 
class sfcon{
	public:
		// std::vector<region*> regions;
 		void printregion(std::vector<region*> regions){
			for(int i=0; i<regions.size(); i++){
				std::cout<<regions[i]->_ptlo<<" "<<regions[i]->_ptup<<std::endl;
                          std::cout<<regions[i]->_etalo<<" "<<regions[i]->_etaup<<std::endl;
                          std::cout<<regions[i]->_sf<<std::endl;
				std::cout<<regions[i]->_err<<std::endl;
			}
		}
		region* getregion(std::vector<region*> regions,  double pt, double eta){
			for(int i =0; i<regions.size(); i++){
							if( (pt >= regions[i]->_ptlo) && (pt < regions[i]->_ptup) && (eta >= regions[i]->_etalo) && (eta < regions[i]->_etaup) ){
					return regions[i];
				}
			}
			region* notfound = new region(0,0,0,0,1,1);
			return notfound;
		}
 
};
class dymedsip: public sfcon{
 
 
	public: 
		std::vector<region*> regions{ 
		new region(30.0,40.0,1.2,2.4,1.0154032707214355,0.0007511456215079016), 
		new region(30.0,40.0,0.0,1.2,1.0009021759033203,0.0004008912998138028), 
		new region(60.0,100.0,0.0,1.2,0.9998788237571716,0.0010117313082919517), 
		new region(10.0,20.0,1.2,2.4,1.0278407335281372,0.002889401705862383), 
		new region(60.0,100.0,1.2,2.4,1.0199463367462158,0.0021597164321898983), 
		new region(10.0,20.0,0.0,1.2,1.0136955976486206,0.0027464611751913974), 
		new region(40.0,60.0,1.2,2.4,1.0122606754302979,0.0005431736520548543), 
		new region(20.0,30.0,1.2,2.4,1.0222200155258179,0.0012928614836199169), 
		new region(20.0,30.0,0.0,1.2,1.0038038492202759,0.000841684248703117), 
		new region(40.0,60.0,0.0,1.2,1.0001068115234375,0.00028379151746064154), 
		};
 }; 
 
 
class jpsimedsip: public sfcon{
 
 
	public: 
		std::vector<region*> regions{ 
		new region(17.0,20.0,1.2,2.4,1.1488620042800903,0.042496962767364276), 
		new region(9.0,11.0,1.2,2.4,1.0437226295471191,0.017906913129081402), 
		new region(14.0,17.0,0.0,1.2,1.0093111991882324,1.0804483432049787), 
		new region(2.5,2.75,1.2,2.4,1.0830330848693848,0.040683001928444026), 
		new region(17.0,20.0,0.0,1.2,1.0093111991882324,1.0804355274464943), 
		new region(9.0,11.0,0.0,1.2,0.9874597787857056,0.012336156980656552), 
		new region(3.0,3.25,0.0,1.2,0.9365952014923096,0.04115247468115655), 
		new region(2.0,2.5,0.0,1.2,0.0,1.606037612440322), 
		new region(4.5,5.0,0.0,1.2,0.9368633031845093,0.010298861287312909), 
		new region(2.5,2.75,0.0,1.2,0.23771195113658905,0.2510997911638736), 
		new region(3.75,4.0,1.2,2.4,1.0183812379837036,0.029614816323128262), 
		new region(3.25,3.5,0.0,1.2,0.9608831405639648,0.022415552340519194), 
		new region(3.0,3.25,1.2,2.4,1.0452394485473633,0.03322032920999197), 
		new region(6.0,7.0,1.2,2.4,1.0515586137771606,0.019906329318178793), 
		new region(5.0,5.5,0.0,1.2,0.9367852210998535,0.008125308809595909), 
		new region(7.0,9.0,1.2,2.4,1.0832977294921875,0.01811078455203635), 
		new region(6.0,7.0,0.0,1.2,0.967613935470581,0.008456306108842269), 
		new region(2.0,2.5,1.2,2.4,0.9965125918388367,0.0374575581095548), 
		new region(5.5,6.0,1.2,2.4,0.9747517704963684,0.021018702622954778), 
		new region(5.0,5.5,1.2,2.4,1.0250568389892578,0.02352326136202505), 
		new region(3.5,3.75,1.2,2.4,0.9665367603302002,0.025256936678641068), 
		new region(2.75,3.0,0.0,1.2,0.5768245458602905,0.08087428297271852), 
		new region(5.5,6.0,0.0,1.2,0.9532095193862915,0.008905159446970169), 
		new region(4.0,4.5,1.2,2.4,1.0186028480529785,0.022346014954426934), 
		new region(3.25,3.5,1.2,2.4,1.0401490926742554,0.034386108510982845), 
		new region(4.5,5.0,1.2,2.4,1.012101173400879,0.022093267257327534), 
		new region(11.0,14.0,0.0,1.2,1.0002305507659912,0.004386706400062749), 
		new region(3.75,4.0,0.0,1.2,0.9318346381187439,0.015067085027929071), 
		new region(4.0,4.5,0.0,1.2,0.9210644960403442,0.012687689057482195), 
		new region(7.0,9.0,0.0,1.2,1.014001727104187,0.01323760316527494), 
		new region(14.0,17.0,1.2,2.4,1.0899323225021362,0.027913185242438136), 
		new region(3.5,3.75,0.0,1.2,0.9413628578186035,0.1844010187771035), 
		new region(11.0,14.0,1.2,2.4,1.0757273435592651,0.021946527305542543), 
		new region(2.75,3.0,1.2,2.4,1.0376192331314087,0.03922022065148539), 
		};
 }; 
 
 
class dymini: public sfcon{
 
 
	public: 
		std::vector<region*> regions{ 
		new region(30.0,40.0,1.2,2.4,1.000382900238037,0.00029978281874701285), 
		new region(30.0,40.0,0.0,1.2,0.9997930526733398,0.00027645634783528814), 
		new region(60.0,100.0,0.0,1.2,1.0000348091125488,0.000520508207490416), 
		new region(10.0,20.0,1.2,2.4,1.0013043880462646,0.001468566864930186), 
		new region(60.0,100.0,1.2,2.4,0.9997677803039551,0.0006595958215218025), 
		new region(10.0,20.0,0.0,1.2,1.0009604692459106,0.002303645711558526), 
		new region(40.0,60.0,1.2,2.4,1.0000721216201782,0.00019343566830418372), 
		new region(20.0,30.0,1.2,2.4,1.0006842613220215,0.000590743496488326), 
		new region(20.0,30.0,0.0,1.2,1.002672791481018,0.0007413416440633151), 
		new region(40.0,60.0,0.0,1.2,0.9997212290763855,0.00016642077760316455), 
		};
 }; 
 
 
class Muon_medsip{
	public:
		dymedsip* _con1;
  		jpsimedsip* _con2;
  		Muon_medsip(){
			_con1 = new dymedsip();
			_con2 = new jpsimedsip();
		}
		region* getregion( double pt, double eta ){
			if(pt>=20){
				return	_con1->getregion( _con1->regions,pt,eta);
			}
			if(pt<20){
				return  _con2->getregion( _con2->regions,pt,eta);
			}
		}
};
 
 
class Muon_mini{
 public:
		dymini* _con1;
 		Muon_mini(){
			_con1 = new dymini();
			}
		region* getregion( double pt, double eta){
			if(pt>=20){
				return _con1->getregion( _con1->regions, pt, eta);
			}
			if(pt<20 && eta<1.2){
				double sf= (9.902e-7 * pt) + (0.9998 );
				double err= 0.0;
				region* extrap_region = new region(1,1,1,1,sf,err);
				return extrap_region;
				}
			if(pt<20 && eta>=1.2){
				double sf= (-1.934e-5 * pt) + (1.001 );
				double err= 0.0;
				region* extrap_region = new region(1,1,1,1,sf,err);
				return extrap_region;
			}
		}
};
 
 
int main(){
Muon_medsip* m1 = new Muon_medsip();
Muon_mini* m2 = new Muon_mini();
std::cout<<"test"<<std::endl;
region* r = m1->getregion(5,1.2);
region* r1 = m1->getregion(57,2.3);
region* r2 = m2->getregion(3,1.0);
region* r3 = m2->getregion(7,2.0);
region* r4 = m2->getregion(22,0.9);
std::cout<<r->_sf<<" "<<r->_err<<std::endl;
std::cout<<r1->_sf<<" "<<r1->_err<<std::endl;
std::cout<<r2->_sf<<" "<<r2->_err<<std::endl;
std::cout<<r3->_sf<<" "<<r3->_err<<std::endl;
std::cout<<r4->_sf<<" "<<r4->_err<<std::endl;
}
