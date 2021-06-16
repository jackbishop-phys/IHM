//////////////////////////////////////////
// I hate Mondays (IHM)			//
// V1.0 J. Bishop Dec. 2020		//
// Calculates gas properties using	//
// GARFIELD++				//
//////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <TCanvas.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TRandom3.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include "MediumMagboltz.hh"
using namespace Garfield;
int main(int argc, char * argv[]) {
//
  std::cout<<std::endl<<std::endl<<"Gas drift generator"<<std::endl;
  int selection=0;
  while(selection!=1 && selection!=2) {
          selection=0;
	  std::cout<<"Please select gas mode: 1 for single gas or 2 for mixed gas"<<std::endl;
	  std::cin>>selection;
  }
  std::cout<<selection<<" selected"<<std::endl;

  MediumMagboltz* gas = new MediumMagboltz();
  if(selection==1) {
  	std::cout<<"Type in name of gas"<<std::endl;
	std::cout<<"Examples: He,CO2,Methane,Isobutane..."<<std::endl;
	std::string gasname;
	std::cin>>gasname;
  	gas->SetComposition(gasname,100.);
  }
  if(selection==2) {
  	std::cout<<"Type in name of gas 1"<<std::endl;
	std::cout<<"Examples: He,CO2,Methane,Isobutane..."<<std::endl;

	std::string gasname1;
	std::cin>>gasname1;
  	std::cout<<"Type in fraction (%) of gas 1"<<std::endl;
	double frac1;
	std::cin>>frac1;
  	std::cout<<"Type in name of gas 2"<<std::endl;
	std::string gasname2;
	std::cin>>gasname2;
  	std::cout<<"Type in fraction (%) of gas 2"<<std::endl;
	double frac2;
	std::cin>>frac2;
  	gas->SetComposition(gasname1,frac1,gasname2,frac2);
  }
  std::cout<<"Type in pressure in Torr"<<std::endl;
  double pressure;
  std::cin>>pressure;
  std::cout<<"Type in field cage voltage (across the 13-cm gap)"<<std::endl;
  double voltage;
  std::cin>>voltage;
  std::cout<<"Electric field is "<<voltage/13.<<" V/cm"<<std::endl;
  double efield=voltage/13.;
  float temperature =  293.15;
  gas->SetTemperature(temperature);
  gas->SetPressure(pressure);
  gas->SetMaxElectronEnergy(200.);
  gas->SetFieldGrid(efield,efield,1,false);
//  gas->GenerateGasTable(1,false);
//  gas->Initialise(true);
  double vx,vy,vz,dl,dt,alpha;
  double eta,lor,vxerr,vyerr,vzerr,dlerr,dterr,alphaerr,etaerr,lorerr,alphatof;
  std::array<double, 6ul> difftens;
  /** Run Magboltz for a given electric field, magnetic field and angle.
    * \param[in] e electric field
    * \param[in] b magnetic field
    * \param[in] btheta angle between electric and magnetic field
    * \param[in] ncoll number of collisions (in multiples of 10<sup>7</sup>)
                 to be simulated
    * \param[in] verbose verbosity flag
    * \param[out] vx,vy,vz drift velocity vector
    * \param[out] dl,dt diffusion cofficients
    * \param[out] alpha Townsend cofficient
    * \param[out] eta attachment cofficient
    * \param[out] lor Lorentz angle
    * \param[out] vxerr,vyerr,vzerr errors on drift velocity
    * \param[out] dlerr,dterr errors on diffusion coefficients
    * \param[out] alphaerr,etaerr errors on Townsend/attachment coefficients
    * \param[out] lorerr error on Lorentz angle
    * \param[out] alphatof effective Townsend coefficient \f$(\alpha - \eta)\f$
    *             calculated using time-of-flight method
    * \param[out] difftens components of the diffusion tensor (zz, xx, yy, xz, yz, xy)
    */
    
    gas->RunMagboltz(efield,0,0,1,false,vx,vy,vz,dl,dt,alpha,eta,lor,vxerr,vyerr,vzerr,dlerr,dterr,alphaerr,etaerr,lorerr,alphatof,difftens);
    std::cout<<"\033[1m\033[32m"<<"Drift velocity: "<<vz<<" cm/ns"<<"\033[0m"<<std::endl;
    std::cout<<"\033[1m\033[32m"<<"Drift resolution: "<<dl<<" cm^1/2"<<"\033[0m"<<std::endl;
    std::cout<<"\033[1m\033[32m"<<"Time resolution: "<<dt<<" cm^1/2"<<"\033[0m"<<std::endl;

  return 0;
}
