/**
Copyright 2009-2018 National Technology and Engineering Solutions of Sandia, 
LLC (NTESS).  Under the terms of Contract DE-NA-0003525, the U.S.  Government 
retains certain rights in this software.

Sandia National Laboratories is a multimission laboratory managed and operated
by National Technology and Engineering Solutions of Sandia, LLC., a wholly 
owned subsidiary of Honeywell International, Inc., for the U.S. Department of 
Energy's National Nuclear Security Administration under contract DE-NA0003525.

Copyright (c) 2009-2018, NTESS

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.

    * Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Questions? Contact sst-macro-help@sandia.gov
*/

#include <dumpi/common/perfctrtags.h>
#include <dumpi/dumpiconfig.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

typedef const char* tagstr_t;

static int arrlen_ = 0;
static uint32_t *dumpi_papi_perfctr_map_ = NULL;
static tagstr_t *dumpi_tagstr_map_ = NULL;   

#ifdef DUMPI_HAVE_PAPI

#include <papi.h>

#define DUMPI_ADD_ASSOCIATION(THE_PAPI_TAG)					\
  do {									\
    dumpi_papi_perfctr_map_[DUMPI_##THE_PAPI_TAG] = THE_PAPI_TAG;	\
    dumpi_tagstr_map_[DUMPI_##THE_PAPI_TAG] = #THE_PAPI_TAG;		\
  } while(0)

#else /* ! DUMPI_HAVE_PAPI */

#define DUMPI_ADD_ASSOCIATION(THE_PAPI_TAG)					\
  do {									\
    dumpi_papi_perfctr_map_[DUMPI_##THE_PAPI_TAG] = -1;			\
    dumpi_tagstr_map_[DUMPI_##THE_PAPI_TAG] = #THE_PAPI_TAG;		\
  } while(0)

#endif /* ! DUMPI_HAVE_PAPI */

void dumpi_init_perfctr_tags(void) {
  int count;
  arrlen_ = DUMPI_PAPI_END+1;
  count = arrlen_;
  if(dumpi_papi_perfctr_map_ != NULL)
    return;
  /* Any undefined perfcounters set to PAPI_END by default */
  dumpi_papi_perfctr_map_ = (uint32_t*)calloc(count, sizeof(uint32_t));
  assert(dumpi_papi_perfctr_map_ != NULL);
  dumpi_tagstr_map_ = (tagstr_t*)calloc(count, sizeof(tagstr_t));
  assert(dumpi_papi_perfctr_map_ != NULL && dumpi_tagstr_map_ != NULL);
  /* Populate all associations */
  DUMPI_ADD_ASSOCIATION(PAPI_L1_DCM);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_ICM);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_DCM);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_ICM);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_DCM);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_ICM);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_TCM);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_TCM);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_TCM);
  DUMPI_ADD_ASSOCIATION(PAPI_CA_SNP);
  DUMPI_ADD_ASSOCIATION(PAPI_CA_SHR);
  DUMPI_ADD_ASSOCIATION(PAPI_CA_CLN);
  DUMPI_ADD_ASSOCIATION(PAPI_CA_INV);
  DUMPI_ADD_ASSOCIATION(PAPI_CA_ITV);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_LDM);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_STM);
  DUMPI_ADD_ASSOCIATION(PAPI_BRU_IDL);
  DUMPI_ADD_ASSOCIATION(PAPI_FXU_IDL);
  DUMPI_ADD_ASSOCIATION(PAPI_FPU_IDL);
  DUMPI_ADD_ASSOCIATION(PAPI_LSU_IDL);
  DUMPI_ADD_ASSOCIATION(PAPI_TLB_DM);
  DUMPI_ADD_ASSOCIATION(PAPI_TLB_IM);
  DUMPI_ADD_ASSOCIATION(PAPI_TLB_TL);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_LDM);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_STM);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_LDM);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_STM);
  DUMPI_ADD_ASSOCIATION(PAPI_BTAC_M);
  DUMPI_ADD_ASSOCIATION(PAPI_PRF_DM);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_DCH);
  DUMPI_ADD_ASSOCIATION(PAPI_TLB_SD);
  DUMPI_ADD_ASSOCIATION(PAPI_CSR_FAL);
  DUMPI_ADD_ASSOCIATION(PAPI_CSR_SUC);
  DUMPI_ADD_ASSOCIATION(PAPI_CSR_TOT);
  DUMPI_ADD_ASSOCIATION(PAPI_MEM_SCY);
  DUMPI_ADD_ASSOCIATION(PAPI_MEM_RCY);
  DUMPI_ADD_ASSOCIATION(PAPI_MEM_WCY);
  DUMPI_ADD_ASSOCIATION(PAPI_STL_ICY);
  DUMPI_ADD_ASSOCIATION(PAPI_FUL_ICY);
  DUMPI_ADD_ASSOCIATION(PAPI_STL_CCY);
  DUMPI_ADD_ASSOCIATION(PAPI_FUL_CCY);
  DUMPI_ADD_ASSOCIATION(PAPI_HW_INT);
  DUMPI_ADD_ASSOCIATION(PAPI_BR_UCN);
  DUMPI_ADD_ASSOCIATION(PAPI_BR_CN);
  DUMPI_ADD_ASSOCIATION(PAPI_BR_TKN);
  DUMPI_ADD_ASSOCIATION(PAPI_BR_NTK);
  DUMPI_ADD_ASSOCIATION(PAPI_BR_MSP);
  DUMPI_ADD_ASSOCIATION(PAPI_BR_PRC);
  DUMPI_ADD_ASSOCIATION(PAPI_FMA_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_TOT_IIS);
  DUMPI_ADD_ASSOCIATION(PAPI_TOT_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_INT_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_FP_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_LD_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_SR_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_BR_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_VEC_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_RES_STL);
  DUMPI_ADD_ASSOCIATION(PAPI_FP_STAL);
  DUMPI_ADD_ASSOCIATION(PAPI_TOT_CYC);
  DUMPI_ADD_ASSOCIATION(PAPI_LST_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_SYC_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_DCH);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_DCH);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_DCA);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_DCA);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_DCA);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_DCR);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_DCR);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_DCR);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_DCW);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_DCW);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_DCW);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_ICH);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_ICH);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_ICH);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_ICA);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_ICA);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_ICA);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_ICR);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_ICR);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_ICR);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_ICW);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_ICW);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_ICW);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_TCH);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_TCH);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_TCH);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_TCA);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_TCA);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_TCA);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_TCR);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_TCR);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_TCR);
  DUMPI_ADD_ASSOCIATION(PAPI_L1_TCW);
  DUMPI_ADD_ASSOCIATION(PAPI_L2_TCW);
  DUMPI_ADD_ASSOCIATION(PAPI_L3_TCW);
  DUMPI_ADD_ASSOCIATION(PAPI_FML_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_FAD_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_FDV_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_FSQ_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_FNV_INS);
  DUMPI_ADD_ASSOCIATION(PAPI_FP_OPS);
#ifdef _BGL
  DUMPI_ADD_ASSOCIATION(PAPI_BGL_OED);
  DUMPI_ADD_ASSOCIATION(PAPI_BGL_TS_32B);
  DUMPI_ADD_ASSOCIATION(PAPI_BGL_TS_FULL);
  DUMPI_ADD_ASSOCIATION(PAPI_BGL_TR_DPKT);
  DUMPI_ADD_ASSOCIATION(PAPI_BGL_TR_FULL);
#endif /* ! _BGL */
  DUMPI_ADD_ASSOCIATION(MLX_XMIT_DATA);
  DUMPI_ADD_ASSOCIATION(MLX_RCV_DATA);
  DUMPI_ADD_ASSOCIATION(PAPI_END);
}

/*
 * Get string name for a perfcounter.
 */
const char* dumpi_perfctr_name(int tag) {
  dumpi_init_perfctr_tags();
  if(tag >= 0 && tag <= DUMPI_PAPI_END) {
    return dumpi_tagstr_map_[tag];
  }
  else {
    return "ERROR_INVALID_PAPI_TAG";
  }
}

/*
 * Get PAPI label for a DUMPI_PAPI tag.
 */
int dumpi_get_event_code(dumpi_papi_tag tag) {
  dumpi_init_perfctr_tags();
  assert((int)tag >= 0 && tag <= DUMPI_PAPI_END);
  return dumpi_papi_perfctr_map_[tag];
}
