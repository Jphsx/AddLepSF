
import json
import sys
#import uproot
from ROOT import TFile, TTree
from array import array
#first 3 input arguments are relative/path/to/jsonSF
#relative path is intended to be up one level
json_medsip_dy = sys.argv[1]
json_medsip_jpsi = sys.argv[2]
json_mini_dy = sys.argv[3]
json_medsip_dy_el = sys.argv[4]
json_medsip_jpsi_el = sys.argv[5]
json_mini_dy_el = sys.argv[6]

itest = "DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root"

def processdict(dic):
	print(dic.keys())
	pt = [ x.split(" ")[0] for x in dic.keys() ]
	pt_str = pt
	pt = [ x.split('[')[-1].split(']')[0] for x in pt ]
	pt = [ x.split(',') for x in pt ]
	pt = [ list(map(float,x)) for x in pt ]	

	eta = [ x.split(" ")[1] for x in dic.keys() ]
	eta_str = eta
	eta = [ x.split('[')[-1].split(']')[0] for x in eta ]
	eta = [ x.split(',') for x in eta ]
	eta = [ list(map(float,x)) for x in eta ]	

	return pt,eta,pt_str,eta_str

class sfcontainer:

	def __init__(self, dicts):
		self.dict1 = dicts[0]
		self.dict2 = dicts[1]	
		self.ptlist, self.etalist, self.pt_str, self.eta_str = processdict(self.dict1)

	def getvalue(self, pt,eta ):
		
		idx = [ i for i, (p,e) in enumerate(zip(self.ptlist,self.etalist)) if ( pt >= p[0] and pt < p[1] ) and ( eta >= e[0] and eta < e[1] ) ] 
	#	print idx
		if len(idx) > 0:
			idx = idx[0]
			return self.dict1[self.pt_str[idx]+" "+self.eta_str[idx]]
		else:
			return 1.0


def sfselector(sfJ, sfZ, sfJ_el, sfZ_el, pt, eta, pdg):
	if pt < 20.0 and pdg == 11:
		return sfJ.getvalue(pt,eta)
	if pt >= 20.0 and pdg == 11:
		return sfZ.getvalue(pt,eta)
	if pt < 20.0 and pdg == 13:
		return sfJ_el.getvalue(pt,eta)
	if pt >= 20.0 and pdg == 13:
		return sfZ_el.getvalue(pt,eta)
	

#generate dictionary from json file
def gendict(filename):
	_dict = dict()
	_dict2 = dict()
	with open(filename) as json_file:
    		sf = json.load(json_file)
	
    	for x in sf['Medium_PtEtaBins']['pt_abseta_ratio']:

		for y in sf['Medium_PtEtaBins']['pt_abseta_ratio'][x]:

			z = sf['Medium_PtEtaBins']['pt_abseta_ratio'][x][y]['value']
			err = sf['Medium_PtEtaBins']['pt_abseta_ratio'][x][y]['error']
			key =  str(x)+" "+str(y)
			value = float(z)
			_dict.update([(key,value)])
			_dict2.update([(key,err)])
			

	return [_dict, _dict2]

"""
#load json into classes
sfZ = sfcontainer(gendict(json_medsip_dy))
sfJ = sfcontainer(gendict(json_medsip_jpsi))
sfZiso = sfcontainer(gendict(json_mini_dy))

sfZ_el = sfcontainer(gendict(json_medsip_dy_el))
sfJ_el = sfcontainer(gendict(json_medsip_jpsi_el))
sfZiso_el = sfcontainer(gendict(json_mini_dy_el))


#print("sfZ")
#print sfZ.dict1
#print("sfZmini")
#print sfZiso.dict1
#print type(sfZ.ptlist)
#print sfZ.getvalue( 22.0, 1.3)
#print sfZ.getvalue( 30000, -46)


maxn=255
ifile = TFile.Open(itest)
tree = ifile.KUAnalysis 
tree2 = ifile.EventCount
ofile = TFile("./output/testout.root", "RECREATE")
newtree= tree.CloneTree(0)
newtree.SetAutoSave(999999999999999)
evtct = tree2.CloneTree()
evtct.SetAutoSave(99999999999999)
#other2 = ifile.Histograms.Clone()

wms = array( 'f', maxn*[0.] )
wiso = array( 'f', maxn*[0.])

newtree.Branch( 'weight_lep', wms, 'wms[Nlep]/F')
newtree.Branch( 'weightiso_lep',wiso, 'wiso[Nlep]/F' )

run = 20
i=0
for event in tree:

	for i,(pt,eta,pdg) in enumerate(zip(event.PT_lep, event.Eta_lep, event.PDGID_lep)):
		wiso[i] = sfZiso.getvalue(pt,abs(eta))
		wms[i] = sfselector(sfJ, sfZ, sfJ_el, sfZ_el, pt,abs(eta), abs(pdg) )
	
	newtree.Fill()
#	i = i+1
#	if i>run:
#		break	

#ofile = TFile('otest.root','RECREATE')
#ofile.WriteTObject(newtree)


#ofile.Write()
other2 = ifile.Histograms
other2.ReadAll()
ofile.mkdir("Histograms")
ofile.cd("Histograms")
other2.GetList().Write()

ofile.Write()
ofile.Close()

#file = uproot.open(testroot)
#print file.keys()
#tree = file['KUAnalysis']
#print tree.keys()
#branches = tree.arrays(namedecode='utf-8')
#branch1 = branches['PT_lep'][1:5]
#branch2 = branches['PDGID_lep'][1:5]
#branch3 = branches['Nlep'][1:5]
#print branches
#
#print branch1
#print branch2
#print branch3
 

#print branches
#branch1 = tree.arrays()[b'PT_lep'][0]
#branch1 = branch1[1:5]
#branch2 = tree.arrays()[b'PDGID_lep'][1:5]
#branch2 = branch2[1:5]
#print branch1
#print branch2

#'Nele', 'Nmu', 'Nlep', 'PT_lep', 'Eta_lep', 'Phi_lep', 'M_lep', 'Charge_lep', 'PDGID_lep'
"""
