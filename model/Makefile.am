# GNU Automake config

EXTRA_DIST = base@@ *.gts CVM_* cvm_vs30* interfaces.vo model_top@@ \
	moho@@ topo_dem@@

all:

install:
	mkdir -p ${prefix}/model
	cp base@@ ${prefix}/model
	cp *.gts ${prefix}/model
	cp CVM_* ${prefix}/model
	cp CVMSM_* ${prefix}/model
	cp cvm_vs30* ${prefix}/model
	cp interfaces.vo ${prefix}/model
	cp model_top@@ ${prefix}/model
	cp moho@@ ${prefix}/model
	cp topo_dem@@ ${prefix}/model
	cp GFM* ${prefix}/model

clean:
