// EnergyPlus, Copyright (c) 1996-2020, The Board of Trustees of the University of Illinois,
// The Regents of the University of California, through Lawrence Berkeley National Laboratory
// (subject to receipt of any required approvals from the U.S. Dept. of Energy), Oak Ridge
// National Laboratory, managed by UT-Battelle, Alliance for Sustainable Energy, LLC, and other
// contributors. All rights reserved.
//
// NOTICE: This Software was developed under funding from the U.S. Department of Energy and the
// U.S. Government consequently retains certain rights. As such, the U.S. Government has been
// granted for itself and others acting on its behalf a paid-up, nonexclusive, irrevocable,
// worldwide license in the Software to reproduce, distribute copies to the public, prepare
// derivative works, and perform publicly and display publicly, and to permit others to do so.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met:
//
// (1) Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//
// (2) Redistributions in binary form must reproduce the above copyright notice, this list of
//     conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//
// (3) Neither the name of the University of California, Lawrence Berkeley National Laboratory,
//     the University of Illinois, U.S. Dept. of Energy nor the names of its contributors may be
//     used to endorse or promote products derived from this software without specific prior
//     written permission.
//
// (4) Use of EnergyPlus(TM) Name. If Licensee (i) distributes the software in stand-alone form
//     without changes from the version obtained under this License, or (ii) Licensee makes a
//     reference solely to the software portion of its product, Licensee must refer to the
//     software as "EnergyPlus version X" software, where "X" is the version number Licensee
//     obtained under this License and may not use a different name for the software. Except as
//     specifically required in this Section (4), Licensee shall not use in a company name, a
//     product name, in advertising, publicity, or other promotional activities any name, trade
//     name, trademark, logo, or other designation of "EnergyPlus", "E+", "e+" or confusingly
//     similar designation, without the U.S. Department of Energy's prior written consent.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// ObjexxFCL Headers
#include <ObjexxFCL/string.functions.hh>
#include <ObjexxFCL/time.hh>

// EnergyPlus Headers
#include <EnergyPlus/DataComplexFenestration.hh>
#include <EnergyPlus/DataGlobals.hh>
#include <EnergyPlus/TARCOGCommon.hh>
#include <EnergyPlus/TARCOGGassesParams.hh>
#include <EnergyPlus/TARCOGOutput.hh>
#include <EnergyPlus/TARCOGParams.hh>

namespace EnergyPlus {

namespace TARCOGOutput {

    // MODULE INFORMATION:
    //       AUTHOR         Simon Vidanovic
    //       DATE WRITTEN   June/22/2010
    //       MODIFIED       na
    //       RE-ENGINEERED  na

    //  Revision: 6.0.36  (June/22/2010)
    //   - Initial setup, extracted from TARCOG.for

    // PURPOSE OF THIS MODULE:
    // A module which contains debug dump subroutines

    // METHODOLOGY EMPLOYED:
    // <description>

    // REFERENCES:
    // na

    // OTHER NOTES:
    // na

    // USE STATEMENTS:

    // Using/Aliasing
    using namespace TARCOGCommon;
    using namespace TARCOGGassesParams;
    using namespace TARCOGParams;

    int winID;
    int iguID;

    std::string const VersionNumber(" 7.0.15.00 ");
    std::string const VersionCompileDateCC(" August 02, 2012");

    // Functions

    void WriteInputArguments(InputOutputFile &InArgumentsFile,
                             const std::string &DBGD,
                             Real64 const tout,
                             Real64 const tind,
                             Real64 const trmin,
                             Real64 const wso,
                             int const iwd,
                             Real64 const wsi,
                             Real64 const dir,
                             Real64 const outir,
                             int const isky,
                             Real64 const tsky,
                             Real64 const esky,
                             Real64 const fclr,
                             Real64 const VacuumPressure,
                             Real64 const VacuumMaxGapThickness,
                             const Array1D_int &ibc,
                             Real64 const hout,
                             Real64 const hin,
                             int const standard,
                             int const ThermalMod,
                             Real64 const SDScalar,
                             Real64 const height,
                             Real64 const heightt,
                             Real64 const width,
                             Real64 const tilt,
                             Real64 const totsol,
                             int const nlayer,
                             const Array1D<DataComplexFenestration::iComplexShadeType> &LayerType,
                             const Array1D<Real64> &thick,
                             const Array1D<Real64> &scon,
                             const Array1D<Real64> &asol,
                             const Array1D<Real64> &tir,
                             const Array1D<Real64> &emis,
                             const Array1D<Real64> &Atop,
                             const Array1D<Real64> &Abot,
                             const Array1D<Real64> &Al,
                             const Array1D<Real64> &Ar,
                             const Array1D<Real64> &Ah,
                             const Array1D<Real64> &SlatThick,
                             const Array1D<Real64> &SlatWidth,
                             const Array1D<Real64> &SlatAngle,
                             const Array1D<Real64> &SlatCond,
                             const Array1D<Real64> &SlatSpacing,
                             const Array1D<Real64> &SlatCurve,
                             const Array1D_int &nslice,
                             const Array1D<Real64> &LaminateA,
                             const Array1D<Real64> &LaminateB,
                             const Array1D<Real64> &sumsol,
                             const Array1D<Real64> &gap,
                             const Array1D<Real64> &vvent,
                             const Array1D<Real64> &tvent,
                             const Array1D<Real64> &presure,
                             const Array1D_int &nmix,
                             Array2A_int const iprop,
                             Array2A<Real64> const frct,
                             Array2A<Real64> const xgcon,
                             Array2A<Real64> const xgvis,
                             Array2A<Real64> const xgcp,
                             const Array1D<Real64> &xwght)
    {

        // Using/Aliasing
        // Argument array dimensioning
        EP_SIZE_CHECK(ibc, 2);
        EP_SIZE_CHECK(LayerType, maxlay);
        EP_SIZE_CHECK(thick, maxlay);
        EP_SIZE_CHECK(scon, maxlay);
        EP_SIZE_CHECK(asol, maxlay);
        EP_SIZE_CHECK(tir, maxlay2);
        EP_SIZE_CHECK(emis, maxlay2);
        EP_SIZE_CHECK(Atop, maxlay);
        EP_SIZE_CHECK(Abot, maxlay);
        EP_SIZE_CHECK(Al, maxlay);
        EP_SIZE_CHECK(Ar, maxlay);
        EP_SIZE_CHECK(Ah, maxlay);
        EP_SIZE_CHECK(SlatThick, maxlay);
        EP_SIZE_CHECK(SlatWidth, maxlay);
        EP_SIZE_CHECK(SlatAngle, maxlay);
        EP_SIZE_CHECK(SlatCond, maxlay);
        EP_SIZE_CHECK(SlatSpacing, maxlay);
        EP_SIZE_CHECK(SlatCurve, maxlay);
        EP_SIZE_CHECK(nslice, maxlay);
        EP_SIZE_CHECK(LaminateA, maxlay);
        EP_SIZE_CHECK(LaminateB, maxlay);
        EP_SIZE_CHECK(sumsol, maxlay);
        EP_SIZE_CHECK(gap, maxlay);
        EP_SIZE_CHECK(vvent, maxlay1);
        EP_SIZE_CHECK(tvent, maxlay1);
        EP_SIZE_CHECK(presure, maxlay1);
        EP_SIZE_CHECK(nmix, maxlay1);
        iprop.dim(maxgas, maxlay1);
        frct.dim(maxgas, maxlay1);
        xgcon.dim(3, maxgas);
        xgvis.dim(3, maxgas);
        xgcp.dim(3, maxgas);
        EP_SIZE_CHECK(xwght, maxgas);

        // Locals
        Array1D_int DATE_TIME(8);
        Array1D_string real_CLOCK(3);

        int i;
        int j;

        // Formats
        // static constexpr auto Format_10001("TARCOG v.{}compiled {}\n");
        static constexpr auto Format_1000("TARCOG input arguments:\n");
        static constexpr auto Format_1001("TARCOG debug output, {:4}-{:02}-{:02}, {:02}:{:02}:{:02}\n");
        static constexpr auto Format_1002("     WindowID:{:8}  - Not specified\n");
        static constexpr auto Format_1003("     WindowID:{:8} \n");
        static constexpr auto Format_1006("     IGUID:   {:8}  - Not specified\n");
        static constexpr auto Format_1007("     IGUID:   {:8} \n");
        static constexpr auto Format_1005("Simulation parameters:\n");
        static constexpr auto Format_1010("  Tout       =  {:10.6F} K ( {:7.3F} deg C) - Outdoor temperature\n");
        static constexpr auto Format_1015("  Tint       =  {:10.6F} K ( {:7.3F} deg C) - Indoor temperature\n");
        // static constexpr auto Format_1016("  Trmout     =  {:10.6F} K ( {:7.3F} deg C) - Outdoor mean radiant temp.\n");
        // static constexpr auto Format_1017("  Gout       =  {:10.6F} \n");
        // static constexpr auto Format_1018("  Gin        =  {:10.6F} \n");
        // static constexpr auto Format_1019("  Ebsky      =  {:10.6F} \n");
        // static constexpr auto Format_10191("  Ebroom     =  {:10.6F} \n");
        static constexpr auto Format_1020("  Trmin      =  {:10.6F} K ( {:7.3F} deg C) - Indoor mean radiant temp.\n");
        static constexpr auto Format_1030("  wso        =  {:7.3F}    - Outdoor wind speed [m/s]\n");
        static constexpr auto Format_1032("  iwd        =    0        - Wind direction - windward\n");
        static constexpr auto Format_1033("  iwd        =    1        - Wind direction - leeward\n");
        static constexpr auto Format_1035("  wsi        =  {:7.3F}    - Indoor forced air speed [m/s]\n");
        static constexpr auto Format_1040("  dir        = {:8.3F}    - Direct solar radiation [W/m^2]\n");
        static constexpr auto Format_1041("  outir       = {:8.3F}    - IR radiation [W/m^2]\n");
        static constexpr auto Format_1045("  isky       =  {:3}        - Flag for handling tsky, esky\n");
        static constexpr auto Format_1050("  tsky           =  {:10.6F} K ( {:7.3F} deg C) - Night sky temperature\n");
        static constexpr auto Format_1055("  esky           =  {:7.3F}    - Effective night sky emmitance\n");
        static constexpr auto Format_1060("  fclr           =  {:7.3F}    - Fraction of sky that is clear\n");
        static constexpr auto Format_1061("  VacuumPressure =  {:7.3F}    - maximum allowed gas pressure to be considered as vacuum\n");
        static constexpr auto Format_1062("  VacuumMaxGapThickness =  {:7.3F}    - maximum allowed vacuum gap thickness with support pillar\n");
        static constexpr auto Format_1063("  ibc(1)         =  {:3}        - Outdoor BC switch\n");
        static constexpr auto Format_1065("  hout           =  {:9.5F}  - Outdoor film coeff. [W/m^2-K]\n");
        static constexpr auto Format_1066("  ibc(2)         =  {:3}        - Indoor BC switch\n");
        static constexpr auto Format_1068("  hin            =  {:9.5F}  - Indoor film coeff. [W/m^2-K]\n");
        static constexpr auto Format_1070("  standard   =  {:3}        - ISO 15099 calc. standard\n");
        static constexpr auto Format_1071("  standard   =  {:3}        - EN 673/ISO 10292 Declared calc. standard\n");
        static constexpr auto Format_1072("  standard   =  {:3}        - EN 673/ISO 10292 Design calc. standard\n");
        static constexpr auto Format_10731("  ThermalMod =  {:3}        - ISO15099 thermal model\n");
        static constexpr auto Format_10732("  ThermalMod =  {:3}        - Scaled Cavity Width (SCW) thermal model\n");
        static constexpr auto Format_10733("  ThermalMod =  {:3}        - Convective Scalar Model (CSM) thermal model\n");
        static constexpr auto Format_10740("  SDScalar =  {:7.5F}      - Factor of Venetian SD layer contribution to convection\n\n (only if "
                                           "ThermalModel = 2, otherwise ignored)\n");
        static constexpr auto Format_1075("IGU parameters:\n");
        static constexpr auto Format_1076("  height     =  {:10.6F} - IGU cavity height [m]\n");
        static constexpr auto Format_1077("  heightt    =  {:10.6F} - Total window height [m]\n");
        static constexpr auto Format_1078("  width      =  {:10.6F} - Window width [m]\n");
        static constexpr auto Format_1079("  tilt       =  {:7.3F}    - Window tilt [deg]\n");
        static constexpr auto Format_1080("  totsol     =  {:10.6F} - Total solar transmittance of IGU\n");
        static constexpr auto Format_1081("  nlayer     =  {:3}        - Number of glazing layers\n");
        static constexpr auto Format_1089("IGU layers list:\n");
        static constexpr auto Format_10802(" Layer{:3} : {:1}              - Specular layer - Monolyhtic Glass\n");
        static constexpr auto Format_10803(" Layer{:3} : {:1}              - Laminated Glass\n");
        static constexpr auto Format_10804(" Layer{:3} : {:1}              - Horizontal Venetian Blind\n");
        static constexpr auto Format_10805(" Layer{:3} : {:1}              - Woven Shade\n");
        static constexpr auto Format_10806(" Layer{:3} : {:1}              - Diffuse Shade\n");
        static constexpr auto Format_10809(" Layer{:3} : {:1}              - UNKNOWN TYPE!\n");
        static constexpr auto Format_10810(" Layer{:3} : {:1}              - Vertical Venetian Blind\n");
        static constexpr auto Format_1085("    nslice     = {:3}          - Number of slices\n");
        static constexpr auto Format_1090("    thick   = {:10.6F}   - Thickness [m]\n");
        static constexpr auto Format_1091("    scon    = {:10.6F}   - Thermal conductivity [W/m-K]\n");
        static constexpr auto Format_1092("    asol    = {:12.8F} - Absorbed solar energy [W/m^2]\n");
        static constexpr auto Format_1093("    tir     = {:12.8F} - IR transmittance\n");
        static constexpr auto Format_1094("    emis1   = {:10.6F}   - IR outdoor emissivity\n");
        static constexpr auto Format_1095("    emis2   = {:10.6F}   - IR indoor emissivity\n");
        static constexpr auto Format_1100("    Atop    = {:10.6F}   - Top opening area [m^2]\n");
        static constexpr auto Format_1101("    Abot    = {:10.6F}   - Bottom opening area [m^2]\n");
        static constexpr auto Format_1102("    Al      = {:10.6F}   - Left opening area [m^2]\n");
        static constexpr auto Format_1103("    Ar      = {:10.6F}   - Right opening area [m^2]\n");
        static constexpr auto Format_1105("    Ah      = {:10.6F}   - Total area of holes [m^2]\n");
        static constexpr auto Format_11051("    SlatThick   = {:10.6F}   - Slat thickness [m]\n");
        static constexpr auto Format_11052("    SlatWidth   = {:10.6F}   - Slat width [m]\n");
        static constexpr auto Format_11053("    SlatAngle   = {:10.6F}   - Slat tilt angle [deg]\n");
        static constexpr auto Format_11054("    SlatCond    = {:10.6F}   - Conductivity of the slat material [W/m.K]\n");
        static constexpr auto Format_11055("    SlatSpacing = {:10.6F}   - Distance between slats [m]\n");
        static constexpr auto Format_11056("    SlatCurve   = {:10.6F}   - Curvature radius of the slat [m]\n");
        static constexpr auto Format_1110("IGU Gaps:\n");
        static constexpr auto Format_1111(" Gap {:2}:\n");
        static constexpr auto Format_11110(" Outdoor space:\n");
        static constexpr auto Format_11111(" Indoor space:\n");
        static constexpr auto Format_1112("    gap        = {:12.5F} - Gap width [m]\n");
        static constexpr auto Format_1113("    presure    = {:12.5F} - Gas pressure [N/m^2]\n");
        static constexpr auto Format_1114("    nmix       = {:6}       - Num. of gasses in a gas mix\n");
        static constexpr auto Format_1115("      Gas {:1}:     {}     {:6.2F} %\n");
        static constexpr auto Format_1120("    vvent      = {:12.5F} - Forced ventilation speed [m/s]\n");
        static constexpr auto Format_1121("    tvent      = {:12.5F} - Temperature in connected gap [K]\n");
        static constexpr auto Format_1130("      Gas mix coefficients - gas {:1}, {:6.2F} %\n");
        static constexpr auto Format_1131("        gcon   = {:11.6F}, {:11.6F}, {:11.6F} - Conductivity\n");
        static constexpr auto Format_1132("        gvis   = {:11.6F}, {:11.6F}, {:11.6F} - Dynamic viscosity\n");
        static constexpr auto Format_1133("        gcp    = {:11.6F}, {:11.6F}, {:11.6F} - Spec.heat @ const.P\n");
        static constexpr auto Format_1134("        wght   = {:11.6F}                           - Molecular weight\n");
        static constexpr auto Format_1198("=====  =====  =====  =====  =====  =====  =====  =====  =====  =====  =====\n");

        // bi...Create debug file w/ Tarcog's input arguments:

        // File is not open and nothing cannot be written
        if (!InArgumentsFile.good()) return;

        date_and_time(real_CLOCK(1), real_CLOCK(2), real_CLOCK(3), DATE_TIME);

        print(InArgumentsFile, "\n");
        //  write(InArgumentsFile, 10001) VersionNumber, VersionCompileDateCC
        print(InArgumentsFile, Format_1001, DATE_TIME(1), DATE_TIME(2), DATE_TIME(3), DATE_TIME(5), DATE_TIME(6), DATE_TIME(7));
        print(InArgumentsFile, "\n");

        if (winID == -1) {
            print(InArgumentsFile, Format_1002, winID);
        } else {
            print(InArgumentsFile, Format_1003, winID);
        }

        if (iguID == -1) {
            print(InArgumentsFile, Format_1006, iguID);
        } else {
            print(InArgumentsFile, Format_1007, iguID);
        }

        print(InArgumentsFile, "     Debug dir:     {}\n", DBGD);

        print(InArgumentsFile, "\n");
        print(InArgumentsFile, Format_1000);
        print(InArgumentsFile, "\n");
        print(InArgumentsFile, Format_1005);
        print(InArgumentsFile, Format_1010, tout, tout - DataGlobalConstants::KelvinConv());
        print(InArgumentsFile, Format_1015, tind, tind - DataGlobalConstants::KelvinConv());
        print(InArgumentsFile, Format_1020, trmin, trmin - DataGlobalConstants::KelvinConv());
        print(InArgumentsFile, Format_1030, wso);
        if (iwd == 0) print(InArgumentsFile, Format_1032); // windward
        if (iwd == 1) print(InArgumentsFile, Format_1033); // leeward
        print(InArgumentsFile, Format_1035, wsi);
        print(InArgumentsFile, Format_1040, dir);
        print(InArgumentsFile, Format_1041, outir);
        print(InArgumentsFile, Format_1045, isky);
        print(InArgumentsFile, Format_1050, tsky, tsky - DataGlobalConstants::KelvinConv());
        print(InArgumentsFile, Format_1055, esky);
        print(InArgumentsFile, Format_1060, fclr);
        print(InArgumentsFile, Format_1061, VacuumPressure);
        print(InArgumentsFile, Format_1062, VacuumMaxGapThickness);
        print(InArgumentsFile, Format_1063, ibc(1));
        print(InArgumentsFile, Format_1065, hout);
        print(InArgumentsFile, Format_1066, ibc(2));
        print(InArgumentsFile, Format_1068, hin);

        if (standard == ISO15099) print(InArgumentsFile, Format_1070, standard);
        if (standard == EN673) print(InArgumentsFile, Format_1071, standard);
        if (standard == EN673Design) print(InArgumentsFile, Format_1072, standard);

        if (ThermalMod == THERM_MOD_ISO15099) {
            print(InArgumentsFile, Format_10731, ThermalMod);
            print(InArgumentsFile, Format_10740, SDScalar);
        }

        if (ThermalMod == THERM_MOD_SCW) {
            print(InArgumentsFile, Format_10732, ThermalMod);
            print(InArgumentsFile, Format_10740, SDScalar);
        }

        if (ThermalMod == THERM_MOD_CSM) {
            print(InArgumentsFile, Format_10733, ThermalMod);
            print(InArgumentsFile, Format_10740, SDScalar);
        }

        //    if (ThermalMod.eq.THERM_MOD_CSM)
        //        write(InArgumentsFile, 10740) SDScalar

        print(InArgumentsFile, "\n");

        print(InArgumentsFile, Format_1075);
        print(InArgumentsFile, Format_1076, height);
        print(InArgumentsFile, Format_1077, heightt);
        print(InArgumentsFile, Format_1078, width);
        print(InArgumentsFile, Format_1079, tilt);
        print(InArgumentsFile, Format_1080, totsol);
        print(InArgumentsFile, Format_1081, nlayer);
        print(InArgumentsFile, "\n");

        print(InArgumentsFile, Format_1089);
        for (i = 1; i <= nlayer; ++i) {
            {
                auto const SELECT_CASE_var(LayerType(i));
                if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::OtherShadingType) { // Diffuse Shade
                    print(InArgumentsFile, Format_10806, i, LayerType(i));
                } else if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::Woven) { // Woven Shade
                    print(InArgumentsFile, Format_10805, i, LayerType(i));
                } else if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::VenetianHorizontal) { // Horizontal venetian blind
                    print(InArgumentsFile, Format_10804, i, LayerType(i));
                } else if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::VenetianVertical) { // Vertical venetian blind
                    print(InArgumentsFile, Format_10810, i, LayerType(i));
                } else if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::Specular) { // Specular layer
                    if (nslice(i) <= 1) {
                        print(InArgumentsFile, Format_10802, i, LayerType(i)); // Monolithic glass
                    } else {
                        print(InArgumentsFile, Format_10803, i, LayerType(i)); // Laminated layer
                    }
                } else {
                    print(InArgumentsFile, Format_10809, i, LayerType(i));
                }
            }

            print(InArgumentsFile, Format_1090, thick(i));
            print(InArgumentsFile, Format_1091, scon(i));
            print(InArgumentsFile, Format_1092, asol(i));
            print(InArgumentsFile, Format_1093, tir(2 * i - 1));
            print(InArgumentsFile, Format_1094, emis(2 * i - 1));
            print(InArgumentsFile, Format_1095, emis(2 * i));

            if (LayerType(i) == DataComplexFenestration::iComplexShadeType::VenetianHorizontal ||
                LayerType(i) == DataComplexFenestration::iComplexShadeType::VenetianVertical) { // SD layer
                print(InArgumentsFile, Format_1100, Atop(i));
                print(InArgumentsFile, Format_1101, Abot(i));
                print(InArgumentsFile, Format_1102, Al(i));
                print(InArgumentsFile, Format_1103, Ar(i));
                print(InArgumentsFile, Format_1105, Ah(i));

                print(InArgumentsFile, Format_11051, SlatThick(i));
                print(InArgumentsFile, Format_11052, SlatWidth(i));
                print(InArgumentsFile, Format_11053, SlatAngle(i));
                print(InArgumentsFile, Format_11054, SlatCond(i));
                print(InArgumentsFile, Format_11055, SlatSpacing(i));
                print(InArgumentsFile, Format_11056, SlatCurve(i));

                // bi...Input arguments correction patch:

                //     if (ApplyVenetianPatch.eq..TRUE.) then
                //      SlatThick(i) = Thick(i)
                //      SlatWidth(i) = SlatWidth(i) / 1000.0d0
                //      SlatCurve(i) = SlatCurve(i) / 1000.0d0
                //      SlatSpacing(i) = SlatSpacing(i) / 1000.0d0
                //      write(InArgumentsFile, *) 'After applying the patch:'
                //        write(InArgumentsFile, 11051) SlatThick(i)
                //        write(InArgumentsFile, 11052) SlatWidth(i)
                //        write(InArgumentsFile, 11053) SlatAngle(i)
                //        write(InArgumentsFile, 11054) SlatCond(i)
                //        write(InArgumentsFile, 11055) SlatSpacing(i)
                //        write(InArgumentsFile, 11056) SlatCurve(i)
                //     end if

                // bi...end Input arguments correction patch
            }

            if (nslice(i) > 1) { // SD layer
                print(InArgumentsFile, Format_1085, nslice(i));
                print(InArgumentsFile, Format_1085, LaminateA(i));
                print(InArgumentsFile, Format_1085, LaminateB(i));
                print(InArgumentsFile, Format_1085, sumsol(i));
            }
        } // i - layers

        print(InArgumentsFile, "\n");

        print(InArgumentsFile, Format_1110);

        for (i = 1; i <= nlayer + 1; ++i) { // loop through gaps:
            if ((i > 1) && (i <= nlayer)) print(InArgumentsFile, Format_1111, i - 1);
            if (i == 1) print(InArgumentsFile, Format_11110);
            if (i == nlayer + 1) print(InArgumentsFile, Format_11111);
            if ((i > 1) && (i <= nlayer)) print(InArgumentsFile, Format_1112, gap(i - 1));
            print(InArgumentsFile, Format_1113, presure(i));
            if ((i > 1) && (i <= nlayer)) {
                print(InArgumentsFile, Format_1120, vvent(i));
            }
            if ((i > 1) && (i <= nlayer)) {
                print(InArgumentsFile, Format_1121, tvent(i));
            }
            print(InArgumentsFile, Format_1114, nmix(i));

            // if (mgas.eq.1) then ! call gasses by names:
            //  do  j = 1, nmix(i)
            //    if (iprop(i, j).eq.1) write(InArgumentsFile, 1115) iprop(i, j), 'Air,     ', 100*frct(i, j) ! Air
            //    if (iprop(i, j).eq.2) write(InArgumentsFile, 1115) iprop(i, j), 'Argon,   ', 100*frct(i, j) ! Argon
            //    if (iprop(i, j).eq.3) write(InArgumentsFile, 1115) iprop(i, j), 'Krypton, ', 100*frct(i, j) ! Krypton
            //    if (iprop(i, j).eq.4) write(InArgumentsFile, 1115) iprop(i, j), 'Xenon,   ', 100*frct(i, j) ! Xenon
            //  end do  ! j - mix loop
            // end if

            // if (mgas.eq.0) then ! show received gass properties:
            for (j = 1; j <= nmix(i); ++j) {
                // if (iprop(i, j).eq.1) write(InArgumentsFile, 1115) iprop(i, j), ' ' 100*frct(i, j) ! Air
                print(InArgumentsFile, Format_1115, iprop(j, i), ' ', 100 * frct(j, i)); // gas
                // if (iprop(i, j).eq.2) write(InArgumentsFile, 1116) iprop(i, j), 100*frct(i, j) ! Argon
                // if (iprop(i, j).eq.3) write(InArgumentsFile, 1117) iprop(i, j), 100*frct(i, j) ! Krypton
                // if (iprop(i, j).eq.4) write(InArgumentsFile, 1118) iprop(i, j), 100*frct(i, j) ! Xenon
                print(InArgumentsFile, Format_1130, iprop(j, i), 100 * frct(j, i));
                print(InArgumentsFile, Format_1131, xgcon(1, iprop(j, i)), xgcon(2, iprop(j, i)), xgcon(3, iprop(j, i)));
                print(InArgumentsFile, Format_1132, xgvis(1, iprop(j, i)), xgvis(2, iprop(j, i)), xgvis(3, iprop(j, i)));
                print(InArgumentsFile, Format_1133, xgcp(1, iprop(j, i)), xgcp(2, iprop(j, i)), xgcp(3, iprop(j, i)));
                print(InArgumentsFile, Format_1134, xwght(iprop(j, i)));
            } // - j - one mix
              // end if  ! MGAS = 1 - "table" gasses
        }     // i - gas loop

        print(InArgumentsFile, "\n");
        print(InArgumentsFile, Format_1198);

        // close(InArgumentsFile)

        //!!!!!!!!!!!!!!!!!!
        //!!
        //!! Formats:
        //!!
        //!!!!!!!!!!!!!!!!!!

        // 1000  format('TARCOG input arguments list - {:4}-{:02}-',I2.2, ', ', I2.2,':{:02}:',I2.2)

        // 1010  format('  Tout       =  ', F10.6,  ' - Outdoor temperature [K]')
        // 1015  format('  Tin        =  ', F10.6,  ' - Indoor temperature [K]')

        // 1016  format('  Trmout     =  ', F10.6,  ' - Outdoor mean radiant temperature [K]')

        // 1020  format('  Trmin      =  ', F10.6,  ' - Indoor mean radiant temperature [K]')
        // 1050  format('  tsky       =  ', F10.6,  ' - Night sky temperature [K]')

        // 1115  format('      Gas ', I1, ':     Air,     ', F6.2,' %')
        // 1116  format('      Gas ', I1, ':     Argon,   ', F6.2,' %')
        // 1117  format('      Gas ', I1, ':     Krypron, ', F6.2,' %')
        // 1118  format('      Gas ', I1, ':     Xenon,   ', F6.2,' %')

        // 1199  format('-----  *****  -----  *****  -----  *****  -----  *****  -----  *****  -----')
    }

    void WriteModifiedArguments(InputOutputFile &InArgumentsFile,
                                [[maybe_unused]] std::string const &DBGD,
                                Real64 const esky,
                                Real64 const trmout,
                                Real64 const trmin,
                                Real64 const ebsky,
                                Real64 const ebroom,
                                Real64 const Gout,
                                Real64 const Gin,
                                int const nlayer,
                                const Array1D<DataComplexFenestration::iComplexShadeType> &LayerType,
                                const Array1D_int &nmix,
                                Array2A<Real64> const frct,
                                const Array1D<Real64> &thick,
                                const Array1D<Real64> &scon,
                                const Array1D<Real64> &gap,
                                Array2A<Real64> const xgcon,
                                Array2A<Real64> const xgvis,
                                Array2A<Real64> const xgcp,
                                const Array1D<Real64> &xwght)
    {

        // Using/Aliasing
        // Argument array dimensioning
        EP_SIZE_CHECK(LayerType, maxlay);
        EP_SIZE_CHECK(nmix, maxlay1);
        frct.dim(maxgas, maxlay1);
        EP_SIZE_CHECK(thick, maxlay);
        EP_SIZE_CHECK(scon, maxlay);
        EP_SIZE_CHECK(gap, MaxGap);
        xgcon.dim(3, maxgas);
        xgvis.dim(3, maxgas);
        xgcp.dim(3, maxgas);
        EP_SIZE_CHECK(xwght, maxgas);

        // Locals
        int i;
        int j;

        // Formats
        static constexpr auto Format_1014("Adjusted input arguments:\n");
        static constexpr auto Format_1013(" Gass coefficients:\n");
        static constexpr auto Format_1016("  Trmout     =  {:10.6F} K ( {:7.3F} deg C) - Outdoor mean radiant temp.\n");
        static constexpr auto Format_1017("  Gout       =  {:10.6F} \n");
        static constexpr auto Format_1018("  Gin        =  {:10.6F} \n");
        static constexpr auto Format_1019("  Ebsky      =  {:10.6F} \n");
        static constexpr auto Format_10191("  Ebroom     =  {:10.6F} \n");
        static constexpr auto Format_1020("  Trmin      =  {:10.6F} K ( {:7.3F} deg C) - Indoor mean radiant temp.\n");
        static constexpr auto Format_1055("  esky       =  {:7.3F}    - Effective night sky emmitance\n");
        static constexpr auto Format_1084(" Layer{:3} : {:1}              - Venetian Blind\n");
        static constexpr auto Format_1090("    thick   = {:10.6F}   - Thickness [m]\n");
        static constexpr auto Format_1091("    scon    = {:10.6F}   - Thermal conductivity [W/m-K]\n");
        static constexpr auto Format_1130("      Gas mix coefficients - gas {:1}, {:6.2F} %\n");
        static constexpr auto Format_1131("        gcon   = {:11.6F}, {:11.6F}, {:11.6F} - Conductivity\n");
        static constexpr auto Format_1132("        gvis   = {:11.6F}, {:11.6F}, {:11.6F} - Dynamic viscosity\n");
        static constexpr auto Format_1133("        gcp    = {:11.6F}, {:11.6F}, {:11.6F} - Spec.heat @ const.P\n");
        static constexpr auto Format_1134("        wght   = {:11.6F}                           - Molecular weight\n");
        static constexpr auto Format_1111(" Gap {:2}:\n");
        static constexpr auto Format_1112(" Gap width: {:11.8F}\n");
        static constexpr auto Format_11110(" Outdoor space:\n");
        static constexpr auto Format_11111(" Indoor space:\n");
        static constexpr auto Format_1198("=====  =====  =====  =====  =====  =====  =====  =====  =====  =====  =====\n");

        // open(unit=InArgumentsFile,  file=TRIM(DBGD)//DebugOutputFileName,  status='unknown', access=FileMode, &
        //        position=FilePosition, form='formatted', iostat=nperr)
        // if (nperr.ne.0)  open(unit=InArgumentsFile,  file=DebugOutputFileName,  status='unknown', access=FileMode, &
        //        position=FilePosition, form='formatted', iostat=nperr)
        print(InArgumentsFile, "\n");
        print(InArgumentsFile, Format_1014);
        print(InArgumentsFile, "\n");
        print(InArgumentsFile, Format_1055, esky);
        print(InArgumentsFile, Format_1016, trmout, trmout - DataGlobalConstants::KelvinConv());
        print(InArgumentsFile, Format_1020, trmin, trmin - DataGlobalConstants::KelvinConv());
        print(InArgumentsFile, Format_1019, ebsky);
        print(InArgumentsFile, Format_10191, ebroom);
        print(InArgumentsFile, Format_1017, Gout);
        print(InArgumentsFile, Format_1018, Gin);
        print(InArgumentsFile, "\n");

        for (i = 1; i <= nlayer; ++i) {
            if (LayerType(i) == DataComplexFenestration::iComplexShadeType::VenetianHorizontal ||
                LayerType(i) == DataComplexFenestration::iComplexShadeType::VenetianVertical) { // SD layer
                print(InArgumentsFile, Format_1084, i, LayerType(i));
                print(InArgumentsFile, Format_1090, thick(i));
                print(InArgumentsFile, Format_1091, scon(i));
            }
        }
        print(InArgumentsFile, "\n");

        print(InArgumentsFile, Format_1013);
        for (i = 1; i <= nlayer + 1; ++i) { // loop through gaps:
            if ((i > 1) && (i <= nlayer)) print(InArgumentsFile, Format_1111, i - 1);
            if ((i > 1) && (i <= nlayer)) print(InArgumentsFile, Format_1112, gap(i - 1));
            if (i == 1) print(InArgumentsFile, Format_11110);
            if (i == nlayer + 1) print(InArgumentsFile, Format_11111);
            //    write(InArgumentsFile, 1111) i-1
            for (j = 1; j <= nmix(i); ++j) {
                print(InArgumentsFile, Format_1130, j, 100 * frct(j, i));
                print(InArgumentsFile, Format_1131, xgcon(1, j), xgcon(2, j), xgcon(3, j));
                print(InArgumentsFile, Format_1132, xgvis(1, j), xgvis(2, j), xgvis(3, j));
                print(InArgumentsFile, Format_1133, xgcp(1, j), xgcp(2, j), xgcp(3, j));
                print(InArgumentsFile, Format_1134, xwght(j));
            } // j - gas mix
        }     // i - gaps
        print(InArgumentsFile, "\n");
        print(InArgumentsFile, Format_1198);
        // close(InArgumentsFile)

        //!!!!!!!!!!!!!!!!!!
        //!!
        //!! Formats:
        //!!
        //!!!!!!!!!!!!!!!!!!
    }

    void WriteOutputArguments(InputOutputFile &OutArgumentsFile,
                              [[maybe_unused]] std::string const &DBGD,
                              int const nlayer,
                              Real64 const tamb,
                              const Array1D<Real64> &q,
                              const Array1D<Real64> &qv,
                              const Array1D<Real64> &qcgas,
                              const Array1D<Real64> &qrgas,
                              const Array1D<Real64> &theta,
                              const Array1D<Real64> &vfreevent,
                              const Array1D<Real64> &vvent,
                              const Array1D<Real64> &Keff,
                              const Array1D<Real64> &ShadeGapKeffConv,
                              Real64 const troom,
                              Real64 const ufactor,
                              Real64 const shgc,
                              Real64 const sc,
                              Real64 const hflux,
                              Real64 const shgct,
                              Real64 const hcin,
                              Real64 const hrin,
                              Real64 const hcout,
                              Real64 const hrout,
                              const Array1D<Real64> &Ra,
                              const Array1D<Real64> &Nu,
                              const Array1D<DataComplexFenestration::iComplexShadeType> &LayerType,
                              const Array1D<Real64> &Ebf,
                              const Array1D<Real64> &Ebb,
                              const Array1D<Real64> &Rf,
                              const Array1D<Real64> &Rb,
                              Real64 const ebsky,
                              Real64 const Gout,
                              Real64 const ebroom,
                              Real64 const Gin,
                              Real64 const ShadeEmisRatioIn,
                              Real64 const ShadeEmisRatioOut,
                              Real64 const ShadeHcRatioIn,
                              Real64 const ShadeHcRatioOut,
                              Real64 const HcUnshadedIn,
                              Real64 const HcUnshadedOut,
                              const Array1D<Real64> &hcgas,
                              const Array1D<Real64> &hrgas,
                              Real64 const AchievedErrorTolerance,
                              int const NumOfIter)
    {

        // Using/Aliasing
        // Argument array dimensioning
        EP_SIZE_CHECK(q, maxlay3);
        EP_SIZE_CHECK(qv, maxlay1);
        EP_SIZE_CHECK(qcgas, maxlay1);
        EP_SIZE_CHECK(qrgas, maxlay1);
        EP_SIZE_CHECK(theta, maxlay2);
        EP_SIZE_CHECK(vfreevent, maxlay1);
        EP_SIZE_CHECK(vvent, maxlay1);
        EP_SIZE_CHECK(Keff, maxlay);
        EP_SIZE_CHECK(ShadeGapKeffConv, MaxGap);
        EP_SIZE_CHECK(Ra, maxlay);
        EP_SIZE_CHECK(Nu, maxlay);
        EP_SIZE_CHECK(LayerType, maxlay);
        EP_SIZE_CHECK(Ebf, maxlay);
        EP_SIZE_CHECK(Ebb, maxlay);
        EP_SIZE_CHECK(Rf, maxlay);
        EP_SIZE_CHECK(Rb, maxlay);
        EP_SIZE_CHECK(hcgas, maxlay);
        EP_SIZE_CHECK(hrgas, maxlay);

        // Locals
        Array1D_int DATE_TIME(8);
        Array1D_string real_CLOCK(3);

        int i;

        // Formats
        static constexpr auto Format_2000("TARCOG calculation results - {:4}-{:02}-{:02}, {:02}:{:02}:{:02}\n");
        static constexpr auto Format_2120("  Ufactor  = {:12.6F}\n");
        static constexpr auto Format_2130("  SHGC     = {:12.6F}\n");
        static constexpr auto Format_2131("  SHGC_OLD = {:12.6F}\n");
        static constexpr auto Format_2132("  SC       = {:12.6F}\n");
        static constexpr auto Format_2140("  hcin  = {:10.6F}   hrin  = {:10.6F}   hin  = {:10.6F}\n");
        static constexpr auto Format_2150("  hcout = {:10.6F}   hrout = {:10.6F}   hout = {:10.6F}\n");
        static constexpr auto Format_2155("  Ra({:1}) ={:15.6F}        Nu({:1}) ={:12.6F}\n");
        static constexpr auto Format_2160("  hcgas({:1}) ={:15.6F}      hrgas({:1}) ={:24.6F}\n");
        static constexpr auto Format_2170("  hflux    = {:12.6F}\n");
        static constexpr auto Format_2105("                                            Tamb ={:11.6F} K ( {:7.3F} deg C)\n");
        static constexpr auto Format_2110("  ----------------- ------------------   Theta{:2} ={:11.6F} K ( {:7.3F} deg C)\n");
        static constexpr auto Format_2111(
            "  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ "
            "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\   Theta{:2} ={:11.6F} K ( {:7.3F} "
            "deg C)\n");
        static constexpr auto Format_2112("  +++++++++++++++++ ++++++++++++++++++   Theta{:2} ={:11.6F} K ( {:7.3F} deg C)\n");
        static constexpr auto Format_2115("                                           Troom ={:11.6F} K ( {:7.3F} deg C)\n");
        static constexpr auto Format_2180("           qout ={:12.5F}\n");
        static constexpr auto Format_2190("  |     qpane{:2} ={:12.5F}        |\n");
        static constexpr auto Format_2195("  |     qpane{:2} ={:12.5F}        |         keffc{:2} ={:11.6F}\n");
        static constexpr auto Format_2199("  |      qlayer{:2} ={:12.5F}       |\n");
        static constexpr auto Format_2210("            qin ={:11.6F}\n");
        static constexpr auto Format_2300("            q{:2} ={:12.5F}\n");
        static constexpr auto Format_2320("           qv{:2} ={:12.5F}\n");
        static constexpr auto Format_2321("       airspd{:2} ={:12.5F}    keff{:2} ={:12.5F}\n");
        static constexpr auto Format_2322("           qc{:2} ={:12.5F}      qr{:2} ={:12.5F}\n");
        static constexpr auto Format_2330("  ShadeEmisRatioIn  ={:11.6F}        ShadeEmisRatioOut ={:11.6F}\n");
        static constexpr auto Format_2331("  ShadeHcRatioIn    ={:11.6F}        ShadeHcRatioOut   ={:11.6F}\n");
        static constexpr auto Format_2332("  HcUnshadedIn      ={:11.6F}        HcUnshadedOut     ={:11.6F}\n");
        static constexpr auto Format_2350("Heat Flux Flow and Temperatures of Layer Surfaces:\n");
        static constexpr auto Format_2351("Basic IGU properties:\n");
        static constexpr auto Format_4205("  Ebsky ={:11.6F} [W/m2], Gout ={:11.6F} [W/m2]\n");
        static constexpr auto Format_4215("  Ebroom ={:11.6F} [W/m2], Gin  ={:11.6F} [W/m2]\n");
        static constexpr auto Format_4110("  Ef{:2} ={:11.6F} [W/m2], Rf{:2} ={:11.6F} [W/m2]\n");
        static constexpr auto Format_4111("  ----------------- ------------------\n");
        static constexpr auto Format_4112("  Ef{:2} ={:11.6F} [W/m2], Rf{:2} ={:11.6F} [W/m2]\n");
        static constexpr auto Format_4113("  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ "
                                          "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
        static constexpr auto Format_4114("  Ef{:2} ={:11.6F} [W/m2], Rf{:2} ={:11.6F} [W/m2]\n");
        static constexpr auto Format_4115("  +++++++++++++++++ ++++++++++++++++++\n");
        static constexpr auto Format_4116("  Ef{:2} ={:11.6F} [W/m2], Rf{:2} ={:11.6F} [W/m2]\n");
        static constexpr auto Format_4117("  ooooooooooooooooo oooooooooooooooooo\n");
        static constexpr auto Format_4120("  Eb{:2} ={:11.6F} [W/m2], Rb{:2} ={:11.6F} [W/m2]\n");
        static constexpr auto Format_4121("  ----------------- ------------------\n");
        static constexpr auto Format_4122("  Eb{:2} ={:11.6F} [W/m2], Rb{:2} ={:11.6F} [W/m2]\n");
        static constexpr auto Format_4123("  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ "
                                          "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
        static constexpr auto Format_4124("  Eb{:2} ={:11.6F} [W/m2], Rb{:2} ={:11.6F} [W/m2]\n");
        static constexpr auto Format_4125("  +++++++++++++++++ ++++++++++++++++++\n");
        static constexpr auto Format_4126("  Eb{:2} ={:11.6F} [W/m2], Rb{:2} ={:11.6F} [W/m2]\n");
        static constexpr auto Format_4127("  ooooooooooooooooo oooooooooooooooooo\n");
        static constexpr auto Format_4190("  |                     |\n");
        static constexpr auto Format_4350("Energy balances on Layer Surfaces:\n");

        // open(unit=OutArgumentsFile,  file=TRIM(DBGD)//DebugOutputFileName,  status='unknown', access=FileMode, &
        //      position=FilePosition, form='formatted', iostat=nperr)
        // if (nperr.ne.0)  open(unit=OutArgumentsFile,  file=DebugOutputFileName,  status='unknown', access=FileMode, &
        //      position=FilePosition, form='formatted', iostat=nperr)
        date_and_time(real_CLOCK(1), real_CLOCK(2), real_CLOCK(3), DATE_TIME);
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2000, DATE_TIME(1), DATE_TIME(2), DATE_TIME(3), DATE_TIME(5), DATE_TIME(6), DATE_TIME(7));
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2350);
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2105, tamb, tamb - DataGlobalConstants::KelvinConv());
        print(OutArgumentsFile, Format_2180, q(1));

        // bi  Write out layer properties:
        for (i = 1; i <= nlayer; ++i) {
            //        write(OutArgumentsFile, 2110) 2*i-1, theta(2*i-1), theta(2*i-1)-273.15d0
            {
                auto const SELECT_CASE_var(LayerType(i));
                if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::Specular) { // Specular layer
                    print(OutArgumentsFile, Format_2110, 2 * i - 1, theta(2 * i - 1), theta(2 * i - 1) - DataGlobalConstants::KelvinConv());
                    print(OutArgumentsFile, Format_2190, i, q(2 * i));
                    print(OutArgumentsFile, Format_2110, 2 * i, theta(2 * i), theta(2 * i) - DataGlobalConstants::KelvinConv());
                } else if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::VenetianHorizontal || SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::VenetianVertical) { // Venetian blind
                    print(OutArgumentsFile, Format_2111, 2 * i - 1, theta(2 * i - 1), theta(2 * i - 1) - DataGlobalConstants::KelvinConv());
                    print(OutArgumentsFile, Format_2195, i, q(2 * i), i, ShadeGapKeffConv(i));
                    print(OutArgumentsFile, Format_2111, 2 * i, theta(2 * i), theta(2 * i) - DataGlobalConstants::KelvinConv());
                } else if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::Woven) { // Venetian blind
                    print(OutArgumentsFile, Format_2112, 2 * i - 1, theta(2 * i - 1), theta(2 * i - 1) - DataGlobalConstants::KelvinConv());
                    print(OutArgumentsFile, Format_2195, i, q(2 * i), i, ShadeGapKeffConv(i));
                    print(OutArgumentsFile, Format_2112, 2 * i, theta(2 * i), theta(2 * i) - DataGlobalConstants::KelvinConv());
                } else if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::OtherShadingType) { // Venetian blind
                    print(OutArgumentsFile, Format_2110, 2 * i - 1, theta(2 * i - 1), theta(2 * i - 1) - DataGlobalConstants::KelvinConv());
                    print(OutArgumentsFile, Format_2190, i, q(2 * i));
                    print(OutArgumentsFile, Format_2110, 2 * i, theta(2 * i), theta(2 * i) - DataGlobalConstants::KelvinConv());
                } else {
                    print(OutArgumentsFile, Format_2110, 2 * i - 1, theta(2 * i - 1), theta(2 * i - 1) - DataGlobalConstants::KelvinConv());
                    print(OutArgumentsFile, Format_2199, i, q(2 * i));
                    print(OutArgumentsFile, Format_2110, 2 * i, theta(2 * i), theta(2 * i) - DataGlobalConstants::KelvinConv());
                }
            }

            //    write(OutArgumentsFile, 2110) 2*i, theta(2*i), theta(2*i)-273.15d0

            // bi  Write out gap properties:
            if (i != nlayer) {
                print(OutArgumentsFile, Format_2300, i, q(2 * i + 1));
                print(OutArgumentsFile, Format_2320, i, qv(i + 1));
                if (vvent(i + 1) == 0) {
                    print(OutArgumentsFile, Format_2321, i, vfreevent(i + 1), i, Keff(i));
                } else {
                    if (i > 1) {
                        print(OutArgumentsFile, Format_2321, i, vvent(i + 1), i, Keff(i - 1));
                        // Autodesk:BoundsViolation Keff(i-1) @ i=1: Fixed in 8.2 by surrounding if block
                    }
                }
                print(OutArgumentsFile, Format_2322, i, qcgas(i + 1), i, qrgas(i + 1));
                //      write(OutArgumentsFile, 2323) i, Keff(i)
                // write(OutArgumentsFile, 2310) i, qprim(2*i + 1)
            } else {
                print(OutArgumentsFile, Format_2210, q(2 * i + 1));
            }
        } // i - layers

        print(OutArgumentsFile, Format_2115, troom, troom - DataGlobalConstants::KelvinConv());

        print(OutArgumentsFile, "\n");

        // Simon: Write energy balances on layer surfaces
        print(OutArgumentsFile, Format_4350);
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_4205, ebsky, Gout);
        print(OutArgumentsFile, "\n");

        for (i = 1; i <= nlayer; ++i) {
            {
                auto const SELECT_CASE_var(LayerType(i));
                if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::Specular) { // Specular layer
                    print(OutArgumentsFile, Format_4110, i, Ebf(i), i, Rf(i));
                    print(OutArgumentsFile, Format_4111);
                    print(OutArgumentsFile, Format_4190);
                    print(OutArgumentsFile, Format_4121);
                    print(OutArgumentsFile, Format_4120, i, Ebb(i), i, Rb(i));
                } else if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::VenetianHorizontal || SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::VenetianVertical) { // Venetian blind
                    print(OutArgumentsFile, Format_4112, i, Ebf(i), i, Rf(i));
                    print(OutArgumentsFile, Format_4113);
                    print(OutArgumentsFile, Format_4190);
                    print(OutArgumentsFile, Format_4123);
                    print(OutArgumentsFile, Format_4122, i, Ebb(i), i, Rb(i));
                } else if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::Woven) { // Venetian blind
                    print(OutArgumentsFile, Format_4114, i, Ebf(i), i, Rf(i));
                    print(OutArgumentsFile, Format_4115);
                    print(OutArgumentsFile, Format_4190);
                    print(OutArgumentsFile, Format_4125);
                    print(OutArgumentsFile, Format_4124, i, Ebb(i), i, Rb(i));
                } else if (SELECT_CASE_var == DataComplexFenestration::iComplexShadeType::OtherShadingType) {
                    print(OutArgumentsFile, Format_4116, i, Ebf(i), i, Rf(i));
                    print(OutArgumentsFile, Format_4117);
                    print(OutArgumentsFile, Format_4190);
                    print(OutArgumentsFile, Format_4127);
                    print(OutArgumentsFile, Format_4126, i, Ebb(i), i, Rb(i));
                } else {
                    print(OutArgumentsFile, Format_4110, i, Ebf(i), i, Rf(i));
                    print(OutArgumentsFile, Format_4111);
                    print(OutArgumentsFile, Format_4190);
                    print(OutArgumentsFile, Format_4121);
                    print(OutArgumentsFile, Format_4120, i, Ebb(i), i, Rb(i));
                }
            }
            print(OutArgumentsFile, "\n");
        }

        print(OutArgumentsFile, Format_4215, ebroom, Gin);

        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2351);
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2120, ufactor);
        print(OutArgumentsFile, Format_2130, shgc);
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2132, sc);
        print(OutArgumentsFile, Format_2170, hflux);
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2131, shgct);
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2140, hcin, hrin, hcin + hrin);
        print(OutArgumentsFile, Format_2150, hcout, hrout, hcout + hrout);

        print(OutArgumentsFile, "\n");
        for (i = 1; i <= nlayer - 1; ++i) {
            print(OutArgumentsFile, Format_2155, i, Ra(i), i, Nu(i));
        }
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2330, ShadeEmisRatioIn, ShadeEmisRatioOut);
        print(OutArgumentsFile, Format_2331, ShadeHcRatioIn, ShadeHcRatioOut);
        print(OutArgumentsFile, Format_2332, HcUnshadedIn, HcUnshadedOut);

        print(OutArgumentsFile, "\n");
        for (i = 2; i <= nlayer; ++i) {
            print(OutArgumentsFile, Format_2160, i, hcgas(i), i, hrgas(i));
        }

        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, "  Error Tolerance = {:12.6E}\n", AchievedErrorTolerance);

        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, "  Number of Iterations = {}\n", NumOfIter);

        //  write(OutArgumentsFile, *)
        //  write(OutArgumentsFile, 3333) flux_nonsolar, qeff

        // close(OutArgumentsFile)

        //!!!!!!!!!!!!!!!!!!
        //!!
        //!! Formats:
        //!!
        //!!!!!!!!!!!!!!!!!!

        // 2101  format(' SHGC =   ',F8.6,6x,' SHGC_OLD = ',F8.6,2x,' SC = ',F8.6)
        // 2110  format(' Theta({:3}) = ',F12.6)
        // 2111  format(/'Pane #:', I3/)
        // 2112  format('Number of panes: ',I2)
        // 2113  format('    Thetaslice({:3},',I3') = ',F12.6)

        // 2105  format('                                            Tamb =',F11.6)
        // 2110  format('  ----------------- ------------------   Theta{:2} =',F11.6)
        // 2115  format('                                           Troom =',F11.6)

        // 2190  format('  |       qpane', i2,' =',  F11.6,'       |         keffc', i2,' =',  F11.6)
        // 2195  format('  |////   qpane', i2,' =',  F11.6,'   ////|')

        // 2323  format('         keff', i2,' =',  F12.5)
    }

    void WriteOutputEN673(InputOutputFile &OutArgumentsFile,
                          [[maybe_unused]] std::string const &DBGD,
                          int const nlayer,
                          Real64 const ufactor,
                          Real64 const hout,
                          Real64 const hin,
                          const Array1D<Real64> &Ra,
                          const Array1D<Real64> &Nu,
                          const Array1D<Real64> &hg,
                          const Array1D<Real64> &hr,
                          const Array1D<Real64> &hs,
                          [[maybe_unused]] int &nperr)
    {

        // Argument array dimensioning
        EP_SIZE_CHECK(Ra, maxlay);
        EP_SIZE_CHECK(Nu, maxlay);
        EP_SIZE_CHECK(hg, maxlay);
        EP_SIZE_CHECK(hr, maxlay);
        EP_SIZE_CHECK(hs, maxlay);

        // Locals
        // character(len=*), intent (inout) :: ErrorMessage

        Array1D_int DATE_TIME(8);
        Array1D_string real_CLOCK(3);

        int i;

        // Formats
        static constexpr auto Format_2000("TARCOG calculation results - {:4}-{:02}-{:02}, {:02}:{:02}:{:02}\n");
        static constexpr auto Format_2351("Basic IGU properties:\n");
        static constexpr auto Format_2120("  Ufactor  = {:12.6F}\n");
        static constexpr auto Format_2220("  he = {:8.4F},   hi = {:8.4F}\n");
        static constexpr auto Format_2155("  Ra({:1}) ={:15.6F}        Nu({:1}) ={:12.6F}\n");
        static constexpr auto Format_2230("  hg{:2} ={:15.6E}      hr{:2} ={:15.6E}      hs{:2} ={:15.6E}\n");

        // open(unit=OutArgumentsFile,  file=TRIM(DBGD)//DebugOutputFileName,  status='unknown', access=FileMode,  &
        //      position=FilePosition, form='formatted', iostat=nperr)
        // if (nperr.ne.0)  open(unit=OutArgumentsFile,  file=DebugOutputFileName,  status='unknown', access=FileMode,  &
        //      position=FilePosition, form='formatted', iostat=nperr)
        date_and_time(real_CLOCK(1), real_CLOCK(2), real_CLOCK(3), DATE_TIME);
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2000, DATE_TIME(1), DATE_TIME(2), DATE_TIME(3), DATE_TIME(5), DATE_TIME(6), DATE_TIME(7));
        print(OutArgumentsFile, "\n");

        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2351);
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2120, ufactor);
        print(OutArgumentsFile, "\n");
        print(OutArgumentsFile, Format_2220, hout, hin);
        print(OutArgumentsFile, "\n");
        for (i = 1; i <= nlayer - 1; ++i) {
            print(OutArgumentsFile, Format_2155, i, Ra(i), i, Nu(i));
        }
        print(OutArgumentsFile, "\n");
        for (i = 1; i <= nlayer - 1; ++i) {
            print(OutArgumentsFile, Format_2230, i, hg(i), i, hr(i), i, hs(i));
        }
        // close(OutArgumentsFile)

        //!!!!!!!!!!!!!!!!!!
        //!!
        //!! Formats:
        //!!
        //!!!!!!!!!!!!!!!!!!
    }

    void WriteTARCOGInputFile(Files &files,
                              std::string const &VerNum,
                              Real64 const tout,
                              Real64 const tind,
                              Real64 const trmin,
                              Real64 const wso,
                              int const iwd,
                              Real64 const wsi,
                              Real64 const dir,
                              Real64 const outir,
                              int const isky,
                              Real64 const tsky,
                              Real64 const esky,
                              Real64 const fclr,
                              Real64 const VacuumPressure,
                              Real64 const VacuumMaxGapThickness,
                              int const CalcDeflection,
                              Real64 const Pa,
                              Real64 const Pini,
                              Real64 const Tini,
                              const Array1D_int &ibc,
                              Real64 const hout,
                              Real64 const hin,
                              int const standard,
                              int const ThermalMod,
                              Real64 const SDScalar,
                              Real64 const height,
                              Real64 const heightt,
                              Real64 const width,
                              Real64 const tilt,
                              Real64 const totsol,
                              int const nlayer,
                              const Array1D<DataComplexFenestration::iComplexShadeType> &LayerType,
                              const Array1D<Real64> &thick,
                              const Array1D<Real64> &scon,
                              const Array1D<Real64> &YoungsMod,
                              const Array1D<Real64> &PoissonsRat,
                              const Array1D<Real64> &asol,
                              const Array1D<Real64> &tir,
                              const Array1D<Real64> &emis,
                              const Array1D<Real64> &Atop,
                              const Array1D<Real64> &Abot,
                              const Array1D<Real64> &Al,
                              const Array1D<Real64> &Ar,
                              const Array1D<Real64> &Ah,
                              const Array1D_int &SupportPillar,     // Shows whether or not gap have support pillar
                              const Array1D<Real64> &PillarSpacing, // Pillar spacing for each gap (used in case there is support pillar)
                              const Array1D<Real64> &PillarRadius,  // Pillar radius for each gap (used in case there is support pillar)
                              const Array1D<Real64> &SlatThick,
                              const Array1D<Real64> &SlatWidth,
                              const Array1D<Real64> &SlatAngle,
                              const Array1D<Real64> &SlatCond,
                              const Array1D<Real64> &SlatSpacing,
                              const Array1D<Real64> &SlatCurve,
                              const Array1D_int &nslice,
                              const Array1D<Real64> &gap,
                              const Array1D<Real64> &GapDef,
                              const Array1D<Real64> &vvent,
                              const Array1D<Real64> &tvent,
                              const Array1D<Real64> &presure,
                              const Array1D_int &nmix,
                              Array2A_int const iprop,
                              Array2A<Real64> const frct,
                              Array2A<Real64> const xgcon,
                              Array2A<Real64> const xgvis,
                              Array2A<Real64> const xgcp,
                              const Array1D<Real64> &xwght,
                              const Array1D<Real64> &gama)
    {

        // Using/Aliasing
        using namespace TARCOGGassesParams;

        // Argument array dimensioning
        EP_SIZE_CHECK(ibc, 2);
        EP_SIZE_CHECK(LayerType, maxlay);
        EP_SIZE_CHECK(thick, maxlay);
        EP_SIZE_CHECK(scon, maxlay);
        EP_SIZE_CHECK(YoungsMod, maxlay);
        EP_SIZE_CHECK(PoissonsRat, maxlay);
        EP_SIZE_CHECK(asol, maxlay);
        EP_SIZE_CHECK(tir, maxlay2);
        EP_SIZE_CHECK(emis, maxlay2);
        EP_SIZE_CHECK(Atop, maxlay);
        EP_SIZE_CHECK(Abot, maxlay);
        EP_SIZE_CHECK(Al, maxlay);
        EP_SIZE_CHECK(Ar, maxlay);
        EP_SIZE_CHECK(Ah, maxlay);
        EP_SIZE_CHECK(SupportPillar, maxlay);
        EP_SIZE_CHECK(PillarSpacing, maxlay);
        EP_SIZE_CHECK(PillarRadius, maxlay);
        EP_SIZE_CHECK(SlatThick, maxlay);
        EP_SIZE_CHECK(SlatWidth, maxlay);
        EP_SIZE_CHECK(SlatAngle, maxlay);
        EP_SIZE_CHECK(SlatCond, maxlay);
        EP_SIZE_CHECK(SlatSpacing, maxlay);
        EP_SIZE_CHECK(SlatCurve, maxlay);
        EP_SIZE_CHECK(nslice, maxlay);
        EP_SIZE_CHECK(gap, maxlay);
        EP_SIZE_CHECK(GapDef, MaxGap);
        EP_SIZE_CHECK(vvent, maxlay1);
        EP_SIZE_CHECK(tvent, maxlay1);
        EP_SIZE_CHECK(presure, maxlay1);
        EP_SIZE_CHECK(nmix, maxlay1);
        iprop.dim(maxgas, maxlay1);
        frct.dim(maxgas, maxlay1);
        xgcon.dim(3, maxgas);
        xgvis.dim(3, maxgas);
        xgcp.dim(3, maxgas);
        EP_SIZE_CHECK(xwght, maxgas);
        EP_SIZE_CHECK(gama, maxgas);

        // Locals
        // Support Pillars
        //   0 - does not have support pillar
        //   1 - have support pillar

        int i;
        int j;
        int NumOfProvGasses;

        Array1D_int DATE_TIME(8);
        Array1D_string real_CLOCK(3);

        // Formats
        static constexpr auto Format_111("*\n");
        static constexpr auto Format_112("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
        static constexpr auto Format_113("*------------------------------------------------------------\n");
        static constexpr auto Format_200("* General options:\n");
        static constexpr auto Format_210(
            "* <nlayer, debug, standard, ThermalMod, CalcDeflection, SDScalar, VacuumPressure, VacuumMaxGapThickness>\n");
        static constexpr auto Format_300("* Environmental settings:\n");
        static constexpr auto Format_310("* <tout, tind, wso, iwd, wsi, dir, outir, isky, tsky, esky, fclr, trmin, Pa, Pini, Tini>\n");
        static constexpr auto Format_400("* Overall IGU properties:\n");
        static constexpr auto Format_410("* <totsol, tilt, height, heightt, width>\n");
        static constexpr auto Format_600("* Outdoor environment:\n");
        static constexpr auto Format_610("* <ibc(1), hout, presure(1), 1, 1, 1.0, vvent(1), tvent(1)>\n");
        static constexpr auto Format_700("* IGU definition:\n");
        static constexpr auto Format_800("* Indoor environment:\n");
        static constexpr auto Format_810("* <ibc(2), hin, presure(nlayer+1), 1, 1, 1.0, vvent(nlayer+1), tvent(nlayer+1)>\n");
        static constexpr auto Format_900("* End file\n");
        static constexpr auto Format_10001("* created by TARCOG v. {}\n");
        static constexpr auto Format_1001("* TARCOG debug output for WinCOG, {:4}-{:02}-{:02}, {:02}:{:02}:{:02}\n");
        static constexpr auto Format_1002("*     WindowID:   {:8}  - Not specified\n");
        static constexpr auto Format_1003("*     WindowID:   {:8} \n");
        static constexpr auto Format_1006("*     IGUID:      {:8}  - Not specified\n");
        static constexpr auto Format_1007("*     IGUID:      {:8} \n");
        static constexpr auto Format_1008("*     Num Layers: {:8} \n");
        static constexpr auto Format_1010("    {:1}, {:1}, {:1}, {:1}, {:1}, {:24.12F}, {:24.12F}, {:24.12F}\n");
        static constexpr auto Format_1020("    {:24.12F}, {:24.12F}, {:24.12F}, {:1}, {:24.12F}, {:24.12F}, {:24.12F}, {:1}, {:24.12F}, {:24.12F}, "
                                          "{:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}\n");
        static constexpr auto Format_1030("    {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}\n");
        // static constexpr auto Format_1031("    {:24.12F}, {:24.12F}, {:3}, {:24.12F}, {:3}, {:3}, {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}, "
        //                                  "{:24.12F}, {:24.12F}, {:2}, {:2}, {:2}, {:2}\n");
        static constexpr auto Format_1034("* <PillarSpacing(i), PillarRadius(i)\n");
        static constexpr auto Format_1035("    {:24.12F}, {:24.12F}\n");
        static constexpr auto Format_1040("    {:1}, {:24.12F}, {:24.12F}, {:1}, {:1}, {:24.12F}, {:24.12F}, {:24.12F}\n");
        static constexpr auto Format_1048("* <gap(i), GapDef(i), presure(i+1), nmix(i+1), (iprop(i+1, j), j=1,nmix(i+1)), (frct(i+1, j), "
                                          "\n\nj=1,nmix(i+1)), vvent(i), tvent(i), SupportPillar(i)>\n");
        static constexpr auto Format_1049("* Gap {:1}:\n");
        static constexpr auto Format_1050(
            "* <scon(i), asol(i), thick(i), emis(2*i-1), emis(2*i), tir(2*i-1), YoungsMod(i),\n\n PoissonsRat(i), LayerType(i), nslice(i)>\n");
        static constexpr auto Format_1051("    {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}, {:1}, {:1}\n");
        static constexpr auto Format_1052("* <Atop(i), Abot(i), Al(i), Ar(i), Ah(i)>\n");
        static constexpr auto Format_1053("    {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}\n");
        static constexpr auto Format_1054("* <SlatThick(i), SlatWidth(i), SlatAngle(i), SlatCond(i), SlatSpacing(i), SlatCurve(i)>\n");
        static constexpr auto Format_1055("    {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}, {:24.12F}\n");
        static constexpr auto Format_1060("* Layer {:1} - specular-glass:\n");
        static constexpr auto Format_1061("* Layer {:1} - venetian blind:\n");
        static constexpr auto Format_1062("* Layer {:1} - woven shade:\n");
        static constexpr auto Format_1063("* Layer {:1} - diffuse shade:\n");
        static constexpr auto Format_1064("* Layer {:1} - ???:\n");
        static constexpr auto Format_2000("* Gas coefficients information\n");
        static constexpr auto Format_2010("    {:2}\n");
        static constexpr auto Format_2011("* <NumberOfGasses>\n");
        static constexpr auto Format_2020("    {:12.6E}\n");
        static constexpr auto Format_2021("* <MolecularWeight>\n");
        static constexpr auto Format_2030(", {:12.6E}");
        static constexpr auto Format_2031("* <gconA, gconB, gconC>\n");
        static constexpr auto Format_2032("* <gvisA, gvisB, gvisC>\n");
        static constexpr auto Format_2033("* <gcpA, gcpB, gcpC>\n");
        static constexpr auto Format_2034("* <Gamma>\n");

        // open(unit=WINCogFile,  file=TRIM(DBGD)//TRIM(WinCogFileName),  status='unknown', access=FileMode, &
        //       position=FilePosition, form='formatted', iostat=nperr)
        // if (nperr.ne.0) open(unit=WINCogFile,  file=TRIM(WinCogFileName),  status='unknown', access=FileMode, &
        //                      position=FilePosition, form='formatted', iostat=nperr)
        // else
        //  open(unit=WINCogFile,  file=TRIM(DBGD)//TRIM(SHGCFileName),  status='unknown', access=FileMode, &
        //         position=FilePosition, form='formatted', iostat=nperr)
        //  if (nperr.ne.0) open(unit=WINCogFile,  file=TRIM(SHGCFileName),  status='unknown', access=FileMode, &
        //                        position=FilePosition, form='formatted', iostat=nperr)
        // end if

        // bi...Create WINCOG input file using Tarcog's input arguments:

        // bi...Write the header:

        date_and_time(real_CLOCK(1), real_CLOCK(2), real_CLOCK(3), DATE_TIME);

        print(files.WINCogFile, Format_112);
        print(files.WINCogFile, Format_111);
        print(files.WINCogFile, Format_1001, DATE_TIME(1), DATE_TIME(2), DATE_TIME(3), DATE_TIME(5), DATE_TIME(6), DATE_TIME(7));
        print(files.WINCogFile, Format_10001, VerNum); //, VerDat
        print(files.WINCogFile, Format_111);

        if (winID == -1) {
            print(files.WINCogFile, Format_1002, winID);
        } else {
            print(files.WINCogFile, Format_1003, winID);
        }
        if (iguID == -1) {
            print(files.WINCogFile, Format_1006, iguID);
        } else {
            print(files.WINCogFile, Format_1007, iguID);
        }

        print(files.WINCogFile, Format_1008, nlayer);
        print(files.WINCogFile, Format_111);
        print(files.WINCogFile, Format_112);

        // bi...Write main body:

        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_200);
        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_210);
        print(files.WINCogFile, Format_1010, nlayer, 2, standard, ThermalMod, CalcDeflection, SDScalar, VacuumPressure, VacuumMaxGapThickness);

        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_300);
        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_310);
        print(files.WINCogFile, Format_1020, tout, tind, wso, iwd, wsi, dir, outir, isky, tsky, esky, fclr, trmin, Pa, Pini, Tini);

        // if (mgas.eq.0) then
        NumOfProvGasses = 0;
        while (xwght(NumOfProvGasses + 1) != 0) {
            ++NumOfProvGasses;
        }
        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_2000);
        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_2011);
        print(files.WINCogFile, Format_2010, NumOfProvGasses);
        for (i = 1; i <= NumOfProvGasses; ++i) {
            print(files.WINCogFile, Format_2021);
            print(files.WINCogFile, Format_2020, xwght(i));
            print(files.WINCogFile, Format_2031);
            //            ObjexxFCL::gio::write(Format_2020) ,  xgcon(1, 1);
            for (j = 2; j <= 3; ++j) {
                print(files.WINCogFile, Format_2030, xgcon(j, i));
            }
            print(files.WINCogFile, "\n");
            print(files.WINCogFile, Format_2032);
            //            ObjexxFCL::gio::write(Format_2020) , xgvis(1, 1);
            for (j = 2; j <= 3; ++j) {
                print(files.WINCogFile, Format_2030, xgvis(j, i));
            }
            print(files.WINCogFile, "\n");
            print(files.WINCogFile, Format_2033);
            //            ObjexxFCL::gio::write(Format_2020) ,  xgcp(1, 1);
            for (j = 2; j <= 3; ++j) {
                print(files.WINCogFile, Format_2030, xgcp(j, i));
            }
            print(files.WINCogFile, "\n");
            print(files.WINCogFile, Format_2034);
            print(files.WINCogFile, Format_2020, gama(i));
        } // i = 1, NumProvGasses
        // end if

        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_400);
        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_410);
        print(files.WINCogFile, Format_1030, totsol, tilt, height, heightt, width);

        // write(files.WINCogFile,500)
        // write(files.WINCogFile,*) SlatLength, SlatSpacing, SlatAngle, &
        //    CurvatureRadius, SubdivisionNumber, Rf, Rb, T, Ef_IR, Eb_IR, T_IR, &
        //    NumThetas, SOLMethod, FIRMethod, SOLhemCalc, SOLdifCalc
        // write(files.WINCogFile,*) '    0.016, 0.012, 45, 0.0, 5, 0, 0.70, 0.40, 0.00, 0.90, 0.90, 0.00, 1, 1, 1, 1'
        // write(files.WINCogFile,117)
        // write(files.WINCogFile,*) '    0.003, 0.01, 0.8, 0.6, 1, 1, 1'
        // write(files.WINCogFile,118)
        // write(files.WINCogFile,*) '    1'
        // write(files.WINCogFile,*) '    0'
        // write(files.WINCogFile,*) '    1'
        // write(files.WINCogFile,*) '    0'

        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_600);
        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_610);
        print(files.WINCogFile, Format_1040, ibc(1), hout, presure(1), 1, 1, 1.0, vvent(1), tvent(1));

        print(files.WINCogFile, Format_700);

        for (i = 1; i <= nlayer; ++i) {
            print(files.WINCogFile, Format_113);
            if (LayerType(i) == DataComplexFenestration::iComplexShadeType::Specular) {
                print(files.WINCogFile, Format_1060, i);
            } else if (LayerType(i) == DataComplexFenestration::iComplexShadeType::VenetianHorizontal || LayerType(i) == DataComplexFenestration::iComplexShadeType::VenetianVertical) {
                print(files.WINCogFile, Format_1061, i);
            } else if (LayerType(i) == DataComplexFenestration::iComplexShadeType::Woven) {
                print(files.WINCogFile, Format_1062, i);
            } else if (LayerType(i) == DataComplexFenestration::iComplexShadeType::OtherShadingType) {
                print(files.WINCogFile, Format_1063, i);
            } else {
                print(files.WINCogFile, Format_1064, i);
            }
            print(files.WINCogFile, Format_113);

            print(files.WINCogFile, Format_1050);
            print(files.WINCogFile,
                  Format_1051,
                  scon(i),
                  asol(i),
                  thick(i),
                  emis(2 * i - 1),
                  emis(2 * i),
                  tir(2 * i - 1),
                  YoungsMod(i),
                  PoissonsRat(i),
                  LayerType(i),
                  nslice(i));

            if (IsShadingLayer(LayerType(i))) {
                print(files.WINCogFile, Format_1052);
                print(files.WINCogFile, Format_1053, Atop(i), Abot(i), Al(i), Ar(i), Ah(i));
            }

            if (LayerType(i) == DataComplexFenestration::iComplexShadeType::VenetianHorizontal || LayerType(i) == DataComplexFenestration::iComplexShadeType::VenetianVertical) {
                print(files.WINCogFile, Format_1054);
                print(files.WINCogFile, Format_1055, SlatThick(i), SlatWidth(i), SlatAngle(i), SlatCond(i), SlatSpacing(i), SlatCurve(i));
            }

            if (i < nlayer) {
                print(files.WINCogFile, Format_113);
                print(files.WINCogFile, Format_1049, i);
                print(files.WINCogFile, Format_113);
                print(files.WINCogFile, Format_1048);
                print(files.WINCogFile, "    {:24.12F}, {:24.12F}, {:24.12F}, {:1}, ", gap(i), GapDef(i), presure(i + 1), nmix(i + 1));
                for (j = 1; j <= nmix(i + 1); ++j) {
                    print(files.WINCogFile, "{:1}, ", iprop(j, i + 1));
                }
                for (j = 1; j <= nmix(i + 1); ++j) {
                    print(files.WINCogFile, "{:24.12F}, ", frct(j, i + 1));
                }
                print(files.WINCogFile, "    {:24.12F}, {:24.12F}, {:1}, \n", vvent(i + 1), tvent(i + 1), SupportPillar(i));
                if (SupportPillar(i) == YES_SupportPillar) {
                    print(files.WINCogFile, Format_1034);
                    print(files.WINCogFile, Format_1035, PillarSpacing(i), PillarRadius(i));
                }
            }
        } //  i - layers

        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_800);
        print(files.WINCogFile, Format_113);

        print(files.WINCogFile, Format_810);
        print(files.WINCogFile, Format_1040, ibc(2), hin, presure(nlayer + 1), 1, 1, 1.0, vvent(nlayer + 1), tvent(nlayer + 1));

        print(files.WINCogFile, Format_113);
        print(files.WINCogFile, Format_900);
        print(files.WINCogFile, Format_113);
        //  write(files.WINCogFile, 1198)
        print(files.WINCogFile, "\n");

        // close(files.WINCogFile)

        //!!!!!!!!!!!!!!!!!!
        //!!
        //!! Formats:
        //!!
        //!!!!!!!!!!!!!!!!!!

        //  General:

        //  Gaps/environment:

        //  Layers:

        // 2020  format('    ',F12.6)
    }

    void FinishDebugOutputFiles(Files &files, int const nperr)
    {

        // Locals

        // Formats
        static constexpr auto Format_2360("TARCOG status: {:3} - Normal termination.\n");
        static constexpr auto Format_2361("TARCOG status: {:3} - Warning!\n");
        static constexpr auto Format_2362("TARCOG status: {:3} - Error!\n");
        static constexpr auto Format_1199("#####  #####  #####  #####  #####  #####  #####  #####  #####  #####  #####\n");

        if (files.WriteDebugOutput) {
            // open(unit=OutArgumentsFile,  file=TRIM(DBGD)//DebugOutputFileName,  status='unknown', position='APPEND',  &
            //      &  form='formatted', iostat=ferr)
            // if (ferr.ne.0) open(unit=OutArgumentsFile,  file=DebugOutputFileName,  status='unknown', position='APPEND',  &
            //      &  form='formatted', iostat=ferr)

            print(files.DebugOutputFile, "\n");
            if ((nperr > 0) && (nperr < 1000)) {
                print(files.DebugOutputFile, Format_2362, nperr);
            } else if ((nperr >= 1000)) {
                print(files.DebugOutputFile, Format_2361, nperr);
            } else {
                print(files.DebugOutputFile, Format_2360, nperr);
            }

            print(files.DebugOutputFile, "\n");
            print(files.DebugOutputFile, Format_1199);
            print(files.DebugOutputFile, Format_1199);

            // close(DebugOutputFile)
        } // debug

        // Close debug files
        if (files.DebugOutputFile.good()) {
            files.DebugOutputFile.close();
        }

        if (files.WINCogFile.good()) {
            files.WINCogFile.close();
        }

        if (files.IterationCSVFile.good()) {
            files.IterationCSVFile.close();
        }

        if (files.TarcogIterationsFile.good()) {
            files.TarcogIterationsFile.close();
        }

        //!!!!!!!!!!!!!!!!!!
        //!!
        //!! Formats:
        //!!
        //!!!!!!!!!!!!!!!!!!
    }

    void PrepDebugFilesAndVariables(
        Files &files, std::string const &Debug_dir, std::string const &Debug_file, int const Debug_mode, int const win_ID, int const igu_ID)
    {

        // Locals
        char LastPathChar;
        std::string::size_type LastPathCharIndex;

        files.DBGD = Debug_dir;

        LastPathCharIndex = len(Debug_dir);
        if (LastPathCharIndex > 0) {
            LastPathChar = Debug_dir[LastPathCharIndex - 1];
            if (LastPathChar != '/') files.DBGD = Debug_dir + '/';
            if ((LastPathChar == '/') && (LastPathCharIndex == 1)) files.DBGD = "";
        }

        // DebugDir = Debug_dir
        files.DebugMode = Debug_mode;
        winID = win_ID;
        iguID = igu_ID;

        // setup file names if file name is provided, otherwise keep default
        if (Debug_file != "") {
            files.WINCogFileName = Debug_file + ".w7";
            // SHGCFileName = TRIM(Debug_file)//'_SHGC.w7'
            files.DebugOutputFileName = Debug_file + ".dbg";
        }

        // bi...Write debug output files - if debug flag > 0:

        files.WriteDebugOutput = false;
        if ((Debug_mode > minDebugFlag) && (Debug_mode <= maxDebugFlag)) {

            files.WriteDebugOutput = true;
            if (Debug_mode == appendResultsToFile) {
                files.FilePosition = "APPEND";
                files.FileMode = "SEQUENTIAL";
            }
            if ((Debug_mode == resultsToNewFile) || (Debug_mode == saveIntermediateResults)) {
                files.FilePosition = "ASIS";
                files.FileMode = "SEQUENTIAL";
            }

            const auto open_file = [&](InputOutputFile &of, const std::string &fileName, const bool forAppend) {
                of.fileName = files.DBGD + fileName;
                of.open(forAppend);

                if (!of.good()) {
                    of.fileName = fileName;
                    of.open(forAppend);
                }

                std::clog << "File: '" << of.fileName << "': " << of.good() << std::endl;
            };

            open_file(files.DebugOutputFile, files.DebugOutputFileName, files.FilePosition == "APPEND");
            open_file(files.WINCogFile, files.WINCogFileName, files.FilePosition == "APPEND");

            if (Debug_mode == saveIntermediateResults) {
                open_file(files.TarcogIterationsFile, files.TarcogIterationsFileName, true);
                open_file(files.IterationCSVFile, files.IterationCSVName, true);
            }
        }
    }

} // namespace TARCOGOutput

} // namespace EnergyPlus
