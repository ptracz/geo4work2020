#include "myapp.h"
#include <iostream>

#include <ogr\ogrsf_frmts\ogrsf_frmts.h>
#include <gdal.h>

using namespace std;

int main()
{
	cout << "my frist app" << endl;
	
	SimleGDALCompilerChecker();

	system("pause");
	return 0;
}

// this function is checking if project is configured properly to use GDAL
void SimleGDALCompilerChecker()
{
	GDALDriver *pDriver = nullptr;

	OGRRegisterAll();

	pDriver = GetGDALDriverManager()->GetDriverByName("ESRI Shapefile");

	if(pDriver == nullptr)
	{
		cout << endl << "There is something wrong with project configuration for GDAL" << endl;
	}
	else cout << endl  << "Project is properly configured for GDAL. You rock!" << endl;
}