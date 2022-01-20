# GNU Automake config

# Installing the data to model/$(MODEL) facilitates installing model data files
# under the UCVM data directory.

MODEL=cvmh
MODEL_URL=https://g-c662a6.a78b8.36fe.data.globus.org/ucvm/models/CVMH/cvmh
MODEL_DIR=$(datadir)/model/$(MODEL)

model_files = \
	base@@ \
	BASE.gts \
	BATO.gts \
	CVM_CM_TAG@@ \
	CVM_CM.vo \
	CVM_CM_VP@@ \
	CVM_CM_VS@@ \
	CVM_HR_TAG@@ \
	CVM_HR.vo \
	CVM_HR_VP@@ \
	CVM_HR_VS@@ \
	CVM_LR.vo \
	CVMSM_flags@@ \
	CVMSM_tag66@@ \
	CVMSM_vp66@@ \
	CVMSM_vs66@@ \
	cvm_vs30_wills.hdr \
	cvm_vs30_wills.mdl \
	interfaces.vo \
	model_top@@ \
	moho@@ \
	MOHO.gts \
	topo_dem@@ \
	tsurf/CMxVM_Model3D_CalMex_BATO.ts \
	tsurf/CMxVM_Model3D_CM_BASE_Folded.dxf \
	tsurf/CMxVM_Model3D_CM_BASE_Folded.ts \
	tsurf/CVMH_Basement64.ts \
	tsurf/CVMH_CalMex_BATO.ts \
	tsurf/CVMH_Moho64.ts \
	tsurf/CVMH_Moho.ts

installed_data:
	$(MKDIR_P) $(MODEL_DIR)/tsurf
	for f in $(model_files); do $(CURL) -o $(MODEL_DIR)/$$f $(MODEL_URL)/$$f; done
	touch $(abs_builddir)/installed_data

install: installed_data


# End of file
