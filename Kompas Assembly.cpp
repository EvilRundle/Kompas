#include "pch.h"
#include "framework.h"
#include "ЛР6_ППИ_сборка.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef __LIBTOOL_H
#include "libtool.h"
#endif

#ifndef __LHEAD3D_H
#include <LHead3d.h>
#endif

#import "ksConstants3D.tlb" no_namespace named_guids
#import "ksConstants.tlb" no_namespace named_guids
#import "kAPI2D5COM.tlb"  no_namespace named_guids
#import "kAPI3D5COM.tlb"  no_namespace named_guids 
#import "kAPI7.tlb"       no_namespace named_guids

int kp;

TAN tcUp[4];
TAN tcDown[4];

double xPointUp[2];
double yPointUp[2];
double xPointDown[2];
double yPointDown[2];


void CreateRectangle(double x, double y, double height, double width)
{
	RectangleParam par;
	::memset(&par, 0, sizeof(RectangleParam));
	par.x = x;
	par.y = y;
	par.ang = 0.00;
	par.height = height;
	par.width = width;
	par.pCorner = ::CreateArray(CORNER_ARR, 0);
	par.style = 1;
	::ksRectangle(&par, 0);
}

void CreateObject(ISketchDefinitionPtr sketchDefinition, int keyObj)
{
	switch (keyObj)
	{
	/*Корпус*/ {
	case 0:
		TanCircleCircle(0, 50, 10, 0, 0, 38, tcUp);
		LineSeg(tcUp[1].x1, tcUp[1].y1, tcUp[1].x2, tcUp[1].y2, 1);
		LineSeg(-tcUp[1].x1, tcUp[1].y1, -tcUp[1].x2, tcUp[1].y2, 1);
		ArcByPoint(0, 50, 10, tcUp[1].x1, tcUp[1].y1, -tcUp[1].x1, tcUp[1].y1, -1, 1);
		IntersectCirLin(0, 0, 38, tcUp[1].x1, tcUp[1].y1, 235.944202, &kp, xPointUp, yPointUp);
		TanCircleCircle(0, -50, 10, 0, 0, 38, tcDown);
		LineSeg(tcDown[1].x1, tcDown[1].y1, tcDown[1].x2, tcDown[1].y2, 1);
		LineSeg(-tcDown[1].x1, tcDown[1].y1, -tcDown[1].x2, tcDown[1].y2, 1);
		ArcByPoint(0, -50, 10, tcDown[1].x1, tcDown[1].y1, -tcDown[1].x1, tcDown[1].y1, -1, 1);
		IntersectCirLin(0, 0, 38, tcDown[1].x1, tcDown[1].y1, 235.944202, &kp, xPointDown, yPointDown);
		ArcByPoint(0, 0, 38, xPointUp[0], yPointUp[0], xPointUp[0], -yPointUp[0], 1, 1);
		ArcByPoint(0, 0, 38, xPointDown[0], yPointDown[0], xPointDown[0], -yPointDown[0], 1, 1);
		sketchDefinition->EndEdit();
		break;
	case 1:
		Circle(0, 50, 5.5, 1);
		Circle(0, -50, 5.5, 1);
		sketchDefinition->EndEdit();
		break;
	case 2:
		Circle(0, 0, 38, 1);
		sketchDefinition->EndEdit();
		break;
	case 3:
		CreateRectangle(10, 0, 15, -49);
		LineSeg(15, 0, -54, 0, 3);
		sketchDefinition->EndEdit();
		break;
	case 4:
		Circle(0, 25, 5.5, 1);
		Circle(0, -25, 5.5, 1);
		sketchDefinition->EndEdit();
		break;
		}
	/*Крышка*/ {
	case 5:
		Circle(0, 0, 38, 1);
		sketchDefinition->EndEdit();
		break;
	case 6:
		Circle(0, 25, 5.5, 1);
		Circle(0, -25, 5.5, 1);
		sketchDefinition->EndEdit();
		break;
	}
	/*Трубка*/ {
	case 7:
		CreateRectangle(10, 11, 4, -80);
		LineSeg(15, 0, -54, 0, 3);
		sketchDefinition->EndEdit();
		break;
	}
	}
}

IDocument3DPtr CreateFile()
{
	IDocument3DPtr pDocument3d(ksGet3dDocument(), false);
	pDocument3d->Create(FALSE, TRUE);
	return (pDocument3d);
}

void SaveFile()
{
	IDocument3DPtr pDocument3d(ksGetActive3dDocument(), false);
	TCHAR fileName[255];
	char buf[255];
	if (ksSaveFile("*.m3d", "ЛР6_ППИ.m3d", 0, buf, 255, 1))
	{
		wsprintf(fileName, L"%hs", buf);
		pDocument3d->SaveAs(fileName);
	}
}

void CreateO3dPlane(IPartPtr part, IPlaneOffsetDefinitionPtr planeOffsetDefinition, int keyO3dPlane)
{
	switch (keyO3dPlane)
	{
	case 0:
	{
		IEntityPtr basePlane(part->GetDefaultEntity(o3d_planeXOY), false);
		planeOffsetDefinition->SetPlane(basePlane);
		break;
	}
	case 1:
	{
		IEntityPtr basePlane(part->GetDefaultEntity(o3d_planeXOZ), false);
		planeOffsetDefinition->SetPlane(basePlane);
		break;
	}
	case 2:
	{
		IEntityPtr basePlane(part->GetDefaultEntity(o3d_planeYOZ), false);
		planeOffsetDefinition->SetPlane(basePlane);
		break;
	}
	}
}

void CreateSketch(IPartPtr part, ISketchDefinitionPtr sketchDefinition, IEntityPtr entitySketch, int keyBPlane)
{
	switch (keyBPlane)
	{
	case 0:
	{
		IEntityPtr basePlane(part->GetDefaultEntity(o3d_planeXOY), false);
		// Установка параметров эскиза
		sketchDefinition->SetPlane(basePlane); // Установим плоскость XOY базовой для эскиза
		// Создадим эскиз
		entitySketch->Create();
		break;
	}
	case 1:
	{
		IEntityPtr basePlane(part->GetDefaultEntity(o3d_planeXOZ), false);
		// Установка параметров эскиза
		sketchDefinition->SetPlane(basePlane); // Установим плоскость XOZ базовой для эскиза
		// Создадим эскиз
		entitySketch->Create();
		break;
	}
	case 2:
		IEntityPtr basePlane(part->GetDefaultEntity(o3d_planeYOZ), false);
		// Установка параметров эскиза
		sketchDefinition->SetPlane(basePlane); // Установим плоскость YOZ базовой для эскиза
		// Создадим эскиз
		entitySketch->Create();
		break;
	}
}

void CreateExtr(IPartPtr part, IEntityPtr entitySketch, int keyExtr, int keyDir, double depth)
{
	switch (keyExtr)
	{
	case 0:
	{
		IEntityPtr entityExtrusion(part->NewEntity(o3d_baseExtrusion), false);
		if (entityExtrusion)
		{
			IBaseExtrusionDefinitionPtr extrusionDefinition(IUnknownPtr(entityExtrusion->GetDefinition(), false));
			if (extrusionDefinition)
			{
				switch (keyDir)
				{
				case 0:
					extrusionDefinition->SetDirectionType(dtNormal);
					extrusionDefinition->SetSideParam(true, etBlind, depth, 0, false);
					extrusionDefinition->SetSketch(entitySketch);
					entityExtrusion->Create();
					break;
				case 1:
					extrusionDefinition->SetDirectionType(dtMiddlePlane);
					extrusionDefinition->SetSideParam(true, etBlind, depth, 0, false);
					extrusionDefinition->SetSketch(entitySketch);
					entityExtrusion->Create();
					break;
				case 2:
					extrusionDefinition->SetDirectionType(dtReverse);
					extrusionDefinition->SetSideParam(true, etBlind, depth, 0, false);
					extrusionDefinition->SetSketch(entitySketch);
					entityExtrusion->Create();
					break;
				}
			}
		}
		break;
	}
	case 1:
	{
		IEntityPtr entityExtrusion(part->NewEntity(o3d_cutExtrusion), false);
		if (entityExtrusion)
		{
			IBaseExtrusionDefinitionPtr extrusionDefinition(IUnknownPtr(entityExtrusion->GetDefinition(), false));
			if (extrusionDefinition)
			{
				switch (keyDir)
				{
				case 0:
					extrusionDefinition->SetDirectionType(dtNormal);
					extrusionDefinition->SetSideParam(true, etBlind, depth, 0, false);
					extrusionDefinition->SetSketch(entitySketch);
					entityExtrusion->Create();
					break;
				case 1:
					extrusionDefinition->SetDirectionType(dtMiddlePlane);
					extrusionDefinition->SetSideParam(true, etBlind, depth, 0, false);
					extrusionDefinition->SetSketch(entitySketch);
					entityExtrusion->Create();
					break;
				case 2:
					extrusionDefinition->SetDirectionType(dtReverse);
					extrusionDefinition->SetSideParam(true, etBlind, depth, 0, false);
					extrusionDefinition->SetSketch(entitySketch);
					entityExtrusion->Create();
					break;
				}
			}
		}
		break;
	}
	case 2:
	{
		IEntityPtr entityRotate(part->NewEntity(o3d_baseRotated), false);
		if (entityRotate)
		{
			IBaseRotatedDefinitionPtr baseRotatedDefinition(IUnknownPtr(entityRotate->GetDefinition(), false));
			if (baseRotatedDefinition)
			{
				baseRotatedDefinition->SetToroidShapeType(false);
				baseRotatedDefinition->SetDirectionType(dtBoth);
				baseRotatedDefinition->SetThinParam(false, dtBoth, 1, 0);
				baseRotatedDefinition->SetSideParam(true, 360);
				baseRotatedDefinition->SetSketch(entitySketch);
				entityRotate->Create();
			}
		}
		break;
	}
	case 3:
	{
		IEntityPtr entityCutRotate(part->NewEntity(o3d_cutRotated), false);
		if (entityCutRotate)
		{
			ICutRotatedDefinitionPtr cutRotatedDefinition(IUnknownPtr(entityCutRotate->GetDefinition(), false));
			if (cutRotatedDefinition)
			{

				cutRotatedDefinition->SetToroidShapeType(true);
				cutRotatedDefinition->SetDirectionType(dtBoth);
				cutRotatedDefinition->SetSideParam(true, 360);
				cutRotatedDefinition->SetThinParam(false, dtBoth, 0, 0);
				cutRotatedDefinition->SetSketch(entitySketch);
				entityCutRotate->Create();
			}
		}
	}
	}
}

void CreateModel(IDocument3DPtr ref, int keyObj, int keyBPlane, int keyExtr, int keyDir, double depth)
{
	IPartPtr part(ref->GetPart(pTop_Part), false);
	if (part)
	{
		IEntityPtr entitySketch(part->NewEntity(o3d_sketch), false);
		if (entitySketch)
		{
			ISketchDefinitionPtr sketchDefinition(IUnknownPtr(entitySketch->GetDefinition(), false));
			if (sketchDefinition)
			{
				CreateSketch(part, sketchDefinition, entitySketch, keyBPlane);
				if (sketchDefinition->BeginEdit())
				{
					CreateObject(sketchDefinition, keyObj);
				}
				CreateExtr(part, entitySketch, keyExtr, keyDir, depth);
			}
		}
	}
}

void CreateOffsetPlane(IDocument3DPtr ref, double dist, int keyO3dPlane, int keyObj, int keyExtr, int keyDir, double depth)
{
	int i = 1;
	IPartPtr part(ref->GetPart(pTop_Part), false);
	if (part)
	{
		IEntityPtr entityPlaneOffset(part->NewEntity(o3d_planeOffset), false);
		IEntityPtr entitySketch(part->NewEntity(o3d_sketch), false);
		if ((bool)entityPlaneOffset && (bool)entitySketch)
		{
			IPlaneOffsetDefinitionPtr planeOffsetDefinition(IUnknownPtr(entityPlaneOffset->GetDefinition(), false));
			if (planeOffsetDefinition)
			{
				planeOffsetDefinition->SetOffset(dist);
				CreateO3dPlane(part, planeOffsetDefinition, keyO3dPlane);
				entityPlaneOffset->SetName(_bstr_t("Смещенная плоскость" + 'i'));
				entityPlaneOffset->SetHidden(false);
				entityPlaneOffset->Create();
					ISketchDefinitionPtr sketchDefinition(IUnknownPtr(entitySketch->GetDefinition(), false));
					if (sketchDefinition)
					{
						sketchDefinition->SetPlane(entityPlaneOffset);
						entitySketch->Create();
						if (sketchDefinition->BeginEdit())
						{
							CreateObject(sketchDefinition, keyObj);
						}
						CreateExtr(part, entitySketch, keyExtr, keyDir, depth);
					}
				i++;
			}
		}
	}
}

void Assembly()
{
	IDocument3DPtr pDocument3d(ksGet3dDocument(), false);
	pDocument3d->Create(FALSE, FALSE);
	IPartPtr part(pDocument3d->GetPart(pTop_Part), false);
	if (part)
	{
		TCHAR fileName[255];
		char buf[255];
		if (ChoiceFile("*.m3d", 0, buf, 255))
			wsprintf(fileName, L"%hs", buf);
		pDocument3d->SetPartFromFile(fileName, part, TRUE);
		if (ChoiceFile("*.m3d", 0, buf, 255))
			wsprintf(fileName, L"%hs", buf);
		pDocument3d->SetPartFromFile(fileName, part, TRUE);
		if (ChoiceFile("*.m3d", 0, buf, 255))
			wsprintf(fileName, L"%hs", buf);
		pDocument3d->SetPartFromFile(fileName, part, TRUE);
		part->GetPart(0);
		IEntityCollectionPtr entityCollection(part->EntityCollection(o3d_face), false);
		IEntityPtr EntityFaceConcentric1(pDocument3d->UserSelectEntity(NULL, NULL, _bstr_t(_T("Укажите круглую грань на первом объекте"))), false);
		IEntityPtr EntityFaceDistance1(pDocument3d->UserSelectEntity(NULL, NULL, _bstr_t(_T("Укажите плоскую грань на первом объекте"))), false);
		part->GetPart(1);
		entityCollection = part->EntityCollection(o3d_face);
		IEntityPtr EntityFaceConcentric2(pDocument3d->UserSelectEntity(NULL, NULL, _bstr_t(_T("Укажите круглую грань на втором объекте"))), false);
		IEntityPtr EntityFaceDistance2(pDocument3d->UserSelectEntity(NULL, NULL, _bstr_t(_T("Укажите плоскую грань на втором объекте"))), false);
		part->GetPart(2);
		entityCollection = part->EntityCollection(o3d_face);
		IEntityPtr EntityFaceConcentric3(pDocument3d->UserSelectEntity(NULL, NULL, _bstr_t(_T("Укажите круглую грань на третем объекте"))), false);
		IEntityPtr EntityFaceDistance3(pDocument3d->UserSelectEntity(NULL, NULL, _bstr_t(_T("Укажите плоскую грань на третем объекте"))), false);
		pDocument3d->AddMateConstraint(mc_Concentric, EntityFaceConcentric1, EntityFaceConcentric2, 0, 0, 0);
		pDocument3d->AddMateConstraint(mc_Concentric, EntityFaceConcentric1, EntityFaceConcentric3, 0, 0, 0);
		pDocument3d->AddMateConstraint(mc_Distance, EntityFaceDistance2, EntityFaceDistance3, 0, 0, 0);
		pDocument3d->RebuildDocument();
	}
}

char* WINAPI LIBRARYNAME()
{
	return "Лабораторная работа 6(сборка)";
}

void WINAPI LIBRARYENTRY(unsigned int comm)
{
	IDocument3DPtr ref = CreateFile();
	/*Создание модели - корпуса*/ {
		//CreateModel(ref, 0, 1, 0, 0, 12);
		//CreateModel(ref, 1, 1, 1, 1, 24);
		//CreateOffsetPlane(ref, 12, 1, 2, 0, 0, 28);
		//CreateOffsetPlane(ref, 40, 1, 3, 3, 1, 20);
		//CreateOffsetPlane(ref, 40, 1, 4, 1, 0, 40);
	}
	/*Создание модели - крышка*/ {
		//CreateOffsetPlane(ref, 70, 1, 5, 0, 1, 40);
		//CreateOffsetPlane(ref, 90, 1, 6, 1, 1, 80);
		//CreateOffsetPlane(ref, 50, 1, 3, 3, 1, 20);
		//SaveFile();
	}
	/*Создание модели - трубка*/ {
		CreateModel(ref, 7, 1, 2, 0, 40);
		//SaveFile();
	}
	Assembly();
}