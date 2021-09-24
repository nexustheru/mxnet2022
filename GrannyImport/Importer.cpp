#include "Importer.h"
#include <QtWidgets/qmessagebox.h>
#include <inode.h>
#include <impapi.h>
#include <strclass.h>

ImpInterface* i;
Interface* gi;
Interface12* ip12 = GetCOREInterface12();
Interface* ip = GetCOREInterface();

using namespace MaxSDK::Graphics;

	vector<Point3> triangles;
	vector<int> trianglesInt;
	vector<Point3> normals;
	vector<Point3> vertexx;
	vector<Point2> uv;
	vector<INode*> bones;
	vector<char*> material;
	ImpNode* impnodee;

Importer::Importer(QWidget* parent) //:QWidget(parent)
{
	setupUi(this);
	setWindowTitle("Granny Import");
	grmod = new GrannyMod();
	connect(this->pushButton, SIGNAL(pressed()), this, SLOT(setOptions()));
}

void Importer::setmaxlobals(ImpInterface* I, Interface* GI, ImpNode* impnode)
{
	 i=I;
	 gi=GI;
	 impnodee = impnode;
}

void Importer::setGlobals(std::string* filename)
{
	 fiilename=filename;
	 this->filenameLineEdit->setText(QString::fromStdString(*fiilename));
	 granny_file_info* ginfo=grmod->loadFile(filename);
	 std::stringstream ss;
	 ss << "Meshcount=" << std::to_string(ginfo->MeshCount) << endl;
	 ss << "Animationcount=" << std::to_string(ginfo->AnimationCount) << endl;
	 ss << "Materialcount=" << std::to_string(ginfo->MaterialCount) << endl;
	 ss << "Modelcount=" << std::to_string(ginfo->ModelCount) << endl;
	 ss << "Skeletoncount=" << std::to_string(ginfo->SkeletonCount) << endl;
	 ss << "Texturecount=" << std::to_string(ginfo->TextureCount) << endl;
	 ss << "Vertexcount=" << std::to_string(ginfo->VertexDataCount) << endl;
	 ss << "Trianglecount=" << std::to_string(ginfo->TriTopologyCount) << endl;
	 QString com = QString::fromStdString(ss.str());
	 this->textEdit->setText(com);
show();

}

void SetVertex(Mesh& mesh, const vector<Point3>& v)
{
	int n = v.size();
	mesh.setNumVerts(n);
	for (int i = 0; i < n; ++i)
	{
		const Point3& t = v[i];
		mesh.setVert(i, t.x,t.y,t.z);

	}
}

TriObject* createTriangleMesh(const std::vector<Point3>& points,
	const std::vector<Point3>& normals,
	const std::vector<Point2>& uvs,
	const std::vector<int>& triangleVertIndices)
{
	TriObject* triobj = CreateNewTriObject();
	if (triobj == NULL)
		return NULL;

	assert(points.size() == normals.size() && normals.size() == uvs.size());
	assert(triangleVertIndices.size() % 3 == 0);

	int numVertices = (int)points.size();
	int numTriangles = (int)triangleVertIndices.size() / 3;
	Mesh& mesh = triobj->GetMesh();

	// set vertex positions
	mesh.setNumVerts(numVertices);
	for (int i = 0; i < numVertices; i++)
		mesh.setVert(i, points[i]);

	// set vertex normals
	mesh.SpecifyNormals();
	MeshNormalSpec* normalSpec = mesh.GetSpecifiedNormals();
	normalSpec->ClearNormals();
	normalSpec->SetNumNormals(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		normalSpec->Normal(i) = normals[i].Normalize();
		normalSpec->SetNormalExplicit(i, true);
	}

	// set UVs
	// TODO: multiple map channels?
	// channel 0 is reserved for vertex color, channel 1 is the default texture mapping
	mesh.setNumMaps(2);
	mesh.setMapSupport(1, TRUE);  // enable map channel
	MeshMap& map = mesh.Map(1);
	map.setNumVerts(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		UVVert& texVert = map.tv[i];
		texVert.x = uvs[i].x;
		texVert.y = uvs[i].y;
		texVert.z = 0.0f;
	}

	// set triangles
	mesh.setNumFaces(numTriangles);
	normalSpec->SetNumFaces(numTriangles);
	map.setNumFaces(numTriangles);
	for (int i = 0, j = 0; i < numTriangles; i++, j += 3)
	{
		// three vertex indices of a triangle
		int v0 = triangleVertIndices[j];
		int v1 = triangleVertIndices[j + 1];
		int v2 = triangleVertIndices[j + 2];

		// vertex positions
		Face& face = mesh.faces[i];
		face.setMatID(1);
		face.setEdgeVisFlags(1, 1, 1);
		face.setVerts(v0, v1, v2);

		// vertex normals
		MeshNormalFace& normalFace = normalSpec->Face(i);
		normalFace.SpecifyAll();
		normalFace.SetNormalID(0, v0);
		normalFace.SetNormalID(1, v1);
		normalFace.SetNormalID(2, v2);

		// vertex UVs
		TVFace& texFace = map.tf[i];
		texFace.setTVerts(v0, v1, v2);
	}

	mesh.InvalidateGeomCache();
	mesh.InvalidateTopologyCache();

	return triobj;
}

void SetMaps(Mesh& mesh, const vector<Point3>& v)
{
	int numVertices = v.size();
	mesh.setNumMaps(2);
	mesh.setMapSupport(1, TRUE);  // enable map channel
	MeshMap& map = mesh.Map(1);
	map.setNumVerts(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		UVVert& texVert = map.tv[i];
		texVert.x = uv[i].x;
		texVert.y = uv[i].y;
		texVert.z = 0.0f;
	}

}

void SetTriangles(Mesh& mesh, const vector<Point3>& v)
{
	int n = v.size();
	int nm = mesh.getNumMaps();
	mesh.setNumFaces(n);
	mesh.setNumTVFaces(nm);
	for (int j = 0; j < nm; ++j)
		mesh.setNumMapFaces(j + 1, n, TRUE);

	for (int i = 0; i < n; ++i) 
	{
		const Point3& t = v[i];
		Face& f = mesh.faces[i];
		f.setVerts(t.x, t.y, t.z);
		f.Show();
		f.setEdgeVisFlags(EDGE_VIS, EDGE_VIS, EDGE_VIS);

		TVFace& tf = mesh.tvFace[i];
		tf.setTVerts(t.x, t.y, t.z);
		for (int j = 0; j < nm; ++j) 
		{
			if (TVFace* tvFace = mesh.mapFaces(j + 1))
				tvFace[i].setTVerts(t.x, t.y, t.z);
		}
	}
	
	mesh.InvalidateGeomCache();
	mesh.InvalidateTopologyCache();
}

void SetNormal(Mesh& mesh, const vector<Point3>& v)
{
	int n = v.size();
	mesh.SpecifyNormals();
	MeshNormalSpec* normalSpec = mesh.GetSpecifiedNormals();
	normalSpec->ClearNormals();
	normalSpec->SetNumNormals(n);
	for (int i = 0; i < n; i++)
	{
		normalSpec->Normal(i) = normals[i].Normalize();
		normalSpec->SetNormalExplicit(i, true);
	}

}

void setSkin(Mesh& mesh, granny_mesh* gmesh,INode* modelnode)
{
	Interface* ip = GetCOREInterface();
	if (gmesh->BoneBindingCount > 0)
	{
		Modifier* skin = (Modifier*)CreateInstance(SClass_ID(OSM_CLASS_ID), SKIN_CLASSID);
		ISkinImportData* skinInterface = (ISkinImportData*)skin->GetInterface(I_SKINIMPORTDATA);

		for (int b = 0; b < gmesh->BoneBindingCount; ++b)
		{
			granny_bone_binding* bb = &gmesh->BoneBindings[b];
			Object* pBone = (Object*)ip->CreateInstance(GEOMOBJECT_CLASS_ID, BONE_OBJ_CLASSID);
			INode* boneNode = ip->CreateObjectNode(pBone);
			boneNode->SetName(WStr::FromACP(bb->BoneName));
			skinInterface->AddBoneEx(boneNode,true);
			bones.push_back(boneNode);
		}
		
	}
}
void setMaterial(Mesh& mesh, granny_mesh* gmesh)
{

}
void setSkeleton(Mesh& mesh, granny_mesh* gmesh)
{
	/*if (grfile->.size() > 0)
	{
		for (int s = 0; s < grmod->get_skeleton().size(); ++s)
		{
			auto gskel = grmod->get_skeleton().at(s);
		}
	}*/
}
bool Importer::LoadMeshs(granny_mesh* gmesh)
{
	try
	{
	  triangles.clear();
	  normals.clear();
	  vertexx.clear();
	  trianglesInt.clear();
	  uv.clear();

	  fillvector(gmesh);
	  TriObject* tri = CreateNewTriObject();	  
	  Mesh& mesh = tri->GetMesh();
	  SetVertex(mesh, vertexx);	  
	  SetNormal(mesh, vertexx);
      SetTriangles(mesh, triangles);
	  SetMaps(mesh, vertexx);

	  impnodee->Reference(tri);
	  INode* n = impnodee->GetINode();
	 /* string name = "";
	  n->SetName(name.c_str());*/
	  n->SetObjectRef(tri);
	  //i->AddNodeToScene(impnodee);

	 // Object* obk = tri;	 
	  //INode* rootnode=ip->CreateObjectNode(obk);
	  //setSkin(mesh, gmesh, rootnode);//test
	  i=new ImpInterface();
	  ip->RedrawViews(0, 0, 0);
	  return true;
	  }
	catch (exception* ex)
	{
		QMessageBox msgBox;
		msgBox.setText(ex->what());
		msgBox.exec();
		return false;
	}
	
}

void Importer::fillvector(granny_mesh* gmesh)
{
	int nVertices_ = GrannyGetMeshVertexCount(gmesh);
	uint8_t* vertices_=(uint8_t*)GrannyGetMeshVertices(gmesh);
	int nIndices_= GrannyGetMeshIndexCount(gmesh);
	uint8_t* indices_ = (uint8_t*)GrannyGetMeshIndices(gmesh);

	auto* vertex_data = gmesh->PrimaryVertexData;
	auto nTri_ = GrannyGetMeshTriangleGroupCount(gmesh);
	auto tri_ = GrannyGetMeshTriangleGroups(gmesh);

	const char* mmname = "";

	//vertex
	granny_pwnt3432_vertex* vertices;
	vertices = new granny_pwnt3432_vertex[vertex_data->VertexCount];
	(*GrannyCopyMeshVertices)(gmesh, GrannyPWNT3432VertexType, vertices);
	for (int v = 0; v < vertex_data->VertexCount; ++v)
	{
		granny_pwnt3432_vertex& vertex = vertices[v];
		Point3* vert = new Point3(vertex.Position[0], vertex.Position[1], vertex.Position[2]);
		Point3* vertn = new Point3(vertex.Normal[0], vertex.Normal[1], vertex.Normal[2]);
		Point2* vertuv = new Point2(vertex.UV[0], vertex.UV[1]);
		vertexx.push_back(*vert);
		normals.push_back(*vertn);
		uv.push_back(*vertuv);
	}
	
	//triangles
	if (gmesh->PrimaryTopology->Index16Count)
	{
		uint16_t* indices = (uint16_t*)indices_;
		for (int iGroup = 0; iGroup < nTri_; ++iGroup)
		{
			for (int iTriangle = 0; iTriangle < tri_[iGroup].TriCount; ++iTriangle)
			{
				mmname = gmesh->MaterialBindings[tri_[iGroup].MaterialIndex].Material->Name;
				granny_uint32 index0 = (tri_[iGroup].TriFirst + iTriangle) * 3;

				granny_uint32 index1 = indices[index0 + 0] ;//add +1 if exporting to obj
				granny_uint32 index2 = indices[index0 + 1] ;//add +1 if exporting to obj
				granny_uint32 index3 = indices[index0 + 2] ;//add +1 if exporting to obj

				int a = (granny_uint32)index1;
				int b = (granny_uint32)index2;
				int c = (granny_uint32)index3;
				Point3* triiis = new Point3(a, b, c);
				triangles.push_back(*triiis);
				trianglesInt.push_back(index1);
				trianglesInt.push_back(index2);
				trianglesInt.push_back(index3);
				
			}
		}

	}

	
}


void Importer::setOptions()
{
	if(this->meshCheckBox->isChecked())
	{
		for(int i=0 ;i < grmod->get_mesh().size();i++)
		{
			LoadMeshs(grmod->get_mesh().at(i));
			
		}
		
		mprintf(L"File Loaded");
	}
}

Importer::~Importer()
{
  
}
