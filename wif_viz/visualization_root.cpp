#include "visualization_root.hpp"
#include <vector>
namespace wif_viz
{


visualization_root_c::visualization_root_c(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range) :
	visualization_c(flow, min_range, max_range)
{
	flow = flow;

}


visualization_root_c::~visualization_root_c()
{
	//
}

void visualization_root_c::draw(const std::string & filename)
{
	if(velocity_bins.x != 0 && velocity_bins.y != 0)
	{
		std::string filename1 = filename + "velocity";
		const char * savename = filename1.c_str();
		TCanvas * c = new TCanvas("c", "c", 1000, 1000);
		velocity->Draw("CONT1Z");
		velocity->GetXaxis()->SetTitle("x");
		velocity->GetYaxis()->SetTitle("y");
		velocity->GetXaxis()->CenterTitle();
		velocity->GetYaxis()->CenterTitle();
		velocity->SetTitle("contour plot velocity");
		c->SaveAs(savename);
		c->Destructor();
	}

	if(psi_bins.x != 0 && psi_bins.y != 0)
	{
		std::string filename2 = filename + "psi";
		const char * savename = filename2.c_str();
		TCanvas * c = new TCanvas("c", "c", 1000, 1000);
		psi->Draw("CONT1Z");
		psi->GetXaxis()->SetTitle("x");
		psi->GetYaxis()->SetTitle("y");
		psi->GetXaxis()->CenterTitle();
		psi->GetYaxis()->CenterTitle();
		psi->SetTitle("contour plot psi");
		c->SaveAs(savename);
		c->Destructor();
	}

	if(phi_bins.x != 0 && phi_bins.y != 0)
	{
		std::string filename3 = filename + "phi";
		const char * savename = filename3.c_str();
		TCanvas * c = new TCanvas("c", "c", 1000, 1000);
		phi->Draw("CONT1Z");
		phi->GetXaxis()->SetTitle("x");
		phi->GetYaxis()->SetTitle("y");
		phi->GetXaxis()->CenterTitle();
		phi->GetYaxis()->CenterTitle();
		phi->SetTitle("contour plot phi");
		c->SaveAs(savename);
		c->Destructor();
	}

}

void visualization_root_c::FillBins()
{
	TH2F * velocity = new TH2F("harr", "test", velocity_bins.x, min_range.x, max_range.x, velocity_bins.y, min_range.y, max_range.y);
	TH2F * psi = new TH2F("harr", "test", psi_bins.x, min_range.x, max_range.x, psi_bins.y, min_range.y, max_range.y);
	TH2F * phi = new TH2F("harr", "test", phi_bins.x, min_range.x, max_range.x, phi_bins.y, min_range.y, max_range.y);
	std::vector<wif_core::vector_2d_c> flows;
	flows[1] = velocity_bins;
	flows[2] = psi_bins;
	flows[3] = phi_bins;
	wif_core::vector_2d_c pos;

	for(int k = 1; k <= 3; k++)
	{
		double stepsx = round((max_range.x - min_range.x) / flows[k].x);
		double stepsy = round((max_range.y - min_range.y) / flows[k].y);

		for(int i = 1; i <= flows[k].x; i++)
		{
			for(int j = 1; j <= flows[k].y; j++)
			{
				double evaluateX = min_range.x + i * stepsx - stepsx / 2;
				double evaluateY = min_range.y + j * stepsy - stepsy / 2;
				pos.x = evaluateX;
				pos.y = evaluateY;

				if(k == 1)
				{
					wif_core::vector_2d_c vel = flow->get_velocity(pos);
					velocity->SetBinContent(i, j, sqrt(pow(vel.x, 2) + pow(vel.y, 2)));
				}
				else if(k == 2)
				{
					psi->SetBinContent(i, j, flow->get_psi(pos));
				}
				else
				{
					phi->SetBinContent(i, j, flow->get_phi(pos));
				}
			}
		}
	}
}
}// namespace wif_viz
