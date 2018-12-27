/*
** Astrolog (Version 6.40) File: extern.h
**
** IMPORTANT NOTICE: Astrolog and all chart display routines and anything
** not enumerated below used in this program are Copyright (C) 1991-2018 by
** Walter D. Pullen (Astara@msn.com, http://www.astrolog.org/astrolog.htm).
** Permission is granted to freely use, modify, and distribute these
** routines provided these credits and notices remain unmodified with any
** altered or distributed versions of the program.
**
** The main ephemeris databases and calculation routines are from the
** library SWISS EPHEMERIS and are programmed and copyright 1997-2008 by
** Astrodienst AG. The use of that source code is subject to the license for
** Swiss Ephemeris Free Edition, available at http://www.astro.com/swisseph.
** This copyright notice must not be changed or removed by any user of this
** program.
**
** Additional ephemeris databases and formulas are from the calculation
** routines in the program PLACALC and are programmed and Copyright (C)
** 1989,1991,1993 by Astrodienst AG and Alois Treindl (alois@astro.ch). The
** use of that source code is subject to regulations made by Astrodienst
** Zurich, and the code is not in the public domain. This copyright notice
** must not be changed or removed by any user of this program.
**
** The original planetary calculation routines used in this program have
** been copyrighted and the initial core of this program was mostly a
** conversion to C of the routines created by James Neely as listed in
** 'Manual of Computer Programming for Astrologers', by Michael Erlewine,
** available from Matrix Software.
**
** The PostScript code within the core graphics routines are programmed
** and Copyright (C) 1992-1993 by Brian D. Willoughby (brianw@sounds.wa.com).
**
** More formally: This program is free software; you can redistribute it
** and/or modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 2 of the
** License, or (at your option) any later version. This program is
** distributed in the hope that it will be useful and inspiring, but
** WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** General Public License for more details, a copy of which is in the
** LICENSE.HTM file included with Astrolog, and at http://www.gnu.org
**
** Initial programming 8/28-30/1991.
** X Window graphics initially programmed 10/23-29/1991.
** PostScript graphics initially programmed 11/29-30/1992.
** Last code change made 7/22/2018.
*/

/*
******************************************************************************
** Function Declarations.
******************************************************************************
*/

#ifdef PROTO
#define P(t) t
#else
#define P(t) ()
#endif

/* From astrolog.cpp */
/**
 *
 */
#ifdef __cplusplus
extern "C" {
#endif
extern void InitColors P((void));
extern void Action P((void));
extern void InitVariables P((void));
extern flag FProcessCommandLine P((char *));
extern int NParseCommandLine P((char *, char **));
extern int NPromptSwitches P((char *, char *[MAXSWITCHES]));
extern int NProcessSwitchesRare P((int, char **, int, flag, flag, flag));
extern flag FProcessSwitches P((int, char **));  // 处理命令
extern void InitProgram P((void)); // 初始化程序
#ifdef __cplusplus
}
#endif



/* From data.cpp & data2.cpp */

#define MM ciCore.mon
#define DD ciCore.day
#define YY ciCore.yea
#define TT ciCore.tim
#define ZZ ciCore.zon
#define SS ciCore.dst
#define OO ciCore.lon
#define AA ciCore.lat

#define Mon ciMain.mon
#define Day ciMain.day
#define Yea ciMain.yea
#define Tim ciMain.tim
#define Zon ciMain.zon
#define Dst ciMain.dst
#define Lon ciMain.lon
#define Lat ciMain.lat

#define MonT ciTran.mon
#define DayT ciTran.day
#define YeaT ciTran.yea
#define TimT ciTran.tim
#define ZonT ciTran.zon
#define DstT ciTran.dst
#define LonT ciTran.lon
#define LatT ciTran.lat

#define planet    cp0.obj
#define planetalt cp0.alt
#define ret       cp0.dir
#define chouse    cp0.cusp
#define inhouse   cp0.house

#define FIgnoreA(a) (ignorea[a] || rAspOrb[a] < 0.0)
#define DEFAULT_LOC DMS(122, 19, 38), DMS(47, 36, 37)
#define FProperGraph(o) !(!us.fGraphAll && (FCusp(o) || \
  (us.fInDayMonth && ((o) == oMoo || (us.fInDayYear && (o) <= oMar)))))

#define FCmSwissAny() (us.fEphemFiles && !us.fPlacalcPla)
#define FCmSwissEph() (us.fEphemFiles && !us.fPlacalcPla && !us.fSwissMosh)
#define FCmSwissMosh() (us.fEphemFiles && !us.fPlacalcPla && us.fSwissMosh)
#define FCmSwissStar() (us.fEphemFiles && !us.fPlacalcPla && !us.fMatrixStar)
#define FCmPlacalc() (us.fEphemFiles && us.fPlacalcPla)
#define FCmMatrix() (!us.fEphemFiles && us.fMatrixPla)

/**
 * 用户设定参数
 */
extern US us;
/**
 * astrolog 内部参数
 */
extern IS is;
/**
 * chart info
 */
extern CI ciCore, ciMain, ciTwin, ciThre, ciFour, ciTran, ciSave;


extern CP cp0, cp1, cp2, cp3, cp4;
extern CONST CP *rgpcp[5];
extern CONST CI *rgpci[5];

extern PT3R space[oNorm+1];
extern real force[objMax];
extern GridInfo *grid;
extern int starname[cStar+1], kObjA[objMax];

extern byte ignore[objMax], ignore2[objMax], ignorea[cAspect+1],
  ignorez[arMax], ignore7[rrMax], pluszone[cSector+1];
extern real rAspAngle[cAspect+1], rAspOrb[cAspect+1], rObjOrb[oNorm+2],
  rObjAdd[oNorm+2];
extern int ruler1[oNorm+1], ruler2[oNorm+1], exalt[oNorm+1], rules[cSign+1],
  kMainA[9], kRainbowA[8], kElemA[cElem], kAspA[cAspect+1], kObjU[oNorm+1];
extern real rObjInf[oNorm1+6], rHouseInf[cSign+6], rAspInf[cAspect+1],
  rTransitInf[oNorm1+1];

extern CONST char *szAppName, *szSignName[cSign+1], *szSignAbbrev[cSign+1],
  *szSignEnglish[cSign+1], *szHouseTradition[cSign+1], *szSystem[cSystem],
  *szAspectName[cAspect2+1], *szAspectAbbrev[cAspect2+1],
  *szAspectGlyph[cAspect2+1], *szAspectConfig[cAspConfig],
  *szElem[cElem], *szMode[3], *szMonth[cSign+1], *szDay[cWeek], *szZon[cZone],
  *szDir[4], *szSuffix[cSign+1], *szEphem[cmMax];
extern CONST int rgAspConfig[cAspConfig];
extern CONST real rZon[cZone];
extern CONST char *szObjName[objMax], *szCnstlName[cCnstl+1],
  *szCnstlAbbrev[cCnstl+1], *szCnstlMeaning[cCnstl+1],
  *szCnstlGenitive[cCnstl+1];
extern CONST real rStarBrightMatrix[cStar+1], rStarData[cStar*6];
extern char *szMindPart[oNorm+1], *szDesc[cSign+1], *szDesire[cSign+1],
  *szLifeArea[cSign+1], *szInteract[cAspect+1], *szTherefore[cAspect+1],
  *szModify[3][cAspect];
extern CONST StrLook rgObjName[], rgSystem[], rgAspectName[];
extern real rStarBright[cStar+1];
extern char *szStarCustom[cStar+1];
extern CONST char *szObjDisp[objMax], *szAspectDisp[cAspect2+1],
  *szAspectAbbrevDisp[cAspect2+1], *szAspectGlyphDisp[cAspect2+1];

extern CONST real rObjDist[oNorm+1], rObjYear[oNorm+1], rObjDiam[oVes+1],
  rObjDay[oPlu+1], rObjMass[oPlu+1], rObjAxis[oPlu+1];
extern CONST byte cSatellite[oPlu+1];
extern CONST AI ai[cPart];

extern CONST int cErrorCount[oPlu-oJup+1];
extern CONST int iErrorOffset[oPlu-oJup+1];
extern CONST real rErrorData[72+51+42*3];
extern OE rgoe[oVes+cUran-2];
extern int rgObjSwiss[cUran],
  rgTypSwiss[cUran], rgPntSwiss[cUran], rgFlgSwiss[cUran];
extern char *szMacro[48], *szWheel[4+1];
extern CONST char *szColor[cColor+2], *szColorHTML[cColor];

extern int rgObjRay[oNorm+1], rgSignRay[cSign+1], rgSignRay2[cSign+1][cRay+1],
  rgObjEso1[oNorm+1], rgObjEso2[oNorm+1], rgObjHie1[oNorm+1],
  rgObjHie2[oNorm+1], rgSignEso1[cSign+1], rgSignEso2[cSign+1],
  rgSignHie1[cSign+1], rgSignHie2[cSign+1], kRayA[cRay+2];
extern CONST char *szRayName[cRay+1], *szRayWill[cRay+1];


/* From general.cpp */

#define PrintAltitude(deg) PrintSz(SzAltitude(deg))
#define ErrorValR(sz, r) ErrorValN(sz, (int)r)
#define FEqCI(ci1, ci2) (\
  ci1.mon == ci2.mon && ci1.day == ci2.day && ci1.yea == ci2.yea && \
  ci1.tim == ci2.tim && ci1.dst == ci2.dst && ci1.zon == ci2.zon && \
  ci1.lon == ci2.lon && ci1.lat == ci2.lat && \
  (ci1.nam == ci2.nam || NCompareSz(ci1.nam, ci2.nam) == 0) && \
  (ci1.loc == ci2.loc || NCompareSz(ci1.loc, ci2.loc) == 0))

extern void SwapR P((real *, real *));
extern int CchSz P((CONST char *));
extern int NCompareSz P((CONST char *, CONST char *));
extern int FMatchSz P((CONST char *, CONST char *));
extern void ClearB P((lpbyte, int));
extern void CopyRgb P((byte *, byte *, int));
extern real RSgn P((real));
extern real Angle P((real, real));
extern real Mod P((real));
extern real ModRad P((real));
extern long Dvd P((long, long));
extern int SzLookup P((CONST StrLook *, CONST char *));
extern int Mod12 P((int));
extern real DecToDeg P((real));
extern real DegToDec P((real));
extern real MinDistance P((real, real));
extern real MinDifference P((real, real));
extern real Midpoint P((real, real));
extern real PolarDistance P((real, real, real, real));
extern char *Dignify P((int, int));
extern void EnsureRay P((void));
extern void EnsureStarBright P((void));
extern int DayInMonth P((int, int));
extern int DaysInMonth P((int, int));
extern int DayOfWeek P((int, int, int));
extern int AddDay P((int, int, int, int));
extern real GetOrb P((int, int, int));
extern CONST char *SzAspect P((int));
extern CONST char *SzAspectAbbrev P((int));
extern void Terminate P((int));
extern void PrintSz P((CONST char *));
extern void PrintCh P((char));
extern void PrintSzScreen P((CONST char *));
extern void PrintNotice P((CONST char *));
extern void PrintWarning P((CONST char *));
extern void PrintError P((CONST char *));
extern void ErrorArgc P((CONST char *));
extern void ErrorValN P((CONST char *, int));
extern void ErrorArgv P((CONST char *));
extern void ErrorSwitch P((CONST char *));
extern void ErrorEphem P((CONST char *, long));
extern void PrintTab P((char, int));
extern void AnsiColor P((int));
extern void PrintZodiac P((real));
extern char *SzZodiac P((real));
extern char *SzAltitude P((real));
extern char *SzDegree P((real));
extern char *SzDate P((int, int, int, int));
extern char *SzTime P((int, int, int));
extern char *SzTim P((real)); //   计算 小时:分
extern char *SzZone P((real));
extern char *SzLocation P((real, real));
extern char *SzElevation P((real));
extern char *SzLength P((real));
extern void GetTimeNow P((int *, int *, int *, real *, real, real));
extern int NFromAltN P((int));
extern char *ProcessProgname P((char *));
extern char *SzPersist P((char *));
extern lpbyte PAllocate P((long, CONST char *));


/* From io.cpp */

extern FILE *FileOpen P((CONST char *, int, char *));
extern flag FProcessSwitchFile P((CONST char *, FILE *));
extern flag FOutputData P((void)); // chart info 写入到文件
extern int NParseSz P((CONST char *, int));
// 解析经度 维度 --  pmLon pmLat
extern real RParseSz P((CONST char *, int));
extern void InputString P((CONST char *, char *));
extern int NInputRange P((CONST char *, int, int, int));
extern real RInputRange P((CONST char *, real, real, int));
extern flag FInputData P((CONST char *));


/* From calc.cpp */

#define RBiorhythm(day, rate) (RSin(((day)/(rate))*rPi2)*100.0)
#define HousePlaceIn2D(deg) HousePlaceIn(deg, 0.0)

extern int HousePlaceIn P((real, real));
extern real HousePlaceIn3D P((real, real));
extern void ComputeInHouses P((void));
extern void ComputeHouses P((int));
extern void ComputeStars P((real, real));
extern real Decan P((real));
extern real Navamsa P((real));
extern void RecToPol P((real, real, real *, real *));
extern void SphToRec P((real, real, real, real *, real *, real *));
extern void ComputeEphem P((real));
extern real CastChart P((flag));
extern void CastSectors P((void));
extern flag FEnsureGrid P((void));
extern flag FAcceptAspect P((int, int, int));
extern void GetAspect P((real *, real *, real *, real *, int, int));
extern void GetParallel P((real *, real *, real *, real *, int, int));
extern flag FCreateGrid P((flag));
extern flag FCreateGridRelation P((flag));
extern void CreateElemTable P((ET *));

#ifdef SWISS
extern flag FSwissPlanet
  P((int, real, flag, real *, real *, real *, real *));
extern void SwissHouse P((real, real, real, int,
  real *, real *, real *, real *, real *, real *, real *));
extern void SwissComputeStars P((real, flag));
extern flag SwissComputeStar P((real, int, real *, real *, real *));
extern double SwissJulDay P((int, int, int, real, int));
extern void SwissRevJul P((real, int, int *, int *, int *, double *));
#endif


/* From matrix.cpp */

#define EclToEqu(Z, L) CoorXform(Z, L, is.OB)
#define EquToEcl(Z, L) CoorXform(Z, L, -is.OB)
#define EquToLocal(Z, L, T) CoorXform(Z, L, T)
#define JulianDayFromTime(t) ((t)*36525.0+2415020.0)
#define IoeFromObj(obj) \
  ((obj) < oMoo ? 0 : ((obj) <= cPlanet ? (obj)-2 : (obj)-uranLo+cPlanet-2))
#define Tropical(deg) ((deg) - is.rSid + us.rZodiacOffset)

extern real MC, Asc, RA, OB;

extern long MdyToJulian P((int, int, int));
extern real MdytszToJulian P((int, int, int, real, real, real));
extern void JulianToMdy P((real, int *, int *, int *));
extern real ProcessInput P((flag));
extern void PolToRec P((real, real, real *, real *));
extern real RecToSph P((real, real, real));
extern void CoorXform P((real *, real *, real));
extern void ComputeVariables P((real *));
extern real CuspMidheaven P((void));
extern real CuspAscendant P((void));
extern real CuspEastPoint P((void));
extern real CuspPlacidus P((real, real, flag));
extern void HousePlacidus P((void));
extern void HouseKoch P((void));
extern void HouseEqual P((void));
extern void HouseCampanus P((void));
extern void HouseMeridian P((void));
extern void HouseRegiomontanus P((void));
extern void HousePorphyry P((void));
extern void HouseMorinus P((void));
extern void HouseTopocentric P((void));
extern real ReadThree P((real, real, real));
extern void RecToSph2 P((real, real, real, real *, real *, real *));
extern void ErrorCorrect P((int, real *, real *, real *));
extern void ProcessPlanet P((int, real));
extern void ComputePlanets P((void));
extern void ComputeLunar P((real *, real *, real *, real *));


#ifdef PLACALC
/* From placalc2.cpp */

extern flag FPlacalcPlanet
  P((int, real, flag, real *, real *, real *, real *));
extern double julday P((int, int, int, double, int));
extern void revjul P((double, int, int *, int *, int *, double *));
#endif


/* From charts0.cpp */

extern void PrintW P((CONST char *, int));
extern void DisplayCredits P((void));
extern void PrintS P((CONST char *));
extern void DisplaySwitches P((void));
extern void DisplaySwitchesRare P((void));
extern void PrintObjects P((void));
extern void PrintAspects P((void));
extern void PrintSigns P((void));
#ifdef CONSTEL
extern CONST char *GetSzGenitive P((char *, CONST char *));
extern void GetSzConstel P((char *, int));
extern void PrintConstellations P((void));
#endif
extern void PrintOrbit P((void));
extern int NCompareSzPart P((int, int));
extern void DisplayArabic P((void));
#ifdef GRAPH
extern void DisplayKeysX P((void));
extern void DisplaySwitchesX P((void));
#ifdef WIN
extern void DisplaySwitchesW P((void));
#endif
#endif /* GRAPH */
extern flag FPrintTables P((void));


/* From charts1.cpp */
extern void PrintHeader P((void));   // 打印头部
extern void ChartListing P((void));  // 打印主体

extern void ChartGrid P((void));
extern void PrintGrand P((char, int, int, int, int));
extern void DisplayGrands P((void));
extern void PrintHouse P((int, int));
extern void PrintWheelCenter P((int));
extern void PrintWheelSlot P((int));
extern void ChartWheel P((void));
extern void PrintAspectSummary P((int *, int *, int, real));
extern void ChartAspect P((void));
extern void PrintMidpointSummary P((int *, int, long));
extern void ChartMidpoint P((void));
extern void ChartHorizon P((void));
extern void ChartOrbit P((void));
extern void ChartSector P((void));
extern void ChartAstroGraph P((void));
extern void PrintChart P((flag));

/* From charts2.cpp */
extern void ChartListingRelation P((void));
extern void ChartGridRelation P((void));
extern void ChartAspectRelation P((void));
extern void ChartMidpointRelation P((void));
extern void CastRelation P((void));
extern void PrintInDayEvent P((int, int, int, int));
extern void PrintAspect P((int, int, int, int, int, int, int, char));
extern void ChartInDayInfluence P((void));
extern void ChartTransitInfluence P((flag));
extern void ChartTransitGraph P((flag, flag));
extern void EclToHorizon P((real *, real *, real, real, real, real));
extern void ChartCalendarMonth P((void));
extern void ChartCalendarYear P((void));
extern void DisplayRelation P((void));


/* From charts3.cpp */

extern void ChartInDaySearch P((flag));
extern void ChartTransitSearch P((flag));
extern void ChartInDayHorizon P((void));
extern void ChartEphemeris P((void));


/* From intrpret.cpp */
#define RObjInf(i) rObjInf[Min(i, oNorm1)]
#define RTransitInf(i) rTransitInf[Min(i, oNorm1)]

#ifdef INTERPRET
extern void FieldWord P((CONST char *));
extern void InterpretGeneral P((void));
extern void InterpretAspectGeneral P((void));
extern void InterpretLocation P((void));
extern void InterpretAspect P((int, int));
extern void InterpretGrid P((void));
extern void InterpretMidpoint P((int, int));
extern void InterpretInDay P((int, int, int));
extern void InterpretTransit P((int, int, int));
extern void InterpretSynastry P((void));
extern void InterpretAspectRelation P((int, int));
extern void InterpretGridRelation P((void));
extern void InterpretMidpointRelation P((int, int));
#endif
extern void SortRank P((real *, int *, int));
extern void ComputeInfluence P((real[oNorm+1], real[oNorm+1]));
extern void ChartInfluence P((void));


#ifdef GRAPH
/* From xdata.cpp */
extern GS gs;
extern GI gi;
#ifdef X11
extern XSizeHints hint;
extern char xkey[];
extern CONST char *szColorX[cColor];
extern KV rgbind[cColor];
extern KV fg, bg;
#endif
#ifdef WIN
extern int ikPalette[cColor];
#endif
#ifdef WCLI
extern WI wi;
#endif
extern char *szWheelX[4+1];

extern CONST KV rgbbmp[cColor];
extern KI kMainB[9], kRainbowB[8], kElemB[cElem], kAspB[cAspect+1],
  kObjB[objMax], kRayB[cRay+2];
extern CONST char szObjectFont[oNorm+1], szAspectFont[cAspect+1],
  *szDrawSign[cSign+2], *szDrawSign2[cSign+2], *szDrawObjectDef[oNorm+5],
  *szDrawObjectDef2[oNorm+5], *szDrawHouse[cSign+1], *szDrawHouse2[cSign+1],
  *szDrawAspectDef[cAspect2+1], *szDrawAspectDef2[cAspect2+1],
  *szDrawCh[256-32], *szWorldData[62*3], *szDrawConstel[cCnstl+1];
extern CONST char *szDrawObject[oNorm+5], *szDrawObject2[oNorm+5],
  *szDrawAspect[cAspect2+1], *szDrawAspect2[cAspect2+1];

/* From xgeneral.cpp */

#define BBmGet(rg, x, y) ((rg)[(y)*gi.cbBmpRow + ((x) >> 1)])
#define FBmGet(rg, x, y) (BBmGet(rg, x, y) >> (((x)&1^1) << 2) & 15)
#define BmSet(rg, x, y, o) BBmGet(rg, x, y) = BBmGet(rg, x, y) & \
  15 << (((x)&1) << 2) | (o) << (((x)&1^1) << 2)

#define PutByte(n) putc((byte)(n), file)
#define PutWord(n) PutByte(BLo(n)); PutByte(BHi(n))
#define PutLong(n) PutWord(WLo(n)); PutWord(WHi(n))

#define DrawEdge(x1, y1, x2, y2) \
  DrawBox(x1, y1, x2, y2, gi.nScaleT, gi.nScaleT)
#define DrawEdgeAll() DrawEdge(0, 0, gs.xWin-1, gs.yWin-1)
#define DrawLine(x1, y1, x2, y2) DrawDash(x1, y1, x2, y2, 0)
#define DrawCircle(x, y, xr, yr) \
  DrawEllipse((x)-(xr), (y)-(yr), (x)+(xr), (y)+(yr))

extern void DrawColor P((KI));
extern void DrawPoint P((int, int));
extern void DrawPointStar P((int, int, real));
extern void DrawSpot P((int, int));
extern void DrawBlock P((int, int, int, int));
extern void DrawBox P((int, int, int, int, int, int));
extern void DrawClearScreen P((void));
extern void DrawDash P((int, int, int, int, int));
extern void DrawWrap P((int, int, int, int, int, int));
extern void ClipLesser P((int *, int *, int *, int *, int));
extern void ClipGreater P((int *, int *, int *, int *, int));
extern void DrawClip P((int, int, int, int, int, int, int, int, int));
extern void DrawEllipse P((int, int, int, int));
extern void DrawSz P((CONST char *, int, int, int));
extern void DrawSign P((int, int, int));
extern void DrawHouse P((int, int, int));
extern void DrawObject P((int, int, int));
extern void DrawAspect P((int, int, int));
extern int NFromPch P((CONST char **));
extern void DrawTurtle P((CONST char *, int, int));


/* From xdevice.cpp */

#ifdef META
/* Macros to output the various metafile commands used. */

#define MetaRecord(S, R) MetaLong((long)(S)); MetaWord(R)
#define MetaSelectObject(O) MetaRecord(4, 0x12D); MetaWord(O)
#define MetaDeleteObject(O) MetaRecord(4, 0x1F0); MetaWord(O)
#define MetaSaveDc() MetaRecord(3, 0x01E)
#define MetaRestoreDc() MetaRecord(4, 0x127); MetaWord((word)-1)
#define MetaWindowOrg(X, Y) MetaRecord(5, 0x20B); MetaWord(Y); MetaWord(X)
#define MetaWindowExt(X, Y) MetaRecord(5, 0x20C); MetaWord(Y); MetaWord(X)
#define MetaCreatePen(S, W, C) MetaRecord(8, 0x2FA); MetaWord(S); \
  MetaWord(W); MetaWord(W); MetaLong(C)
#define MetaCreateBrush(S, C) MetaRecord(7, 0x2FC); \
  MetaWord(S); MetaLong(C); MetaWord(0 /* Not used */);
#define MetaCreateFont(S, X, Y, C) MetaRecord(12+(S), 0x2FB); MetaWord(Y); \
  MetaWord(X); MetaWord(0 /* Angle */); MetaWord(0 /* Not used */); \
  MetaWord(400 /* Normal Weight */); MetaWord(0 /* Italic, Underline */); \
  MetaWord(WFromBB(0 /* Strikeout */, C)); \
  MetaWord(WFromBB(4 /* TrueType */, 0 /* Clip */))
#define MetaBkMode(M) MetaRecord(4, 0x102); MetaWord(M)
#define MetaTextAlign(A) MetaRecord(4, 0x12E); MetaWord(A)
#define MetaTextColor(C) MetaRecord(5, 0x209); MetaLong(C);
#define MetaTextOut(X, Y, S) MetaRecord(7+((S)+1)/2, 0xA32); \
  MetaWord(Y); MetaWord(X); MetaWord(S); MetaWord(0 /* ETO */)
#define MetaRectangle(X1, Y1, X2, Y2) MetaRecord(7, 0x41B); \
  MetaWord(Y2); MetaWord(X2); MetaWord(Y1); MetaWord(X1)
#define MetaEllipse(X1, Y1, X2, Y2) MetaRecord(7, 0x418); \
  MetaWord(Y2); MetaWord(X2); MetaWord(Y1); MetaWord(X1)
#define MetaEscape(S) MetaRecord((S), 0x626); \
  MetaWord(15 /* MFCOMMENT */); MetaWord(((S)-5)*2 /* Bytes in comment */);
#endif /* META */

#define WirePoint(x, y, z) WireLine(x, y, z, x, y, z)

extern void WriteXBitmap P((FILE *, CONST char *, char));
extern void WriteAscii P((FILE *));
extern void WriteBmp P((FILE *));
extern void BeginFileX P((void));
extern void EndFileX P((void));
extern void PsStrokeForce P((void));
extern void PsStroke P((int));
extern void PsLineCap P((flag));
extern void PsDash P((int));
extern void PsLineWidth P((int));
extern void PsFont P((int));
extern void PsBegin P((void));
extern void PsEnd P((void));
extern void MetaWord P((word));
extern void MetaLong P((long));
extern void MetaSelect P((void));
extern void MetaInit P((void));
extern void WriteMeta P((FILE *));
extern void WriteWire P((FILE *));
extern void WireLine P((int, int, int, int, int, int));
extern void WireDrawGlobe P((flag, real));
extern void WireChartOrbit P((void));
extern void WireChartSphere P((void));


/* From xcharts0.cpp */

extern int DrawPrint P((CONST char *, int, int));
extern void DrawSidebar P((void));
extern void DrawWheel
  P((real *, real *, int, int, real, real, real,real,real,real,real));
extern void DrawSymbolRing
  P((real *, real *, real *, int, int, real, real, real,real,real,real));
extern flag FReadWorldData P((char **, char **, char **));
extern flag FGlobeCalc P((real, real, int *, int *, int, int, int, int, int));
extern flag FMapCalc P((real, real, int *, int *, flag, flag, real, real,
  int, int, int, int, int, int));

extern void DrawLeyLine P((real, real, real, real));
extern void DrawLeyLines P((int));
extern void DrawMap P((flag, flag, real));
extern void DrawChartX P((void));


/* From xcharts1.cpp */

extern void XChartWheel P((void));
extern void XChartAstroGraph P((void));
extern void XChartGrid P((void));
extern void XChartHorizon P((void));
extern void XChartHorizonSky P((void));
extern void OrbitPlot P((real *, real *, real *, real));
extern void OrbitRecord P((void));
extern void XChartOrbit P((void));
extern void XChartSector P((void));
extern void DrawArrow P((int, int, int, int));
extern void XChartDispositor P((void));
extern void XChartEsoteric P((void));
extern void XChartCalendar P((void));
extern void XChartSphere P((void));


/* From xcharts2.cpp */

extern flag FProper P((int));
extern void FillSymbolRing P((real *, real));
extern void FillSymbolLine P((real *));
extern real PlaceInX P((real));
extern real HousePlaceInX P((real, real));
extern void XChartWheelRelation P((void));
extern void XChartWheelThreeFour P((void));
extern void XChartGridRelation P((void));
extern void XChartEphemeris P((void));
extern void XChartTransit P((flag, flag));
extern void XChartBiorhythm P((void));


/* From xscreen.cpp */

extern void InitColorsX P((void));
#ifdef ISG
extern void ResizeWindowToChart P((void));
extern void BeginX P((void));
extern void AddTime P((int, int));
extern void Animate P((int, int));
extern void CommandLineX P((void));
extern void SquareX P((int *, int *, flag));
extern void InteractX P((void));
extern void EndX P((void));
#endif
extern int NProcessSwitchesX P((int, char **, int, flag, flag, flag));
extern int NProcessSwitchesRareX P((int, char **, int, flag, flag, flag));
extern flag FActionX P((void));
#endif /* GRAPH */


#ifdef WIN
/* From wdriver.cpp */

extern WI wi;
extern OPENFILENAME ofn;
extern PRINTDLG prd;
extern char szFileName[cchSzMaxFile], szFileTitle[cchSzMaxFile], *szFileTemp;

#define TextClearScreen() PatBlt(wi.hdc, 0, 0, wi.xClient, wi.yClient, \
  !gs.fInverse ? BLACKNESS : WHITENESS);
#define CheckMenu(cmd, f) \
  CheckMenuItem(wi.hmenu, (uint)cmd, f ? MF_CHECKED : MF_UNCHECKED);
#define WiCheckMenu(cmd, f) CheckMenu(cmd, f); wi.fMenu = fTrue
#define WiDoDialog(pfn, dlg) \
  dlgproc = (DLGPROC)MakeProcInstance(pfn, wi.hinst); \
  DialogBox(wi.hinst, MAKEINTRESOURCE(dlg), wi.hwnd, dlgproc); \
  FreeProcInstance((FARPROC)dlgproc)

#define SetCheck(id, f) CheckDlgButton(hdlg, id, f)
#define SetRadio(id, idLo, idHi) CheckRadioButton(hdlg, idLo, idHi, id)
#define SetEdit(id, sz) SetDlgItemText(hdlg, id, (LPCSTR)sz)
#define SetEditN(id, n) SetDlgItemInt(hdlg, id, n, fTrue)
#define SetCombo(id, sz) \
  SendDlgItemMessage(hdlg, id, CB_ADDSTRING, 0, (LPARAM)(LPCSTR)sz)
#define ClearCombo(id) SendDlgItemMessage(hdlg, id, CB_RESETCONTENT, 0, 0);
#define GetCheck(id) IsDlgButtonChecked(hdlg, id)
#define GetEdit(id, sz) GetDlgItemText(hdlg, id, sz, cchSzMax)
#define GetEditN(id) GetDlgItemInt(hdlg, id, NULL, fTrue)
#define EnsureN(n, f, sz) if (!(f)) { ErrorEnsure(n, sz); return fTrue; }
#define EnsureR(r, f, sz) EnsureN((int)r, f, sz)

extern LRESULT API WndProc P((HWND, UINT, WPARAM, LPARAM));
extern int NProcessSwitchesW P((int, char **, int, flag, flag, flag));
extern void BootExternal P((CONST char *, CONST char *));
extern WORD WCmdFromRc P((int));
extern void SetRel P((int));
extern void ProcessState P((void));
extern int NWmCommand P((WORD));
extern void API RedoMenu P((void));
extern flag API FRedraw P((void));
extern flag FCreateDesktopIcon P((void));
extern flag FCreateProgramGroup P((flag));
extern flag FRegisterExtensions P((void));
extern flag FUnregisterExtensions P((void));


/* From wdialog.cpp */

extern void SetEditSz(HWND, int, CONST char *);
extern void SetEditR(HWND, int, real, int);
extern void SetEditMDYT(HWND, int, int, int, int, int, int, int, real);
extern void SetEditSZOA(HWND, int, int, int, int, real, real, real, real);
extern void SetEditColor(HWND, int, KI);
extern real GetEditR(HWND, int);
extern void ErrorEnsure(int, CONST char *);
extern flag FOutputSettings P((void));
extern flag API DlgOpenChart P((void));
extern flag API DlgSaveChart P((void));
extern flag API DlgPrint P((void));
extern flag API DlgAbortProc P((HDC, int));
extern BOOL API DlgAbort P((HWND, uint, WPARAM, LPARAM));
extern flag API DlgCommand P((HWND, uint, WORD, LONG));
extern flag API DlgColor P((HWND, uint, WORD, LONG));
extern flag API DlgInfo P((HWND, uint, WORD, LONG));
extern flag API DlgDefault P((HWND, uint, WORD, LONG));
extern flag API DlgInfoAll P((HWND, uint, WORD, LONG));
extern flag API DlgAspect P((HWND, uint, WORD, LONG));
extern flag API DlgObject P((HWND, uint, WORD, LONG));
extern flag API DlgObject2 P((HWND, uint, WORD, LONG));
extern flag API DlgRestrict P((HWND, uint, WORD, LONG));
extern flag API DlgStar P((HWND, uint, WORD, LONG));
extern flag API DlgCalc P((HWND, uint, WORD, LONG));
extern flag API DlgDisplay P((HWND, uint, WORD, LONG));
extern flag API DlgTransit P((HWND, uint, WORD, LONG));
extern flag API DlgProgress P((HWND, uint, WORD, LONG));
extern flag API DlgChart P((HWND, uint, WORD, LONG));
extern flag API DlgGraphics P((HWND, uint, WORD, LONG));
extern flag API DlgAbout P((HWND, uint, WORD, LONG));
#endif /* WIN */

/* extern.h */
