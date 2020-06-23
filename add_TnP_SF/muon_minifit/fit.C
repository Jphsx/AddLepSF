void fit(){


        TFile* f = TFile::Open("./EfficienciesAndSF_GOLDMINI_fine_Z.root");
        //TFile* f = TFile::Open("../filedump/goldmini_fine/EfficienciesAndSF_GOLDMINI_fine_Z.root");
//      f->ls();
//      f->cd("Medium_PtEtaBins");
        f->ls();
        gStyle->SetOptFit(1);

         TH2F* plot = (TH2F*) f->Get("Medium_PtEtaBins/abseta_pt_ratio");
        // TH2F* ploteffdata = (TH2F*) f->Get("Medium_PtEtaBins/efficienciesDATA/abseta_pt_DATA");
        // TH2F* ploteffmc = (TH2F*) f->Get("Medium_PtEtaBins/efficienciesMC/abseta_pt_MC");


       // TCanvas* sf1 = new TCanvas();
       // plot->Draw();
       // sf1->SaveAs("SFgminiZ.pdf");

        TCanvas* c1 = new TCanvas();

        TH1D* bin1 = plot->ProjectionY("barrel",1,1);
       // bin1->Fit("pol0");
       // bin1->Draw();
       // c1->SaveAs("SF_barrel_gmini_p0fit.pdf");

        bin1->Fit("pol1");
        bin1->Draw();
        c1->SaveAs("SF_barrel_gmini_p1fit.pdf");


        TCanvas* c2 = new TCanvas();

        TH1D* bin2 = plot->ProjectionY("cap",2,2);
       // bin2->Fit("pol0");
       // bin2->Draw();
       // c2->SaveAs("SF_cap_gmini_p0fit.pdf");

        bin2->Fit("pol1");
        bin2->Draw();
        c2->SaveAs("SF_cap_gmini_p1fit.pdf");



	//get errors from each bin, 
	//first barrel fit
//	p0                        =     0.999751   +/-   0.000446692 
//	p1                        =  9.90171e-07   +/-   9.12493e-06 

	double prediction_variance=1e-9;
	//std::vector<double> f1error
	std::vector<double> value;
	std::vector<double> bincenter;
	std::vector<double> valerror;

	//comment out one of these to either fit the barrel(bin1) or endcap(bin2)
	TH1D* bin = bin1;
//	TH1D* bin = bin2;

	int nbins = bin->GetNbinsX();
	for(int i=1; i<nbins; i++){
	
		value.push_back( bin->GetBinContent(i) );
		bincenter.push_back( bin->GetBinCenter(i) );
		valerror.push_back(bin->GetBinError(i) );
	}	
	std::vector<double> modelvalue;
	for(int i=0; i<bincenter.size(); i++){
		double pt = bincenter.at(i);
		modelvalue.push_back( 9.90171e-07 * pt + 0.999751 );
	}	
	for(int i=0; i<value.size(); i++){
		std::cout<<"(obs, err,pt,fit) "<<value.at(i)<<" "<<valerror.at(i)<<" "<<bincenter.at(i)<<" "<<modelvalue.at(i)<<std::endl;
	}

	//compute chi2 
	double chi2=99;
	double offset = 1e-9;
	while(chi2 >= 10.0 ){
		//std::cout<<"in the loop";
		chi2=0.0;
		prediction_variance += offset;
		//std::cout<<"var "<<prediction_variance<<std::endl;
		for(int i=0; i< value.size(); i++){
			chi2+= ((value[i] - modelvalue[i])*(value[i] - modelvalue[i]))/prediction_variance;
		}	
		//std::cout<<chi2<<std::endl;
	}
	std::cout<<" fit prediction error:(flat errors)  "<< sqrt(prediction_variance) <<" chi2: "<< chi2<<std::endl;

	std::cout<<"individual offsets"<<std::endl;
	chi2=0.0;
	double erroroffset = 17.0906/10.0;
	for(int i =0; i< value.size(); i++){
		chi2+= ( (value[i] - modelvalue[i])*(value[i] - modelvalue[i]))/( (valerror[i] *sqrt(erroroffset))*(valerror[i]*sqrt(erroroffset)));
	}
	std::cout<<"offset "<<erroroffset<<" chi2 "<<chi2<<std::endl;	
	
	std::vector<double> scaled_err;
	std::vector<double> weights;
	for(int i=0; i<valerror[i]; i++){
		double s_err = valerror[i] * sqrt(erroroffset);
		scaled_err.push_back( s_err );
		weights.push_back( 1.0/(s_err*s_err));
	}
	/*
	std::vector<double> wprime;
	double norm=0;
	for(int i=0; i<weights.size(); i++){
		norm+= weights.at(i);
	}
	for(int i=0; i<weights.size(); i++){
		wprime.push_back(weights[i]/norm);
	}

	double gooderror = 0.;
		for(int i =0;i<wprime.size(); i++){
		gooderror += (wprime[i]*wprime[i])*(scaled_err[i]*scaled_err[i]);
	}	
	gooderror = sqrt(gooderror);
	std::cout<<"fit prediction error: (chi2 scaled to 1 with individual errors) "<< gooderror<<std::endl;

	*/
	
	double weightvar = 0.0;
	double sum = 0.0;
	for(int i=0; i< scaled_err.size(); i++){
		sum+= 1./(scaled_err[i] * scaled_err[i]);
	}
	weightvar = sqrt(1./sum);
	std::cout<<"fit prediction error: (chi2 scaled to 1 with individual errors) "<< weightvar<<std::endl;





}


