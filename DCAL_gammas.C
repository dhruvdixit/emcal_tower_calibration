{
//=========Macro generated from canvas: c3/c3
//=========  (Thu Jul 21 15:42:05 2016) by ROOT version5.34/30
   TCanvas *c3 = new TCanvas("c3", "c3",1420,52,500,500);
   gStyle->SetOptStat(0);
   c3->Range(-1.75,-55.78125,10.75,502.0313);
   c3->SetFillColor(0);
   c3->SetBorderMode(0);
   c3->SetBorderSize(2);
   c3->SetFrameBorderMode(0);
   c3->SetFrameBorderMode(0);
   
   TH1D *gammaHist80DC = new TH1D("gammaHist80DC","DCAL #gamma for #chi^{2} cuts",100,-0.5,9.5);
   gammaHist80DC->SetBinContent(6,419);
   gammaHist80DC->SetBinContent(7,363);
   gammaHist80DC->SetBinContent(8,425);
   gammaHist80DC->SetBinContent(9,385);
   gammaHist80DC->SetBinContent(10,347);
   gammaHist80DC->SetBinContent(11,343);
   gammaHist80DC->SetBinContent(12,316);
   gammaHist80DC->SetBinContent(13,299);
   gammaHist80DC->SetBinContent(14,254);
   gammaHist80DC->SetBinContent(15,181);
   gammaHist80DC->SetBinContent(16,183);
   gammaHist80DC->SetBinContent(17,140);
   gammaHist80DC->SetBinContent(18,103);
   gammaHist80DC->SetBinContent(19,79);
   gammaHist80DC->SetBinContent(20,50);
   gammaHist80DC->SetBinContent(21,42);
   gammaHist80DC->SetBinContent(22,28);
   gammaHist80DC->SetBinContent(23,22);
   gammaHist80DC->SetBinContent(24,22);
   gammaHist80DC->SetBinContent(25,13);
   gammaHist80DC->SetBinContent(26,8);
   gammaHist80DC->SetBinContent(27,12);
   gammaHist80DC->SetBinContent(28,11);
   gammaHist80DC->SetBinContent(29,9);
   gammaHist80DC->SetBinContent(30,14);
   gammaHist80DC->SetBinContent(31,12);
   gammaHist80DC->SetBinContent(32,15);
   gammaHist80DC->SetBinContent(33,22);
   gammaHist80DC->SetBinContent(34,7);
   gammaHist80DC->SetBinContent(35,11);
   gammaHist80DC->SetBinContent(36,16);
   gammaHist80DC->SetBinContent(37,14);
   gammaHist80DC->SetBinContent(38,9);
   gammaHist80DC->SetBinContent(39,9);
   gammaHist80DC->SetBinContent(40,13);
   gammaHist80DC->SetBinContent(41,5);
   gammaHist80DC->SetBinContent(42,7);
   gammaHist80DC->SetBinContent(43,9);
   gammaHist80DC->SetBinContent(44,3);
   gammaHist80DC->SetBinContent(45,1);
   gammaHist80DC->SetBinContent(46,1);
   gammaHist80DC->SetBinContent(47,2);
   gammaHist80DC->SetBinContent(49,1);
   gammaHist80DC->SetBinContent(50,1);
   gammaHist80DC->SetBinContent(53,1);
   gammaHist80DC->SetBinContent(54,1);
   gammaHist80DC->SetBinContent(59,1);
   gammaHist80DC->SetBinContent(62,1);
   gammaHist80DC->SetBinContent(69,1);
   gammaHist80DC->SetBinContent(82,1);
   gammaHist80DC->SetBinContent(86,1);
   gammaHist80DC->SetBinContent(90,1);
   gammaHist80DC->SetBinContent(99,1);
   gammaHist80DC->SetBinContent(101,1);
   gammaHist80DC->SetEntries(4236);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   gammaHist80DC->SetLineColor(ci);
   //gammaHist80DC->SetMarkerStyle(2);
   gammaHist80DC->GetXaxis()->SetLabelFont(42);
   gammaHist80DC->GetXaxis()->SetLabelSize(0.035);
   gammaHist80DC->GetXaxis()->SetTitleSize(0.035);
   gammaHist80DC->GetXaxis()->SetTitleFont(42);
   gammaHist80DC->GetYaxis()->SetLabelFont(42);
   gammaHist80DC->GetYaxis()->SetLabelSize(0.035);
   gammaHist80DC->GetYaxis()->SetTitleSize(0.035);
   gammaHist80DC->GetYaxis()->SetTitleFont(42);
   gammaHist80DC->GetZaxis()->SetLabelFont(42);
   gammaHist80DC->GetZaxis()->SetLabelSize(0.035);
   gammaHist80DC->GetZaxis()->SetTitleSize(0.035);
   gammaHist80DC->GetZaxis()->SetTitleFont(42);
   gammaHist80DC->Draw();
   
   TH1D *gammaHist200DC = new TH1D("gammaHist200DC","gammaHistDC 80 < #chi^{2} <= 200",100,-0.5,9.5);
   gammaHist200DC->SetBinContent(6,2);
   gammaHist200DC->SetBinContent(7,3);
   gammaHist200DC->SetBinContent(8,7);
   gammaHist200DC->SetBinContent(9,26);
   gammaHist200DC->SetBinContent(10,38);
   gammaHist200DC->SetBinContent(11,50);
   gammaHist200DC->SetBinContent(12,48);
   gammaHist200DC->SetBinContent(13,44);
   gammaHist200DC->SetBinContent(14,45);
   gammaHist200DC->SetBinContent(15,34);
   gammaHist200DC->SetBinContent(16,24);
   gammaHist200DC->SetBinContent(17,19);
   gammaHist200DC->SetBinContent(18,12);
   gammaHist200DC->SetBinContent(19,8);
   gammaHist200DC->SetBinContent(20,6);
   gammaHist200DC->SetBinContent(21,8);
   gammaHist200DC->SetBinContent(22,6);
   gammaHist200DC->SetBinContent(23,1);
   gammaHist200DC->SetBinContent(24,5);
   gammaHist200DC->SetBinContent(25,1);
   gammaHist200DC->SetBinContent(26,3);
   gammaHist200DC->SetBinContent(27,1);
   gammaHist200DC->SetBinContent(28,2);
   gammaHist200DC->SetBinContent(29,4);
   gammaHist200DC->SetBinContent(30,2);
   gammaHist200DC->SetBinContent(31,3);
   gammaHist200DC->SetBinContent(32,5);
   gammaHist200DC->SetBinContent(33,4);
   gammaHist200DC->SetBinContent(34,2);
   gammaHist200DC->SetBinContent(35,2);
   gammaHist200DC->SetBinContent(36,2);
   gammaHist200DC->SetBinContent(38,1);
   gammaHist200DC->SetBinContent(41,2);
   gammaHist200DC->SetBinContent(42,1);
   gammaHist200DC->SetBinContent(50,1);
   gammaHist200DC->SetBinContent(55,1);
   gammaHist200DC->SetBinContent(56,1);
   gammaHist200DC->SetBinContent(66,1);
   gammaHist200DC->SetBinContent(101,2);
   gammaHist200DC->SetEntries(427);

   ci = TColor::GetColor("#000099");
   gammaHist200DC->SetLineColor(kRed);
   //gammaHist200DC->SetMarkerStyle(3);
   gammaHist200DC->GetXaxis()->SetLabelFont(42);
   gammaHist200DC->GetXaxis()->SetLabelSize(0.035);
   gammaHist200DC->GetXaxis()->SetTitleSize(0.035);
   gammaHist200DC->GetXaxis()->SetTitleFont(42);
   gammaHist200DC->GetYaxis()->SetLabelFont(42);
   gammaHist200DC->GetYaxis()->SetLabelSize(0.035);
   gammaHist200DC->GetYaxis()->SetTitleSize(0.035);
   gammaHist200DC->GetYaxis()->SetTitleFont(42);
   gammaHist200DC->GetZaxis()->SetLabelFont(42);
   gammaHist200DC->GetZaxis()->SetLabelSize(0.035);
   gammaHist200DC->GetZaxis()->SetTitleSize(0.035);
   gammaHist200DC->GetZaxis()->SetTitleFont(42);
   gammaHist200DC->Draw("same");
   
   TH1D *gammaHistBeyondDC = new TH1D("gammaHistBeyondDC","gammaHistDC #chi^{2} > 200",100,-0.5,9.5);
   gammaHistBeyondDC->SetBinContent(6,2);
   gammaHistBeyondDC->SetBinContent(7,3);
   gammaHistBeyondDC->SetBinContent(8,1);
   gammaHistBeyondDC->SetBinContent(9,6);
   gammaHistBeyondDC->SetBinContent(10,1);
   gammaHistBeyondDC->SetBinContent(11,3);
   gammaHistBeyondDC->SetBinContent(12,3);
   gammaHistBeyondDC->SetBinContent(13,7);
   gammaHistBeyondDC->SetBinContent(14,11);
   gammaHistBeyondDC->SetBinContent(15,16);
   gammaHistBeyondDC->SetBinContent(16,19);
   gammaHistBeyondDC->SetBinContent(17,23);
   gammaHistBeyondDC->SetBinContent(18,17);
   gammaHistBeyondDC->SetBinContent(19,21);
   gammaHistBeyondDC->SetBinContent(20,23);
   gammaHistBeyondDC->SetBinContent(21,30);
   gammaHistBeyondDC->SetBinContent(22,26);
   gammaHistBeyondDC->SetBinContent(23,23);
   gammaHistBeyondDC->SetBinContent(24,29);
   gammaHistBeyondDC->SetBinContent(25,15);
   gammaHistBeyondDC->SetBinContent(26,11);
   gammaHistBeyondDC->SetBinContent(27,21);
   gammaHistBeyondDC->SetBinContent(28,21);
   gammaHistBeyondDC->SetBinContent(29,9);
   gammaHistBeyondDC->SetBinContent(30,12);
   gammaHistBeyondDC->SetBinContent(31,18);
   gammaHistBeyondDC->SetBinContent(32,17);
   gammaHistBeyondDC->SetBinContent(33,17);
   gammaHistBeyondDC->SetBinContent(34,17);
   gammaHistBeyondDC->SetBinContent(35,15);
   gammaHistBeyondDC->SetBinContent(36,9);
   gammaHistBeyondDC->SetBinContent(37,9);
   gammaHistBeyondDC->SetBinContent(38,14);
   gammaHistBeyondDC->SetBinContent(39,8);
   gammaHistBeyondDC->SetBinContent(40,3);
   gammaHistBeyondDC->SetBinContent(41,2);
   gammaHistBeyondDC->SetBinContent(43,3);
   gammaHistBeyondDC->SetBinContent(45,1);
   gammaHistBeyondDC->SetBinContent(47,1);
   gammaHistBeyondDC->SetBinContent(51,1);
   gammaHistBeyondDC->SetBinContent(52,2);
   gammaHistBeyondDC->SetBinContent(53,1);
   gammaHistBeyondDC->SetBinContent(59,1);
   gammaHistBeyondDC->SetBinContent(61,1);
   gammaHistBeyondDC->SetBinContent(64,1);
   gammaHistBeyondDC->SetBinContent(67,1);
   gammaHistBeyondDC->SetBinContent(78,1);
   gammaHistBeyondDC->SetBinContent(80,1);
   gammaHistBeyondDC->SetBinContent(87,1);
   gammaHistBeyondDC->SetBinContent(101,11);
   gammaHistBeyondDC->SetEntries(509);

   ci = TColor::GetColor("#000099");
   gammaHistBeyondDC->SetLineColor(kGreen);
   //gammaHistBeyondDC->SetMarkerStyle(4);
   gammaHistBeyondDC->GetXaxis()->SetLabelFont(42);
   gammaHistBeyondDC->GetXaxis()->SetLabelSize(0.035);
   gammaHistBeyondDC->GetXaxis()->SetTitleSize(0.035);
   gammaHistBeyondDC->GetXaxis()->SetTitleFont(42);
   gammaHistBeyondDC->GetYaxis()->SetLabelFont(42);
   gammaHistBeyondDC->GetYaxis()->SetLabelSize(0.035);
   gammaHistBeyondDC->GetYaxis()->SetTitleSize(0.035);
   gammaHistBeyondDC->GetYaxis()->SetTitleFont(42);
   gammaHistBeyondDC->GetZaxis()->SetLabelFont(42);
   gammaHistBeyondDC->GetZaxis()->SetLabelSize(0.035);
   gammaHistBeyondDC->GetZaxis()->SetTitleSize(0.035);
   gammaHistBeyondDC->GetZaxis()->SetTitleFont(42);
   gammaHistBeyondDC->Draw("same");
   
   TLegend *leg = new TLegend(0.7,0.8,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextSize(0.02);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("gammaHist80DC","#chi^{2} <= 80","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(2);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("gammaHist200DC","80 < #chi^{2} <= 200","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("gammaHistBeyondDC","#chi^{2} > 200","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(4);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.2228629,0.9314407,0.7771371,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("gammaHistDC #chi^{2} <= 80");
   pt->Draw();
   c3->Modified();
   c3->cd();
   c3->SetSelected(c3);
}
