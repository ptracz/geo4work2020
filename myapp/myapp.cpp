#include "myapp.h"
#include <iostream>

#include <ogr\ogrsf_frmts\ogrsf_frmts.h>
#include <gdal.h>

using namespace std;

int main()
{
	cout << "my first app" << endl;
	
	CreatePolygonWithHoleLayer();
	//CreatePolygonLayer();
	//ReadPolygonLayer();
	//CreateMultiPointLayer();
	//CreateLineLayer();
	//ReadLineLayer();
	//CreatePointLayer();
	//ReadMultiPointLayer();
	//ReadPointLayer();
	//SimleGDALCompilerChecker();

	system("pause");
	return 0;
}

void CreatePolygonLayer()
{
	GDALAllRegister();
	const char *pszDriverName = "ESRI Shapefile";
	GDALDriver *poDriver;

	poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);
	if (poDriver == NULL)
	{
		printf("%s driver not available.\n", pszDriverName);
		return;
	}

	GDALDataset *poDS;
	poDS = poDriver->Create("my_polygon.shp", 0, 0, 0, GDT_Unknown, NULL);
	if (poDS == NULL)
	{
		printf("Creation of output file failed.\n");
		return;
	}

	OGRLayer *poLayer;
	poLayer = poDS->CreateLayer("my_polygon", NULL, wkbPolygon, NULL);
	if (poLayer == NULL)
	{
		printf("Layer creation failed.\n");
		return;
	}


	OGRFieldDefn oFieldString("Name", OFTString);
	oFieldString.SetWidth(32);
	if (poLayer->CreateField(&oFieldString) != OGRERR_NONE)
	{
		printf("Creating Name field failed.\n");
		return;
	}

	OGRFieldDefn oFieldNumber("Area", OFTReal);
	oFieldNumber.SetWidth(7);
	oFieldNumber.SetPrecision(4);
	if (poLayer->CreateField(&oFieldNumber) != OGRERR_NONE)
	{
		printf("Creating Length field failed.\n");
		return;
	}

	OGRFeature *poFeature;
	poFeature =
		OGRFeature::CreateFeature(poLayer->GetLayerDefn());

	poFeature->SetField("Name", "Lake");
	poFeature->SetField("Area", 20.25);

	OGRPolygon poligon;

	OGRLinearRing ring;

	OGRPoint pt1;
	pt1.setX(10);
	pt1.setY(10);

	ring.addPoint(&pt1);
	ring.addPoint(10, 0);
	ring.addPoint(0, 0);
	ring.addPoint(0, 10);
	ring.addPoint(10, 10);

	poligon.addRing(&ring);

	poFeature->SetGeometry(&poligon);

	if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
	{
		printf("Failed to create feature in shapefile.\n");
		return;
	}

	OGRFeature::DestroyFeature(poFeature);


	GDALClose(poDS);
}

void CreatePolygonWithHoleLayer()
{
	GDALAllRegister();
	const char *pszDriverName = "ESRI Shapefile";
	GDALDriver *poDriver;

	poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);
	if (poDriver == NULL)
	{
		printf("%s driver not available.\n", pszDriverName);
		return;
	}

	GDALDataset *poDS;
	poDS = poDriver->Create("my_polygon_hole.shp", 0, 0, 0, GDT_Unknown, NULL);
	if (poDS == NULL)
	{
		printf("Creation of output file failed.\n");
		return;
	}

	OGRLayer *poLayer;
	poLayer = poDS->CreateLayer("my_polygon_hole", NULL, wkbPolygon, NULL);
	if (poLayer == NULL)
	{
		printf("Layer creation failed.\n");
		return;
	}


	OGRFieldDefn oFieldString("Name", OFTString);
	oFieldString.SetWidth(32);
	if (poLayer->CreateField(&oFieldString) != OGRERR_NONE)
	{
		printf("Creating Name field failed.\n");
		return;
	}

	OGRFieldDefn oFieldNumber("Area", OFTReal);
	oFieldNumber.SetWidth(7);
	oFieldNumber.SetPrecision(4);
	if (poLayer->CreateField(&oFieldNumber) != OGRERR_NONE)
	{
		printf("Creating Length field failed.\n");
		return;
	}

	OGRFeature *poFeature;
	poFeature =
		OGRFeature::CreateFeature(poLayer->GetLayerDefn());

	poFeature->SetField("Name", "Lake");
	poFeature->SetField("Area", 20.25);

	OGRPolygon poligon;
	OGRLinearRing ring;

	ring.addPoint(20, 20);
	ring.addPoint(20, -20);
	ring.addPoint(-20, -20);
	ring.addPoint(-20, 20);
	ring.addPoint(20, 20);

	poligon.addRing(&ring);

	ring.empty();
	ring.addPoint(10, 10);
	ring.addPoint(10, 0);
	ring.addPoint(0, 0);
	ring.addPoint(0, 10);
	ring.addPoint(10, 10);
	ring.reversePoints();

	poligon.addRing(&ring);

	poFeature->SetGeometry(&poligon);

	if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
	{
		printf("Failed to create feature in shapefile.\n");
		return;
	}

	OGRFeature::DestroyFeature(poFeature);


	GDALClose(poDS);
}

void CreateLineLayer()
{
	GDALAllRegister();
	const char *pszDriverName = "ESRI Shapefile";
	GDALDriver *poDriver;

	poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);
	if (poDriver == NULL)
	{
		printf("%s driver not available.\n", pszDriverName);
		return;
	}

	GDALDataset *poDS;
	poDS = poDriver->Create("my_line.shp", 0, 0, 0, GDT_Unknown, NULL);
	if (poDS == NULL)
	{
		printf("Creation of output file failed.\n");
		return;
	}

	OGRLayer *poLayer;
	poLayer = poDS->CreateLayer("my_line", NULL, wkbLineString, NULL);
	if (poLayer == NULL)
	{
		printf("Layer creation failed.\n");
		return;
	}


	OGRFieldDefn oFieldString("Name", OFTString);
	oFieldString.SetWidth(32);
	if (poLayer->CreateField(&oFieldString) != OGRERR_NONE)
	{
		printf("Creating Name field failed.\n");
		return;
	}

	OGRFieldDefn oFieldNumber("Length", OFTReal);
	oFieldNumber.SetWidth(7);
	oFieldNumber.SetPrecision(4);
	if (poLayer->CreateField(&oFieldNumber) != OGRERR_NONE)
	{
		printf("Creating Length field failed.\n");
		return;
	}

	OGRFeature *poFeature;
	poFeature =
		OGRFeature::CreateFeature(poLayer->GetLayerDefn());

	poFeature->SetField("Name", "Road");
	poFeature->SetField("Length", 20.25);

	OGRLineString line;

	OGRPoint pt;
	pt.setX(10);
	pt.setY(20);

	line.addPoint(&pt);

	line.addPoint(20, 10);

	poFeature->SetGeometry(&line);

	if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
	{
		printf("Failed to create feature in shapefile.\n");
		return;
	}

	OGRFeature::DestroyFeature(poFeature);


	GDALClose(poDS);
}

void CreateMultiPointLayer()
{
	GDALAllRegister();
	const char *pszDriverName = "ESRI Shapefile";
	GDALDriver *poDriver;

	poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);
	if (poDriver == NULL)
	{
		printf("%s driver not available.\n", pszDriverName);
		return;
	}

	GDALDataset *poDS;
	poDS = poDriver->Create("my_multipoint.shp", 0, 0, 0, GDT_Unknown, NULL);
	if (poDS == NULL)
	{
		printf("Creation of output file failed.\n");
		return;
	}

	OGRLayer *poLayer;
	poLayer = poDS->CreateLayer("my_multipoint", NULL, wkbMultiPoint, NULL);
	if (poLayer == NULL)
	{
		printf("Layer creation failed.\n");
		return;
	}


	OGRFieldDefn oFieldString("Name", OFTString);
	oFieldString.SetWidth(32);
	if (poLayer->CreateField(&oFieldString) != OGRERR_NONE)
	{
		printf("Creating Name field failed.\n");
		return;
	}

	OGRFieldDefn oFieldNumber("Height", OFTReal);
	oFieldNumber.SetWidth(7);
	oFieldNumber.SetPrecision(4);
	if (poLayer->CreateField(&oFieldNumber) != OGRERR_NONE)
	{
		printf("Creating Height field failed.\n");
		return;
	}

	OGRFeature *poFeature;
	poFeature =
		OGRFeature::CreateFeature(poLayer->GetLayerDefn());

	poFeature->SetField("Name", "MultiLamp");
	poFeature->SetField("Height", 20.25);

	OGRMultiPoint multipoint;

	OGRPoint pt;
	pt.setX(10);
	pt.setY(20);

	multipoint.addGeometry (&pt);

	pt.setX(40);
	pt.setY(50);

	multipoint.addGeometry(&pt);

	poFeature->SetGeometry(&multipoint);

	if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
	{
		printf("Failed to create feature in shapefile.\n");
		return;
	}

	OGRFeature::DestroyFeature(poFeature);


	GDALClose(poDS);
}
void CreatePointLayer()
{
	GDALAllRegister();
	const char *pszDriverName = "ESRI Shapefile";
	GDALDriver *poDriver;

	poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);
	if (poDriver == NULL)
	{
		printf("%s driver not available.\n", pszDriverName);
		return;
	}

	GDALDataset *poDS;
	poDS = poDriver->Create("my_point.shp", 0, 0, 0, GDT_Unknown, NULL);
	if (poDS == NULL)
	{
		printf("Creation of output file failed.\n");
		return;
	}

	OGRLayer *poLayer;
	poLayer = poDS->CreateLayer("my_point", NULL, wkbPoint, NULL);
	if (poLayer == NULL)
	{
		printf("Layer creation failed.\n");
		return;
	}


	OGRFieldDefn oFieldString("Name", OFTString);
	oFieldString.SetWidth(32);
	if (poLayer->CreateField(&oFieldString) != OGRERR_NONE)
	{
		printf("Creating Name field failed.\n");
		return;
	}

	OGRFieldDefn oFieldNumber("Height", OFTReal);
	oFieldNumber.SetWidth(7);
	oFieldNumber.SetPrecision(4);
	if (poLayer->CreateField(&oFieldNumber) != OGRERR_NONE)
	{
		printf("Creating Height field failed.\n");
		return;
	}

	OGRFeature *poFeature;
	poFeature =
		OGRFeature::CreateFeature(poLayer->GetLayerDefn());

	poFeature->SetField("Name", "Lamp");
	poFeature->SetField("Height", 20.25);

	OGRPoint pt(10, 20);
	poFeature->SetGeometry(&pt);

	if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
	{
		printf("Failed to create feature in shapefile.\n");
		return;
	}

	OGRFeature::DestroyFeature(poFeature);


	GDALClose(poDS);
}

void ReadLineLayer()
{
	OGRRegisterAll();

	GDALDataset *poDS = NULL;

	poDS = (GDALDataset*)GDALOpenEx("linie.shp",
		GDAL_OF_VECTOR,
		NULL,
		NULL,
		NULL);

	if (poDS == NULL)
	{
		//error
		return;
	}

	OGRLayer  *poLayer = NULL;
	poLayer = poDS->GetLayerByName("linie");
	if (poLayer == NULL)
	{
		// error
		return;
	}

	OGRFeature *poFeature;

	poLayer->ResetReading();

	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{

		OGRGeometry *poGeometry = NULL;

		poGeometry = poFeature->GetGeometryRef();

		if (poGeometry != NULL
			&& wkbFlatten(poGeometry->getGeometryType()) == wkbLineString)
		{
			OGRLineString *poLine = (OGRLineString *)poGeometry;
			for (int pointNumber = 0; pointNumber < poLine->getNumPoints(); pointNumber++)
			{				
				printf("x: %.3f y: %.3f\n", poLine->getX(pointNumber), poLine->getY(pointNumber));
			}
		}

		OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();

		for (int iField = 0; iField < poFDefn->GetFieldCount(); iField++)
		{
			OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn(iField);

			if (poFieldDefn->GetType() == OFTInteger)
				printf("%d,", poFeature->GetFieldAsInteger(iField));

			else if (poFieldDefn->GetType() == OFTReal)
				printf("%.3f,", poFeature->GetFieldAsDouble(iField));

			else if (poFieldDefn->GetType() == OFTString)
				printf("%s,", poFeature->GetFieldAsString(iField));

			else
				printf("%s,", poFeature->GetFieldAsString(iField));
		}
		printf("\n\r\n\r");

		OGRFeature::DestroyFeature(poFeature);
	}


	GDALClose(poDS);

}

void ReadPolygonLayer()
{
	OGRRegisterAll();

	GDALDataset *poDS = NULL;

	poDS = (GDALDataset*)GDALOpenEx("poligon.shp",
		GDAL_OF_VECTOR,
		NULL,
		NULL,
		NULL);

	if (poDS == NULL)
	{
		//error
		return;
	}

	OGRLayer  *poLayer = NULL;
	poLayer = poDS->GetLayerByName("poligon");
	if (poLayer == NULL)
	{
		// error
		return;
	}

	OGRFeature *poFeature;

	poLayer->ResetReading();

	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{

		OGRGeometry *poGeometry = NULL;

		poGeometry = poFeature->GetGeometryRef();

		if (poGeometry != NULL
			&& wkbFlatten(poGeometry->getGeometryType()) == wkbPolygon)
		{
			OGRPolygon* polygon = (OGRPolygon *)poGeometry;
			OGRLinearRing* ring = polygon->getExteriorRing();
			if (ring == NULL) return;
			for (int pointNo = 0; pointNo < ring->getNumPoints(); pointNo++)
			{
				printf("exterior x: %.3f y: %.3f\n", ring->getX(pointNo), ring->getY(pointNo));
			}
			for (int ringInteriorNumber = 0; ringInteriorNumber < polygon->getNumInteriorRings(); ringInteriorNumber++)
			{
				OGRLinearRing* ringInterior = polygon->getInteriorRing(ringInteriorNumber);
				if (ringInterior == NULL) continue;
				for (int pointNo = 0; pointNo < ringInterior->getNumPoints(); pointNo++)
				{
					printf("interior x: %.3f y: %.3f\n", ringInterior->getX(pointNo), ringInterior->getY(pointNo));
				}
			}
		}
		else
		{
			printf("no polygon geometry\n");
		}

		OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();

		for (int iField = 0; iField < poFDefn->GetFieldCount(); iField++)
		{
			OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn(iField);

			if (poFieldDefn->GetType() == OFTInteger)
				printf("%d,", poFeature->GetFieldAsInteger(iField));

			else if (poFieldDefn->GetType() == OFTReal)
				printf("%.3f,", poFeature->GetFieldAsDouble(iField));

			else if (poFieldDefn->GetType() == OFTString)
				printf("%s,", poFeature->GetFieldAsString(iField));

			else
				printf("%s,", poFeature->GetFieldAsString(iField));
		}
		printf("\n\r\n\r");

		OGRFeature::DestroyFeature(poFeature);
	}


	GDALClose(poDS);

}

void ReadMultiPointLayer()
{
	OGRRegisterAll();

	GDALDataset *poDS = NULL;

	poDS = (GDALDataset*)GDALOpenEx("multipoint.shp",
		GDAL_OF_VECTOR,
		NULL,
		NULL,
		NULL);

	if (poDS == NULL)
	{
		//error
		return;
	}

	OGRLayer  *poLayer = NULL;
	poLayer = poDS->GetLayerByName("multipoint");
	if (poLayer == NULL)
	{
		// error
		return;
	}

	OGRFeature *poFeature;

	poLayer->ResetReading();

	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{

		OGRGeometry *poGeometry = NULL;

		poGeometry = poFeature->GetGeometryRef();

		if (poGeometry != NULL
			&& wkbFlatten(poGeometry->getGeometryType()) == wkbMultiPoint)
		{
			OGRMultiPoint *poMultiPoint = (OGRMultiPoint *)poGeometry;
			for (int pointNumber = 0; pointNumber < poMultiPoint->getNumGeometries(); pointNumber++)
			{
				OGRPoint* point = (OGRPoint*)poMultiPoint->getGeometryRef(pointNumber);
				printf("x: %.3f y: %.3f\n", point->getX(), point->getY());
			}
		}

		OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();

		for (int iField = 0; iField < poFDefn->GetFieldCount(); iField++)
		{
			OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn(iField);

			if (poFieldDefn->GetType() == OFTInteger)
				printf("%d,", poFeature->GetFieldAsInteger(iField));

			else if (poFieldDefn->GetType() == OFTReal)
				printf("%.3f,", poFeature->GetFieldAsDouble(iField));

			else if (poFieldDefn->GetType() == OFTString)
				printf("%s,", poFeature->GetFieldAsString(iField));

			else
				printf("%s,", poFeature->GetFieldAsString(iField));
		}
		printf("\n\r\n\r");

		OGRFeature::DestroyFeature(poFeature);
	}


	GDALClose(poDS);

}

void ReadPointLayer()
{
	OGRRegisterAll();

	GDALDataset *poDS = NULL;

	poDS = (GDALDataset*)GDALOpenEx("point.shp",
		GDAL_OF_VECTOR,
		NULL,
		NULL,
		NULL);

	if (poDS == NULL)
	{
		//error
		return;
	}

	OGRLayer  *poLayer = NULL;
	poLayer = poDS->GetLayerByName("point");
	if (poLayer == NULL)
	{
		// error
		return;
	}

	OGRFeature *poFeature;

	poLayer->ResetReading();

	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{

		OGRGeometry *poGeometry = NULL;

		poGeometry = poFeature->GetGeometryRef();

		if (poGeometry != NULL
			&& wkbFlatten(poGeometry->getGeometryType()) == wkbPoint)
		{
			OGRPoint *poPoint = (OGRPoint *)poGeometry;
			printf("x: %.3f y: %.3f\n", poPoint->getX(), poPoint->getY());
		}
		else
		{
			printf("no point geometry\n");
		}
		
		OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();

		for (int iField = 0; iField < poFDefn->GetFieldCount(); iField++)
		{
			OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn(iField);

			if (poFieldDefn->GetType() == OFTInteger)
				printf("%d,", poFeature->GetFieldAsInteger(iField));

			else if (poFieldDefn->GetType() == OFTReal)
				printf("%.3f,", poFeature->GetFieldAsDouble(iField));

			else if (poFieldDefn->GetType() == OFTString)
				printf("%s,", poFeature->GetFieldAsString(iField));

			else
				printf("%s,", poFeature->GetFieldAsString(iField));
		}
		printf("\n\r\n\r");

		OGRFeature::DestroyFeature(poFeature);
	}


	GDALClose(poDS);

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