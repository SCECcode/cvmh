# GNU Automake config

EXTRA_DIST = cvmh/base@@ cvmh/*.gts cvmh/CVM_* cvmh/cvm_vs30* \
	cvmh/interfaces.vo cvmh/model_top@@ cvmh/moho@@ cvmh/topo_dem@@ cvmh/tsurf

all:

install:
	mkdir -p ${prefix}/model
	cp cvmh/base@@ ${prefix}/model
	cp cvmh/*.gts ${prefix}/model
	cp cvmh/CVM_* ${prefix}/model
	cp cvmh/CVMSM_* ${prefix}/model
	cp cvmh/cvm_vs30* ${prefix}/model
	cp cvmh/interfaces.vo ${prefix}/model
	cp cvmh/model_top@@ ${prefix}/model
	cp cvmh/moho@@ ${prefix}/model
	cp cvmh/topo_dem@@ ${prefix}/model
	cp -r cvmh/tsurf ${prefix}/model

clean:
