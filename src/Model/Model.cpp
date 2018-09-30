
#include "Model.h"
#include "Mesh.h"

#include "Loader/Loader.h"

Model::Model() {
	vao = 0;
	vbos.clear();
	size = 0;
}

void Model::unBufferMesh() {
	Loader::get().UnBuffer(*this);
}
