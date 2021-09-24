#include "GrannyMod.h"
#include <QtWidgets/qmessagebox.h>

GrannyMod::GrannyMod()
{
	
}

granny_file_info* GrannyMod::loadFile(string* filename)
{
	QMessageBox msgBox;
    grannyfile = new granny_file();
    grannyfile = GrannyReadEntireFile(filename->c_str());
    if (grannyfile == 0)
    {
        msgBox.setText("Error: unable to load % s as a Granny file " + QString::fromStdString(filename->c_str()));
        msgBox.exec();
    }
    else
    {
        granny_file_info* GrannyFileInfo = GrannyGetFileInfo(grannyfile);
    	if(GrannyFileInfo->MeshCount > 0)
    	{
    		for(granny_int32x a=0 ;a < GrannyFileInfo->MeshCount;a++)
	         {
              meshes.push_back(GrannyFileInfo->Meshes[a]);
	         }
    	}
      if (GrannyFileInfo->ModelCount > 0)
        {
            for (granny_int32x b = 0; b < GrannyFileInfo->ModelCount; b++)
            {
                models.push_back(GrannyFileInfo->Models[b]);
                trans.push_back(&GrannyFileInfo->Models[b]->InitialPlacement);
            }
        }
         if (GrannyFileInfo->AnimationCount > 0)
        {
            for (granny_int32x c = 0; c < GrannyFileInfo->AnimationCount; c++)
            {
                animations.push_back(GrannyFileInfo->Animations[c]);
            }
        }
        if (GrannyFileInfo->MaterialCount > 0)
        {
            for (granny_int32x d = 0; d < GrannyFileInfo->MaterialCount; d++)
            {
                materials.push_back(GrannyFileInfo->Materials[d]);
            }
        }
        if (GrannyFileInfo->SkeletonCount > 0)
       {
            for (granny_int32x e = 0; e < GrannyFileInfo->SkeletonCount; e++)
            {
                skeletons.push_back(GrannyFileInfo->Skeletons[e]);
            }
         }
        if (GrannyFileInfo->VertexDataCount > 0)
        {
            for (granny_int32x f = 0; f < GrannyFileInfo->VertexDataCount; f++)
            {
                vertex.push_back(GrannyFileInfo->VertexDatas[f]);
            }
        }
        if (GrannyFileInfo->TriTopologyCount > 0)
        {
            for (granny_int32x g = 0; g < GrannyFileInfo->TriTopologyCount; g++)
            {
                triangles.push_back(GrannyFileInfo->TriTopologies[g]);
            }
        }
        return GrannyFileInfo;
        msgBox.setText("Loaded Granny file succesfully " + QString::fromStdString(filename->c_str()));
        msgBox.exec();
    }
    return nullptr;
}

void GrannyMod::createScene(ImpInterface* i, Interface* gi)
{
    ImpNode* node = i->CreateNode();
}

GrannyMod::~GrannyMod()
{
}
