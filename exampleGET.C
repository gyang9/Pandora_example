{
TFile f("/home/guang/work/Pandora/WorkshopContent/data/testEvent_3DST_222_muonFlat_sampleT.root");
TTree* t = (TTree*)f.Get("EDepSimTree");

int event;
double hitLocation[3];
ofstream out;
out.open("test1.txt");

t->SetBranchAddress("event",&event);
t->SetBranchAddress("hitLocation",&hitLocation);

for(Int_t i=0;i<t->GetEntries();i++){
t->GetEntry(i);
	if(event == 2 && hitLocation[1] != 0)
	cout<<hitLocation[1]<<" , "<<endl;
        out<<hitLocation[1]<<" "<<endl;
}

}




