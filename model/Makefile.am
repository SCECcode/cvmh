# GNU Automake config

# Installing the data to model/$(MODEL) facilitates installing model data files
# under the UCVM data directory.

all:
if WITH_CVMH_LARGEDATA_DIR
	echo "USING WITH_CVMH_LARGEDATA_DIR in cvmh"
else
	./make_data_files.py
endif

install:
if WITH_CVMH_LARGEDATA_DIR
	$(MKDIR_P) ${prefix}/data
	$(LN_S) -f $(CVMH_LARGEDATA_DIR) ${prefix}/data/cvmh
	cp config ${prefix}/data
	echo "USING WITH_CVMH_LARGEDATA_DIR in cvmh"
else
	$(MKDIR_P) ${prefix}/data/cvmh
	cp config ${prefix}/data
	cp cvmh/base@@ ${prefix}/data/cvmh
	cp cvmh/*.gts ${prefix}/data/cvmh
	cp cvmh/CVM_* ${prefix}/data/cvmh
	cp cvmh/CVMSM_* ${prefix}/data/cvmh
	cp cvmh/cvm_vs30* ${prefix}/data/cvmh
	cp cvmh/interfaces.vo ${prefix}/data/cvmh
	cp cvmh/model_top@@ ${prefix}/data/cvmh
	cp cvmh/moho@@ ${prefix}/data/cvmh
	cp cvmh/topo_dem@@ ${prefix}/data/cvmh
	cp -r cvmh/tsurf ${prefix}/data/cvmh
endif

clean:
	echo "clean"

#MODEL=cvmh
#MODEL_URL=https://g-c662a6.a78b8.36fe.data.globus.org/ucvm/models/CVMH/cvmh
#MODEL_DIR=$(datadir)/model/$(MODEL)
#
#model_files = \
#	base@@ \
#	BASE.gts \
#	BATO.gts \
#	CVM_CM_TAG@@ \
#	CVM_CM.vo \
#	CVM_CM_VP@@ \
#	CVM_CM_VS@@ \
#	CVM_HR_TAG@@ \
#	CVM_HR.vo \
#	CVM_HR_VP@@ \
#	CVM_HR_VS@@ \
#	CVM_LR.vo \
#	CVMSM_flags@@ \
#	CVMSM_tag66@@ \
#	CVMSM_vp66@@ \
#	CVMSM_vs66@@ \
#	cvm_vs30_wills.hdr \
#	cvm_vs30_wills.mdl \
#	interfaces.vo \
#	model_top@@ \
#	moho@@ \
#	MOHO.gts \
#	topo_dem@@ \
#	tsurf/CMxVM_Model3D_CalMex_BATO.ts \
#	tsurf/CMxVM_Model3D_CM_BASE_Folded.dxf \
#	tsurf/CMxVM_Model3D_CM_BASE_Folded.ts \
#	tsurf/CVMH_Basement64.ts \
#	tsurf/CVMH_CalMex_BATO.ts \
#	tsurf/CVMH_Moho64.ts \
#	tsurf/CVMH_Moho.ts
#
#installed_data:
#	$(MKDIR_P) $(MODEL_DIR)/tsurf
#	for f in $(model_files); do $(CURL) -o $(MODEL_DIR)/$$f $(MODEL_URL)/$$f; done
#	touch $(abs_builddir)/installed_data
#
#install: installed_data


# End of file
