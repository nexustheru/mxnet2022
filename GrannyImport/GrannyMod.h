#pragma once
#include "includes.h"


using namespace std;
class GrannyMod
{
public:
	GrannyMod();

	granny_file_info* loadFile(string* filename);

	void set__vertex_data(int s) {};
	vector<granny_vertex_data*> get_vertex_data() { return vertex; };
	vector<granny_mesh*> get_mesh() { return meshes; };
	vector<granny_skeleton*> get_skeleton() { return skeletons; };
	vector<granny_tri_topology*> get_triangle_data() { return triangles; };
	vector<granny_material*> get_material() { return materials; };
	vector<granny_transform*> get_trans() { return trans; };
	void createScene(ImpInterface* i, Interface* gi);
    granny_file* grannyfile;
	//

	~GrannyMod();
private:
		vector<granny_model*> models;
	vector<granny_animation*> animations;
	vector<granny_skeleton*> skeletons;
	vector<granny_material*> materials;
	vector<granny_vertex_data*> vertex;
	vector<granny_tri_topology*> triangles;
	vector<granny_mesh*> meshes;
	vector<granny_texture*> textures;
	vector<granny_transform*> trans;

	Interface* i;
};

