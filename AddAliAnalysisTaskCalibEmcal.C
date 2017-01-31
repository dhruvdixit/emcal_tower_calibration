// #include "AliAnalysisTaskCalibEmcal.h"

AliAnalysisTaskCalibEmcal *AddAliAnalysisTaskCalibEmcal(TString name = "AliAnalysisTaskCalibEmcal")
{
	AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
	AliAnalysisTaskCalibEmcal *task =
		new AliAnalysisTaskCalibEmcal(name.Data());

	AliEMCALRecoUtils *reco_utils = task->GetEMCALRecoUtils();
  
	gROOT->LoadMacro("$ALICE_PHYSICS/PWGPP/EMCAL/macros/ConfigureEMCALRecoUtils.C");
  
	ConfigureEMCALRecoUtils(reco_utils, kFALSE, kTRUE, kTRUE,
							kFALSE, kFALSE, kFALSE); 

	TString filename = mgr->GetCommonFileName();

	filename += ":AliAnalysisTaskCalibEmcal";

	mgr->AddTask(task);
	mgr->ConnectInput(task, 0, mgr->GetCommonInputContainer());
	mgr->ConnectOutput(task, 1, mgr->CreateContainer("histogram", TList::Class(), AliAnalysisManager::kOutputContainer, filename.Data()));

	return task;
}
