##!/bin/env python

from condor_submit_util import submit
from time import sleep

#______________________________________________________________________________________
def get_master_list():

    dinfos = {}

    ########################################
    ######## WWW BABY MC 2018 102x #########
    ########################################

    sample_info = {

        # "/EGamma/Run2018A-PromptReco-v1/MINIAOD": "data_Run2018Av1_ee",
        # "/EGamma/Run2018A-PromptReco-v2/MINIAOD": "data_Run2018Av2_ee",
        # "/EGamma/Run2018A-PromptReco-v3/MINIAOD": "data_Run2018Av3_ee",
        # "/EGamma/Run2018B-PromptReco-v1/MINIAOD": "data_Run2018Bv1_ee",
        # "/EGamma/Run2018B-PromptReco-v2/MINIAOD": "data_Run2018Bv2_ee",
        # "/EGamma/Run2018C-PromptReco-v1/MINIAOD": "data_Run2018Cv1_ee",
        # "/EGamma/Run2018C-PromptReco-v2/MINIAOD": "data_Run2018Cv2_ee",
        # "/EGamma/Run2018C-PromptReco-v3/MINIAOD": "data_Run2018Cv3_ee",
        "/EGamma/Run2018D-PromptReco-v2/MINIAOD": "data_Run2018Dv2_ee",
        # "/DoubleMuon/Run2018A-PromptReco-v1/MINIAOD": "data_Run2018Av1_mm",
        # "/DoubleMuon/Run2018A-PromptReco-v2/MINIAOD": "data_Run2018Av2_mm",
        # "/DoubleMuon/Run2018A-PromptReco-v3/MINIAOD": "data_Run2018Av3_mm",
        # "/DoubleMuon/Run2018B-PromptReco-v1/MINIAOD": "data_Run2018Bv1_mm",
        # "/DoubleMuon/Run2018B-PromptReco-v2/MINIAOD": "data_Run2018Bv2_mm",
        # "/DoubleMuon/Run2018C-PromptReco-v1/MINIAOD": "data_Run2018Cv1_mm",
        # "/DoubleMuon/Run2018C-PromptReco-v2/MINIAOD": "data_Run2018Cv2_mm",
        # "/DoubleMuon/Run2018C-PromptReco-v3/MINIAOD": "data_Run2018Cv3_mm",
        "/DoubleMuon/Run2018D-PromptReco-v2/MINIAOD": "data_Run2018Dv2_mm",
        # "/MuonEG/Run2018A-PromptReco-v1/MINIAOD": "data_Run2018Av1_em",
        # "/MuonEG/Run2018A-PromptReco-v2/MINIAOD": "data_Run2018Av2_em",
        # "/MuonEG/Run2018A-PromptReco-v3/MINIAOD": "data_Run2018Av3_em",
        # "/MuonEG/Run2018B-PromptReco-v1/MINIAOD": "data_Run2018Bv1_em",
        # "/MuonEG/Run2018B-PromptReco-v2/MINIAOD": "data_Run2018Bv2_em",
        # "/MuonEG/Run2018C-PromptReco-v1/MINIAOD": "data_Run2018Cv1_em",
        # "/MuonEG/Run2018C-PromptReco-v2/MINIAOD": "data_Run2018Cv2_em",
        # "/MuonEG/Run2018C-PromptReco-v3/MINIAOD": "data_Run2018Cv3_em",
        "/MuonEG/Run2018D-PromptReco-v2/MINIAOD": "data_Run2018Dv2_em",

        # Rereco
        "/EGamma/Run2018A-17Sep2018-v2/MINIAOD": "data_Run2018Av2_ee",
        "/EGamma/Run2018B-17Sep2018-v1/MINIAOD": "data_Run2018Bv1_ee",
        "/EGamma/Run2018C-17Sep2018-v1/MINIAOD": "data_Run2018Cv1_ee",
        "/DoubleMuon/Run2018A-17Sep2018-v2/MINIAOD": "data_Run2018Av2_mm",
        "/DoubleMuon/Run2018B-17Sep2018-v1/MINIAOD": "data_Run2018Bv1_mm",
        "/DoubleMuon/Run2018C-17Sep2018-v1/MINIAOD": "data_Run2018Cv1_mm",
        "/MuonEG/Run2018A-17Sep2018-v1/MINIAOD": "data_Run2018Av1_em",
        "/MuonEG/Run2018B-17Sep2018-v1/MINIAOD": "data_Run2018Bv1_em",
        "/MuonEG/Run2018C-17Sep2018-v1/MINIAOD": "data_Run2018Cv1_em",

        "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                               : "www_amcatnlo"               ,
        "/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"                        : "vh_nonbb_amcatnlo"          ,
        "/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"                    : "dy_m1050_madgraph"          ,
        "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                        : "dy_m50_madgraph"            ,
        "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"                             : "wjets_incl_madgraph"        ,
        "/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                 : "wjets_ht100_madgraph"       ,
        "/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                 : "wjets_ht200_madgraph"       ,
        "/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                 : "wjets_ht400_madgraph"       ,
        "/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                 : "wjets_ht600_madgraph"       ,
        "/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                : "wjets_ht800_madgraph"       ,
        "/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"               : "wjets_ht1200_madgraph"      ,
        "/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                : "wjets_ht2500_madgraph"      ,
        "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v4/MINIAODSIM"         : "sts_4f_leptonic_madgraph"   ,
        # ST t-channel top
        # ST t-channel anti-top
        "/ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1/MINIAODSIM"              : "twz_ll_madgraph"            ,
        "/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v3/MINIAODSIM" : "tw_antitopnofullhad_powheg" ,
        "/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v3/MINIAODSIM"     : "tw_topnofullhad_powheg"     ,
        "/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"                   : "ggh_hzz4l_powheg"           ,
        "/WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                            : "vbsww_madgraph"             ,
        "/WW_DoubleScattering_13TeV-pythia8_TuneCP5/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1/MINIAODSIM"                           : "ww_dblsct_pythia"           ,
        "/WW_TuneCP5_13TeV-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"                                                 : "ww_incl_pythia"             ,
        "/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                         : "wz_3lv_amcatnlo"            ,
        "/WZ_TuneCP5_13TeV-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v3/MINIAODSIM"                                                 : "wz_incl_pythia"             ,
        # WZ 1L1Nu2Q
        # WZ 1L3Nu
        # WZ 2L2Q
        # WZ 3LNu 0
        # WZ 3LNu 0
        # WZ 3LNu 1
        # WZ 3LNu 1
        # WZ 3LNu 2
        # WZ 3LNu 2
        # WZ 3LNu 3
        # WZ 3LNu 3
        # WZ 3LNu powheg
        "/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext2-v2/MINIAODSIM"                                 : "zz_4l_powheg"               ,
        "/WWZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                  : "wwz_amcatnlo"               ,
        "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                  : "wzz_amcatnlo"               ,
        "/WZG_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                                       : "wzg_amcatnlo"               ,
        "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                  : "zzz_amcatnlo"               ,
        "/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                 : "ttbar_1ltop_madgraph"       ,
        "/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"              : "ttbar_1ltbr_madgraph"       ,
        "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                                   : "ttbar_dilep_powheg"         ,
        "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                            : "ttbar_semilep_powheg"       ,
        "/TTGamma_SingleLeptFromT_TuneCP5_13TeV_madgraph_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"              : "ttgam_1ltop_madgraph"       ,
        "/TTGamma_SingleLeptFromTbar_TuneCP5_13TeV_madgraph_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"           : "ttgam_1ltbr_madgraph"       ,
        "/TTGamma_Dilept_TuneCP5_13TeV_madgraph_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                       : "ttgam_dilep_madgraph"       ,
        "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"             : "ttw_lnu_amcatnlo"           ,
        "/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                           : "ttz_ll_mll1_amcatnlo"       ,
        "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                     : "ttz_llvv_mll10_amcatnlo"    ,
        "/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                    : "tZq_ll_madgraph"            ,
        "/WWG_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                  : "wwg_amcatnlo"               ,

        "/TGJets_leptonDecays_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                  : "tgjets_lepdecay_madgraph"   ,
        "/WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1/MINIAODSIM"                  : "wg_lnug_amcatnlo"           ,
        "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"                               : "wg_lnug_madgraph"           ,
        "/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                   : "zg_llg_amcatnlo"            ,

        #/TTWJetsToQQ probably not needed
        #/TTZToQQ probably not needed
        # "/ZZ_TuneCP5_13TeV-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"                                                 : "ZZincl"                   ,
        # "/TTPlus1Jet_DiLept_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                : "TTdilep1jet"              ,
        # "/TT_DiLept_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                            : "TTdilep0jet"              ,
        # "/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"          : "TTHtoNonBB"               ,
        # "/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                 : "TTTTnew"                  ,
        # "/TTHH_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                 : "TTHH"                     ,
        # "/TTWZ_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                 : "TTWZ"                     ,
        # "/TTZZ_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                 : "TTZZ"                     ,
        # "/TTTW_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                 : "TTTW"                     ,
        # "/TTTJ_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                 : "TTTJ"                     ,
        # "/TTWH_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                 : "TTWH"                     ,
        # "/TTZH_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                 : "TTZH"                     ,
        # "/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"                                 : "TTWW"                     ,


        }

    dinfos["wvz_2018_102x"] = {
            "samples" : sample_info,
            "year" : 2018,
            "baby_type" : "WVZ"
            }

    return dinfos

#################################################################################################################################################################################################
# SUBMIT JOBS
#################################################################################################################################################################################################


if __name__ == "__main__":

    import argparse
    import sys

    parser = argparse.ArgumentParser(description="Submitting Baby Maker Jobs to Condor")
    parser.add_argument('-p' , '--production' , dest='production' , help='To submit ALL jobs for production'        , default=False         , action='store_true')
    parser.add_argument('-t' , '--test'       , dest='test'       , help='To submit test jobs (5 jobs each sample)' , default=False         , action='store_true')
    parser.add_argument(       '--tag'        , dest='tag'        , help='job tag'                                                          , required=True      )
    parser.add_argument(       '--sample_sets', dest='sample_sets', help='comma separated sample sets (e.g. WWW2018, WWW2017, FR2017, ...)' , required=True      )

    args = parser.parse_args()

    if args.test and args.production:
        parser.print_help()
        print "ERROR: Option conflict. Can't have both -t,--test and -p,--production at the same time."
        sys.exit(1)

    if not args.test and not args.production:
        parser.print_help()
        print "ERROR: Option missing. Choose either -t,--test or -p,--production."
        sys.exit(1)

    if args.test:
        print "Submitting a test job (i.e. 5 jobs max each sample) with tag =", args.tag

    if args.production:
        print "Submitting a production job (i.e. ALL jobs per sample) with tag =", args.tag

    grand_master_list = get_master_list()

    # filter out grand master list and form a master list to be passed on to submit function
    master_list = {}
    if "WVZ2018" in args.sample_sets:
        master_list["wvz_2018_102x"] = grand_master_list["wvz_2018_102x"]

    submit(master_list, args.tag, dotestrun=args.test)

#eof
