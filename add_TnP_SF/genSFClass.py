


import json
import sys
from add_SF import * 

json_medsip_dy = sys.argv[1]
json_medsip_jpsi = sys.argv[2]
json_mini_dy = sys.argv[3]
#json_medsip_dy_el = sys.argv[4]
#json_medsip_jpsi_el = sys.argv[5]
#json_mini_dy_el = sys.argv[6]

#itest = "DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root"


sfZ = sfcontainer(gendict(json_medsip_dy))
sfJ = sfcontainer(gendict(json_medsip_jpsi))
sfZiso = sfcontainer(gendict(json_mini_dy))

#sfZ_el = sfcontainer(gendict(json_medsip_dy_el))
#sfJ_el = sfcontainer(gendict(json_medsip_jpsi_el))
#sfZiso_el = sfcontainer(gendict(json_mini_dy_el))


#generate 6 classes in 1 file with hardcoded regions
infile = open("sfclass.h","w")
#define regions class
infile.write("#include <vector>\n")
infile.write("#include <iostream>\n")
infile.write("class region{\n \n")
infile.write("	public: \n")
infile.write("		region(double ptlo, double ptup, double etalo, double etaup, double sf, double err){\n")
infile.write("			_ptlo = ptlo;\n")
infile.write("                  _etalo = etalo;\n")
infile.write("                  _ptup = ptup;\n")
infile.write("                  _etaup = etaup;\n")
infile.write("                  _sf = sf;\n")
infile.write("			_err = err;\n")
infile.write("           }\n")
infile.write("		double _ptlo;\n")
infile.write("          double _etalo;\n")
infile.write("          double _ptup;\n")
infile.write("          double _etaup;\n")
infile.write("          double _sf;\n")
infile.write("		double _err;\n")
infile.write("};\n \n")

#define parent container
infile.write("class sfcon{\n")
infile.write("	public:\n")
infile.write("		// std::vector<region*> regions;\n ")
infile.write("		void printregion(std::vector<region*> regions){\n")
infile.write("			for(int i=0; i<regions.size(); i++){\n")
infile.write("				std::cout<<regions[i]->_ptlo<<\" \"<<regions[i]->_ptup<<std::endl;\n")
infile.write("                          std::cout<<regions[i]->_etalo<<\" \"<<regions[i]->_etaup<<std::endl;\n")
infile.write("                          std::cout<<regions[i]->_sf<<std::endl;\n")
infile.write("				std::cout<<regions[i]->_err<<std::endl;\n")
infile.write("			}\n")
infile.write("		}\n")
infile.write("		region* getregion(std::vector<region*> regions,  double pt, double eta){\n")
infile.write("			for(int i =0; i<regions.size(); i++){\n			")
infile.write("				if( (pt >= regions[i]->_ptlo) && (pt < regions[i]->_ptup) && (eta >= regions[i]->_etalo) && (eta < regions[i]->_etaup) ){\n")
infile.write("					return regions[i];\n")
infile.write("				}\n")
infile.write("			}\n")
infile.write("			region* notfound = new region(0,0,0,0,1,1);\n")
infile.write("			return notfound;\n")
infile.write("		}\n")
infile.write(" \n")
infile.write("};\n")

def extractregion(key):
	#print key
	#split at space for pt abseta split
	pt = ''.join(key.split(' ')[0])
	pt = ''.join(pt.split('[')[1])
	pt = ''.join(pt.split(']')[0])
	pt = pt.split(',')

	eta = ''.join(key.split(' ')[1])
	eta = ''.join(eta.split('[')[1])
	eta = ''.join(eta.split(']')[0])
	eta = eta.split(',')

	return pt, eta	
from decimal import Decimal
def getInstance(pt,eta,sf, err):
	_sf = Decimal(repr(sf))
	_err = Decimal(repr(err))
	return "new region("+pt[0]+","+pt[1]+","+eta[0]+","+eta[1]+","+str(_sf)+","+str(_err)+"), \n"

def genclass(infile, sfcon , sfname):
	infile.write("class "+sfname+": public sfcon{\n \n \n")
	infile.write("	public: \n")
	#infile.write("		std::vector<region*> regions{ new region(1,2,3,4,99), new region(6,7,8,9,10) }; \n")
	infile.write("		std::vector<region*> regions{ \n")

	keys = sfcon.dict1.keys()
	for key in keys:
		pt, eta = extractregion(key)
		sf = sfcon.dict1[key]
		err = sfcon.dict2[key]
		infile.write("		"+ getInstance(pt,eta,sf,err) )

	infile.write("		};\n ")
	infile.write("}; \n \n \n")
	return 0


#container to store the class names to be instantiated in the manager
genclass(infile, sfZ, "dymedsip")
genclass(infile, sfJ, "jpsimedsip")
genclass(infile, sfZiso, "dymini") 


#instantiate all the classes into a manager
#assume they will always be different, not going to make an abstract class
#do muon medsip
infile.write("class Muon_medsip{\n")
infile.write("	public:\n")
infile.write("		dymedsip* _con1;\n  ")
infile.write("		jpsimedsip* _con2;\n  ")
infile.write("		Muon_medsip(){\n")#dymedsip* con1, jpsimedsip* con2){\n")
infile.write("			_con1 = new dymedsip();\n")
infile.write("			_con2 = new jpsimedsip();\n")
infile.write("		}\n")
infile.write("		region* getregion( double pt, double eta ){\n")
infile.write("			if(pt>=20){\n")
infile.write("				return	_con1->getregion( _con1->regions,pt,eta);\n")
infile.write("			}\n")				
infile.write("			if(pt<20){\n")
infile.write("				return  _con2->getregion( _con2->regions,pt,eta);\n")
infile.write("			}\n")
infile.write("		}\n")
#infile.write("		}\n")
infile.write("};\n \n \n")

#do muon mini
infile.write("class Muon_mini{\n")
infile.write(" public:\n")
infile.write("		dymini* _con1;\n ")
infile.write("		Muon_mini(){\n")
infile.write("			_con1 = new dymini();\n")
infile.write("			}\n")
infile.write("		region* getregion( double pt, double eta){\n")
infile.write("			if(pt>=20){\n")
infile.write("				return _con1->getregion( _con1->regions, pt, eta);\n")
infile.write("			}\n")
infile.write("			if(pt<20 && eta<1.2){\n")
infile.write("				double sf= (9.902e-7 * pt) + (0.9998 );\n")
infile.write("				double err= 0.0046;\n")
infile.write("				region* extrap_region = new region(1,1,1,1,sf,err);\n")
infile.write("				return extrap_region;\n")
infile.write("				}\n")
infile.write("			if(pt<20 && eta>=1.2){\n")
infile.write("				double sf= (-1.934e-5 * pt) + (1.001 );\n")
infile.write("				double err= 0.0038;\n")
infile.write("				region* extrap_region = new region(1,1,1,1,sf,err);\n")
infile.write("				return extrap_region;\n")
infile.write("			}\n")
infile.write("		}\n")
infile.write("};\n \n \n")





#generate test stub for compile and QA
infile.write("int main(){\n")
#infile.write("dymedsip* t = new dymedsip();\n")
#infile.write("t->printregion(t->regions);\n")
infile.write("Muon_medsip* m1 = new Muon_medsip();\n")
infile.write("Muon_mini* m2 = new Muon_mini();\n")
infile.write("std::cout<<\"test\"<<std::endl;\n")
infile.write("region* r = m1->getregion(5,1.2);\n")
infile.write("region* r2 = m2->getregion(3,1.0);\n")
infile.write("region* r3 = m2->getregion(7,2.0);\n")
infile.write("region* r4 = m2->getregion(22,0.9);\n")
infile.write("std::cout<<r->_sf<<\" \"<<r->_err<<std::endl;\n")
infile.write("std::cout<<r2->_sf<<\" \"<<r2->_err<<std::endl;\n")
infile.write("std::cout<<r3->_sf<<\" \"<<r3->_err<<std::endl;\n")
infile.write("std::cout<<r4->_sf<<\" \"<<r4->_err<<std::endl;\n")

infile.write("}\n")
#generate a manager that instantiates all classes
