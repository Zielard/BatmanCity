#include "Model.h"

Model::Model()
{
    indexf = 0;
	numberv = 0;
	numbert = 0;
	numberf = 0;
	numbern = 0;
	flag_load = true;
	flag_uv = true;
    flag = true;
}

Model::~Model()
{


}
void Model::Render_MOD_TEX()
{

     int index=0;
     int indext=0;
     int indextt=0;
     for(int i=1;i<numberf+3;i++)
     {
        indextt=Nindex[i][1];
        indext=UVindex[i][1];
        index=VFindex[i][1];
                glNormal3f(normal[indextt][1],normal[indextt][2],normal[indextt][3]);
        glTexCoord2f (uv[indext][1], uv[indext][2]);
        glVertex3f(vertex[index][1],vertex[index][2],vertex[index][3]);
        //std::cout<<" UV 1: "<<uv[indext][1]<<" UV 2: "<<uv[indext][1]<<std::endl;
        //std::cout<<" F 1: "<<vertex[index][1]<<" F 2: "<<vertex[index][2]<<" F 3: "<<vertex[index][3]<<" in :"<<indext<<std::endl;
        indextt=Nindex[i][2];
        indext=UVindex[i][2];
        index=VFindex[i][2];
                glNormal3f(normal[indextt][1],normal[indextt][2],normal[indextt][3]);
        glTexCoord2f (uv[indext][1], uv[indext][2]);
        glVertex3f(vertex[index][1],vertex[index][2],vertex[index][3]);
        //std::cout<<" UV 1: "<<uv[indext][1]<<" UV 2: "<<uv[indext][1]<<std::endl;
        //std::cout<<" F 1: "<<vertex[index][1]<<" F 2: "<<vertex[index][2]<<" F 3: "<<vertex[index][3]<<" in :"<<indext<<std::endl;
        indextt=Nindex[i][3];
        indext=UVindex[i][3];
        index=VFindex[i][3];
                glNormal3f(normal[indextt][1],normal[indextt][2],normal[indextt][3]);
        glTexCoord2f (uv[indext][1], uv[indext][2]);
        glVertex3f(vertex[index][1],vertex[index][2],vertex[index][3]);
        //std::cout<<" UV 1: "<<uv[indext][1]<<" UV 2: "<<uv[indext][1]<<std::endl;
        //std::cout<<" F 1: "<<vertex[index][1]<<" F 2: "<<vertex[index][2]<<" F 3: "<<vertex[index][3]<<" in :"<<indext<<std::endl;
    //system("pause");
     }
}
void Model::LoadObj(std::string name)
{

	std::ifstream in(name.c_str());
	std::string buffer;
	std::string tmp;
	float v1;
	float v2;
	float v3;
	float t1;
	float t2;
	float t3;
    float n1;
	float n2;
	float n3;
	int push=0;
	int f1;
	int f2;
	int f3;
	int f4;
            int indexF=0;
			int indexU=0;
			int indexM=0;
	std::string pomoc;
	std::string strin[4];
	std::string tbl[3];
	std::string tbll[4];
	std::string tblll[2];

	while (1)
	{

		std::getline(in, buffer);
		std::istringstream line(buffer);
		std::string ch = buffer.substr(0, 2);
		std::string ch_UV = buffer.substr(0, 3);
		if (ch == "v ")
		{
			numberv++;
			line >> tmp >> tbl[0] >> tbl[1] >> tbl[2];
			v1 = (float)atof(tbl[0].c_str());
			v2 = (float)atof(tbl[1].c_str());
			v3 = (float)atof(tbl[2].c_str());
			//std::cout << "wierzcholki v1:" << v1 <<  "v2:"  << v2 << "v3:" << v3 << std::endl;
			vertex[numberv][1] = v1;
			vertex[numberv][2] = v2;
			vertex[numberv][3] = v3;
			//glVertex3f(v1,v2,v3);
		}
		else if (ch_UV == "vt ")
		{
			numbert++;
			line >> tmp >> tblll[0] >> tblll[1];
			t1 = (float)atof(tblll[0].c_str());
			t2 = (float)atof(tblll[1].c_str());
			//std::cout << "wierzcholki f1:" << t1 << "t2:" << t2 << "v3:" << std::endl;
			uv[numbert][1] = t1;
			uv[numbert][2] = t2;
			//std::cout<<uv[numbert][1]<<" "<<uv[numbert][2]<<" 1 "<<std::endl;


		}
        else if (ch_UV == "vn ")
		{
			numbern++;
			line >> tmp >> tbl[0] >> tbl[1] >> tbl[2];
			n1 = (float)atof(tbl[0].c_str());
			n2 = (float)atof(tbl[1].c_str());
			n3 = (float)atof(tbl[2].c_str());
			//std::cout << "wierzcholki v1:" << v1 <<  "v2:"  << v2 << "v3:" << v3 << std::endl;
			normal[numbern][1] = n1;
			normal[numbern][2] = n2;
			normal[numbern][3] = n3;
			//glVertex3f(v1,v2,v3);
		}
		else if (ch == "f ")
		{
			numberf++;
			line >>strin[1];
			line >>strin[2];
			line >>strin[3];
			line >>strin[4];
			for(int i=1;i<5;i++)
            {
             strin[i] += '/'  ;
            }
			f[numberf][1] = strin[2];
			f[numberf][2] = strin[3];
			f[numberf][3] = strin[4];


            for(int i=1;i<4;i++)
                {
            push=0;

                    pomoc.clear();

                    for(int j=0;j<f[numberf][i].length();j++)
                    {
                            if(f[numberf][i][j] != '/')
                            {
                            pomoc +=f[numberf][i][j];
                            }
                            else if(f[numberf][i][j] == '/')
                            {
                                push++;
                                if(push == 1)
                                {
                                indexF++;
                                VFindex[numberf][indexF] = (int)atof(pomoc.c_str());
                            //  std::cout<<VFindex[numberf][indexF]<<" zmienna face"<<std::endl;
                                           if(indexF == 3)
                                           {
                                            indexF=0;
                                           }
                                }
                                else if(push == 2)
                                {
                                    indexU++;
                                    UVindex[numberf][indexU] = (int)atof(pomoc.c_str());
                               // std::cout<<UVindex[numberf][indexU]<<" zmienna UV"<<std::endl;
                                            if(indexU == 3)
                                           {
                                            indexU=0;
                                           }
                                }
                                else if(push == 3)
                                {
                                    indexM++;
                                    Nindex[numberf][indexM] = (int)atof(pomoc.c_str());
                             // std::cout<<Nindex[numberf][indexM]<<" zmienna orm"<<std::endl;
                                        if(indexM == 3)
                                           {
                                            indexM=0;
                                           }
                                }
                            pomoc.clear();
                            }
                    }
                }

			//std::cout << "wierzcholki f1 :("<< f[numberf][1] << "v2 :(" << f[numberf][2] << "v3 :(" << f[numberf][3]<<std::endl;


		}

		else if (in.eof())
		{
//system("pause");
			//std::cout<<"tex:" << numbert<<" index F" <<numberf <<" index V" <<numberv << std::endl;
			break;
		}


	}
}




